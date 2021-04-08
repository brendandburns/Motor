#ifndef __L298N_H__
#define __L298N_H__

#include "MotorController.h"

class L298N : public MotorController {
    private:
        int en_pin;
        int in1_pin;
        int in2_pin;
    
    public:
        L298N(int en, in1, in2) : en_pin(en), in1_pin(in1), in2_pin(in2) {}

        void setRawSpeed(int speed);
        void forward();
        void reverse();
}

#endif // __L298N_H__