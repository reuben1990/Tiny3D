//
//  TinyEntityFactory.cpp
//  proj_mac
//
//  Created by reuben chao on 2/12/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyEntityFactory.h"
#include "TinyMeshManager.h"

namespace Tiny
{
    std::string TinyEntityFactory::mType = "Entity"
    
    std::string& TinyEntityFactory::getType()
    {
        return mType;
    }
    
    TinyMovableObject* TinyEntityFactory::createInstanceImpl(std::string& name, TinyNameValuePairList& params)
    {
        auto iter = params.find("mesh");
        if (iter != params.end())
        {
            TinyMesh* mesh = TinyMeshManager::getSingleton()->load(iter->second);
            return TINY_NEW TinyEntity(name, mesh);
        }
        else
        {
            assert(0 && "no mesh filename found");
        }
    }

}