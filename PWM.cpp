#include <PWM.h>

#ifdef ESP32
#include <Esp.h>

int findChannel(int pin) {
    for (int i = 0; i < PWM_CHANNELS; i++) {
        if pwm_channels[i] == -1 {
            pwm_channels[i] = pin;
            return i;
        }
    }
    return -1;
}

void allocatePWM(int pin) {
    int channel = findChannel(pin);
    if (channel == -1) {
        return;
    }
    ledcAttachPin(pin, channel);
    ledcSetup(channel, 5000, 8);
}

void analogWrite(int pin, uint8_t value) {
    for (int i = 0; i < 16; i++) {
        if (i < pwm_channels.size() && pwm_channels[i] == pin) {
            ledcWrite(i, value);
        }
        return;
    }
}
#endif