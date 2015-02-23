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
    void TinyAutoParamDataSource::setProjectionMatrix(kmMat4& matrix)
    {
        mProjMatrix = matrix;
    }
    
    void TinyAutoParamDataSource::setViewMatrix(kmMat4& matrix)
    {
        mViewMatrix = matrix;
    }
    
    void TinyAutoParamDataSource::setModelMatrix(kmMat4& matrix)
    {
        mModelMatrix = matrix;
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
}