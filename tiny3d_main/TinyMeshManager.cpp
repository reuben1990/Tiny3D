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
        uint8* data;
        uint32 length;
        getFileData(fileName, &data, length);
        
        auto ret = TINY_NEW TinyMesh();
        ret->load(data);
        free(data);
        return ret;
    }
}