cmake_minimum_required(VERSION 3.20)
project(video_play VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV)
set(OPENCV_COMPONENTS
        opencv_core
        opencv_imgproc
        opencv_imgcodecs
        opencv_highgui
        opencv_objdetect
        opencv_video)

add_executable(video_play
       read_images.cpp)

target_link_libraries(
        video_play
        ${OPENCV_COMPONENTS}
)


