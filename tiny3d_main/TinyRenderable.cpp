//
//  TinyRenderable.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyRenderable.h"

namespace Tiny
{
    TinyRenderable::TinyRenderable()
        : mMaterial(nullptr)
    {

    }
    
    virtual TinyRenderable::~TinyRenderable()
    {
        
    }
    
    void TinyEntity::setMaterial(TinyMaterial* material)
    {
        mMaterial = material;
    }
    
    TinyMaterial* TinyEntity::getMaterial()
    {
        return mMaterial;
    }
}