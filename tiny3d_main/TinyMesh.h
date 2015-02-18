//
//  TinyMesh.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinyMesh_h
#define proj_mac_TinyMesh_h

#include "TinyObject.h"
#include "TinySubMesh.h"
#include <vector>
#include "TinyIteratorWrapper.h"
#include <string>
#include "TinyPlatform.h"

namespace Tiny
{
    typedef std::vector<TinySubMesh*> SubMeshList;
    class TinyMesh : public TinyObject
    {
    public:
        TinyMesh(std::string& fileName);
        virtual ~TinyMesh();
        void load();
        VectorIteratorWrapper<SubMeshList, std::vector<TinySubMesh*>::iterator > getSubmeshIterator();
    public:
        SubMeshList mSubMeshs;
        std::string mFileName;
    };
}

#endif
