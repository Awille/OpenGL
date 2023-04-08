cmake_minimum_required(VERSION 3.24)
project(OpenGL)

set(CMAKE_CXX_STANDARD 11)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message(STATUS "Using MinGW compiler")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    message(STATUS "Using Microsoft Visual C++ compiler")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "Using Clang compiler")
else()
    message(FATAL_ERROR "Unsupported compiler")
endif()

#我们以静态库的方式引入glew，需要指定GLEW_STATIC 具体信息如下
#ifdef GLEW_STATIC
#  define GLEWAPI extern
#else
#  ifdef GLEW_BUILD
#    define GLEWAPI extern __declspec(dllexport)
#  else
#    define GLEWAPI extern __declspec(dllimport)
#  endif
#endif
add_definitions(-DGLEW_STATIC)

#include_directory：用于添加头文件包含目录，使编译器可以找到头文件。这个指令将指定的目录添加到编译器的头文件搜索路径中，
#以便在编译时可以找到所需的头文件。通常情况下，include_directory
#指令用于将头文件目录添加到编译器的包含路径，以便在源代码中使用#include指令包含这些头文件。

#link_directory：用于添加库文件链接目录，使链接器可以找到库文件。这个指令将指定的目录添加到链接器的库文件搜索路径中，
#以便在链接时可以找到所需的库文件。通常情况下，link_directory指令用于将库文件目录添加到链接器的搜索路径，
#以便在链接时可以找到这些库文件。

# 添加头文件搜索路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLFW/include/GLFW)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLEW/include/GL)
# 添加库文件搜索路径
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLFW/lib-mingw-w64)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLEW/lib/Release/x64)


add_executable(OpenGL main.cpp)

target_link_libraries(OpenGL libglfw3.a glew32s.lib opengl32)


