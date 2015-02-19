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
    TinyRenderTexture::TinyRenderTexture()
    {
        mPriority = TINY_REND_TO_TEX_RT_GROUP;
    }
    
    TinyRenderTexture::~TinyRenderTexture()
    {
        //
    }
    
    void TinyRenderTexture::swapBuffers()
    {
        //Nothing to do.
    }
}