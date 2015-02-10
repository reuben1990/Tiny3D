//
//  TinyEntity.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinyEntity_h
#define proj_mac_TinyEntity_h

#include "TinyObject.h"
#include "TinyRenderQueue.h"
#include "TinyMovableObject.h"
#include "TinySubEntity.h"
#include <vector>
#include "TinyPlatform.h"

namespace Tiny
{
    class TinyEntity : public TinyMovableObject
    {
    public:
        TinyEntity();
        ~TinyEntity();
        void updateRenderQueue(TinyCamera* cam, TinyRenderQueue* queue);
        void setRenderQueueGroupID(uint8 groupID);
        void setRenderPriority(uint8 priority);
        void setMaterial(TinyMaterial* material);
    protected:
        std::vector<TinySubEntity*> mSubEntitys;
        uint8 mRenderQueueGroupID;
        uint8 mRenderPriority;
    };
}

#endif
