//
// Created by gaojinliang on 2022/7/19.
//

#include <thread>
#include <unistd.h>
#include <android/native_window_jni.h>
#include "opengl_render.h"
#include "../../../../utils/logger.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
OpenGLRender::OpenGLRender(JNIEnv *env, DrawerProxy *drawer_proxy) :
        m_drawer_proxy(drawer_proxy) {
    this->m_env = env;
    // 获取JVM虚拟机，为创建线程作准备
    env->GetJavaVM(&m_jvm_for_thread);
    InitRenderThread();
}

OpenGLRender::~OpenGLRender() {
    delete m_egl_surface;
}

void OpenGLRender::InitRenderThread() {
// 使用智能指针，线程结束时，自动删除本类指针
    std::shared_ptr<OpenGLRender> that(this);
    std::thread t(sRenderThread, that);
    t.detach();
}

void OpenGLRender::sRenderThread(const std::shared_ptr<OpenGLRender> &that) {
    JNIEnv *env;
//将线程附加到虚拟机，并获取env
    if (that->m_jvm_for_thread->AttachCurrentThread(&env, nullptr) != JNI_OK) {
        LOGE(that->TAG, "线程初始化异常")
        return;
    }
    if (!that->InitEGL()) {
        // 解除线程和jvm关联
        that->m_jvm_for_thread->DetachCurrentThread();
        return;
    }
    while (true) {
        switch (that->m_state) {
            case FRESH_SURFACE:
                LOGI(that->TAG, "Loop Render FRESH_SURFACE")
                that->InitDspWindow(env);
                that->CreateSurface();
                that->m_state = RENDERING;
                break;
            case RENDERING:
                that->Render();
                break;
            case SURFACE_DESTROY:
                LOGI(that->TAG, "Loop Render SURFACE_DESTROY")
                that->DestroySurface();
                that->m_state = NO_SURFACE;
                break;
            case STOP:
                LOGI(that->TAG, "Loop Render STOP")
                // 解除线程和jvm关联
                that->ReleaseRender();
                that->m_jvm_for_thread->DetachCurrentThread();
                return;
            case NO_SURFACE:
            default:
                break;
        }
        usleep(20000);
    }
}

bool OpenGLRender::InitEGL() {
    m_egl_surface = new EglSurface();
    return m_egl_surface->Init();
}

void OpenGLRender::InitDspWindow(JNIEnv *env) {
    if (m_surface_ref != nullptr) {
        // 初始化窗口
        m_native_window = ANativeWindow_fromSurface(env, m_surface_ref);
        // 绘制区域的宽高
        m_window_width = ANativeWindow_getWidth(m_native_window);
        m_window_height = ANativeWindow_getHeight(m_native_window);
        // 设置宽高限制缓冲区中的像素数量
        ANativeWindow_setBuffersGeometry(m_native_window, m_window_width,
                                         m_window_height, WINDOW_FORMAT_RGBA_8888);
        LOGD(TAG, "View Port width: %d, height: %d", m_window_width, m_window_height)
    }
}

void OpenGLRender::CreateSurface() {
    if (m_egl_surface == nullptr) {
        return;
    }
    m_egl_surface->CreateEglSurface(m_native_window, m_window_width, m_window_height);
    glViewport(0, 0, m_window_width, m_window_height);
}

void OpenGLRender::DestroySurface() {
    if (m_egl_surface != nullptr) {
        m_egl_surface->DestroyEglSurface();
    }
    ReleaseWindow();
}

void OpenGLRender::Render() {
    m_drawer_proxy->Draw();
    if (m_egl_surface != nullptr) {
        m_egl_surface->SwapBuffers();
    }
    if (m_need_output_pixels && m_pixel_receiver != nullptr) {//输出画面rgba
        m_need_output_pixels = false;
        Render(); //再次渲染最新的画面
        size_t size = m_window_width * m_window_height * 4 * sizeof(uint8_t);
        auto *rgb = (uint8_t *) malloc(size);
        if (rgb == nullptr) {
            realloc(rgb, size);
            LOGE(TAG, "内存分配失败： %s", rgb)
        }
        glReadPixels(0, 0, m_window_width, m_window_height, GL_RGBA, GL_UNSIGNED_BYTE, rgb);
        m_pixel_receiver->ReceivePixel(rgb);
    }
}

void OpenGLRender::ReleaseRender() {
    ReleaseDrawers();
    ReleaseSurface();
    ReleaseWindow();
}

void OpenGLRender::ReleaseSurface() {
    if (m_egl_surface != nullptr) {
        m_egl_surface->Release();
        delete m_egl_surface;
        m_egl_surface = nullptr;
    }
}

void OpenGLRender::ReleaseWindow() {
    if (m_native_window != nullptr) {
        ANativeWindow_release(m_native_window);
        m_native_window = nullptr;
    }
}

void OpenGLRender::ReleaseDrawers() {
    if (m_drawer_proxy != nullptr) {
        m_drawer_proxy->Release();
        delete m_drawer_proxy;
        m_drawer_proxy = nullptr;
    }
}

void OpenGLRender::SetSurface(jobject surface) {
    if (nullptr != surface) {
        m_surface_ref = m_env->NewGlobalRef(surface);
        m_state = FRESH_SURFACE;
    } else {
        m_env->DeleteGlobalRef(m_surface_ref);
        m_state = SURFACE_DESTROY;
    }
}

__attribute__((unused)) void OpenGLRender::SetOffScreenSize(int width, int height) {
    m_window_width = width;
    m_window_height = height;
    m_state = FRESH_SURFACE;
}

__attribute__((unused)) __attribute__((unused)) void OpenGLRender::RequestRgbaData() {
    m_need_output_pixels = true;
}

void OpenGLRender::Stop() {
    m_state = STOP;
}

#pragma clang diagnostic pop