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
    
    TinyMesh::~TinyMesh()
    {
        auto iter = mSubMeshs.begin();
        for (; iter != mSubMeshs.end(); iter ++)
        {
            TinySubMesh* subMesh = *iter;
            TINY_DELETE subMesh;
        }
    }
    
    void TinyMesh::load()
    {
        uint8* data = nullptr;//TODO load from file
        
        TinySubMesh* subMesh = TINY_NEW TinySubMesh();
        uint32 offset = 0;
        for (int i = 0; i < 1; i ++)
        {
            offset = subMesh->load(data, offset);
            mSubMeshs.push_back(subMesh);
        }
    }
    
    VectorIteratorWrapper<TinyMesh::SubMeshList, TinyMesh::SubMeshList::iterator> TinyMesh::getSubmeshIterator()
    {
        return VectorIteratorWrapper<SubMeshList, SubMeshList::iterator>(mSubMeshs.begin(), mSubMeshs.end());
    }
}