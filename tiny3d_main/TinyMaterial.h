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
#include "TinyGPUProgram.h"

namespace Tiny
{
    class TinyMaterial : public TinyObject
    {
    public:
        TinyMaterial();
        ~TinyMaterial();
        bool isTransParent();
        void setProgram(TinyGPUProgram* program);
        TinyGPUProgram* getProgram();
    protected:
        bool mIsTransParent;
        TinyGPUProgram* mProgram;
    };
}

#endif /* defined(__proj_mac__TinyMaterial__) */
