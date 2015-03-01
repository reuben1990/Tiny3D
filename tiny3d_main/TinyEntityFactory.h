//
//  TinyEntityFactory.h
//  proj_mac
//
//  Created by reuben chao on 2/12/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyEntityFactory__
#define __proj_mac__TinyEntityFactory__

#include <stdio.h>
#include <vector>
#include "TinyMovableObjectFactory.h"
#include "TinyMesh.h"
#include "TinySubMesh.h"
#include "TinyCommon.h"
#include "TinySubEntity.h"

namespace Tiny
{
    class TinyEntityFactory : public TinyMovableObjectFactory
    {
    public:
        virtual std::string& getType();
        static std::string mType;
        virtual TinyMovableObject* createInstanceImpl(const std::string& name, const TinyNameValuePairList& params);
    protected:
        typedef std::vector<TinySubEntity*> SubEntityArray;
        SubEntityArray mSubEntitys;
        
    };
}

#endif /* defined(__proj_mac__TinyEntityFactory__) */
