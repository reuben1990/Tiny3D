//
//  TinyHardWareBuffer.h
//  proj_mac
//
//  Created by reuben chao on 2/12/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyHardWareBuffer__
#define __proj_mac__TinyHardWareBuffer__

#include <stdio.h>
#include "TinyObject.h"
#include "TinyPlatform.h"

namespace Tiny
{
    class TinyHardwareBuffer : public TinyObject
    {
    public:
        TinyHardwareBuffer();
        ~TinyHardwareBuffer();
        virtual void readData(const uint8* data, uint32 length, GLenum target, GLenum usage);
        GLuint getHandler();
    protected:
        GLuint mHandler;
    };
}

#endif /* defined(__proj_mac__TinyHardWareBuffer__) */
