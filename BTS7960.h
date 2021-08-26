#ifndef __BTS7960_H__
#define __BTS7960_H__

#include "MotorController.h"

class BTS7960 : public MotorController {
    private:
        int r_en_pin;
        int l_en_pin;
        int r_pwm_pin;
        int l_pwm_pin;
        bool invert;
    
    public:
        BTS7960(int r_en, int l_en, int r_pwm, int l_pwm, bool invert=false);

        void setRawSpeed(int speed);
        void forward();
        void reverse();
        void stop();
};

#endif // __BTS7960_H__