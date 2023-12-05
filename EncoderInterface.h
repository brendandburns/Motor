#ifndef __ENCODER_INTERFACE_H__
#define __ENCODER_INTERFACE_H__

class EncoderInterface {
    public:
        virtual int32_t read() = 0;
};

#endif