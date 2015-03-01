//
//  MovableObjectFactory.cpp
//  proj_mac
//
//  Created by reuben chao on 2/12/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyMovableObjectFactory.h"

namespace Tiny
{
    TinyMovableObjectFactory::TinyMovableObjectFactory()
    {
        
    }
    
    TinyMovableObjectFactory::~TinyMovableObjectFactory()
    {
        
    }
    
    TinyMovableObject* TinyMovableObjectFactory::createInstance(const std::string& name, const TinyNameValuePairList& params)
    {
        return createInstanceImpl(name, params);
    }
}