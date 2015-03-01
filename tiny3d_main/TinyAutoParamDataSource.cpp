//
//  TinyAutoParamDataSource.cpp
//  proj_mac
//
//  Created by reuben chao on 2/23/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyAutoParamDataSource.h"

namespace Tiny
{
    void TinyAutoParamDataSource::setProjectionMatrix(const kmMat4& matrix)
    {
        mProjMatrix = matrix;
    }
    
    void TinyAutoParamDataSource::setViewMatrix(const kmMat4& matrix)
    {
        mViewMatrix = matrix;
    }
    
    void TinyAutoParamDataSource::setModelMatrix(const kmMat4& matrix)
    {
        mModelMatrix = matrix;
    }
    
    void TinyAutoParamDataSource::setEyePositionModelSpace(const kmVec3 &vec)
    {
        mEyePositionModelSpace = vec;
    }
    
    const kmMat4& TinyAutoParamDataSource::getViewMatrix()
    {
        return mViewMatrix;
    }
    
    const kmMat4& TinyAutoParamDataSource::getModelMatrix()
    {
        return mModelMatrix;
    }
    
    const kmMat4& TinyAutoParamDataSource::getProjectionMatrix()
    {
        return mProjMatrix;
    }
    
    const kmVec3& TinyAutoParamDataSource::getEyePositionModelSpace()
    {
        return mEyePositionModelSpace;
    }
}