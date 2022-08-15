package com.example.ffmpeg5learning.sample.ui

import android.graphics.BitmapFactory
import android.opengl.GLSurfaceView.RENDERMODE_WHEN_DIRTY
import android.os.Bundle
import com.example.ffmpeg5learning.R
import com.example.ffmpeg5learning.base.BaseActivity
import com.example.ffmpeg5learning.databinding.ActivitySampleRenderBinding
import com.example.ffmpeg5learning.drawer.IDrawer
import com.example.ffmpeg5learning.drawer.impl.BitmapDrawer
import com.example.ffmpeg5learning.drawer.impl.TriangleDrawer
import com.example.ffmpeg5learning.sample.render.SimpleRender

class SampleRenderActivity : BaseActivity() {

    private lateinit var drawer1: TriangleDrawer
    private lateinit var binding: ActivitySampleRenderBinding

    // 自定义的OpenGL渲染器，详情请继续往下看
    lateinit var drawer: IDrawer

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivitySampleRenderBinding.inflate(layoutInflater)
        setContentView(binding.root)
        val decodeResource =
            BitmapFactory.decodeResource(resources, R.drawable.test)
        drawer = BitmapDrawer(mBitmap = decodeResource)
        drawer1 = TriangleDrawer()
        initRender()
    }

    private fun initRender() {
        binding.glSurface1.setEGLContextClientVersion(2)
        binding.glSurface2.setEGLContextClientVersion(2)
        binding.glSurface1.setRenderer(SimpleRender(drawer))
        binding.glSurface2.setRenderer(SimpleRender(drawer1))
        binding.glSurface2.renderMode = RENDERMODE_WHEN_DIRTY
        binding.glSurface1.renderMode = RENDERMODE_WHEN_DIRTY
    }

    override fun onDestroy() {
        super.onDestroy()
        drawer.release()
        drawer1.release()
    }
}