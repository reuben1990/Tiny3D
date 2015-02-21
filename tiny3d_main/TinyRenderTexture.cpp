//
//  TinyRenderTexture.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyRenderTexture.h"

namespace Tiny
{
    TinyRenderTexture::TinyRenderTexture(uint32 width, uint32 height)
        : TinyRenderTarget(width, height)
    {
        mPriority = TINY_REND_TO_TEX_RT_GROUP;
    }
    
    TinyRenderTexture::~TinyRenderTexture()
    {
        //
    }
    
    void TinyRenderTexture::swapBuffer()
    {
        //Nothing to do.
    }
}