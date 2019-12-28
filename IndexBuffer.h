//
// Created by 姜糖 on 10/17/19.
//

//#ifndef GRAPHICS_INDEXBUFFER_H
//#define GRAPHICS_INDEXBUFFER_H
#include "Assert.h"

#pragma once
class IndexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count) ;
    ~IndexBuffer();

    void Bind() const;
    void Unbind()const;
    inline unsigned int GetCount()const{return m_Count;}
};


//#endif //GRAPHICS_INDEXBUFFER_H
