//
//  TinyCamera.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinyCamera_h
#define proj_mac_TinyCamera_h

#include "kazmath/kazmath.h"
#include "TinyObject.h"
#include "TinySceneManager.h"
#include "TinyMovableObject.h"
#include "TinyViewPort.h"
#include <string>

class TinySceneManager;

namespace Tiny
{
    class TinyCamera : public TinyMovableObject
    {
    public:
        TinyCamera(std::string &name, TinySceneManager *mgr);
        ~TinyCamera();
        void renderScene(TinyViewPort *viewPort);
        void notifyViewPort(TinyViewPort *vp);
        TinyViewPort *getViewPort();
        void getViewMatrix(kmMat4& ret);
        void getProjectionMatrix(kmMat4& ret);
        void updateRenderQueue(TinyCamera* cam, TinyRenderQueue* queue);
        void roll(float radian);
        void pitch(float radian);
        void yaw(float radian);
        void rotate(kmVec3& axis, float radian);
        const kmQuaternion& getOrientation();
    private:
        TinyViewPort *mLastViewPort;
        TinySceneManager *mSceneMgr;
        std::string mName;
        float mFov;
        float mAspect;
        float mNear;
        float mFar;
        kmVec3 mPosition;
        kmQuaternion mOrientation;
        kmVec3 mLocalUpDir;
        kmVec3 mLocalFrontDir;
        kmVec3 mLocalSideDir;
    };
}

#endif


