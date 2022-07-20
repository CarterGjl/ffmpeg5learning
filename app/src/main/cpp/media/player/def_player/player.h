//
// Created by gaojinliang on 2022/7/19.
//

#ifndef FFMPEG5LEARNING_PLAYER_H
#define FFMPEG5LEARNING_PLAYER_H


#include "../../decoder/video/v_decoder.h"
#include "../../decoder/audio/a_decoder.h"

class Player {
private:
    VideoDecoder *m_v_decoder;
    VideoRender *m_v_render;
    AudioDecoder *m_a_decoder;
    AudioRender *m_a_render;

public:
    Player(JNIEnv *jniEnv,jstring path,jobject surface);
    ~Player();

    void play();
    void pause();
};


#endif //FFMPEG5LEARNING_PLAYER_H
