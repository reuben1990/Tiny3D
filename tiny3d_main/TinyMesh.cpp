//
//  TinyMesh.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyMesh.h"
#include "TinyMemoryAlloc.h"

namespace Tiny
{
    TinyMesh::TinyMesh(std::string& fileName)
        : mFileName(fileName)
    {
        
    }
    
    virtual TinyMesh::~TinyMesh()
    {
        auto iter = subMesh.begin();
        for (; iter != subMesh.end(); iter ++)
        {
            TINY_DELETE iter->second;
        }
    }
    
    void TinyMesh::load()
    {
        uint8* data = nullptr;//TODO load from file
        
        auto subMesh = TINY_NEW TinySubMesh(this);
        uint32 offset = 0;
        for (int i = 0; i < 1; i ++)
        {
            offset = subMesh->load(data, offset);
            mSubMeshs.push_back(subMesh);
        }
    }
    
    VectorIteratorWrapper<SubMeshList> TinyMesh::getSubmeshIterator()
    {
        return VectorIteratorWrapper<SubMeshList>(mSubMeshs.begin(), mSubMeshs.end());
    }
}