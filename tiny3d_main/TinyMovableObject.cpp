//
//  TinyMovableObject.cpp
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyMovableObject.h"
#include "TinyCamera.h"
#include "TinyRenderQueue.h"
#include "TinyNode.h"

namespace Tiny
{
    TinyMovableObject::TinyMovableObject(const std::string& name)
        : mParentNode(nullptr)
        , mName(name)
    {
        
    }
    
    TinyMovableObject::~TinyMovableObject()
    {
        
    }
    
    bool TinyMovableObject::isAttached()
    {
        return mParentNode != nullptr;
    }
    
    std::string& TinyMovableObject::getName()
    {
        return mName;
    }
    
    void TinyMovableObject::setName(const std::string& name)
    {
        mName = name;
    }
    
    void TinyMovableObject::notifyAttached(TinyNode* node)
    {
        mParentNode = node;
    }
}