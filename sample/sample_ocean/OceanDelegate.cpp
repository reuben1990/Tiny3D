//
//  OceanDelegate.cpp
//  proj_mac
//
//  Created by reuben chao on 2/20/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include <stdio.h>
#include "TinyDelegate.h"
#include "OceanApplication.h"
#include "TinyMemoryAlloc.h"

namespace Tiny
{
    void TinyDelegate::initialize()
    {
        auto app = TINY_NEW OceanApplication();
        app->initialize();
    }
}