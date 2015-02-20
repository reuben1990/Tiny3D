//
//  TinySceneNode.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinySceneNode_h
#define proj_mac_TinySceneNode_h

#include "TinyObject.h"
#include "kazmath/kazmath.h"
#include <string>
#include <map>
#include "TinyNode.h"
#include "TinyMovableObject.h"
#include "TinyRenderQueue.h"
class TinyCamera;

namespace Tiny
{
    class TinySceneNode : public TinyNode
    {
    public:
        TinySceneNode(std::string& name);
        virtual ~TinySceneNode();
        void attachObject(TinyMovableObject* obj);
        void detattchObject(TinyMovableObject* obj);
        void findVisibleObjects(TinyCamera* cam, TinyRenderQueue* queue);
        TinySceneNode* createChildSceneNode();
    protected:
        std::map<std::string, TinyMovableObject*> mAttachedObjects;
    };
}

#endif
