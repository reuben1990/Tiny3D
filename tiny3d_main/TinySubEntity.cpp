//
//  TinySubEntity.cpp
//  proj_mac
//
//  Created by reuben chao on 2/9/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinySubEntity.h"
#include "TinyEntity.h"

namespace Tiny
{
    TinySubEntity::TinySubEntity(TinyEntity* parent, TinySubMesh* subMesh)
    {
        mSubMesh = subMesh;
        mParentEntity = parent;
    }
    
    TinySubEntity::~TinySubEntity()
    {
        
    }
    
    void TinySubEntity::getRenderOperation(TinyRenderOperation* ro)
    {
        ro->mVertexObject = mSubMesh->mVertexObject;
        ro->mRenderable = this;
        ro->mMaterial = getMaterial();
        TinyGPUProgram* program = ro->mMaterial->getProgram();
        ro->mProgram = program;
    }
    
    void TinySubEntity::getModelMatrix(kmMat4& mat)
    {
        return mParentEntity->getModelMatrix(mat);
    }
}


