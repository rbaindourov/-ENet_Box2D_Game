cmake_minimum_required(VERSION 3.10)
project(ENetBox2DGame)

set(CMAKE_CXX_STANDARD 11)

# Specify ENet include and library directories.
include_directories("/usr/include")
link_directories("/usr/lib/x86_64-linux-gnu")

# Set the directory where box2d's configuration files are located.
set(Box2D_DIR /usr/lib/x86_64-linux-gnu/cmake/box2d)
find_package(box2d REQUIRED)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(ENetBox2DGame 
    src/main.cpp 
    src/physics.cpp 
    src/network.cpp 
    src/renderer.cpp
    src/client.cpp    # Added client.cpp to provide sendInput()
)

target_link_libraries(ENetBox2DGame box2d enet glfw OpenGL::GL)
