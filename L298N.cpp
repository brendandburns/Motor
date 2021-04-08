#include "L298N.h"

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

void L298N::setRawSpeed(int speed)
{
    // TODO: remove this fudge factor as it is Pioneer specific
    analogWrite(this->en_pin, abs(speed) + 20);
}
