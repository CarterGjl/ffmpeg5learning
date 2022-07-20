//
// Created by gaojinliang on 2022/7/19.
//

#ifndef FFMPEG5LEARNING_VIDEO_DRAWER_H
#define FFMPEG5LEARNING_VIDEO_DRAWER_H


#include "../../media/render/video/video_render.h"
#include "drawer.h"

class VideoDrawer : public Drawer, public VideoRender{
public:

    VideoDrawer();
    ~VideoDrawer();

    // 实现 VideoRender 定义的方法
    void InitRender(JNIEnv *env, int video_width, int video_height, int *dst_size) override ;
    void Render(OneFrame *one_frame) override ;
    void ReleaseRender() override ;

    // 实现几类定义的方法
    const char* GetVertexShader() override;
    const char* GetFragmentShader() override;
    void InitCstShaderHandler() override;
    void BindTexture() override;
    void PrepareDraw() override;
    void DoneDraw() override;
};


#endif //FFMPEG5LEARNING_VIDEO_DRAWER_H
