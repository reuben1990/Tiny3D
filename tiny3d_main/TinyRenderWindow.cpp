//
//  TinyRenderWindow.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyRenderWindow.h"

namespace Tiny
{
    TinyRenderWindow::TinyRenderWindow(uint32 width, uint32 height)
    {
        mPriority = TINY_DEFAULT_RT_GROUP;
    }
    
    TinyRenderWindow::~TinyRenderWindow()
    {
        
    }
}