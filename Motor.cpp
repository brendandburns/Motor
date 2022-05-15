#include <Arduino.h>
#include "Motor.h"

#define Kp 0.5
#define Ki 0.0
#define Kd 0.01
#define MIN_ERROR 10

#define Kp_Speed 0.01
#define Ki_Speed 0.0
#define Kd_Speed 1
#define V_RANGE 60
#define MIN_V (V_RANGE + 1)

#define SAMPLE_TIME 1

Motor::Motor(MotorController* controller, EncoderInterface *encoder, const char *name, uint8_t max_speed)
{
    this->controller = controller;
    this->_raw_speed = 0;
    this->name = name;
    this->last_time = millis();
    this->max_speed = max_speed;

    this->encoder = encoder;
    if (encoder != NULL) {
        this->last_position = encoder->read();
        this->_position = last_position;
        this->_setpoint = this->_position;
    
        this->pid = new PID(&this->_position, &this->output, &this->_setpoint, Kp, Ki, Kd, DIRECT);
        this->pid->SetSampleTime(SAMPLE_TIME);
        this->pid->SetOutputLimits(-max_speed, max_speed);
        this->pid->SetMode(AUTOMATIC);

        this->_observed_speed = 0.0;
        this->_desired_speed = this->_observed_speed;
        this->pid_v = new PID(&this->_observed_speed, &this->output_acc, &this->_desired_speed, Kp_Speed, Ki_Speed, Kd_Speed, DIRECT);
        this->pid_v->SetSampleTime(SAMPLE_TIME);
        this->pid_v->SetOutputLimits(-V_RANGE, V_RANGE);
        this->pid_v->SetMode(AUTOMATIC);
    } else {
        this->pid = NULL;
        this->last_position = this->_position = this->_setpoint = 0;
        this->pid_v = NULL;
        this->_observed_speed = this->_desired_speed = 0;
    }

    setRawSpeed(0);
    stop();
}

void Motor::forward()
{
    this->controller->forward();
}

void Motor::reverse()
{
    this->controller->reverse();
}

void Motor::setMaxSpeed(uint8_t speed) {
    this->max_speed = speed;
    if (this->pid != NULL) {
        this->pid->SetOutputLimits(-speed, speed);
    }
}

void Motor::setMode(Motor::MotorMode mode)
{
    this->_mode = mode;
}

Motor::MotorMode Motor::mode()
{
    return this->_mode;
}

void Motor::setDesiredSpeed(int speed)
{
    this->_desired_speed = speed;
    this->setMode(Velocity);
}

double Motor::desired_speed()
{
    return this->_desired_speed;
}

int Motor::raw_speed()
{
    return this->_raw_speed;
}

double Motor::observed_speed()
{
    return this->_observed_speed;
}

void Motor::setRawSpeed(int speed)
{
    if (speed > 0)
    {
        if (speed > this->max_speed)
        {
            speed = this->max_speed;
        }
        this->reverse();
    }
    else if (speed < 0)
    {
        if (speed < -this->max_speed)
        {
            speed = -this->max_speed;
        }
        this->forward();
    }
    else
    {
        this->raw_stop();
    }
    this->_raw_speed = speed;
    this->controller->setRawSpeed(speed);
}

void Motor::raw_stop()
{
    controller->stop();
}

void Motor::stop()
{
    this->setMode(Stop);
}

long Motor::position()
{
    return this->_position;
}

void Motor::setPosition(long position)
{
    this->_setpoint = position;
    this->setMode(Position);
}

void Motor::loop()
{
    if (encoder == NULL) {
        if (this->mode() == Stop) {
            this->raw_stop();
            this->setRawSpeed(0);
        }
        return;
    }
    long position = encoder->read();
    long now = millis();
    this->_position = position;

    long dTime = now - this->last_time;
    if (dTime > 10)
    {
        long dPos = position - this->last_position;
        this->_observed_speed = ((double)dPos * 1000) / dTime;
        this->last_position = position;
        this->last_time = now;
    }

    if (this->mode() == Position)
    {
        if (abs(this->_setpoint - this->_position) < MIN_ERROR)
        {
            this->raw_stop();
        }
        else if (this->pid->Compute())
        {
            this->setRawSpeed(this->output);
        }
    }
    else if (this->mode() == Stop)
    {
        this->raw_stop();
        this->setRawSpeed(0);
    }
    else if (this->mode() == Velocity)
    {
        if (this->_desired_speed == 0)
        {
            this->raw_stop();
        }
        else if (this->pid_v->Compute())
        {
            if (this->_desired_speed > 0)
            {
                this->setRawSpeed(MIN_V + this->output_acc);
            }
            else
            {
                this->setRawSpeed(-MIN_V + this->output_acc);
            }
        }
    }
}

void Motor::printMode(HardwareSerial *serial)
{
    switch (this->mode())
    {
    case Position:
        serial->print("Pos");
        break;
    case Velocity:
        serial->print("Vel");
        break;
    case Raw:
        serial->print("Raw");
        break;
    case Stop:
        serial->print("Stop");
        break;
    }
}

void Motor::print(HardwareSerial *serial)
{
    serial->print(this->name);
    serial->print("\tmode:");
    printMode(serial);
    serial->print("\traw: ");
    serial->print(this->raw_speed());
    if (this->mode() == Position)
    {
        serial->print("\tpos: ");
        serial->print(this->position());
        serial->print("\tdesired_p: ");
        serial->print(this->_setpoint);
    }
    else if (this->mode() == Velocity)
    {
        serial->print("\tdesired_v: ");
        serial->print(this->_desired_speed);
        serial->print("\tobserved_speed: ");
        serial->print(this->observed_speed());
        serial->print("\toutput_acc: ");
        serial->print(this->output_acc);
    }
    serial->println();
}

size_t Motor::print(char *buffer, size_t len)
{
    switch (this->mode())
    {
    case Position:
        return snprintf(buffer, len, "%s\tmode: Pos\traw: %d\tpos: %d\tdesired_p: %d", this->name, this->raw_speed(), this->position(), int(this->_setpoint));
    case Velocity:
        return snprintf(buffer, len, "%s\tmode: Vel\traw: %d\tdesired_v: %d\tobserved_speed: %d", this->name, this->raw_speed(), int(this->desired_speed()), this->observed_speed());
    case Stop:
        return snprintf(buffer, len, "%s\tmode: Stop", this->name);
    case Raw:
        return snprintf(buffer, len, "%s\tmode: Raw\traw: %d", this->name, this->raw_speed());
    default:
        memcpy(buffer, this->name, strlen(this->name) + 1);
        return strlen(this->name) + 1;
    }
}