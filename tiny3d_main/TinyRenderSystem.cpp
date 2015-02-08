//
//  TinyRenderSystem.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyRenderSystem.h"
#include "kazmath/kazmath.h"

namespace Tiny
{
    TinyRenderSystem::TinyRenderSystem():
    mActiveViewPort(nullptr),
    mActiveRenderTarget(nullptr)
    {
    }
    
    TinyRenderSystem::~TinyRenderSystem()
    {
    }
    
    void TinyRenderSystem::setViewPort(TinyViewPort *vp)
    {
        if (!vp)
        {
            mActiveViewPort = nullptr;
            setRenderTarget(nullptr);
        }
        else
        {
            mActiveViewPort = vp;
            TinyRenderTarget *renderTarget;
            renderTarget = vp->getRenderTarget();
            setRenderTarget(renderTarget);
            kmVec2 vpPosition = vp->geViewPortLeftBottom();
            kmVec2 vpSize = vp->getViewPortSize();
            glViewport(vpPosition.x, vpPosition.y vpSize.x, vpSize.y);
            glScissor(vpPosition.x, vpPosition.y vpSize.x, vpSize.y);
        }
    }
    
    void TinyRenderSystem::setRenderTarget(TinyRenderTarget *target)
    {
        mActiveRenderTarget = target;
        if (target)
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, target->getFBO());
        }
    }
    
    void TinyRenderSystem::updateAllRenderTargets()
    {
        std::map<unsigned char, TinyRenderTarget *> iter = mPrioritisedRenderTargets.begin();
        for (; iter != mPrioritisedRenderTargets.end(); iter ++)
        {
            iter->second->update(false);
        }
    }
    
    void TinyRenderSystem::swapAllRenderTargetBuffers()
    {
        std::map<unsigned char, TinyRenderTarget *> iter = mPrioritisedRenderTargets.begin();
        for (; iter != mPrioritisedRenderTargets.end(); iter ++)
        {
            iter->second->swapBuffers();
        }
    }
    
    void TinyRenderSystem::render()
    {
        
    }
    
    void TinyRenderSystem::attachRenderTarget(TinyRenderTarget *target)
    {
        std::pair<unsigned char, TinyRenderTarget *> element(target->getPriority(), target);
        mPrioritisedRenderTargets.insert(element);
    }
    
    void TinyRenderSystem::detachRenderTarget(TinyRenderTarget *target)
    {
        if (target == mActiveRenderTarget)
        {
            mActiveRenderTarget = nullptr;
        }
        std::map<unsigned char, TinyRenderTarget *> iter = mPrioritisedRenderTargets.begin();
        for (; iter != mPrioritisedRenderTargets.end(); iter ++)
        {
            if (iter->second == target)
            {
                mPrioritisedRenderTargets.erase(iter);
            }
        }
    }
}




