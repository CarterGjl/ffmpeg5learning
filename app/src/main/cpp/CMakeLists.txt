# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
# cmake 最低版本
cmake_minimum_required(VERSION 3.18.1)

# 支持gnu++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
# Declares and names the project.

project("ffmpeg5learning")

# 1. 定义so库和头文件所在目录，方面后面使用
set(ffmpeg_lib_dir ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})
set(ffmpeg_head_dir ${CMAKE_SOURCE_DIR}/ffmpeg)

# 2. 添加头文件目录
include_directories(${ffmpeg_head_dir}/include)


# 3. 添加ffmpeg相关的so库
add_library( avutil
        SHARED
        IMPORTED )

set_target_properties( avutil
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_dir}/libavutil.so )

add_library( swresample
        SHARED
        IMPORTED )
set_target_properties( swresample
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_dir}/libswresample.so )

add_library( avcodec
        SHARED
        IMPORTED )
set_target_properties( avcodec
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_dir}/libavcodec.so )

add_library( avfilter
        SHARED
        IMPORTED)
set_target_properties( avfilter
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_dir}/libavfilter.so )
add_library( swscale
        SHARED
        IMPORTED)
set_target_properties( swscale
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_dir}/libswscale.so )

add_library( avformat
        SHARED
        IMPORTED)
set_target_properties( avformat
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_dir}/libavformat.so )

add_library( avdevice
        SHARED
        IMPORTED)
set_target_properties( avdevice
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_dir}/libavdevice.so )
# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#  配置目标so库编译信息
add_library( # Sets the name of the library.
        # 输出so库的名称
        ffmpeg5learning
        # 设置生成库的方式，默认为SHARE动态库
        # Sets the library as a shared library.
        SHARED
        # 列出参与编译的所有源文件
        # Provides a relative path to your source file(s).
        native-lib.cpp
        # 工具
        ${CMAKE_SOURCE_DIR}/utils/logger.h
        ${CMAKE_SOURCE_DIR}/utils/timer.c
        # 播放器
        ${CMAKE_SOURCE_DIR}/media/player/def_player/player.cpp
        ${CMAKE_SOURCE_DIR}/media/player/gl_player/gl_player.cpp

        # 解码器
        ${CMAKE_SOURCE_DIR}/media/one_frame.h
        ${CMAKE_SOURCE_DIR}/media/decoder/i_decoder.h
        ${CMAKE_SOURCE_DIR}/media/decoder/decode_state.h
        ${CMAKE_SOURCE_DIR}/media/decoder/base_decoder.cpp
        ${CMAKE_SOURCE_DIR}/media/decoder/video/v_decoder.cpp
        ${CMAKE_SOURCE_DIR}/media/decoder/audio/a_decoder.cpp
        ${CMAKE_SOURCE_DIR}/media/decoder/i_decode_state_cb.cpp

        # 渲染器
        ${CMAKE_SOURCE_DIR}/media/render/video/video_render.h
        ${CMAKE_SOURCE_DIR}/media/render/video/native_render/native_render.cpp
        ${CMAKE_SOURCE_DIR}/media/render/video/opengl_render/opengl_render.cpp


        ${CMAKE_SOURCE_DIR}/media/render/audio/audio_render.h
        ${CMAKE_SOURCE_DIR}/media/render/audio/opensl_render.cpp
        ${CMAKE_SOURCE_DIR}/media/render/video/opengl_render/opengl_pixel_receiver.h

        # OpenGL EGL核心
        ${CMAKE_SOURCE_DIR}/opengl/egl/egl_core.cpp
        ${CMAKE_SOURCE_DIR}/opengl/egl/egl_surface.cpp
        # OpenGL绘制器
        ${CMAKE_SOURCE_DIR}/opengl/drawer/drawer.cpp
        ${CMAKE_SOURCE_DIR}/opengl/drawer/video_drawer.cpp

        # OpenGL绘制代理器
        ${CMAKE_SOURCE_DIR}/opengl/drawer/proxy/drawer_proxy.cpp
        ${CMAKE_SOURCE_DIR}/opengl/drawer/proxy/def_drawer_proxy_impl.cpp
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.
# 查找代码中使用到的系统库
find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
# 指定编译目标库时，cmake要链接的库
target_link_libraries( # Specifies the target library.
        # 指定目标库，native-lib 是在上面 add_library 中配置的目标库
        ffmpeg5learning
        # 4. 连接 FFmpeg 相关的库
        avutil
        swresample
        avcodec
        avfilter
        swscale
        avformat
        avdevice
        # 5. 连接 android 相关的库
        -landroid
        OpenSLES
        -lEGL
        -lGLESv2
        # Links the target library to the log library
        # included in the NDK.
        # 列出所有需要链接的库
        ${log-lib})