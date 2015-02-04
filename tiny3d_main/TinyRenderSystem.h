//
//  TinyRenderSystem.h
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyRenderSystem__
#define __proj_mac__TinyRenderSystem__

#include <stdio.h>

#include "TinyObject.h"
#include <map>
#include <string>
#include "TinyRenderTarget.h"
#include "TinyGPUProgram.h"

namespace Tiny
{
    class TinyRenderSystem : public TinyObject
    {
    public:
        TinyRenderSystem();
        virtual ~TinyRenderSystem();
        static TinyRenderSystem *getSingleton();
        void initialize();
        void updateAllRenderTargets();
        void swapAllRenderTargetBuffers();
        void render();
        void bindGPUProgram(TinyGPUProgram *program);
        void bindGPUProgramParameters(GPUProgramParameters *params);
        void setRenderTarget(TinyRenderTarget *target);
    private:
        std::map<std::string, TinyRenderTarget *> mRenderTargets;
        static TinyRenderSystem *sSingleton;
    };
}

#endif /* defined(__proj_mac__TinyRenderSystem__) */
