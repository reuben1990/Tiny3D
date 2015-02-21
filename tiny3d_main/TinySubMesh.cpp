//
//  TinySubMesh.cpp
//  proj_mac
//
//  Created by reuben chao on 2/9/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinySubMesh.h"
#include "TinyMesh.h"
#include "TinyMemoryAlloc.h"
#include "kazmath/kazmath.h"

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
        mVertexData->load((uint8*)vdata, sizeof(vdata), sizeof(float), VERTEX_LOCATION_POSITION);
        mIndexData->load((uint8*)idata, sizeof(idata), sizeof(uint32));
        return 0;
    }
}