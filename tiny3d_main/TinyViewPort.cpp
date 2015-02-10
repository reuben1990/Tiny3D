//
//  TinyViewPort.cpp
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include <stdio.h>
#include "TinyViewPort.h"

namespace Tiny
{
    TinyViewPort::TinyViewPort(TinyCamera *cam, TinyRenderTarget *target, float left, float bottom, float width, float height, int zOrder)
        : mCamera(cam)
        , mTarget(target)
        , mzOrder(zOrder)
    {
        mLeftBottomPosition.x = left;
        mLeftBottomPosition.y = bottom;
        mSize.x = width;
        mSize.y = height;
        
        updateDimensions();
        cam->notifyViewPort(this);
    }
    
    TinyViewPort::~TinyViewPort()
    {
        
    }
    
    TinyRenderTarget *TinyViewPort::getRenderTarget()
    {
        return mTarget;
    }
    
    void TinyViewPort::update()
    {
        if (mCamera)
        {
            mCamera->renderScene(this);
        }
    }
    
    void TinyViewPort::updateDimensions()
    {
        //
    }
    
    kmVec2 TinyViewPort::geViewPortLeftBottom()
    {
        return mLeftBottomPosition;
    }
    
    kmVec2 TinyViewPort::getViewPortSize()
    {
        return mSize;
    }
}
