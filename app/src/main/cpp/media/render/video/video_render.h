//
// Created by gaojinliang on 2022/7/19.
//

#ifndef FFMPEG5LEARNING_VIDEO_RENDER_H
#define FFMPEG5LEARNING_VIDEO_RENDER_H
#include <stdint.h>
#include <jni.h>
#include "../../one_frame.h"

class VideoRender {
public:
    virtual void InitRender(JNIEnv *env, int video_width, int video_height, int *dst_size) = 0;
    virtual void Render(OneFrame *one_frame) = 0;
    virtual void ReleaseRender() = 0;
};


#endif //FFMPEG5LEARNING_VIDEO_RENDER_H
