//
//  TinyFrameListener.h
//  proj_mac
//
//  Created by reuben chao on 3/1/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyFrameListener__
#define __proj_mac__TinyFrameListener__

#include <stdio.h>
#include "TinyObject.h"

namespace Tiny
{
    class TinyFrameListener : public TinyObject
    {
    public:
        virtual void onFrameStarted() = 0;
    };
}


#endif /* defined(__proj_mac__TinyFrameListener__) */
