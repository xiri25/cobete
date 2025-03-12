#include "physics.h"
#include "../mathlib/src/mathlib/vec2.h" // XD
#include <stdint.h>
#include <stdio.h>

double thrust_module(const Rocket_t* rocket_state, const double p0)
{
    double a = rocket_state->m_dot * rocket_state->ve;
    double b = (rocket_state->pe - p0) * rocket_state->Ae;
    return a + b;
}

void physics_loop(_Atomic uint8_t* running, const uint8_t iter, Rocket_t* rocket_state, const double dt)
{

    printf("Physics iterations = %d\n", iter);

    for(uint8_t i = 0; i < iter; i++)
    {
        if(rocket_state->m_fuel <= 0)
        {
            printf("Run out of fuel, press ENTER to exit\n");
            atomic_store(running, 0);
        }
        //continue;

        /* Apply a const force downwards */
        vec2 downwards_f_cte = {
            .e1 = 0,
            .e2 = -10,
        };
        double thrust = thrust_module(rocket_state, 1.0); // 1atm XDDDDDDDDDD
        vec2 thrust_vector = vec2_scale(&rocket_state->p, thrust);
        vec2 force = vec2_sum(&downwards_f_cte, &thrust_vector);
        double mass = rocket_state->m_empty + rocket_state->m_fuel;
        double mass_inv = 1.0 / mass;
        vec2 a = vec2_scale(&force, mass_inv);
        vec2 v_delta = vec2_scale(&a, dt);
        vec2_sum_in_place(&rocket_state->v, &v_delta);
        vec2 x_delta = vec2_scale(&rocket_state->v, dt);
        vec2_sum_in_place(&rocket_state->x, &x_delta);
        rocket_state->m_fuel -= rocket_state->m_dot * dt;
    }
    return;
}
