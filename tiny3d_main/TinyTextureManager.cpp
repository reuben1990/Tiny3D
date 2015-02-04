//
//  TinyTextureController.cpp
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#import "GSTextureController.h"
#import "GSOpenGLInfoHelper.h"
#import <OpenGL/gl3.h>
#import <OpenGL/gl3ext.h>

unsigned long getNextPOT(unsigned long x)
{
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >>16);
    return x + 1;
}

@implementation GSTextureController

+ (GSTextureController *)sharedTextureController
{
    static GSTextureController *instance = nil;
    
    if (instance == nil) {
        instance = [[GSTextureController alloc] init];
    }
    
    return instance;
}

- (id)init
{
    self = [super init];
    if (self) {
        GSOpenGLInfoHelper *openGLInfoHelp = [GSOpenGLInfoHelper sharedOpenGLInfoHelper];
        
        if (openGLInfoHelp.openglVersion < 2.0) {
            _supportsNPOT = NO;
        } else {
            _supportsNPOT = YES;
        }
    }
    
    return self;
}

- (GLuint)cubeTextureWithFileNameArr:(NSMutableArray*)fileNameArr useMipmap:(BOOL)isMapmap
{
    //glPixelStorei(GL_UNPACK_ALIGNMENT,4);
    GLuint texObj;
    
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_CUBE_MAP);
    glGenTextures(1, &texObj);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texObj);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    if (isMapmap == NO) {
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    } else {
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    }
    
    for (int cubeIdx = 0; cubeIdx < 6; cubeIdx ++)
    {
        NSMutableArray* dataArr = [NSMutableArray arrayWithCapacity:16];
        NSMutableArray* sizeArr = [NSMutableArray arrayWithCapacity:16];
        NSString* fileName = (NSString *)fileNameArr[cubeIdx];
        [self getFileData:fileName useMipmap:isMapmap dataArr:dataArr sizeArr:sizeArr];
        int mipMapCount = (int)dataArr.count;
        for (int i = 0; i < mipMapCount; i ++)
        {
            CGSize size;
            void* data;
            [sizeArr[i] getValue:&size];
            [dataArr[i] getValue:&data];
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + cubeIdx, i, GL_RGBA, (GLsizei)size.width, (GLsizei)size.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            free(data);
        }
    }
    glDisable(GL_TEXTURE_CUBE_MAP);
    
    return texObj;
}

- (GLuint)textureWithFileName:(NSString *)fileName useMipmap:(BOOL)isMapmap
{
    //glPixelStorei(GL_UNPACK_ALIGNMENT,4);
    GLuint texObj;
    glGenTextures(1, &texObj);
    
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texObj);
    
    NSMutableArray* dataArr = [NSMutableArray arrayWithCapacity:16];
    NSMutableArray* sizeArr = [NSMutableArray arrayWithCapacity:16];
    [self getFileData:fileName useMipmap:isMapmap dataArr:dataArr sizeArr:sizeArr];
    int mipMapCount = (int)dataArr.count;
    for (int i = 0; i < mipMapCount; i ++)
    {
        CGSize size;
        void* data;
        [sizeArr[i] getValue:&size];
        [dataArr[i] getValue:&data];
        glTexImage2D(GL_TEXTURE_2D, i, GL_RGBA, (GLsizei)size.width, (GLsizei)size.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        free(data);
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (isMapmap == NO) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    
    glDisable(GL_TEXTURE_2D);
    
    return texObj;
}

- (void)getFileData:(NSString *)fileName useMipmap:(BOOL)isMapmap dataArr:(NSMutableArray*)dataArr sizeArr:(NSMutableArray*)sizeArr
{
    NSString *fullPath = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:fileName];
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if ([fileManager fileExistsAtPath:fullPath] == NO) {
        NSLog(@"%@ not exist", fullPath);
        return;
    }
    
    NSData *fileData = [[NSData alloc] initWithContentsOfFile:fullPath];
    NSBitmapImageRep *image = [[NSBitmapImageRep alloc] initWithData:fileData];
    CGImageRef cgImage = [image CGImage];
    
    CGImageAlphaInfo info = CGImageGetAlphaInfo(cgImage);
    //support NPOT
    NSUInteger textureWidth, textureHeight;
    if( self.supportsNPOT == NO )
    {
        textureWidth = getNextPOT(CGImageGetWidth(cgImage));
        textureHeight = getNextPOT(CGImageGetHeight(cgImage));
    }
    else
    {
        textureWidth = CGImageGetWidth(cgImage);
        textureHeight = CGImageGetHeight(cgImage);
    }
    CGSize imageSize = CGSizeMake(CGImageGetWidth(cgImage), CGImageGetHeight(cgImage));
    CGColorSpaceRef colorSpace = CGImageGetColorSpace(cgImage);
    BOOL hasAlpha = ((info == kCGImageAlphaPremultipliedLast) || (info == kCGImageAlphaPremultipliedFirst) || (info == kCGImageAlphaLast) || (info == kCGImageAlphaFirst) ? YES : NO);
    
    if(colorSpace) {
        if( hasAlpha ) {
            info = kCGImageAlphaPremultipliedLast;
        } else {
            info = kCGImageAlphaNoneSkipLast;
        }
    } else {
        return;
    }
    
    GLint level = 0;
    NSUInteger width = textureWidth;
    NSUInteger height = textureHeight;
    NSUInteger widthImage = imageSize.width;
    NSUInteger heightImage = imageSize.height;
    do {
        if (level > 0) {
            width /= 2;
            height /= 2;
            
            widthImage /= 2;
            if (widthImage == 0) {
                widthImage = 1;
            }
            
            heightImage /= 2;
            if (heightImage == 0) {
                heightImage = 1;
            }
        }
        
        void *data = malloc(height * width * 4);
        colorSpace = CGColorSpaceCreateDeviceRGB();
        CGContextRef context = CGBitmapContextCreate(data, width, height, 8, 4 * width, colorSpace, info | kCGBitmapByteOrder32Big);
        CGColorSpaceRelease(colorSpace);
        
        CGContextClearRect(context, CGRectMake(0, 0, width, height));
        CGContextTranslateCTM(context, 0, height - heightImage);
        CGContextDrawImage(context, CGRectMake(0, 0, widthImage, heightImage), cgImage);
        
        [dataArr addObject:[NSValue valueWithPointer:data]];
        [sizeArr addObject:[NSValue valueWithSize:CGSizeMake(width, height)]];
        
        CGContextRelease(context);
        
        if (width == 1 && height == 1) {
            break;
        }
        level++;
        
    } while (isMapmap);
}

@end
