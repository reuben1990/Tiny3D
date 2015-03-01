//
//  TinyAutoParamDataSource.h
//  proj_mac
//
//  Created by reuben chao on 2/23/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyAutoParamDataSource__
#define __proj_mac__TinyAutoParamDataSource__

#include "TinyObject.h"
#include "kazmath/kazmath.h"

namespace Tiny
{
    class TinyAutoParamDataSource : public TinyObject
    {
    public:
        void setViewMatrix(const kmMat4& mat);
        void setModelMatrix(const kmMat4& mat);
        void setProjectionMatrix(const kmMat4& mat);
        void setEyePositionModelSpace(const kmVec3& vec);
        
        const kmMat4& getViewMatrix();
        const kmMat4& getModelMatrix();
        const kmMat4& getProjectionMatrix();
        const kmVec3& getEyePositionModelSpace();
    protected:
        kmMat4 mProjMatrix;
        kmMat4 mViewMatrix;
        kmMat4 mModelMatrix;
        kmVec3 mEyePositionModelSpace;
    };
}

#endif /* defined(__proj_mac__TinyAutoParamDataSource__) */
