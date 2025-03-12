#ifndef ROCKET_H
#define ROCKET_H

#include <stdint.h>
#include "../mathlib/src/mathlib/mathlib.h"

typedef struct {
    vec2 x; /* Posicion */
    vec2 v; /* Velocity */
    vec2 f; /* Force of engines */
    double m_empty;
    double m_fuel;
} Rocket_t;

typedef enum {
    MODE_IDLE,
    MODE_LIFTOF,
} RocketMode_t;

typedef enum {
    MODE_IDLE_TIME = 4,
    MODE_LIFTOF_TIME = 6,
} RocketModeTime_t;

#define RocketModeString(x) (#x)

void rocket_loop(uint8_t* physics_iterations_out, Rocket_t* rocket_out, RocketMode_t* mode_out);
void rocket_print_state(const Rocket_t* rocket);

#endif // !ROCKET_H
