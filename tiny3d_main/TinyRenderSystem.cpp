//
//  TinyRenderSystem.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyRenderSystem.h"

namespace Tiny
{
    TinyRenderSystem *TinyRenderSystem::sSingleton = nullptr;
    
    TinyRenderSystem *TinyRenderSystem::getSingleton()
    {
        if (nullptr == sSingleton)
        {
            sSingleton = new TinyRenderSystem();
            sSingleton->initialize();
        }
        return sSingleton;
    }
    
    
}
