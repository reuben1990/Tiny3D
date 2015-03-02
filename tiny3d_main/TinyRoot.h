//
//  TinyRoot.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinyRoot_h
#define proj_mac_TinyRoot_h

#include <map>
#include <set>
#include "TinyObject.h"
#include "TinyRenderSystem.h"
#include "TinySingleton.h"
#include "TinySceneManager.h"
#include "TinyRenderWindow.h"
#include "TinyMovableObjectFactory.h"
#include "TinyFrameListener.h"

namespace Tiny
{
    class TinyRoot : public TinyObject, public TinySingleton<TinyRoot>
    {
    public:
        TinyRoot();
        virtual ~TinyRoot();
        void renderOneFrame(float timeInterval);
        void updateAllRenderTargets();
        TinySceneManager *createSceneManager();
        void addMovableObjectFactory(TinyMovableObjectFactory* factory);
        TinyMovableObjectFactory* getMovableObjectFactory(const std::string& name);
        void attachRenderTarget(TinyRenderTarget* target);
        void addFrameListener(TinyFrameListener* listener);
        void removeFrameListener(TinyFrameListener* listener);
        void fireRenderStartEvent();
    protected:
        typedef std::map<std::string, TinyMovableObjectFactory*> MovableObjectFactoryMap;
        typedef std::set<TinyFrameListener*> FrameListenerSet;
        TinyRenderSystem *mRenderSystem;
        TinySceneManager *mSceneMgr;
        MovableObjectFactoryMap mMovableObjectFactoryMap;
        FrameListenerSet mListenerSet;
        FrameListenerSet mRemovedListenerSet;
    };
}

#endif
