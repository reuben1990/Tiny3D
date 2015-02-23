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
        void setViewMatrix(kmMat4& mat);
        void setModelMatrix(kmMat4& mat);
        void setProjectionMatrix(kmMat4& mat);
    };
}

#endif /* defined(__proj_mac__TinyAutoParamDataSource__) */
