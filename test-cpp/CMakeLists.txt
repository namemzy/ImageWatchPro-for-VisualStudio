cmake_minimum_required(VERSION 3.20)
project(ImageWatchProTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MSVC UTF-8 源文件编码支持
if(MSVC)
    add_compile_options(/utf-8)
endif()

# 查找 OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# 添加可执行文件
add_executable(image_watch_test main.cpp)

# 链接 OpenCV 库
target_link_libraries(image_watch_test ${OpenCV_LIBS})

# Release 模式配置：保留调试信息
if(MSVC)
    # Release 模式下保留调试信息（/Zi）和程序数据库（/Fd）
    target_compile_options(image_watch_test PRIVATE
        $<$<CONFIG:Release>:/Zi>
        $<$<CONFIG:RelWithDebInfo>:/Zi>
    )
    # Release 模式下保留链接器调试信息
    target_link_options(image_watch_test PRIVATE
        $<$<CONFIG:Release>:/DEBUG>
        $<$<CONFIG:Release>:/OPT:REF>
        $<$<CONFIG:Release>:/OPT:ICF>
    )
endif()
