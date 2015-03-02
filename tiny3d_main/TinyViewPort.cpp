//
//  TinyViewPort.cpp
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include <stdio.h>
#include "TinyViewPort.h"
#include "TinyCamera.h"
#include "TinyRenderTarget.h"

namespace Tiny
{
    TinyViewPort::TinyViewPort(TinyCamera *cam, TinyRenderTarget *target, float left, float bottom, float width, float height, int zOrder)
        : mCamera(cam)
        , mTarget(target)
        , mZorder(zOrder)
    {
        kmVec2 targetSize = target->getSize();

        mSize.x = width;
        mSize.y = height;
        mRealSize.x = targetSize.x * width;
        mRealSize.y = targetSize.y * height;
        
        mLeftBottomPosition.x = left;
        mLeftBottomPosition.y = bottom;
        mRealLeftBottomPosition.x = left * targetSize.x;
        mRealLeftBottomPosition.y = bottom * targetSize.y;
        
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
        return mRealLeftBottomPosition;
    }
    
    kmVec2 TinyViewPort::getViewPortSize()
    {
        return mRealSize;
    }
}
