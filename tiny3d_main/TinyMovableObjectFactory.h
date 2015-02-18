//
//  MovableObjectFactory.h
//  proj_mac
//
//  Created by reuben chao on 2/12/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__MovableObjectFactory__
#define __proj_mac__MovableObjectFactory__

#include <stdio.h>
#include <string>
#include "TinyMovableObject.h"

namespace Tiny
{
    class TinyMovableObjectFactory()
    {
    public:
        TinyMovableObjectFactory();
        virtual ~TinyMovableObjectFactory();
        virtual std::string& getType() = 0;
        virtual TinyMovableObject* createInstance();
        virtual TinyMovableObject* createInstanceImpl() = 0;
    protected:
    }
}

#endif /* defined(__proj_mac__MovableObjectFactory__) */
