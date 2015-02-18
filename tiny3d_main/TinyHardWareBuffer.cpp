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
    
    virtual void TinyHardwareBuffer::readData(unsigned char* data, uint32 length, GLenum target, GLenum usage)
    {
        glBindBuffer(target, mHandler);
        glBufferData(target, &length, data, usage);
    }
}