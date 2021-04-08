#ifndef __MOTOR_CONTROLLER_H__
#define __MOTOR_CONTROLLER_H__

class MotorController {
    public:
        MotorController() = 0;

        virtual void setRawSpeed(int speed);
        virtual void forward();
        virtual void reverse();
        virtual void stop();
}

#endif // __MOTOR_CONTROLLER_H__