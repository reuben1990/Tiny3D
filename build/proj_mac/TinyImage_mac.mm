//
//  TinyImage.cpp
//  proj_mac
//
//  Created by reuben chao on 2/19/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyImage.h"
#include "TinyResourceManager.h"
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include "kazmath/kazmath.h"

namespace Tiny
{
    void TinyImage::initWithData(uint8* data, uint32 length, bool isMipmap)
    {
        mIsMipmap = isMipmap;
        NSData* fileData = [NSData dataWithBytes: data   length : length];
        NSBitmapImageRep *image = [[NSBitmapImageRep alloc] initWithData:fileData];
        CGImageRef cgImage = [image CGImage];
        
        CGImageAlphaInfo info = CGImageGetAlphaInfo(cgImage);
        //support NPOT
        NSUInteger textureWidth, textureHeight;
        textureWidth = CGImageGetWidth(cgImage);
        textureHeight = CGImageGetHeight(cgImage);
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
            
            mDataList.push_back((uint8*)data);
            kmVec2 size;
            kmVec2Fill(&size, width, height);
            mSizeList.push_back(size);
            
            CGContextRelease(context);
            
            if (width == 1 && height == 1) {
                break;
            }
            level++;
            
        } while (isMipmap);
    }
}