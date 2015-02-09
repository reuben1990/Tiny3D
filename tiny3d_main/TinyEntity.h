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
#include <vector>

namespace Tiny
{
    class TinyEntity : public TinyMovableObject
    {
    public:
        TinyEntity();
        ~TinyEntity();
        void updateRenderQueue(TinyCamera* cam, TinyRenderQueue* queue);
    protected:
    };
}

#endif
