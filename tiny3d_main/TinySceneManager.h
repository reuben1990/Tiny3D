//
//  TinySceneManager.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinySceneManager_h
#define proj_mac_TinySceneManager_h

#include "TinyObject.h"
#include "TinyCamera.h"
#include "TinyViewPort.h"
#include "TinyRenderTarget.h"
#include "TinySceneNode.h"
#include "TinyRenderQueue.h"
#include "TinyAutoParamDataSource.h"

namespace Tiny
{
    class TinyRenderSystem;
    class TinySceneManager : public TinyObject
    {
    public:
        TinySceneManager();
        virtual ~TinySceneManager();
        void renderScene(TinyCamera *cam);
        void findVisibleObjects(TinyCamera *cam);
        void renderVisibleObjects();
        void updateSceneGraph();
        void renderQueueGroupObjects(TinyRenderQueueGroup* group);
        void renderObjects(TinyRenderableCollection* collection);
        void renderSingleObject(TinyRenderable* renderable);
        void setViewPort(TinyViewPort *vp);
        void setProjectionMatrix(kmMat4& matrix);
        void setViewMatrix(kmMat4& matrix);
        void setModelMatrix(kmMat4& matrix);
        TinySceneNode* getRootSceneNode();
        TinyRenderQueue* getRenderQueue();
        void clearBg();
    private:
        TinyViewPort *mCurrentViewPort;
        TinyCamera *mCameraInProgress;
        TinySceneNode* mSceneRoot;
        TinyRenderSystem* mDestRenderSystem;
        TinyRenderQueue* mRenderQueue;
        TinyAutoParamDataSource mAutoParamDataSource;
    };
}

#endif
