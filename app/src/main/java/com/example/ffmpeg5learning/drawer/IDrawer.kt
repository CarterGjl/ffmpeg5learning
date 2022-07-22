package com.example.ffmpeg5learning.drawer

import android.graphics.SurfaceTexture

interface IDrawer {

    fun setTextureID(id: Int)
    fun draw()
    fun release()
    fun getSurfaceTexture(cb: (st: SurfaceTexture)->Unit) {}
}