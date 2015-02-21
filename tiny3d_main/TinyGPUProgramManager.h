//
//  TinyShaderManager.h
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyGPUProgramManager__
#define __proj_mac__TinyGPUProgramManager__

#include "TinyResourceManager.h"
#include "TinyGPUProgram.h"
#include "TinySingleton.h"
#include <string>

namespace Tiny
{
    class TinyMeshManager;
    
    class TinyGPUProgramManager : public TinyResourceManager, public TinySingleton<TinyGPUProgramManager>
    {
    public:
        TinyGPUProgramManager();
        ~TinyGPUProgramManager();
        TinyGPUProgram* load(std::string vFileName, std::string fFileName);
    protected:
    };
}

#endif