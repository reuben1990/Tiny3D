//
//  TinyShaderManager
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyGPUProgramManager.h"
#include "TinyMemoryAlloc.h"
#include <string>

namespace Tiny
{
    TinyGPUProgramManager::TinyGPUProgramManager()
    {
        
    }
    
    TinyGPUProgramManager::~TinyGPUProgramManager()
    {

    }
    
    TinyGPUProgram* TinyGPUProgramManager::load(std::string vFileName, std::string fFileName)
    {
        uint8* vData;
        uint8* fData;
        uint32 vLength;
        uint32 fLength;
        getFileData(vFileName, &vData, vLength);
        getFileData(fFileName, &fData, fLength);
        
        std::string vStrData = std::string((char*)vData);
        std::string fStrData = std::string((char*)fData);
        //TINYLOG("willrm %s", vData);
        //TINYLOG("willrm %s", fData);
        auto program = TINY_NEW TinyGPUProgram(vStrData, fStrData);
        program->load();
        return program;
    }
}
