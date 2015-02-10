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
    TinyEntity::TinyEntity()
    {
        
    }
    
    TinyEntity::~TinyEntity()
    {
        
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