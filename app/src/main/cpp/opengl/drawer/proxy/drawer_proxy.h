//
// Created by gaojinliang on 2022/7/19.
//

#ifndef FFMPEG5LEARNING_DRAWER_PROXY_H
#define FFMPEG5LEARNING_DRAWER_PROXY_H


#include "../drawer.h"

class DrawerProxy {
public:
    virtual void AddDrawer(Drawer *drawer) = 0;

    virtual void Draw() = 0;

    virtual void Release() = 0;

    virtual ~DrawerProxy() {}
};


#endif //FFMPEG5LEARNING_DRAWER_PROXY_H
