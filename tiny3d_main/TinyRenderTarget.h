//
//  TinyRenderTarget.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinyRenderTarget_h
#define proj_mac_TinyRenderTarget_h

#include "TinyObject.h"
#include "TinyCamera.h"
#include <map>
#include "TinyViewPort.h"
#include "TinyPlatform.h"

#ifndef TINY_NUM_RENDERTARGET_GROUPS
#define TINY_NUM_RENDERTARGET_GROUPS 10
#define TINY_DEFAULT_RT_GROUP 4
#define TINY_REND_TO_TEX_RT_GROUP 2
#endif

namespace Tiny
{
    class TinyRenderTarget : public TinyObject
    {
    public:
        TinyRenderTarget(uint32 width, uint32 height);
        virtual ~TinyRenderTarget();
        
        //be called every frame, to update contens with viewports.
        void update(bool swap);
        
        //fire update events, do update all view ports.
        void updateImpl();
        
        //update all viewports.
        void updateViewPorts();
        
        //swapBuffer.
        virtual void swapBuffer() = 0;
        
        virtual kmVec2 getSize();
        
        //insert a viewport to viewport to viewport list.
        void addViewPort(TinyCamera *cam, int zOrder, float left, float bottom, float width, float height);
        
        TinyViewPort *getViewPort(int zOrder);
        
        //remove a viewport.
        void removeViewPort(int zOrder);
        
        //get render target's fbo.
        GLuint getFBO();
        
        unsigned char getPriority();
        
        virtual void preRender() = 0;
        
    protected:
        float mWidth;
        float mHeight;
        unsigned char mPriority;
        GLuint mFbo;
        std::map<int, TinyViewPort *> mViewPorts;
    };
}

#endif
