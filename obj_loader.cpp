//
// Created by 姜糖 on 12/19/19.
//


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
#include "Camera.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include <set>

const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

using namespace std;

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);

void ScrollCallback(GLFWwindow *window, double xOffset, double yOffset);

void MouseCallback(GLFWwindow *window, double xPos, double yPose);

void DoMovement();

Camera camera;
GLfloat lastX = WIDTH / 2.0f;
GLfloat lastY = HEIGHT / 2.0f;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
bool keys[1024];
bool firstMouse = true;

const char *path = "/Users/jiangtang/Documents/AI/Graphics/Graphics/obj/Cube.obj";
std::vector<glm::vec3> vertices;
std::vector<glm::vec2> uvs;
std::vector<glm::vec3> normals; // Won't be used at the moment.
std::vector<Vertex_Indices> triangles;

std::vector<unsigned int> indices;
std::vector<unsigned int> uv_indices;

bool res = loadOBJ(path, vertices, uvs, normals, indices, uv_indices, triangles);
Mesh mesh(vertices, triangles);


int main()
{

    GLFWwindow *window;

    /* initializing the lib11rary*/
    if (!glfwInit())
    {
        cout << "unsuccessfully initiated" << endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    if (!window)
    {
        cout << "unsuccessfully initiated window" << endl;
        glfwTerminate();
        return -1;
    }
    glewInit();
    /*  Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetScrollCallback(window, ScrollCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSwapInterval(1);
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



    cout << "============= info start =============" << endl;
    cout << "edges " << mesh.GetEdges().size() << endl;
    cout << "faces " << mesh.GetIndicesSize() / 3 << endl;
    cout << "Vertices  " << mesh.GetVerticesSize() << endl;
    cout << "Mapping " << mesh.GetMappingSize() << endl;
    cout << "============= info end =============" << endl;
//
    mesh.Subdivision();
    mesh.Subdivision();
    mesh.Subdivision();
    mesh.Subdivision();

    VertexArray va1;
    VertexBufferLayout layout;
    layout.Push<float>(3);
    VertexBuffer vb1(mesh.GetVertices(), mesh.GetVerticesSize() * 3 * sizeof(float));
    va1.AddBuffer(vb1, layout);
    IndexBuffer ib1(mesh.GetIndicies(), mesh.GetIndicesSize());
    Shader shader("../Res/Shader/obj.shader");
    Shader line_shader("../Res/Shader/line.shader");

    Renderer renderer;
    while (!glfwWindowShouldClose(window))
    {
        /*  Render Here */
        renderer.Clear();

        GLfloat currentFrame = glfwGetTime();
//        cout << currentFrame << endl;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();
        DoMovement();


        //Render
        glm::mat4 model;
        glm::mat4 view;
        view = camera.GetViewMatrix();
        model = glm::translate(model, glm::vec3(1.0f, 1.0f, 1.0f));
//        shader.SetUniformMat4f("model", model);
//        line_shader.SetUniformMat4f("model", model);


        shader.SetUniformMat4f("view", view);
        line_shader.SetUniformMat4f("model", model);

        glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat) SCREEN_WIDTH / (GLfloat) SCREEN_HEIGHT,
                                                0.1f, 1000.0f);
        shader.SetUniformMat4f("projection", projection);
        line_shader.SetUniformMat4f("model", model);


        renderer.DRAW_LINES(va1, ib1, shader);
//        renderer.DRAW_LINES(va1, ib1, line_shader);


        glfwSwapBuffers(window);

        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}


void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (GLFW_KEY_ENTER == key && action == GLFW_PRESS)
    {
        mesh.Subdivision();
        cout << "============= info start =============" << endl;
        cout << "edges " << mesh.GetEdges().size() << endl;
        cout << "faces " << mesh.GetIndicesSize() / 3 << endl;
        cout << "Vertices  " << mesh.GetVerticesSize() << endl;
        cout << "Mapping " << mesh.GetMappingSize() << endl;
        cout << "============= info end =============" << endl;
    }
    if (key >= 0 && key < 1024)
    {
        if (GLFW_PRESS == action)
        {
            keys[key] = true;
        } else if (GLFW_RELEASE == action)
        {
            keys[key] = false;
        }
    }
}

void ScrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
    camera.ProcessMouseScroll(yOffset * 0.1f);
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = yPos - lastY;
    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);

}

void DoMovement()
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

}
