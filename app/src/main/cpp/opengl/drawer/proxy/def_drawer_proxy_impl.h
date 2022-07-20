//
// Created by gaojinliang on 2022/7/19.
//

#ifndef FFMPEG5LEARNING_DEF_DRAWER_PROXY_IMPL_H
#define FFMPEG5LEARNING_DEF_DRAWER_PROXY_IMPL_H
#include "drawer_proxy.h"
#include "../drawer.h"
#include <vector>

class DefDrawerProxyImpl : public DrawerProxy {
private:
    std::vector<Drawer *> m_drawers;

public:
    void AddDrawer(Drawer *drawer);
    void Draw() override;
    void Release() override;
};


#endif //FFMPEG5LEARNING_DEF_DRAWER_PROXY_IMPL_H
