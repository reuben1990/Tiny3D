//
//  TinySubEntity.cpp
//  proj_mac
//
//  Created by reuben chao on 2/9/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinySubEntity.h"

namespace Tiny
{
    TinySubEntity::TinySubEntity(TinySubMesh* subMesh)
    {
        mSubMesh = subMesh;
    }
    
    TinySubEntity::~TinySubEntity()
    {
        
    }
    
    void getRenderOperation(TinyRenderOperation* ro)
    {
        ro->mVertexData = mSubMesh->mVertexData;
        ro->mIndexData = mSubMesh->mIndexData;
        ro->mRenderable = this;
        ro->mMaterial = getMaterial();
        ro->mProgram = ro->mMaterial->getProgram();
    }
}