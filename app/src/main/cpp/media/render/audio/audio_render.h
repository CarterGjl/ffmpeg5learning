//
// Created by gaojinliang on 2022/7/19.
//

#ifndef FFMPEG5LEARNING_AUDIO_RENDER_H
#define FFMPEG5LEARNING_AUDIO_RENDER_H
#include <cstdint>

class AudioRender {
public:
    virtual void InitRender() = 0;
    virtual void Render(uint8_t *pcm, int size) = 0;
    virtual void ReleaseRender() = 0;
    virtual ~AudioRender() {}
};


#endif //FFMPEG5LEARNING_AUDIO_RENDER_H
