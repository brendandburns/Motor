#ifndef __PWM_H__
#define __PWM_H__

#ifdef ESP32
static int[16] pwm_channels = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 , -1, -1, -1}

void analogWrite(int pin, uint8_t value);
#endif

#endif