#include "physics.h"
#include "../mathlib/src/mathlib/vec2.h" // XD
#include <stdint.h>
#include <stdio.h>

void physics_loop(const uint8_t iter, Rocket_t* rocket_state, const double dt)
{

    printf("Physics iterations = %d\n", iter);

    for(uint8_t i = 0; i < iter; i++)
    {
        //continue;

        /* Apply a const force downwards */
        vec2 downwards_f = {
            .e1 = 0,
            .e2 = -10,
        };
        vec2 net_f = vec2_sum(&rocket_state->f, &downwards_f);
        double m_total = rocket_state->m_fuel + rocket_state->m_empty;
        double m_total_inv = 1.0 / m_total;
        vec2 a = vec2_scale(&net_f, m_total_inv);
        vec2 v_delta = vec2_scale(&a, dt);
        vec2_sum_in_place(&rocket_state->v, &v_delta);
        vec2 x_delta = vec2_scale(&rocket_state->v, dt);
        vec2_sum_in_place(&rocket_state->x, &x_delta);
        rocket_state->m_fuel -= 1.0;  // This should be done by the rocket_loop
    }
    return;
}
