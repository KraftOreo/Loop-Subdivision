//
// Created by 姜糖 on 10/17/19.
//

//#ifndef GRAPHICS_VERTEXARRAY_H
//#define GRAPHICS_VERTEXARRAY_H
#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Assert.h"

class VertexArray
{
private:
    unsigned int m_RendererID;

public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout &layout);
    void Bind() const;
    void Unbind() const;
};

//#endif //GRAPHICS_VERTEXARRAY_H
