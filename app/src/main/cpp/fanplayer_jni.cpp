//
// Created by gaojinliang on 2022/8/10.
//

#include <jni.h>
#include <cstdint>
#include <cstring>
#include "utils/logger.h"
#include "utils/stdefine.h"

extern "C" {
#include <libavcodec/avcodec.h>
int av_jni_set_java_vm(void *vm, void *log_ctx);
}


jlong nativeOpen(JNIEnv *env, jobject obj, jstring url, jobject jsurface, jint w, jint h,
                 jstring params) {
    DO_USE_VAR(obj);
    DO_USE_VAR(jsurface);
    DO_USE_VAR(w);
    DO_USE_VAR(h);
    return 1;
}

void nativeClose(JNIEnv *env, jobject thiz, jlong hplayer) {

}

void nativePlay(JNIEnv *env, jobject thiz, jlong hplayer) {

}

void nativePause(JNIEnv *env, jobject thiz, jlong hplayer) {

}

void nativeSeek(JNIEnv *env, jobject thiz, jlong hplayer, jlong ms) {

}

void nativeSetParam(JNIEnv *env, jobject thiz, jlong hplayer, jint id, jlong value) {

}

jlong nativeGetParam(JNIEnv *env, jobject thiz, jlong hplayer, jint id) {

    return 0;
}

void nativeSetDisplaySurface(JNIEnv *env, jobject thiz, jlong hplayer, jobject surface) {

}

jstring getFFmpegVersion(JNIEnv *env, jobject thiz) {
    char strBuffer[1024 * 4] = {0};
    strcat(strBuffer, "libavcodec : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVCODEC_VERSION));
    strcat(strBuffer, "\nlibavformat : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVFORMAT_VERSION));
    strcat(strBuffer, "\nlibavutil : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVUTIL_VERSION));
    strcat(strBuffer, "\nlibavfilter : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVFILTER_VERSION));
    strcat(strBuffer, "\nlibswresample : ");
    strcat(strBuffer, AV_STRINGIFY(LIBSWRESAMPLE_VERSION));
    strcat(strBuffer, "\nlibswscale : ");
    strcat(strBuffer, AV_STRINGIFY(LIBSWSCALE_VERSION));
    strcat(strBuffer, "\navcodec_configure : \n");
    strcat(strBuffer, avcodec_configuration());
    strcat(strBuffer, "\navcodec_license : ");
    strcat(strBuffer, avcodec_license());
    LOG_INFO("GetFFmpegVersion\n%s", strBuffer, "")

//ASanTestCase::MainTest();

    return env->NewStringUTF(strBuffer);
}

//++ jni register ++//
static JavaVM* g_jvm = nullptr;

JNINativeMethod g_methods[] = {
        {"nativeOpen",              "(Ljava/lang/String;Ljava/lang/Object;IILjava/lang/String;)J", (void *) nativeOpen},
        {"nativeClose",             "(J)V",                                                        (void *) nativeClose},
        {"nativePlay",              "(J)V",                                                        (void *) nativePlay},
        {"nativePause",             "(J)V",                                                        (void *) nativePause},
        {"nativeSeek",              "(JJ)V",                                                       (void *) nativeSeek},
        {"nativeSetParam",          "(JIJ)V",                                                      (void *) nativeSetParam},
        {"nativeGetParam",          "(JI)J",                                                       (void *) nativeGetParam},
        {"nativeSetDisplaySurface", "(JLjava/lang/Object;)V",                                      (void *) nativeSetDisplaySurface},
        {"getFFmpegVersion",        "()Ljava/lang/String;",                                        (void *) getFFmpegVersion},
};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOG_INFO("JNI_OnLoad", "---fanplayer-----", "JNI_OnLoad")
    JNIEnv *env = nullptr;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK || !env) {
        __android_log_print(ANDROID_LOG_ERROR, "fanplayer_jni", "ERROR: GetEnv failed\n");
        return -1;
    }

    jclass cls = env->FindClass("com/example/ffmpeg5learning/player/MediaPlayer");
    int ret = env->RegisterNatives(cls, g_methods, sizeof(g_methods) / sizeof(g_methods[0]));
    if (ret != JNI_OK) {
        __android_log_print(ANDROID_LOG_ERROR, "fanplayer_jni",
                            "ERROR: failed to register native methods !\n");
        return -1;
    }

    // for g_jvm
    g_jvm = vm;
    av_jni_set_java_vm(vm, nullptr);

    return JNI_VERSION_1_6;
}
