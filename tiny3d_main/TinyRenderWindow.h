//
//  TinyRenderWindow.h
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyRenderWindow__
#define __proj_mac__TinyRenderWindow__

#include <stdio.h>
#include "TinyRenderTarget.h"


namespace Tiny
{
    class TinyRenderWindow : public TinyRenderTarget
    {
    public:
        TinyRenderWindow(uint32 width, uint32 height);
        ~TinyRenderWindow();
    };
}

#endif /* defined(__proj_mac__TinyRenderWindow__) */
