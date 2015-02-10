//
//  TinyMaterial.h
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyMaterial__
#define __proj_mac__TinyMaterial__

#include <stdio.h>
#include "TinyObject.h"

namespace Tiny
{
    class TinyMaterial : public TinyObject
    {
    public:
        TinyMaterial();
        ~TinyMaterial();
        bool isTransParent();
    protected:
        mIsTransParent;
    };
}

#endif /* defined(__proj_mac__TinyMaterial__) */
