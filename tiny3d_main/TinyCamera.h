//
//  TinyCamera.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "kazmath/kazmath.h"
#include "GSInputController.h"
#include "TinyObject.h"

//@interface GSCameraController : NSObject<GSInputDelegate>
//
//@property (nonatomic, readonly) kmVec3 eye;
//@property (nonatomic, readonly) kmVec3 center;
//@property (nonatomic, readonly) kmVec3 up;
//@property (nonatomic, readwrite) float moveSpeed;
//@property (nonatomic, readwrite) float rotateSpeed;
//@property (nonatomic, readwrite) float fov;
//@property (nonatomic, readwrite) float aspect;
//@property (nonatomic, readwrite) float near;
//@property (nonatomic, readwrite) float far;
//
//- (id)initWithEye:(kmVec3)eye Center:(kmVec3)center Up:(kmVec3)up;
//
//- (kmMat4)viewMatrix;
//- (kmMat4)perspectiveMatrix;
//
//@end

#include "TinySceneManager.h"
#include "TinyMovableObject.h"
#include <string>

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
        kmMat4& getViewMatrix();
        kmMat4& getProjectionMatrix();
    private:
        TinyViewPort *mLastViewPort;
        TinySceneManager *mSceneMgr;
        std::string mName;
        float mFov;
        float mAspect;
        float mNear;
        float mFar;
    };
}




