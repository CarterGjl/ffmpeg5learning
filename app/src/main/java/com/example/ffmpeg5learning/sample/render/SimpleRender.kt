package com.example.ffmpeg5learning.sample.render

import android.opengl.GLES20
import android.opengl.GLSurfaceView
import android.util.Log
import com.example.ffmpeg5learning.drawer.IDrawer
import com.example.ffmpeg5learning.opengl.OpenGLTools
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

private const val TAG = "SimpleRender"
class SimpleRender(private val mDrawer: IDrawer) : GLSurfaceView.Renderer {

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        // 清屏 颜色黑色
        GLES20.glClearColor(0f, 0f, 0f, 0f)
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT)
        // TODO: 设置textureId
        mDrawer.setTextureID(OpenGLTools.createTextureIds(1)[0])
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        GLES20.glViewport(0, 0, width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        Log.d(TAG, "onDrawFrame: ")
        mDrawer.draw()
    }
}