package com.example.ffmpeg5learning

import android.os.Bundle
import androidx.core.view.WindowCompat
import com.example.ffmpeg5learning.adapter.FuncAdapter
import com.example.ffmpeg5learning.base.BaseActivity
import com.example.ffmpeg5learning.bean.FFmpegFuncItem
import com.example.ffmpeg5learning.bean.SampleFuncItem
import com.example.ffmpeg5learning.databinding.ActivityHomeBinding
import com.example.ffmpeg5learning.player.MediaPlayer

class HomeActivity : BaseActivity() {

    private lateinit var activityHomeBinding: ActivityHomeBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        WindowCompat.setDecorFitsSystemWindows(window, false)
        activityHomeBinding = ActivityHomeBinding.inflate(layoutInflater)
        setContentView(activityHomeBinding.root)
//        MediaPlayer().nativeOpen("abc",Any(),20,20,"dfasfasf")
        activityHomeBinding.tvVersion.text = MediaPlayer().getFFmpegVersion()
        val funcAdapter = FuncAdapter()
        activityHomeBinding.rv.adapter = funcAdapter
        val dataList = mutableListOf(FFmpegFuncItem(), SampleFuncItem())
        funcAdapter.refreshData(dataList)
    }
}