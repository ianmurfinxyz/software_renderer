cmake_minimum_required(VERSION 3.20)
project(software_renderer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE
        src/Body.cpp
        src/Camera.cpp
        src/Color.cpp
        src/DepthBuffer.cpp
        src/grutil.cpp
        src/looptime.cpp
        src/main.cpp
        src/Matrix4.cpp
        src/Mesh.cpp
        src/Renderer.cpp
        src/Scene.cpp
        src/Vector3.cpp)

add_executable(demo ${SOURCE})
target_include_directories(demo PUBLIC include)

if(WIN_MING)
    target_link_libraries(demo -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf)
else()
    target_link_libraries(demo -lSDL2 -lSDL2_ttf)
endif()
