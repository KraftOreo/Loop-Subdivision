//
// Created by 姜糖 on 10/25/19.
//
#include <glew.h>
#include <iostream>

//#ifndef GRAPHICS_ASSERT_H
//#define GRAPHICS_ASSERT_H
#pragma once
#define ASSERT(x) if (!(x))  __builtin_debugtrap();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

//#endif //GRAPHICS_ASSERT_H
