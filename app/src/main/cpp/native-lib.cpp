#include <jni.h>
#include <string>
#include <unistd.h>
#include "utils/logger.h"
#include "media/player/def_player/player.h"
#include "media/player/gl_player/gl_player.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_ffmpeg5learning_MainActivity_ffmpegVersion(JNIEnv *env, jobject thiz) {

    //获取avutil数字版本号
    int version = avutil_version();
    //获取avutil三个子版本号
    int a = version / (int) pow(2, 16);
    int b = (int) (version - a * pow(2, 16)) / (int) pow(2, 8);
    int c = version % (int) pow(2, 8);
    //拼接avutil完整版本号
    char *charArray = new char[1024];
//    std::stringstream() << a << "." << b << "." << c << '\0' >> charArray;
    char str[25];
    jclass mclass = env->FindClass("com/example/ffmpeg5learning/MainActivity");
    jmethodID  mid = env->GetMethodID(mclass,"callback", "(Ljava/lang/String;)V");
    env->CallVoidMethod(thiz, mid, env->NewStringUTF("fdas"));
    auto *n = new std::string("dsfa edafsa");
    sprintf(charArray, "%d%s%d%s%d", a, ".", b, ".", c);
    return env->NewStringUTF(n->c_str());
}

}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_ffmpeg5learning_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF(avcodec_configuration());
}
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
#include <libavcodec/jni.h>
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    av_jni_set_java_vm(vm, reserved);
    LOG_INFO("JNI_OnLoad", "--------", "");
    return JNI_VERSION_1_4;
}

JNIEXPORT jlong JNICALL
Java_com_example_ffmpeg5learning_MainActivity_createPlayer(JNIEnv *env, jobject thiz, jstring path,
                                                           jobject surface) {
    auto *player = new Player(env, path, surface);
    return (jlong) player;
}

JNIEXPORT void JNICALL
Java_com_example_ffmpeg5learning_MainActivity_pause(JNIEnv *env, jobject thiz, jlong player) {
    auto *p = (Player *) player;
    p->pause();
}

JNIEXPORT void JNICALL
Java_com_example_ffmpeg5learning_MainActivity_play(JNIEnv *env, jobject thiz, jlong player) {
    auto *p = (Player *) player;
    p->play();
}
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_ffmpeg5learning_MainActivity_playOrPause(JNIEnv *env, jobject thiz, jlong player) {
    auto *p = (GLPlayer *) player;
    p->PlayOrPause();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_ffmpeg5learning_MainActivity_stop(JNIEnv *env, jobject thiz, jlong player) {
    auto *p = (GLPlayer *) player;
    p->Release();
}
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ffmpeg5learning_MainActivity_createGLPlayer(JNIEnv *env, jobject thiz,
                                                             jstring path, jobject surface) {
    auto *player = new GLPlayer(env, path);
    player->SetSurface(surface);
    return (jlong) player;
}