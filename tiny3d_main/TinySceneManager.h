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
#include "TinyRenderSystem.h"
#include "TinyRenderTarget.h"
#include "TinySingleton.h"
#include "TinySceneNode.h"
#include "TinyRenderQueue.h"

namespace Tiny
{
    class TinySceneManager : public TinyObject, public TinySingleton
    {
    public:
        TinySceneManager();
        ~TinySceneManager();
        void renderScene(TinyCamera *cam);
        void findVisibleObjects(TinyCamera *cam);
        void renderVisibleObjects();
        void updateSceneGraph();
        void renderVisibleObjects();
        void renderQueueGroupObjects(TinyRenderQueueGroup* group);
        void renderObjects(TinyRenderableCollection* collection);
        void renderSingleObject(TinyRenderable* renderable);
        void setViewPort(TinyViewPort *vp);
        void setViewMatrix(kmMat4& matrix);
        TinySceneNode* getRootSceneNode();
        TinyRenderQueue* getRenderQueue();
    private:
        TinyViewPort *mCurrentViewPort;
        TinyCamera *mCameraInProgress;
        TinySceneNode* mSceneRoot;
        TinyRenderSystem *mDestRenderSystem;
        RenderQueue* mRenderQueue;
    };
}

#endif
