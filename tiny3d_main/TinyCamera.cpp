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
        , mNear(0.1)
        , mFar(1000)
        , mPosition(kmVec3Make(0, 0, 0))
        , mOrientation(kmQuaternionMake(0, 0, 0, 1))
        , mLocalUpDir(kmVec3Make(0, 1, 0))
        , mLocalFrontDir(kmVec3Make(0, 0, -1))
        , mLocalSideDir(kmVec3Make(1, 0, 0))
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
            kmQuaternion derivedOrientation;
            kmVec3 derivedPosition;
            kmQuaternionMultiply(&derivedOrientation, &parentNodeDerivedOrientation, &mOrientation);
            kmVec3Add(&derivedPosition, &parentNodeDerivedPosition, &mPosition);
            
            kmVec3 worldFrontDir, worldUpDir, worldCenter;
            kmQuaternionMultiplyVec3(&worldFrontDir, &derivedOrientation, &mLocalFrontDir);
            kmQuaternionMultiplyVec3(&worldUpDir, &derivedOrientation, &mLocalUpDir);
            kmVec3Add(&worldCenter, &derivedPosition, &worldFrontDir);
            kmMat4LookAt(&ret, &derivedPosition, &worldCenter, &worldUpDir);
        }
        else
        {
            kmMat4Identity(&ret);
        }
    }

    void TinyCamera::getProjectionMatrix(kmMat4& ret)
    {
        float degree = radianToDegree(mFov);
        kmMat4PerspectiveProjection(&ret, degree, mAspect, mNear, mFar);
    }
    
    void TinyCamera::updateRenderQueue(TinyCamera* cam, TinyRenderQueue* queue)
    {
        //
    }
    
    void TinyCamera::roll(float radian)
    {
        kmVec3 rollAxis;
        kmQuaternionMultiplyVec3(&rollAxis, &mOrientation, &mLocalSideDir);
        rotate(rollAxis, radian);
    }
    
    void TinyCamera::pitch(float radian)
    {
        kmVec3 pitchAxis;
        kmQuaternionMultiplyVec3(&pitchAxis, &mOrientation, &mLocalFrontDir);
        rotate(pitchAxis, radian);
    }
    
    void TinyCamera::yaw(float radian)
    {
        rotate(mLocalUpDir, radian);
    }
    
    void TinyCamera::rotate(kmVec3& axis, float radian)
    {
        kmQuaternion quaternionDiff, orientationBefore;
        kmQuaternionRotationAxis(&quaternionDiff, &axis, radian);
        orientationBefore = kmQuaternionMake(mOrientation.x, mOrientation.y, mOrientation.z, mOrientation.w);
        kmQuaternionMultiply(&mOrientation, &quaternionDiff, &orientationBefore);
    }
    
    const kmQuaternion& TinyCamera::getOrientation()
    {
        return mOrientation;
    }
    
    void TinyCamera::moveRelative(const kmVec3& vec)
    {
        kmVec3 diff;
        kmQuaternionMultiplyVec3(&diff, &mOrientation, &vec);
        kmVec3Add(&mPosition, &mPosition, &diff);
    }
}



