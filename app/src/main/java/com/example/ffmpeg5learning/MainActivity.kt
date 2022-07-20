package com.example.ffmpeg5learning

import android.annotation.SuppressLint
import android.os.Bundle
import android.os.Environment
import android.view.Surface
import android.view.SurfaceHolder
import androidx.appcompat.app.AppCompatActivity
import com.example.ffmpeg5learning.databinding.ActivityMainBinding
import java.io.File

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    val path = Environment.getExternalStorageDirectory().absolutePath + "/mvtest.mp4"
    private var player: Long? = null
    @SuppressLint("SetTextI18n")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

//        val path = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS)?.absolutePath+ "/mvtest.mp4"
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = "${stringFromJNI()}${ ffmpegVersion()}"
        if(File(path).exists()) {
            binding.sfv.holder.addCallback(object :SurfaceHolder.Callback{
                override fun surfaceCreated(holder: SurfaceHolder) {
                }

                override fun surfaceChanged(
                    holder: SurfaceHolder,
                    format: Int,
                    width: Int,
                    height: Int
                ) {
                    if (player == null) {
                        player = createGLPlayer(path, holder.surface)
                        playOrPause(player!!)
                    }
                }

                override fun surfaceDestroyed(holder: SurfaceHolder) {
                    stop(player!!)
                }
            })
        }

    }

    override fun onResume() {
        super.onResume()
        if (player != null) {
            play(player!!)
        }
    }

    /**
     * A native method that is implemented by the 'ffmpeg5learning' native library,
     * which is packaged with this application.
     */
    private external fun stringFromJNI(): String

    external fun ffmpegVersion(): String

//    external fun ffmpegInfo(): String

    private external fun createPlayer(path: String, surface: Surface): Long

    private external fun play(player: Long)
    private external fun pause(player: Long)


    private external fun createGLPlayer(path: String, surface: Surface): Long
    private external fun playOrPause(player: Long)
    private external fun stop(player: Long)

    companion object {
        // Used to load the 'ffmpeg5learning' library on application startup.
        init {
            System.loadLibrary("ffmpeg5learning")
        }
    }
}