//
// Created by gaojinliang on 2022/7/19.
//

#ifndef FFMPEG5LEARNING_GL_PLAYER_H
#define FFMPEG5LEARNING_GL_PLAYER_H


#include "../../decoder/video/v_decoder.h"
#include "../../../opengl/drawer/proxy/drawer_proxy.h"
#include "../../../opengl/drawer/video_drawer.h"
#include "../../render/video/opengl_render/opengl_render.h"
#include "../../decoder/audio/a_decoder.h"

class GLPlayer {
private:
    VideoDecoder *m_v_decoder;
    OpenGLRender *m_gl_render;
    DrawerProxy *m_v_drawer_proxy;
    VideoDrawer *m_v_drawer;
    AudioDecoder *m_a_decoder;
    AudioRender *m_a_render;
public:
    GLPlayer(JNIEnv *jniEnv, jstring path);
    ~GLPlayer();
    void SetSurface(jobject surface);
    void PlayOrPause();
    void Release();
};

#endif //FFMPEG5LEARNING_GL_PLAYER_H
