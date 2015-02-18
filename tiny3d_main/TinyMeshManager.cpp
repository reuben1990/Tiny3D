//
//  TinyMeshManager.cpp
//  proj_mac
//
//  Created by reuben chao on 2/13/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyMeshManager.h"
#include "TinyMemoryAlloc.h"

namespace Tiny
{
    TinyMesh* TinyMeshManager::load(std::string& fileName)
    {
        auto ret = TINY_NEW TinyMesh(fileName);
        ret->load();
        return ret;
    }
}