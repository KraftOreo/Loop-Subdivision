//
// Created by 姜糖 on 10/17/19.
//

//#ifndef GRAPHICS_VERTEXBUFFERLAYOUT_H
//#define GRAPHICS_VERTEXBUFFERLAYOUT_H
#pragma once

#include <vector>
#include <glew.h>
#include "Assert.h"

struct VertexBufferElement
{
    unsigned int type;
    int count;
    unsigned char normalized;
    static unsigned int GetSizeofType(unsigned int type){
        switch (type)
        {
            case GL_FLOAT:              return 4;
            case GL_UNSIGNED_INT:       return 4;
            case GL_UNSIGNED_BYTE:      return 1;

        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Element;
    unsigned int m_Stride;
public:
    VertexBufferLayout()
    :m_Stride(0){}

    template <typename T>
    void Push(int count)
    {
        //static_assert(false, "shit");
    }
    template<>
    void Push<float>(int count)
    {
        m_Element.push_back({ GL_FLOAT, count, GL_FALSE } );
        m_Stride += count * VertexBufferElement::GetSizeofType(GL_FLOAT);
    }
    template<>
    void Push<unsigned int>(int count)
    {
        m_Element.push_back( { GL_UNSIGNED_INT, count, GL_FALSE } );
        m_Stride += count * VertexBufferElement::GetSizeofType(GL_UNSIGNED_INT);

    }
    template<>
    void Push<unsigned char>(int count)
    {
        m_Element.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE } );
        m_Stride += count * VertexBufferElement::GetSizeofType(GL_UNSIGNED_BYTE);
    }
    inline const std::vector<VertexBufferElement> GetElements()const {return m_Element;}
    inline unsigned int GetStride() const {return m_Stride;}
};

//#endif //GRAPHICS_VERTEXBUFFERLAYOUT_H
