#include <stdio.h>
#include <stdatomic.h>
#include <pthread.h>
#include <assert.h>
#include <stdint.h>
#include <time.h>

#include "physics/physics.h"
#include "rocket/rocket.h"

#define UNO_K_MILLONES 1000000000.0
double time_now_ms(void) {
  struct timespec current_time;
  clock_gettime(CLOCK_REALTIME, &current_time);
  return current_time.tv_sec + (current_time.tv_nsec / UNO_K_MILLONES) * 1000;
}

typedef struct {
    _Atomic uint8_t* running;
} main_loop_args_t;

void* main_loop_thread(void* thread_args)
{
    main_loop_args_t* args = (main_loop_args_t*)thread_args;

    uint8_t target_fps = 1;
    double target_ms = 1000.0 / target_fps;

    // TODO: A function to do this would be better
    Rocket_t rocket_state = {
        .x = {.e1 = 0, .e2 = 0},
        .v = {.e1 = 0, .e2 = 0},
        .f = {.e1 = 0, .e2 = 0},
        .m_fuel = 100.0,
        .m_empty = 10.0,
    };
    uint8_t physics_iterations = MODE_IDLE_TIME; // For now
    RocketMode_t mode = MODE_IDLE;

    while(atomic_load(args->running))
    {
        rocket_print_state(&rocket_state);

        double begin_loop = time_now_ms();

        physics_loop(physics_iterations, &rocket_state, 0.1);

        double end_physics = time_now_ms();

        rocket_loop(&physics_iterations, &rocket_state, &mode);

        double end_loop = time_now_ms();
        double physics_time = end_physics - begin_loop;
        double rocket_time = end_loop - end_physics;
        double main_loop_time = end_loop - begin_loop;
        printf("Main_loop_time = %fms, physics_loop_time = %fms, physics_loop_count = %d, rocket_loop_time = %fms\n",
               main_loop_time,
               physics_time,
               physics_iterations,
               rocket_time);

        double remaining_time = target_ms - main_loop_time;
        printf("remaining_time = %fms\n", remaining_time);
        if( remaining_time > 0.0 )
        {
            //usleep((unsigned int)remaining_time);
            double remaining_time_ns = remaining_time * 1000000;
            struct timespec timespec = {
                .tv_sec = 0,
                .tv_nsec = remaining_time_ns,
            };
            nanosleep(&timespec, NULL);
        } else {
            printf("%fms longer thant target\n", remaining_time);
        }
        printf("\n");
    }

    if(atomic_load(args->running))
    {
        // Si el bucle sale por lo que sea, dejar de correr
        atomic_store(args->running, 0);
    }

    return (void*)NULL;
}

int main(void)
{
    _Atomic uint8_t running = 1;

    main_loop_args_t thread_args = {
        .running = &running,
    };

    pthread_t sim_thread;
    assert( pthread_create(&sim_thread, NULL, main_loop_thread, (void*)&thread_args) == 0 );

    getchar();
    atomic_store(&running, 0);

    // TODO: Wake up any thread before joining, if there is lock or conds to wait

    assert( pthread_join(sim_thread, NULL) == 0 );

    // TODO: Destroy any pthread_mutex and pthread_cond if there are any

    return 0;
}
