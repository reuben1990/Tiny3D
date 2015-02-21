//
//  TinyMesh.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinyMesh_h
#define proj_mac_TinyMesh_h

#include <vector>
#include <string>
#include "TinyObject.h"
#include "TinyIteratorWrapper.h"
#include "TinyPlatform.h"
#include "TinySubMesh.h"

namespace Tiny
{
    class TinyMesh : public TinyObject
    {
    public:
        typedef std::vector<TinySubMesh*> SubMeshList;
        TinyMesh(std::string& fileName);
        virtual ~TinyMesh();
        void load();
        VectorIteratorWrapper<SubMeshList, SubMeshList::iterator > getSubmeshIterator();
    public:
        SubMeshList mSubMeshs;
        std::string mFileName;
    };
}

#endif
