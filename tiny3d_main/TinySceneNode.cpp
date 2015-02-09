//
//  TinySceneNode.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinySceneNode.h"

namespace Tiny
{
    void TinySceneNode::attachObject(TinyMovableObject* obj)
    {
        assert(!obj->isAttached() && "Obj was already attached to an node.");
        auto result = mAttachedObjects->insert(std::pair<std::string, TinyMovableObject*>(obj->getName(), obj));
        assert(result.second && "Objects was not attached because an object of the same name was"
               "already attached to this node.");
        obj->notifyAttached(this);
    }
    
    void TinySceneNode::findVisibleObjects(TinyCamera* cam, RenderQueue* queue)
    {
        auto iter = mAttachedObjects.begin();
        for (; iter != mAttachedObjects.end(); iter ++)
        {
            iter->second->updateRenderQueue(cam, queue);
        }
        auto nodeIter = mChildren.begin();
        for (; nodeIter != mChildren.end(); nodeIter ++)
        {
            nodeIter->second->findVisibleObjects(cam, queue);
        }
    }
}