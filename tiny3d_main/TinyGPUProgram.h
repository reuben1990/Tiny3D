//
//  TinyGPUProgram.h
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyGPUProgram__
#define __proj_mac__TinyGPUProgram__

#include <stdio.h>
#include "TinyObject.h"
#include <string>
#include <map>

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
        GP_MATRIX_2X2,
        GP_MATRIX_3X3,
        GP_MATRIX_4X4,
        GP_SAMPLER,
        GP_SAMPLERCUBE
    };
    
    class TinyGPUProgramParameter : public TinyObject
    {
    public:
        void calcLocation(GLuint program);
        std::string mName;
        TinyGPUProgramParameterType mType;
        GLint mLocation;
        void* mBindData;
    };
    
    class TinyGPUProgramParameters : public TinyObject
    {
    public:
        TinyGPUProgramParameters()
        ~TinyGPUProgramParameters();
        void setParameter(const TinyGPUProgramParameter& value);
        void bindParametersToProgram(GLuint program);
    protected:
        std::map<std::string, TinyGPUProgramParameter> mParams;
    };
    
    class TinyGPUProgram : public TinyObject
    {
    public:
        TinyGPUProgram(std::string& vs, std::string& fs);
        ~TinyGPUProgram();
        void load();
        void useProgram();
        void setParameter(const TinyGPUProgramParameter& value);
        GLuint getHandler();
    protected:
        TinyGPUProgramParameters* mParams;
        GLuint mHandler;
        std::string& mVertexShaderSource;
        std::string& mFragmentShaderSource;
    };
}

#endif /* defined(__proj_mac__TinyGPUProgram__) */
