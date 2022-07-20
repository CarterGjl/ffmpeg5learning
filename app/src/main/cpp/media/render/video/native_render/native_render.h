//
// Created by gaojinliang on 2022/7/19.
//

#ifndef FFMPEG5LEARNING_NATIVE_RENDER_H
#define FFMPEG5LEARNING_NATIVE_RENDER_H


#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <jni.h>

#include "../video_render.h"
#include "../../../../utils/logger.h"

extern "C" {
#include <libavutil/mem.h>
}

class NativeRender: public VideoRender {
private:
    const char *TAG = "NativeRender";

    // Surface引用，必须使用引用，否则无法在线程中操作
    jobject m_surface_ref = nullptr;

    // 存放输出到屏幕的缓存数据
    ANativeWindow_Buffer m_out_buffer;

    // 本地窗口
    ANativeWindow *m_native_window = nullptr;

    //显示的目标宽
    int m_dst_w;

    //显示的目标高
    int m_dst_h;

public:
    NativeRender(JNIEnv *env, jobject surface);
    ~NativeRender();
    void InitRender(JNIEnv *env, int video_width, int video_height, int *dst_size) override ;
    void Render(OneFrame *one_frame) override ;
    void ReleaseRender() override ;
};


#endif //FFMPEG5LEARNING_NATIVE_RENDER_H
