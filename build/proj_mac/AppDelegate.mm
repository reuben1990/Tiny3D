//
//  AppDelegate.m
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#import "AppDelegate.h"
#import "OpenGLView.h"
#include "TinyRoot.h"
#include "TinyDelegate.h"

static AppDelegate* sDelegate = nil;

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    sDelegate = self;
    Tiny::TinyDelegate* delegate = Tiny::TinyDelegate::getSingleton();
    delegate->initialize();
    mTimer = [NSTimer timerWithTimeInterval:(1.0 / 60.0) target:self selector:@selector(visit:) userInfo:nil repeats:YES];
    [[NSRunLoop currentRunLoop]addTimer:mTimer forMode:NSDefaultRunLoopMode];
}

+ (AppDelegate*)sharedDelegate
{
    return sDelegate;
}

- (void)visit:(NSTimer*)timer
{
    if ([timer isEqual:mTimer] == YES)
    {
        Tiny::TinyRoot::getSingleton()->renderOneFrame([mTimer timeInterval]);
    }
}

- (OpenGLView*)createGLView:(NSInteger)width height:(NSInteger)height
{
    OpenGLView* glView = nullptr;
    NSOpenGLPixelFormatAttribute attributes[] = {
        NSOpenGLPFAColorSize, 32,
        NSOpenGLPFADepthSize, 16,
        NSOpenGLPFAStencilSize, 8,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        0
    };
    
    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
    if (pixelFormat == nil)
    {
        NSLog(@"Faild create pixel format");
    }
    else
    {
        //TODO ignore width height now.
        glView = [[OpenGLView alloc] initWithFrame:self.window.frame pixelFormat:pixelFormat];
    }
    [self.window setContentView:glView];
    return glView;
}


- (void)applicationWillTerminate:(NSNotification *)aNotification
{
    
}

@end
