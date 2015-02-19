//
//  TinyVertexIndexData.cpp
//  proj_mac
//
//  Created by reuben chao on 2/13/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyVertexIndexData.h"
#include "TinyMemoryAlloc.h"
#include "TinyPlatform.h"

namespace Tiny
{
    TinyIndexData::TinyIndexData()
        : mBuffer(TINY_NEW TinyHardwareBuffer())
    {
    }
    
    TinyIndexData::~TinyIndexData()
    {
        TINY_DELETE mBuffer;
    }
    
    void TinyIndexData::load(uint8* data, uint32 length, uint32 vertexSize)
    {
        mVertexSize = vertexSize;
        mBuffer->readData(data, length, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    }
    
    uint32 TinyIndexData::getVertexSize()
    {
        return mVertexSize;
    }
    
    TinyHardwareBuffer* TinyIndexData::getBuffer()
    {
        return mBuffer;
    }
    
    TinyVertexData::TinyVertexData()
    {
        
    }
    
    TinyVertexData::~TinyVertexData()
    {

    }
 
    void TinyVertexData::load(uint8* data, uint32 length, uint32 size, TinyVertexAttrLocation location)
    {
        auto iter = mVertexElements.find(location);
        TinyVertexElement* element;
        if (iter == mVertexElements.end())
        {
            element = TINY_NEW TinyVertexElement();
            mVertexElements.insert(std::pair<TinyVertexAttrLocation, TinyVertexElement*>(location, element));
        }
        else
        {
            element = iter->second;
        }
        element->load(data, length, size);
    }
    
    MapIterator<TinyVertexElementMap > TinyVertexData::getBufferIterator()
    {
        return MapIterator<TinyVertexElementMap >(mVertexElements.begin(), mVertexElements.end());
    }
    
    TinyVertexElement::TinyVertexElement()
        : mBuffer(TINY_NEW TinyHardwareBuffer())
        , mSize(0)
    {
        
    }
    
    TinyVertexElement::~TinyVertexElement()
    {
        TINY_DELETE mBuffer;
    }
    
    void TinyVertexElement::load(uint8* data, uint32 length, uint32 size)
    {
        mBuffer->readData(data, length, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
        mSize = size;
    }
}




