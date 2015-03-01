//
//  TinyGPUProgram.h
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyGPUProgram__
#define __proj_mac__TinyGPUProgram__

#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
#include "TinyObject.h"
#include "TinyPlatform.h"
#include "TinyAutoParamDataSource.h"

namespace Tiny
{
    enum TinyGPUProgramParameterType
    {
        GP_FLOAT1,
        GP_FLOAT2,
        GP_FLOAT3,
        GP_FLOAT4,
        GP_INT1,
        GP_INT2,
        GP_INT3,
        GP_INT4,
        GP_MATRIX_3X3,
        GP_MATRIX_4X4,
        GP_SAMPLER,
        GP_SAMPLERCUBE,
        GP_UNDEFINE
    };
    
    class TinyGPUProgramParameter : public TinyObject
    {
    public:
        TinyGPUProgramParameter(const std::string& name,
                                TinyGPUProgramParameterType type,
                                const void* data);
        TinyGPUProgramParameter();
        virtual ~TinyGPUProgramParameter();
        TinyGPUProgramParameter& operator = (const TinyGPUProgramParameter& param);
        uint32 getDataSizeByType(TinyGPUProgramParameterType type);
        void calcLocation(GLuint program);
        
        TinyGPUProgramParameterType mType;
        std::string mName;
        void* mBindData;
        GLint mLocation;
    };
    
    class TinyGPUProgramParameters : public TinyObject
    {
    public:
        TinyGPUProgramParameters();
        ~TinyGPUProgramParameters();
        void setParameter(const TinyGPUProgramParameter& value);
        void bindParametersToProgram(GLuint program);
        void updateAutoParams(TinyAutoParamDataSource* autoPram);
    protected:
        std::map<std::string, TinyGPUProgramParameter> mParams;
    };
    
    class TinyGPUProgram : public TinyObject
    {
    public:
        TinyGPUProgram(const std::string& vs, const std::string& fs);
        ~TinyGPUProgram();
        void load();
        void useProgram();
        void setParameter(const TinyGPUProgramParameter& value);
        TinyGPUProgramParameters* getGPUProgramParameters();
        GLuint getHandler();
    protected:
        TinyGPUProgramParameters* mParams;
        GLuint mHandler;
        const std::string& mVertexShaderSource;
        const std::string& mFragmentShaderSource;
    };
}

#endif /* defined(__proj_mac__TinyGPUProgram__) */
