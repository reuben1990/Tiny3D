//
//  TinyEntity.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include <stdio.h>
#include "TinyMovableObject.h"

namespace Tiny
{
    TinyEntity::TinyEntity(std::string& name, TinyMesh* mesh)
        : TinyMovableObject(name)
    {
        mName = name;
        mMesh = mesh;
        initialize();
    }
    
    TinyEntity::~TinyEntity()
    {
        
    }
    
    void TinyEntity::initialize()
    {
        buildSubEntityList(mMesh, &mSubEntitys);
    }
    
    void TinyEntity::buildSubEntityList(TinyMesh* mesh, SubEntityList* list)
    {
        auto iter = mMesh->getSubmeshIterator();
        while (iter.hasMoreElements())
        {
            TinySubMesh* subMesh = iter.getNext();
            mSubEntitys.push_back(TINY_NEW TinySubEntity(subMesh));
        }
        
    }
    
    void TinyEntity::updateRenderQueue(TinyCamera* cam, TinyRenderQueue* queue)
    {
        auto iter = mSubEntitys.begin();
        for (; iter <= mSubEntitys.end(); iter ++)
        {
            queue->addRenderable(iter->second, mRenderQueueGroupID, mRenderPriority);
        }
    }
    
    void TinyEntity::setRenderQueueGroupID(uint8 groupID)
    {
        mRenderQueueGroupID = groupID;
    }
    
    void TinyEntity::setRenderPriority(uint8 priority)
    {
        mRenderPriority = priority;
    }
}