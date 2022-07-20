//
// Created by gaojinliang on 2022/7/19.
//

#include "def_drawer_proxy_impl.h"

void DefDrawerProxyImpl::AddDrawer(Drawer *drawer) {
    m_drawers.push_back(drawer);
}

void DefDrawerProxyImpl::Draw() {
    for (auto & m_drawer : m_drawers) {
        m_drawer->Draw();
    }
}

void DefDrawerProxyImpl::Release() {
    for (auto & m_drawer : m_drawers) {
        m_drawer->Release();
        delete m_drawer;
    }

    m_drawers.clear();
}
