#ifndef __ENCODER_LIB_ENCODER_H__
#define __ENCODER_LIB_ENCODER_H__

#include <Encoder.h>

#include "EncoderInterface.h"

class EncoderLibEncoder : public EncoderInterface {
    private:
        Encoder* _delegate;
    
    public:
        EncoderLibEncoder(Encoder* delegate) : _delegate(delegate) {}

        int32_t read() { return _delegate->read(); }
};

#endif