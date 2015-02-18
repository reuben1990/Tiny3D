//
//  TinyShaderManager
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyGPUProgramManager.h"
#include <string>

namespace Tiny
{
    TinyGPUProgramManager::TinyGPUProgramManager()
    {
        
    }
    
    TinyGPUProgramManager::~TinyGPUProgramManager()
    {

    }
    
    TinyGPUProgram* TinyGPUProgramManager::load(std::string& vFileName, std::string& fFileName)
    {
        uint8* vData, fData;
        uint32 vLength, fLength;
        getFileData(vFileName, &vData, vLength);
        getFileData(fFileName, &fData, fLength);
        
        std::string vStrData = vData;
        std::string fStrData = fData;
        auto program = TINY_NEW TinyGPUProgram(vStrData, fStrData);
        program->load();
        return program;
    }
}
