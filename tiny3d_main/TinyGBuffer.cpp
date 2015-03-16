//
//  TinyGBuffer.cpp
//  proj_mac
//
//  Created by reuben chao on 3/17/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyGBuffer.h"

namespace Tiny
{
    TinyGBuffer::TinyGBuffer(uint32 width, uint32 height)
    : TinyRenderTarget(width, height)
    {
        mPriority = TINY_REND_TO_GBUFFER_RT_GROUP;
        
        setupFBO();
    }
    
    TinyGBuffer::~TinyGBuffer()
    {
        
    }
    
    void TinyGBuffer::createGBufTex( GLenum texUnit, GLenum format, GLuint &texid ) {
        glActiveTexture(texUnit);
        glGenTextures(1, &texid);
        glBindTexture(GL_TEXTURE_2D, texid);
        glTexStorage2D(GL_TEXTURE_2D, 1, format, mWidth, mHeight);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    
    void TinyGBuffer::setupFBO()
    {
        GLuint depthBuf, posTex, normTex, colorTex;
        
        // Create and bind the FBO
        glGenFramebuffers(1, &mFbo);
        glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
        
        // The depth buffer
        glGenRenderbuffers(1, &depthBuf);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuf);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, mWidth, mHeight);
        
        // Create the textures for position, normal and color
        createGBufTex(GL_TEXTURE0, GL_RGB32F, posTex);  // Position
        createGBufTex(GL_TEXTURE1, GL_RGB32F, normTex); // Normal
        createGBufTex(GL_TEXTURE2, GL_RGB8, colorTex);  // Color
        
        // Attach the textures to the framebuffer
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuf);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, posTex, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normTex, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, colorTex, 0);
        
        GLenum drawBuffers[] = {GL_NONE, GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,
            GL_COLOR_ATTACHMENT2};
        glDrawBuffers(4, drawBuffers);
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

}