//
//Created by 姜糖 on 10/17/19.
//

//#ifndef GRAPHICS_RENDERER_H
//#define GRAPHICS_RENDERER_H
#pragma once
#include <glew.h>
#include <iostream>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Assert.h"


class Renderer
{
public:
    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader & shader) const;
    void DRAW_LINES(const VertexArray &va, const IndexBuffer &ib, const Shader & shader) const;
    void Draw(const VertexArray &va, const IndexBuffer &vb) const;
    void Clear() const;
};

//#endif //GRAPHICS_RENDERER_H
