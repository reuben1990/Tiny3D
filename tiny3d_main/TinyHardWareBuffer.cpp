//
//  TinyHardWareBuffer.cpp
//  proj_mac
//
//  Created by reuben chao on 2/12/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyHardWareBuffer.h"

namespace Tiny
{
    TinyHardwareBuffer::TinyHardwareBuffer()
        : mHandler(0)
    {
        glGenBuffers(1, &mHandler);
    }
    
    TinyHardwareBuffer::~TinyHardwareBuffer()
    {
        
    }
    
    void TinyHardwareBuffer::readData(const uint8* data, uint32 length, GLenum target, GLenum usage)
    {
        glBindBuffer(target, mHandler);
        glBufferData(target, length, data, usage);
    }
    
    GLuint TinyHardwareBuffer::getHandler()
    {
        return mHandler;
    }
}