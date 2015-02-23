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
#include <map>
#include "TinyObject.h"
#include "TinyRenderTarget.h"
#include "TinyGPUProgram.h"
#include "TinyViewPort.h"
#include "TinyRenderTarget.h"
#include "TinyRenderOperation.h"

namespace Tiny
{
    class TinyRenderSystem : public TinyObject
    {
    public:
        TinyRenderSystem();
        virtual ~TinyRenderSystem();
        void updateAllRenderTargets();
        void swapAllRenderTargetBuffers();
        void render(TinyRenderOperation* ro);
        void bindGPUProgram(TinyGPUProgram *program);
        void bindGPUProgramParameters(TinyGPUProgramParameters *params);
        void setRenderTarget(TinyRenderTarget *target);
        void setViewPort(TinyViewPort *vp);
        void setProjectionMatrix(kmMat4& matrix);
        void setViewMatrix(kmMat4& matrix);
        void setModelMatrix(kmMat4& matrix);
        void attachRenderTarget(TinyRenderTarget *target);
        void detachRenderTarget(TinyRenderTarget *target);
        void clearBg();
    private:
        typedef std::map<unsigned char, TinyRenderTarget *> TinyRenderTargetMap;
        TinyRenderTargetMap mPrioritisedRenderTargets;
        TinyViewPort *mActiveViewPort;
        TinyRenderTarget *mActiveRenderTarget;
        kmMat4 mProjMatrix;
        kmMat4 mViewMatrix;
        kmMat4 mModelMatrix;
    };
}

#endif /* defined(__proj_mac__TinyRenderSystem__) */
