//
// Created by gaojinliang on 2022/7/19.
//

#ifndef FFMPEG5LEARNING_OPENGL_PIXEL_RECEIVER_H
#define FFMPEG5LEARNING_OPENGL_PIXEL_RECEIVER_H
class OpenGLPixelReceiver {
public:
    virtual void ReceivePixel(uint8_t *rgba) = 0;
};
#endif //FFMPEG5LEARNING_OPENGL_PIXEL_RECEIVER_H
