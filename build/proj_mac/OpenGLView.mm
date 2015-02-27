 //
//  OpenGLView.m
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include <vector>
#include <string>
#import "OpenGLView.h"
#import "TinyInputManager.h"
#include "TinyMouse.h"
#include "TinyKeyboard.h"
#include "TinyRoot.h"
#include "kazmath/kazmath.h"
#include "TinyMath.h"
#include "TinyDelegate.h"


@implementation OpenGLView

- (void) awakeFromNib
{
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
        assert(0 && "Faild create pixel format");
    }
    else
    {
        [self setPixelFormat:pixelFormat];
    }
    
    [self prepareOpenGL];
    [super update];
    [[self openGLContext] makeCurrentContext];
    [[self openGLContext] update];
    
    Tiny::TinyDelegate* delegate = Tiny::TinyDelegate::getSingleton();
    delegate->initialize();
    
    //create mouse and keyboard delegate
    Tiny::TinyInputObject *inputObject_mouse = Tiny::TinyInputManager::getSingleton()->getInputObject(Tiny::InputDevice::Mouse);
    mMouse = (Tiny::TinyMouse *)inputObject_mouse;
    Tiny::TinyInputObject *inputObject_keyboard = Tiny::TinyInputManager::getSingleton()->getInputObject(Tiny::InputDevice::Keyboard);
    mKeyBoard = (Tiny::TinyKeyboard *)inputObject_keyboard;
    
    //schedule main loop
    mTimer = [NSTimer timerWithTimeInterval:(1.0 / 60.0) target:self selector:@selector(visit:) userInfo:nil repeats:YES];
    [[NSRunLoop currentRunLoop]addTimer:mTimer forMode:NSDefaultRunLoopMode];
}

- (void)visit:(NSTimer*)timer
{
    if ([timer isEqual:mTimer] == YES)
    {
        [self drawRect:[self frame]];
    }
}

-(void)drawRect:(NSRect)dirtyRect
{
    [[self openGLContext] makeCurrentContext];
    Tiny::TinyRoot::getSingleton()->renderOneFrame([mTimer timeInterval]);
    [[self openGLContext] flushBuffer];
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

#pragma mark - keyboard and mouse event

- (void)keyDown:(NSEvent *)theEvent
{
    [super keyDown:theEvent];
    NSString *characters = [theEvent characters];
    std::string keys;
    for (NSUInteger i = 0; i < [characters length]; ++i)
    {
        unichar character = [characters characterAtIndex:i];
        Tiny::TinyKeyEvent event;
        event.mKeyCode = character;
        mKeyBoard->keyPressed(&event);
    }
    //NSLog(@"keyDown: %@", characters);
}

- (void)keyUp:(NSEvent *)theEvent
{
    [super keyUp:theEvent];
    NSString *characters = [theEvent characters];
    std::string keys;
    for (NSUInteger i = 0; i < [characters length]; ++i)
    {
        unichar character = [characters characterAtIndex:i];
        Tiny::TinyKeyEvent event;
        event.mKeyCode = character;
        mKeyBoard->keyReleased(&event);
    }
    //NSLog(@"keyUp: %@", characters);
}

- (void)mouseMoved:(NSEvent *)theEvent
{
    [super mouseMoved:theEvent];
    
    Tiny::TinyMouseEvent event;
    event.state.deltaX = [theEvent deltaX];
    event.state.deltaY = [theEvent deltaY];
    
    NSPoint location = [theEvent locationInWindow];;
    kmVec2 vec2 = Tiny::kmVec2Make(location.x, location.y);
    
    mMouse->setLocation(&vec2);
    mMouse->mouseMoved(&event);
    //NSLog(@"mouseMoved: x:%f y:%f", x, y);
}

- (void)mouseDown:(NSEvent *)theEvent
{
    [super mouseDown:theEvent];
    NSPoint location = [theEvent locationInWindow];
    Tiny::TinyMouseEvent event;
    kmVec2 vec2 = Tiny::kmVec2Make(location.x, location.y);
    mMouse->setLocation(&vec2);
    mMouse->mousePressed(&event, Tiny::TinyMouseButtonID::MB_Left);
    //NSLog(@"mouseDown: location:%f %f", location.x, location.y);
}

- (void)mouseUp:(NSEvent *)theEvent
{
    [super mouseUp:theEvent];
    NSPoint location = [theEvent locationInWindow];
    Tiny::TinyMouseEvent event;
    kmVec2 vec2 = Tiny::kmVec2Make(location.x, location.y);
    mMouse->setLocation(&vec2);
    mMouse->mouseReleased(&event, Tiny::TinyMouseButtonID::MB_Left);
    //NSLog(@"mouseUp: location:%f %f", location.x, location.y);
}

- (void)rightMouseDown:(NSEvent *)theEvent
{
    //[super rightMouseDown:theEvent];
//    NSPoint location = [theEvent locationInWindow];
//    [[TinyInputManager sharedInputController] mouseRightDown:location];
    //NSLog(@"rightMouseDown: location:%f %f", location.x, location.y);
}

- (void)rightMouseUp:(NSEvent *)theEvent
{
    //[super rightMouseUp:theEvent];
//    NSPoint location = [theEvent locationInWindow];
//    [[TinyInputManager sharedInputController] mouseRightUp:location];
    //NSLog(@"rightMouseUp: location:%f %f", location.x, location.y);
}

- (void)mouseDragged:(NSEvent *)theEvent
{
    [super mouseDragged:theEvent];
    
    Tiny::TinyMouseEvent event;
    event.state.deltaX = [theEvent deltaX];
    event.state.deltaY = [theEvent deltaY];
    
    NSPoint location = [theEvent locationInWindow];;
    kmVec2 vec2 = Tiny::kmVec2Make(location.x, location.y);
    
    mMouse->setLocation(&vec2);
    mMouse->mouseDraged(&event);
    //NSLog(@"mouseDragd: x:%f y:%f", x, y);
}

- (void)rightMouseDragged:(NSEvent *)theEvent
{
    //[super rightMouseDragged:theEvent];
//    CGFloat x = [theEvent deltaX];
//    CGFloat y = [theEvent deltaY];
//    [[TinyInputManager sharedInputController] mouseRightDragWithX:x andY:y];
    //NSLog(@"rightMouseDragged: x:%f y:%f", x, y);
}

- (void)scrollWheel:(NSEvent *)theEvent
{
    //[super scrollWheel:theEvent];
//    CGFloat x = [theEvent scrollingDeltaX];
//    CGFloat y = [theEvent scrollingDeltaY];
//    [[TinyInputManager sharedInputController] mouseScrollWithX:x andY:y];
    //NSLog(@"scrollWheel: x:%f y:%f", x, y);
}

- (void)mouseEntered:(NSEvent *)theEvent
{
    //[super mouseEntered:theEvent];
    //NSLog(@"mouseEntered");
}

- (void)mouseExited:(NSEvent *)theEvent
{
    //[super mouseExited:theEvent];
    //NSLog(@"mouseExited");
}

- (void)cursorUpdate:(NSEvent *)theEvent
{
    //[super cursorUpdate:theEvent];
    //NSLog(@"cursorUpdate");
}

@end
