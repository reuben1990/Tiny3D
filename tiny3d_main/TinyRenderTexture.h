//
//  TinyRenderTexture.h
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyRenderTexture__
#define __proj_mac__TinyRenderTexture__

#include <stdio.h>
#include "TinyRenderTarget.h"
#include "TinyPlatform.h"

namespace Tiny
{
    class TinyRenderTexture : public TinyRenderTarget
    {
    public:
        TinyRenderTexture(uint32 width, uint32 height);
        ~TinyRenderTexture();
        virtual void swapBuffer();
    };
}

#endif /* defined(__proj_mac__TinyRenderTexture__) */
