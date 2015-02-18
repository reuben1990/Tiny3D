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
    
    void TinyIndexData::load(uint8* data, uint32 length)
    {
        mBuffer->readData(data, length, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    }
    
    TinyVertexData::TinyVertexData()
        : mBuffer(TINY_NEW TinyHardwareBuffer())
    {
        
    }
    
    TinyVertexData::~TinyVertexData()
    {
        TINY_DELETE mBuffer;
    }
 
    void TinyVertexData::load(uint8* data, uint32 length)
    {
        mBuffer->readData(data, length, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    }
}