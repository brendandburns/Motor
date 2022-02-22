#include <Arduino.h>
#include <Encoder.h>

#include "Motor.h"
#include "L298N.h"

L298N controller(1, 2, 3);
Encoder enc(3, 4);

Motor m(&controller, &enc, "test", 10);

// void setup() {}
// void loop() {}