#include <Arduino.h>
#include <Encoder.h>
#include <ESP32Encoder.h>

#include "EncoderLibEncoder.h"
#include "ESP32LibEncoder.h"
#include "Motor.h"
#include "L298N.h"

L298N controller(1, 2, 3);
Encoder enc(3, 4);
EncoderLibEncoder ele(&enc);

ESP32Encoder enc2;
ESP32LibEncoder e32e(&enc2);

Motor m(&controller, &ele, "test", 10);
Motor m2(&controller, &e32e, "test", 10);

// void setup() {}
// void loop() {}