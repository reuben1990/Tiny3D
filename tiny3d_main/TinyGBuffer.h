//
//  TinyGBuffer.h
//  proj_mac
//
//  Created by reuben chao on 3/17/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyGBuffer__
#define __proj_mac__TinyGBuffer__

#include <stdio.h>
#include "TinyPrerequisite.h"
#include "TinyObject.h"
#include "TinyRenderTarget.h"

namespace Tiny
{
    class TinyGBuffer : public TinyRenderTarget
    {
    public:
        TinyGBuffer(uint32 width, uint32 height);
        ~TinyGBuffer();
        void createGBufTex( GLenum texUnit, GLenum format, GLuint &texid );
        void setupFBO();
    };
}

#endif /* defined(__proj_mac__TinyGBuffer__) */
