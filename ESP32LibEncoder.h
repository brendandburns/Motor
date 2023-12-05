#ifndef __ESP32_LIB_ENCODER_H__
#define __ESP32_LIB_ENCODER_H__

#include <ESP32Encoder.h>

#include "EncoderInterface.h"

class ESP32LibEncoder : public EncoderInterface {
    private:
        ESP32Encoder* _delegate;
    
    public:
        ESP32LibEncoder(ESP32Encoder* delegate) : _delegate(delegate) {}

        int32_t read() { return (int32_t)_delegate->getCount(); }
};

#endif