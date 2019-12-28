//
// Created by 姜糖 on 10/17/19.
//

//#ifndef GRAPHICS_VERTEXBUFFER_H
//#define GRAPHICS_VERTEXBUFFER_H
#pragma once
#include "Assert.h"
class VertexBuffer
{
private:
    unsigned int m_RendererID;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind()const;
    void Unbind()const;

};


//#endif //GRAPHICS_VERTEXBUFFER_H
