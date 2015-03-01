//
//  TinyEntity.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include <stdio.h>
#include "TinyEntity.h"
#include "TinyMovableObject.h"
#include "TinyRenderQueue.h"
#include "TinySubEntity.h"
#include "TinyMesh.h"
#include "TinyMemoryAlloc.h"
#include "TinyNode.h"

namespace Tiny
{
    TinyNameGenerator TinyEntity::mNameGenerator("entity");
    
    TinyEntity::TinyEntity(const std::string& name, TinyMesh* mesh)
        : TinyMovableObject(name)
    {
        mMesh = mesh;
        initialize();
    }
    
    TinyEntity::TinyEntity(TinyMesh* mesh)
    : TinyMovableObject(mNameGenerator.generate())
    {
        mMesh = mesh;
        initialize();
    }
    
    TinyEntity::~TinyEntity()
    {
        auto iter = mSubEntitys.begin();
        for (; iter <= mSubEntitys.end(); iter ++)
        {
            TinySubEntity* subEnt = *iter;
            TINY_DELETE subEnt;
        }
    }
    
    void TinyEntity::initialize()
    {
        buildSubEntityList(mMesh, &mSubEntitys);
    }
    
    void TinyEntity::buildSubEntityList(TinyMesh* mesh, SubEntityList* list)
    {
        auto iter = mMesh->getSubmeshIterator();
        while (iter.hasMoreElements())
        {
            TinySubMesh* subMesh = iter.getNext();
            mSubEntitys.push_back(TINY_NEW TinySubEntity(this, subMesh));
        }
        
    }
    
    void TinyEntity::updateRenderQueue(TinyCamera* cam, TinyRenderQueue* queue)
    {
        auto iter = mSubEntitys.begin();
        for (; iter != mSubEntitys.end(); iter ++)
        {
            queue->addRenderable(*iter, mRenderQueueGroupID, mRenderPriority);
        }
    }
    
    void TinyEntity::setRenderQueueGroupID(uint8 groupID)
    {
        mRenderQueueGroupID = groupID;
    }
    
    void TinyEntity::setRenderPriority(uint8 priority)
    {
        mRenderPriority = priority;
    }
    
    void TinyEntity::setMaterial(TinyMaterial* material)
    {
        mMaterial = material;
        auto iter = mSubEntitys.begin();
        for (; iter != mSubEntitys.end(); iter ++)
        {
            TinySubEntity* subEnt = *iter;
            subEnt->setMaterial(mMaterial);
        }
    }
    
    void TinyEntity::getModelMatrix(kmMat4& mat)
    {
        if (mParentNode)
        {
            mParentNode->getModelMatrix(mat);
        }
    }
    
    TinySubEntity* TinyEntity::getSubEntity(uint32 index)
    {
        if (index >= mSubEntitys.size())
            assert(false && "subentity index out of range");
        return mSubEntitys[index];
    }
}



