//
//  TinyMovableObject.h
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyMovableObject__
#define __proj_mac__TinyMovableObject__

#include <stdio.h>
#include "TinyObject.h"
#include <string>
#include "kazmath/kazmath.h"

class TinyNode;

namespace Tiny {
    class TinyMovableObject : public TinyObject
    {
    public:
        TinyMovableObject();
        ~TinyMovableObject();
        bool isAttached();
        std::string& getName();
        void setName(std::string& name);
        void notifyAttached(TinyNode* node);
        void updateRenderQueue(TinyCamera* cam, TinyRenderQueue* queue) = 0;
    protected:
        std::string mName;
        TinyNode* mParentNode;
    };
}

#endif /* defined(__proj_mac__TinyMovableObject__) */
