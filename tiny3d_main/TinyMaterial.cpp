//
//  TinyMaterial.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyMaterial.h"

namespace Tiny
{
    TinyMaterial::TinyMaterial()
        : mIsTransParent(false);
        : mProgram(nullptr)
    {
        
    }
    
    TinyMaterial::~TinyMaterial()
    {
        if (mProgram != nullptr)
        {
            TINY_DELETE mProgram;
        }
    }
    
    bool TinyMaterial::isTransParent()
    {
        return mIsTransParent;
    }
    
    void TinyMaterial::setProgram(TinyGPUProgram* program)
    {
        if (mProgram != nullptr)
        {
            TINY_DELETE mProgram;
        }
        mProgram = program;
    }
    
    TinyGPUProgram* TinyMaterial::getProgram()
    {
        return mProgram;
    }
}