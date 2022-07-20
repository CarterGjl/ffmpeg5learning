//
// Created by gaojinliang on 2022/7/19.
//

#ifndef FFMPEG5LEARNING_I_DECODE_STATE_CB_H
#define FFMPEG5LEARNING_I_DECODE_STATE_CB_H

#include "../one_frame.h"

class IDecoder;

class IDecodeStateCb {
public:
    IDecodeStateCb();
    virtual void DecodePrepare(IDecoder *decoder) = 0;
    virtual void DecodeReady(IDecoder *decoder) = 0;
    virtual void DecodeRunning(IDecoder *decoder) = 0;
    virtual void DecodePause(IDecoder *decoder) = 0;
    virtual bool DecodeOneFrame(IDecoder *decoder, OneFrame *frame) = 0;
    virtual void DecodeFinish(IDecoder *decoder) = 0;
    virtual void DecodeStop(IDecoder *decoder) = 0;
};

#endif //FFMPEG5LEARNING_I_DECODE_STATE_CB_H
