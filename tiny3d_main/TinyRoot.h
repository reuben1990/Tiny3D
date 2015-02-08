//
//  TinyRoot.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinyRoot_h
#define proj_mac_TinyRoot_h

#include "TinyObject.h"
#include "TinyRenderSystem.h"
#include "TinySingleton.h"
#include "TinySceneManager.h"
#include "TinyRenderWindow.h"

namespace Tiny {
    class TinyRoot : public TinyObject, public TinySingleton<TinyRoot>
    {
    public:
        TinyRoot();
        virtual ~TinyRoot();
        void renderOneFrame(float timeInterval);
        void updateAllRenderTargets();
        TinySceneManager *createSceneManager();
    private:
        TinyRenderSystem *mRenderSystem;
        TinySceneManager *mSceneMgr;
    };
}

#endif
