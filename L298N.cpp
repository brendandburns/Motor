#include "L298N.h"

L298N::L298N(int en, int in1, int in2) : en_pin(en), in1_pin(in1), in2_pin(in2)
{
    pinMode(en, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
}

void L298N::forward()
{
    digitalWrite(this->in1_pin, LOW);
    digitalWrite(this->in2_pin, HIGH);
}

void L298N::reverse()
{
    digitalWrite(this->in1_pin, HIGH);
    digitalWrite(this->in2_pin, LOW);
}

void L298N::stop()
{
    digitalWrite(this->in1_pin, LOW);
    digitalWrite(this->in2_pin, LOW);
}

void L298N::setRawSpeed(int speed)
{
    // TODO: remove this fudge factor as it is Pioneer specific
    analogWrite(this->en_pin, abs(speed) + 20);
}
