//
//  TinySubMesh.cpp
//  proj_mac
//
//  Created by reuben chao on 2/9/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinySubMesh.h"

namespace Tiny
{
    TinySubMesh::TinySubMesh()
    {
        mVertexData = TINY_NEW TinyVertexData();
        mIndexData = TINY_NEW TinyIndexData();
    }
    
    TinySubMesh::~TinySubMesh()
    {
        TINY_DELETE mVertexData;
        TINY_DELETE mIndexData;
    }
    
    uint32 TinySubMesh::load(uint8* data, uint32 offset)
    {
        //TODO
        kmVec3 vdata[] =
        {
            {0, 1, 0},
            {0, 0, 0},
            {1, 0, 0}
        };
        GLushort idata[] = {0, 1, 2};
        mVertexData->load(vdata, sizeof(vdata), VERTEX_LOCATION_POSITION);
        mIndexData->load(idata, sizeof(idata));
    }
}