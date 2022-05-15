#ifndef __MOTORS_H__
#define __MOTORS_H__

#include <PID_v1.h>

#include "MotorController.h"
#include "EncoderInterface.h"

class Motor
{
public:
    enum MotorMode
    {
        Stop,
        Position,
        Velocity,
        Raw
    };

private:
    // Meta
    long last_time;

    // Motors
    const char *name;
    int _raw_speed;
    double _observed_speed;

    uint8_t max_speed;

    MotorController *controller;

    // Encoder
    EncoderInterface *encoder;
    double _position;

    // Position PID
    PID *pid;
    double output;
    double _setpoint;

    // Velocity PID
    PID *pid_v;
    long last_position;
    // Output for velocity control is acceleration
    double output_acc;
    double _desired_speed;

    // Mode
    MotorMode _mode;

public:
    Motor(MotorController* controller, EncoderInterface *encoder, const char *name, uint8_t max_speed);

    void forward();
    void reverse();
    void stop();

    void setMaxSpeed(uint8_t speed);
    void setMode(MotorMode mode);
    MotorMode mode();

    void setDesiredSpeed(int speed);
    double desired_speed();
    int raw_speed();
    double observed_speed();

    void setPosition(long position);
    long position();

    void loop();
    void print(HardwareSerial *serial);
    size_t print(char *buffer, size_t len);

    void setRawSpeed(int speed);

private:
    void raw_stop();
    void printMode(HardwareSerial *serial);
};

#endif // __MOTORS_H__