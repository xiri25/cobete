#include "rocket.h"
#include "../mathlib/src/mathlib/vec2.h"
#include <stdio.h>
#include <assert.h>

const char* _rocket_mode_string(const RocketMode_t mode)
{
    switch (mode) {
        case MODE_IDLE:
            return "MODE_IDLE";
            break;
        case MODE_LIFTOF:
            return "MODE_LIFTOF";
            break;
    }
 
    assert( 1 == 0 ); // Should not be here ever
    return "Unreachable";
}

void _print_rocket_mode(const RocketMode_t mode)
{
    const char* mode_str = _rocket_mode_string(mode); // The parameter is unused
    printf("%s\n", mode_str);
}

void rocket_print_state(const Rocket_t* rocket)
{
    printf("Rocket State:\n");
    printf("    pos = (%f, %f)\n", rocket->x.e1, rocket->x.e2);
    printf("    vel = (%f, %f)\n", rocket->v.e1, rocket->v.e2);
    printf("    fmo = (%f, %f)\n", rocket->f.e1, rocket->f.e2);
    printf("    m_fuel = %f\n", rocket->m_fuel);
    printf("    m_empty = %f\n", rocket->m_empty);
}

RocketModeTime_t rocket_mode_handler(const RocketMode_t mode)
{
    switch (mode) {
        case MODE_IDLE:
            _print_rocket_mode(mode);
            return MODE_IDLE_TIME;
            break;
        case MODE_LIFTOF:
            _print_rocket_mode(mode);
            return MODE_LIFTOF_TIME;
            break;
    }

    assert( 1 == 0 ); // Should not be here ever
    return MODE_IDLE_TIME;
}

void rocket_loop(uint8_t* physics_iterations_out, Rocket_t* rocket_out, RocketMode_t* mode_out)
{
    *physics_iterations_out = rocket_mode_handler(*mode_out);
}
