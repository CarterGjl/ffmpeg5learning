package com.example.ffmpeg5learning.bean

import android.content.Context
import android.content.Intent
import com.example.ffmpeg5learning.MainActivity
import com.example.ffmpeg5learning.sample.ui.SampleRenderActivity

abstract class FuncItem(val funcTitle: String, var cls: Class<out Any>) : IFuncItem {
    override fun clickItem(context: Context) {
        context.startActivity(Intent(context,cls))
    }
}

interface IFuncItem {
    fun clickItem(context: Context)
}

class FFmpegFuncItem : FuncItem("ffmpeg",MainActivity::class.java)
class SampleFuncItem : FuncItem("sample_render",SampleRenderActivity::class.java)