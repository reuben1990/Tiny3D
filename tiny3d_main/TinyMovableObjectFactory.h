//
//  MovableObjectFactory.h
//  proj_mac
//
//  Created by reuben chao on 2/12/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyMovableObjectFactory__
#define __proj_mac__TinyMovableObjectFactory__

#include <stdio.h>
#include <string>
#include "TinyObject.h"
#include "TinyMovableObject.h"
#include "TinyCommon.h"

namespace Tiny
{
    class TinyMovableObjectFactory : public TinyObject
    {
    public:
        TinyMovableObjectFactory();
        virtual ~TinyMovableObjectFactory();
        virtual std::string& getType() = 0;
        virtual TinyMovableObject* createInstance(std::string& name, TinyNameValuePairList& params);
        virtual TinyMovableObject* createInstanceImpl(std::string& name, TinyNameValuePairList& params) = 0;
    protected:
    };
}

#endif /* defined(__proj_mac__MovableObjectFactory__) */
