#include "BTS7960.h"
#include <Arduino.h>
#include "PWM.h"

BTS7960::BTS7960(int r_en, int l_en, int r_pwm, int l_pwm, bool invert) : r_en_pin(r_en), l_en_pin(l_en), r_pwm_pin(r_pwm), l_pwm_pin(l_pwm), invert(invert)
{
    pinMode(r_en, OUTPUT);
    pinMode(l_en, OUTPUT);
    pinMode(r_pwm, OUTPUT);
    pinMode(l_pwm, OUTPUT);
}

void BTS7960::forward()
{
    digitalWrite(this->r_en_pin, HIGH);
    digitalWrite(this->l_en_pin, HIGH);
}

void BTS7960::reverse()
{
    digitalWrite(this->r_en_pin, HIGH);
    digitalWrite(this->l_en_pin, HIGH);
}

void BTS7960::stop()
{
    digitalWrite(this->r_en_pin, LOW);
    digitalWrite(this->l_en_pin, LOW);
    analogWrite(this->r_pwm_pin, 0);
    analogWrite(this->l_pwm_pin, 0);
}

void BTS7960::setRawSpeed(int speed)
{
    if (invert) {
        speed = -speed;
    }
    if (speed > 0) {
        analogWrite(this->r_pwm_pin, 0);
        delayMicroseconds(100);
        analogWrite(this->l_pwm_pin, speed);
    } else if (speed < 0) {
        analogWrite(this->l_pwm_pin, 0);
        delayMicroseconds(100);
        analogWrite(this->r_pwm_pin, -speed);       
    } else {
        this->stop();
    }
}
