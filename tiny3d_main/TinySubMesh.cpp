//
//  TinySubMesh.cpp
//  proj_mac
//
//  Created by reuben chao on 2/9/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include <map>
#include <vector>
#include "TinySubMesh.h"
#include "TinyMesh.h"
#include "TinyMemoryAlloc.h"
#include "kazmath/kazmath.h"

namespace Tiny
{
    TinySubMesh::TinySubMesh()
        : mVertexObject(TINY_NEW TinyVertexObject())
    {

    }
    
    TinySubMesh::~TinySubMesh()
    {
        
        TINY_DELETE mVertexObject;
    }
    
    uint32 TinySubMesh::load(uint8* data, uint32 offset)
    {
        struct ElementGroup
        {
            kmVec3 position;
            kmVec2 uv;
            kmVec3 normal;
//            bool operator == (const ElementGroup& elementGroup)
//            {
//                bool positionEqual = kmVec3AreEqual(&position, &elementGroup.position) == 1;
//                bool uvEqual = kmVec2AreEqual(&uv, &elementGroup.uv) == 1;
//                bool normalEqual = kmVec3AreEqual(&normal, &elementGroup.normal) == 1;
//                return positionEqual && uvEqual && normalEqual;
//            }
//            
//            bool operator < (const ElementGroup& elementGroup) const
//            {
//                return position.x < elementGroup.position.x;
//            }
        };
        
        std::vector<kmVec3> temp_position_pool;
        std::vector<kmVec2> temp_uv_pool;
        std::vector<kmVec3> temp_normal_pool;
        std::vector<uint32> temp_position_index;
        std::vector<uint32> temp_uv_index;
        std::vector<uint32> temp_normal_index;
        
        std::vector<kmVec3> out_position_pool;
        std::vector<kmVec2> out_uv_pool;
        std::vector<kmVec3> out_normal_pool;
        std::vector<uint32> out_index;
        
        char* rawData = (char*) data;
        const char* delim = "\r\n";
        char* line = nullptr;
        uint32 triangleCnt = 0;
        while (true)
        {
            char* src = line == nullptr ? rawData : nullptr;
            line = strtok(src, delim);
            if (not line)
                break;
            char headWord[128];
            sscanf(line, "%s", headWord);
            size_t offset = strlen(headWord) + 1;
            line += offset;
            
            if (strcmp(headWord, "v") == 0)
            {
                kmVec3 v;
                sscanf(line, "%f %f %f", &v.x, &v.y, &v.z);
                temp_position_pool.push_back(v);
            }
            if (strcmp(headWord, "vt") == 0)
            {
                kmVec2 vt;
                sscanf(line, "%f %f", &vt.x, &vt.y);
                temp_uv_pool.push_back(vt);
            }
            if (strcmp(headWord, "vn") == 0)
            {
                kmVec3 vn;
                sscanf(line, "%f %f %f", &vn.x, &vn.y, &vn.z);
                temp_normal_pool.push_back(vn);
            }
            if (strcmp(headWord, "f") == 0)
            {
                for (int i = 0; i < 3; i ++)
                {
                    temp_position_index.push_back(0);
                    temp_uv_index.push_back(0);
                    temp_normal_index.push_back(0);
                }
                sscanf(line, "%d/%d/%d %d/%d/%d %d/%d/%d"
                       , &temp_position_index[triangleCnt * 3]
                       , &temp_uv_index[triangleCnt * 3]
                       , &temp_normal_index[triangleCnt * 3]
                       , &temp_position_index[triangleCnt * 3 + 1]
                       , &temp_uv_index[triangleCnt * 3 + 1]
                       , &temp_normal_index[triangleCnt * 3 + 1]
                       , &temp_position_index[triangleCnt * 3 + 2]
                       , &temp_uv_index[triangleCnt * 3 + 2]
                       , &temp_normal_index[triangleCnt * 3 + 2]);
                
                ++ triangleCnt;
            }
        }
//        std::map<ElementGroup, uint32> elementPool;
//        size_t vertexCnt = triangleCnt * 3;
//        uint32 elementPoolCnt = 0;
//        for (int i = 0; i < vertexCnt; ++ i)
//        {
//            auto elementGroup = ElementGroup();
//            elementGroup.position = temp_position_pool[temp_position_index[i]];
//            elementGroup.uv = temp_uv_pool[temp_uv_index[i]];
//            elementGroup.normal = temp_normal_pool[temp_normal_index[i]];
//            auto iter = elementPool.find(elementGroup);
//            if (iter != elementPool.end())
//            {
//                out_index.push_back(iter->second);
//            }
//            else
//            {
//                uint32 index = elementPoolCnt ++;
//                elementPool.insert(std::map<ElementGroup, uint32>::value_type(elementGroup, index));
//                out_index.push_back(index);
//            }
//        }
        
        size_t vertexCnt = triangleCnt * 3;
        uint32 index = 0;
        for (int i = 0; i < vertexCnt; ++ i)
        {
            out_position_pool.push_back(temp_position_pool[temp_position_index[i] - 1]);
            out_uv_pool.push_back(temp_uv_pool[temp_uv_index[i] - 1]);
            out_normal_pool.push_back(temp_normal_pool[temp_normal_index[i] - 1]);
            out_index.push_back(index ++);
        }
        
        uint32 positionPoolLen = (uint32)(sizeof(kmVec3) * out_position_pool.size());
        uint32 uvPoolLen = (uint32)(sizeof(kmVec2) * out_uv_pool.size());
        uint32 normalPoolLen = (uint32)(sizeof(kmVec3) * out_normal_pool.size());
        uint32 indexPoolLen = (uint32)(sizeof(uint32) * out_index.size());
        
        mVertexObject->loadVertexElement((uint8*)&out_position_pool[0], positionPoolLen, 3, VERTEX_LOCATION_POSITION);
        mVertexObject->loadVertexElement((uint8*)&out_uv_pool[0], uvPoolLen, 2, VERTEX_LOCATION_UV);
        mVertexObject->loadVertexElement((uint8*)&out_normal_pool[0], normalPoolLen, 3, VERTEX_LOCATION_NORMAL);
        mVertexObject->loadIndexElement((uint8*)&out_index[0], indexPoolLen, (uint32)out_index.size());
        return 0;
    }
}