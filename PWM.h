#ifndef __PWM_H__
#define __PWM_H__

#include <stdint.h>

#ifdef ESP32_FOO

#define PWM_CHANNELS 16
static int pwm_channels[PWM_CHANNELS] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 , -1, -1, -1};

void analogWrite(int pin, uint8_t value);
#endif

#endif