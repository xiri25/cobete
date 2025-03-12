#ifndef PHYSICS_H
#define PHYSICS_H

#include "../rocket/rocket.h"

#include <stdint.h>

void physics_loop(const uint8_t iter, Rocket_t* rocket_state, const double dt);

#endif // !PHYSICS_H
