//
//  TinyCamera.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyCamera.h"
#include "TinyMath.h"

namespace Tiny
{
    

    TinyCamera::TinyCamera(std::string &name, TinySceneManager *mgr)
        : TinyMovableObject(name)
        , mSceneMgr(mgr)
        , mName(name)
        , mLastViewPort(nullptr)
        , mFov(kTinyPI / 4)
        , mAspect(4 / 3)
        , mNear(10)
        , mFar(1000)
    {
        
    }

    TinyCamera::~TinyCamera()
    {
        
    }

    void TinyCamera::renderScene(TinyViewPort *viewPort)
    {
        notifyViewPort(viewPort);
        mSceneMgr->renderScene(this);
    }

    void TinyCamera::notifyViewPort(TinyViewPort *vp)
    {
        mLastViewPort = vp;
        auto vpSize = vp->getViewPortSize();
        mAspect = vpSize.x / vpSize.y;
        
    }

    TinyViewPort *TinyCamera::getViewPort()
    {
        return mLastViewPort;
    }

    void TinyCamera::getViewMatrix(kmMat4& ret)
    {
        if (mParentNode)
        {
            auto parentNodeDerivedOrientation = mParentNode->getDerivedOrientation();
            auto parentNodeDerivedPosition = mParentNode->getDerivedPosition();
            auto frontDir = kmVec3Make(0, 0, -1);
            auto upDir = kmVec3Make(0, 1, 0);
            kmVec3 worldFrontDir, worldUpDir, worldCenter;
            kmQuaternionMultiplyVec3(&worldFrontDir, &parentNodeDerivedOrientation, &frontDir);
            kmQuaternionMultiplyVec3(&worldUpDir, &parentNodeDerivedOrientation, &upDir);
            kmVec3Add(&worldCenter, &parentNodeDerivedPosition, &frontDir);
            kmMat4LookAt(&ret, &parentNodeDerivedPosition, &worldCenter, &worldUpDir);
        }
        else
        {
            kmMat4Identity(&ret);
        }
    }

    void TinyCamera::getProjectionMatrix(kmMat4& ret)
    {
        kmMat4PerspectiveProjection(&ret, mFov, mAspect, mNear, mFar);
    }
    
    void TinyCamera::updateRenderQueue(TinyCamera* cam, TinyRenderQueue* queue)
    {
        //
    }
}

//- (void)updateInput:(NSTimeInterval)timeInterval
//{
//    kmVec3 f, s, u;
//    
//    kmVec3Subtract(&f, &_center, &_eye);
//    kmVec3Normalize(&f, &f);
//    
//    kmVec3Normalize(&_up, &_up);
//    
//    kmVec3Cross(&s, &f, &_up);
//    kmVec3Normalize(&s, &s);
//    
//    kmVec3Cross(&u, &s, &f);
//    kmVec3Normalize(&s, &s);
//    
//    GSInputController *inputController = [GSInputController sharedInputController];
//    float delta = _moveSpeed * timeInterval;
//    if ([inputController keyIsPressed:NSLeftArrowFunctionKey]
//        || [inputController keyIsPressed:'a']
//        || [inputController keyIsPressed:'A']) {
//        kmVec3Scale(&s, &s, -delta);
//        kmVec3Add(&_eye, &_eye, &s);
//        kmVec3Add(&_center, &_center, &s);
//    } else if ([inputController keyIsPressed:NSRightArrowFunctionKey]
//               || [inputController keyIsPressed:'d']
//               || [inputController keyIsPressed:'D']) {
//        kmVec3Scale(&s, &s, delta);
//        kmVec3Add(&_eye, &_eye, &s);
//        kmVec3Add(&_center, &_center, &s);
//    } else if ([inputController keyIsPressed:NSUpArrowFunctionKey]
//               || [inputController keyIsPressed:'w']
//               || [inputController keyIsPressed:'W']) {
//        kmVec3Scale(&f, &f, delta);
//        kmVec3Add(&_eye, &_eye, &f);
//        kmVec3Add(&_center, &_center, &f);
//    } else if ([inputController keyIsPressed:NSDownArrowFunctionKey]
//               || [inputController keyIsPressed:'s']
//               || [inputController keyIsPressed:'S']) {
//        kmVec3Scale(&f, &f, -delta);
//        kmVec3Add(&_eye, &_eye, &f);
//        kmVec3Add(&_center, &_center, &f);
//    }
//}
//
//- (void)mouseLeftDragWithX:(CGFloat)x andY:(CGFloat)y
//{
//    float thetaX = -x * _rotateSpeed;
//    float thetaY = -y * _rotateSpeed;
//    
//    kmVec3 f, s, yawAxis, frontDir;
//    
//    kmVec3Subtract(&f, &_center, &_eye);
//    kmVec3Normalize(&f, &f);
//    kmVec3Normalize(&_up, &_up);
//    kmVec3Cross(&s, &f, &_up);
//    kmVec3Normalize(&s, &s);
//    
//    yawAxis.x = 0;
//    yawAxis.y =1;
//    yawAxis.z = 0;
//    
//    kmVec3Subtract(&frontDir, &_center, &_eye);
//    
//    kmQuaternion yaw, pitch;
//    kmQuaternionRotationAxis(&yaw, &yawAxis, thetaX);
//    kmQuaternionRotationAxis(&pitch, &s, thetaY);
//    kmQuaternionMultiplyVec3(&frontDir, &pitch, &frontDir);
//    kmQuaternionMultiplyVec3(&frontDir, &yaw, &frontDir);
//    kmQuaternionMultiplyVec3(&_up, &pitch, &_up);
//    kmQuaternionMultiplyVec3(&_up, &yaw, &_up);
//    
//    kmVec3Add(&_center, &_eye, &frontDir);
//}
