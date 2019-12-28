//
//  main.cpp
//  graphics
//
//  Created by 姜糖 on 10/8/19.
//  Copyright © 2019 姜糖. All rights reserved.


#include <glew.h>
#include <glfw3.h>
#include <cstdio>
#include <iostream>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "Assert.h"
#include "src/vender/glm/glm.hpp"
#include "src/vender/glm/gtc/matrix_transform.hpp"

int main1(){

    GLFWwindow* window;
    
    /* initializing the library*/
    if (!glfwInit()) {
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
//    glfwPollEvents();
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glewInit();
    /*  Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit()!=GLEW_OK) {
        std::cout<<"Error!"<<std::endl;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;


    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,//0
         0.5f, -0.5f, 1.0f, 0.0f,//1
         0.5f,  0.5f, 1.0f, 1.0f,//2
        -0.5f,  0.5f, 0.0f, 1.0f//3
    };
    unsigned int indices[]{0, 1 ,2 ,
                           2, 3, 0};

    // generate a buffer of memory of GPU
    // We tell the CPU how the data in the memory is drawn and its layouts
    GLCall(glEnable(GL_BLEND));
   // GLCall(glEnable(GL_TEXTURE_2D));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);

    va.AddBuffer(vb, layout);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(positions))
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);
    printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));

    IndexBuffer ib(indices, 6);

    glm::mat4 proj = glm::ortho(-4.0f, 4.0f,-3.0f, 3.0f, -1.0f, 1.0f );
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    glm::mat4 mvp = proj * view;

    Shader shader("../Res/Shader/basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color",  0.8f, 0.3f, 0.8f, 1.0f);
    shader.SetUniformMat4f("u_MVP", mvp);
    Texture texture("../Res/Texture/baobao.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();
    Renderer renderer;
    float r = 0.0f;
    float increment = 0.05f;
    while (!glfwWindowShouldClose(window)) {
        /*  Render Here */
        renderer.Clear();
        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        renderer.Draw(va, ib, shader);
        //GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        if (r > 1.0f){
            increment = -0.05f;
        }
        else if (r < 0.05){
            increment = 0.05f;
        }
        r += increment;
        //GLLogCall("glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr)", __FILE__, __LINE__);
        glfwSwapBuffers(window);
        
        glfwPollEvents();
        
    }

    glfwTerminate();
    return 0;
    
}


