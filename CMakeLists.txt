# 设置CMake版本
cmake_minimum_required(VERSION 3.16)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

# 打开编译数据库生成
Set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(lightlog VERSION 0.1)
Set(CMAKE_CXX_VISIBILITY_PRESET hidden)

add_compile_options(-W -O3 -g)
# Build the library with C++17 standard support, independent from other including
# software which may use a different CXX_STANDARD or CMAKE_CXX_STANDARD.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build lightlog_lib as a shared library." ON)

add_subdirectory(src)
enable_testing()
add_subdirectory(test)
