//
//  TinyRenderQueue.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyRenderQueue.h"
#include "TinyMemoryAlloc.h"

namespace Tiny
{

    TinyRenderQueue::TinyRenderQueue()
    {
        //
    }

    TinyRenderQueue::~TinyRenderQueue()
    {
        auto iter = mRenderQueueGroups.begin();
        for (; iter != mRenderQueueGroups.end(); iter ++)
        {
            TINY_DELETE iter->second;
        }
        mRenderQueueGroups.clear();
    }

    void TinyRenderQueue::addRenderable(TinyRenderable* renderable, uint8 groupID, uint8 priority)
    {
        auto group = getQueueGroup(groupID);
        group->addRenderable(renderable, priority);
    }
    
    MapIterator<RenderQueueGroupMap> TinyRenderQueue::getQueueGroupIterator();
    {
        return MapIterator<RenderQueueGroupMap>(mRenderQueueGroups.begin(); mRenderQueueGroups.end());
    }
    
    TinyRenderQueueGroup* TinyRenderQueue::getQueueGroup(uint8 groupID)
    {
        auto iter = mRenderQueueGroups.find(groupID);
        TinyRenderQueueGroup* group;
        if (iter == mRenderQueueGroups.end())
        {
            group = TINY_NEW TinyQueueGroup();
            mRenderQueueGroups.insert(std::pair<uint8, TinyRenderQueueGroup*>(groupID, group));
        }
        else
        {
            gourp = iter->second;
        }
        return group;
    }
    
    TinyRenderQueueGroup::TinyRenderQueueGroup()
    {
        //
    }
    
    TinyRenderQueueGroup::~TinyRenderQueueGroup()
    {
        auto iter = mRenderPriorityGroups.begin();
        for (; iter != mRenderPriorityGroups.end(); iter ++)
        {
            TINY_DELETE iter->second;
        }
        mRenderPriorityGroups.clear();
    }
    
    void TinyRenderQueueGroup::addRenderable(TinyRenderable* renderable, uint8 priority)
    {
        auto group = mRenderPriorityGroups->find(priority);
        gourp->addRenderable(renderable);
    }
    
    MapIterator<RenderPriorityGroupMap > TinyRenderQueueGroup::getPriorityGroupIterator()
    {
        return MapIterator<RenderPriorityGroupMap >(mRenderPriorityGroups.begin(), mRenderPriorityGroups.end());
    }
    
    TinyRenderPriorityGroup* TinyRenderQueueGroup::getPriorityGroup(uint8 priority)
    {
        auto iter = mRenderPriorityGroups.find(priority);
        TinyRenderPriorityGroup* group;
        if (iter == mRenderPriorityGroups.end())
        {
            group = TINY_NEW TinyRenderPriorityGroup();
            mRenderPriorityGroups.insert(std::pair<uint8, TinyRenderPriorityGroup*>(priority, group));
        }
        else
        {
            gourp = iter->second;
        }
        return group;
    }
    
    TinyRenderPriorityGroup::TinyRenderPriorityGroup()
        : mSolidCollection(TINY_NEW TinyRenderableCollection())
        , mTransParentCollection(TINY_NEW TinyRenderableCollection())
    {
        //
    }
    
    TinyRenderPriorityGroup::~TinyRenderPriorityGroup()
    {
        TINY_DELETE mSolidCollection;
        TINY_DELETE mTransParentCollection;
    }
    
    void TinyRenderPriorityGroup::addRenderable(TinyRenderable* renderable)
    {
        auto material = renderable->getMaterial();
        if (material->isTransParent())
        {
            mTransParentCollection->addRenderable(renderable);
        }
        else
        {
            mSolidCollection->addRenderable(renderable);
        }
    }
    
    TinyRenderableCollection* TinyRenderPriorityGroup::getSolidCollection()
    {
        return mSolidCollection;
    }
    
    TinyRenderableCollection* TinyRenderPriorityGroup::getTransParentCollection()
    {
        return mTransParentCollection;
    }
    
    TinyRenderableCollection::TinyRenderableCollection()
    {
        //
    }
    
    TinyRenderableCollection::~TinyRenderableCollection()
    {
        //
    }
    
    void TinyRenderableCollection::addRenderable(TinyRenderable* renderable)
    {
        mRenderables.push_back(renderable);
    }
    
    VectorIterator<RenderableArray > TinyRenderableCollection::getRenderableIterator()
    {
        return VectorIterator<RenderableArray >(mRenderables.begin(), mRenderables.end());
    }
}




