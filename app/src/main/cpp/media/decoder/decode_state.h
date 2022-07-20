//
// Created by gaojinliang on 2022/7/18.
//

#ifndef FFMPEG5LEARNING_DECODE_STATE_H
#define FFMPEG5LEARNING_DECODE_STATE_H
enum DecodeState {
    STOP,
    PREPARE,
    START,
    DECODING,
    PAUSE,
    FINISH
};
#endif //FFMPEG5LEARNING_DECODE_STATE_H
