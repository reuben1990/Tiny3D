//
//  TinySceneNode.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinySceneNode.h"
#include "TinyMemoryAlloc.h"

namespace Tiny
{
    TinySceneNode::TinySceneNode(std::string name)
        : TinyNode(name)
    {
        
    }
    
    TinySceneNode::~TinySceneNode()
    {
        
    }
    
    void TinySceneNode::attachObject(TinyMovableObject* obj)
    {
        assert(!obj->isAttached() && "Obj was already attached to an node.");
        auto result = mAttachedObjects.insert(std::pair<std::string, TinyMovableObject*>(obj->getName(), obj));
        assert(result.second && "Objects was not attached because an object of the same name was"
               "already attached to this node.");
        obj->notifyAttached(this);
    }
    
    void TinySceneNode::findVisibleObjects(TinyCamera* cam, TinyRenderQueue* queue)
    {
        auto iter = mAttachedObjects.begin();
        for (; iter != mAttachedObjects.end(); iter ++)
        {
            iter->second->updateRenderQueue(cam, queue);
        }
        auto nodeIter = mChildren.begin();
        for (; nodeIter != mChildren.end(); nodeIter ++)
        {
            TinySceneNode* node = dynamic_cast<TinySceneNode*>(nodeIter->second);
            node->findVisibleObjects(cam, queue);
        }
    }
    
    TinySceneNode* TinySceneNode::createChildSceneNode()
    {
        auto child = TINY_NEW TinySceneNode(mNameGenerator.generate());
        addChild(child);
        return child;
    }
}