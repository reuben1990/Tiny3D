//
//  TinyRenderTarget.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyRenderTarget.h"
#include "TinyMemoryAlloc.h"

namespace Tiny
{
    TinyRenderTarget::TinyRenderTarget(uint32 width, uint32 height)
        : mPriority(TINY_DEFAULT_RT_GROUP)
        , mFbo(0)
        , mWidth(width)
        , mHeight(height)
    {
        
    }
    
    TinyRenderTarget::~TinyRenderTarget()
    {
        
    }
    
    GLuint TinyRenderTarget::getFBO()
    {
        return mFbo;
    }
    
    void TinyRenderTarget::update(bool swap)
    {
        updateImpl();
        if (swap)
        {
            //swapBuffer();
        }
    }
    
    kmVec2 TinyRenderTarget::getSize()
    {
        kmVec2 ret;
        kmVec2Fill(&ret, mWidth, mHeight);
        return ret;
    }
    
    void TinyRenderTarget::updateImpl()
    {
        updateViewPorts();
    }
    
    void TinyRenderTarget::addViewPort(TinyCamera *cam, int zOrder, float left, float bottom, float width, float height)
    {
        auto iter = mViewPorts.find(zOrder);
        if (iter == mViewPorts.end())
        {
            TinyViewPort *vp = TINY_NEW TinyViewPort(cam, this, left, bottom, width, height, 0);
            mViewPorts[zOrder] = vp;
        }
    }
    
    TinyViewPort *TinyRenderTarget::getViewPort(int zOrder)
    {
        TinyViewPort *ret = nullptr;
        auto vpIter = mViewPorts.find(zOrder);
        if (vpIter != mViewPorts.end())
        {
            ret = vpIter->second;
        }
        return ret;
    }
    
    void TinyRenderTarget::removeViewPort(int zOrder)
    {
        auto vpIter = mViewPorts.find(zOrder);
        if (vpIter != mViewPorts.end())
        {
            TINY_DELETE vpIter->second;
            mViewPorts.erase(zOrder);
        }
    }
    
    unsigned char TinyRenderTarget::getPriority()
    {
        return mPriority;
    }
    
    void TinyRenderTarget::updateViewPorts()
    {
        auto iter = mViewPorts.begin();
        for (; iter != mViewPorts.end(); iter ++)
        {
            iter->second->update();
        }
    }
    
    void TinyRenderTarget::clearBg()
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        TINYLOG("glClear");
    }
}




