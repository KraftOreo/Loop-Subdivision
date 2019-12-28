cmake_minimum_required(VERSION 3.15)
project(Graphics)

set(CMAKE_CXX_STANDARD 14)





set(GLEW_H /usr/local/Cellar/glew/2.1.0/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.3/include/GLFW)
include_directories(${GLEW_H} ${GLFW_H})

# 添加目标链接
set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.0.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3/lib/libglfw.3.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

# 执行编译命令

set(SOURCE_FILES main.cpp)
add_executable(Graphics Application.cpp IndexBuffer.cpp IndexBuffer.h Renderer.cpp Renderer.h Shader.cpp Shader.h VertexArray.cpp VertexArray.h VertexBuffer.h VertexBuffer.cpp VertexBufferLayout.h Assert.h Assert.cpp src/vender/stb_image/stb_image.h src/vender/stb_image/stb_image.cpp Texture.cpp Texture.h obj_loader.cpp Camera.h ObjLoader.h Mesh.h VertexInfo.h)


# mac下这步很重要
if (APPLE)
    target_link_libraries(Graphics "-framework OpenGL")
    target_link_libraries(Graphics "-framework GLUT")
endif()