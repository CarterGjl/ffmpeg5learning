package com.example.ffmpeg5learning.player

class MediaPlayer {

    companion object {
        init {
            System.loadLibrary("ffmpeg5learning")
        }
    }

    external fun nativeOpen(url: String, surface: Any, w: Int, h: Int, params: String): Long

    external fun nativeClose(hplayer: Long)

    external fun nativePlay(hplayer: Long)

    external fun nativePause(hplayer: Long)

    external fun nativeSeek(hplayer: Long, ms: Long)

    external fun nativeSetParam(hplayer: Long, id: Int, value: Long)

    external fun nativeGetParam(hplayer: Long, id: Int): Long

    external fun nativeSetDisplaySurface(hplayer: Long, surf: Any)

    external fun getFFmpegVersion():String
}