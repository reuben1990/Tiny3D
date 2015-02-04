//
//  TinyCamera.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#import "TinyCamera.h"

@implementation TinyCameraController

- (id)initWithEye:(kmVec3)eye Center:(kmVec3)center Up:(kmVec3)up
{
    self = [super init];
    if (self) {
        kmVec3Fill(&_eye, eye.x, eye.y, eye.z);
        kmVec3Fill(&_center, center.x, center.y, center.z);
        kmVec3Fill(&_up, up.x, up.y, up.z);
        _moveSpeed = 3.0;
        _rotateSpeed = 0.01;
        _fov = 45.0;
        _aspect = 4.0/3.0;
        _near = 0.1;
        _far = 1000.0;
        
        [[GSInputController sharedInputController] addEventDelegate:self];
    }
    
    return self;
}

- (kmMat4)viewMatrix
{
    kmMat4 view;
    kmMat4LookAt(&view, &_eye, &_center, &_up);
    return view;
}

- (kmMat4)perspectiveMatrix
{
    kmMat4 projection;
    kmMat4PerspectiveProjection(&projection, _fov, _aspect, _near, _far);
    return projection;
}
- (void)updateInput:(NSTimeInterval)timeInterval
{
    kmVec3 f, s, u;
    
    kmVec3Subtract(&f, &_center, &_eye);
    kmVec3Normalize(&f, &f);
    
    kmVec3Normalize(&_up, &_up);
    
    kmVec3Cross(&s, &f, &_up);
    kmVec3Normalize(&s, &s);
    
    kmVec3Cross(&u, &s, &f);
    kmVec3Normalize(&s, &s);
    
    GSInputController *inputController = [GSInputController sharedInputController];
    float delta = _moveSpeed * timeInterval;
    if ([inputController keyIsPressed:NSLeftArrowFunctionKey]
        || [inputController keyIsPressed:'a']
        || [inputController keyIsPressed:'A']) {
        kmVec3Scale(&s, &s, -delta);
        kmVec3Add(&_eye, &_eye, &s);
        kmVec3Add(&_center, &_center, &s);
    } else if ([inputController keyIsPressed:NSRightArrowFunctionKey]
               || [inputController keyIsPressed:'d']
               || [inputController keyIsPressed:'D']) {
        kmVec3Scale(&s, &s, delta);
        kmVec3Add(&_eye, &_eye, &s);
        kmVec3Add(&_center, &_center, &s);
    } else if ([inputController keyIsPressed:NSUpArrowFunctionKey]
               || [inputController keyIsPressed:'w']
               || [inputController keyIsPressed:'W']) {
        kmVec3Scale(&f, &f, delta);
        kmVec3Add(&_eye, &_eye, &f);
        kmVec3Add(&_center, &_center, &f);
    } else if ([inputController keyIsPressed:NSDownArrowFunctionKey]
               || [inputController keyIsPressed:'s']
               || [inputController keyIsPressed:'S']) {
        kmVec3Scale(&f, &f, -delta);
        kmVec3Add(&_eye, &_eye, &f);
        kmVec3Add(&_center, &_center, &f);
    }
}

- (void)mouseLeftDragWithX:(CGFloat)x andY:(CGFloat)y
{
    float thetaX = -x * _rotateSpeed;
    float thetaY = -y * _rotateSpeed;
    
    kmVec3 f, s, yawAxis, frontDir;
    
    kmVec3Subtract(&f, &_center, &_eye);
    kmVec3Normalize(&f, &f);
    kmVec3Normalize(&_up, &_up);
    kmVec3Cross(&s, &f, &_up);
    kmVec3Normalize(&s, &s);
    
    yawAxis.x = 0;
    yawAxis.y =1;
    yawAxis.z = 0;
    
    kmVec3Subtract(&frontDir, &_center, &_eye);
    
    kmQuaternion yaw, pitch;
    kmQuaternionRotationAxis(&yaw, &yawAxis, thetaX);
    kmQuaternionRotationAxis(&pitch, &s, thetaY);
    kmQuaternionMultiplyVec3(&frontDir, &pitch, &frontDir);
    kmQuaternionMultiplyVec3(&frontDir, &yaw, &frontDir);
    kmQuaternionMultiplyVec3(&_up, &pitch, &_up);
    kmQuaternionMultiplyVec3(&_up, &yaw, &_up);
    
    kmVec3Add(&_center, &_eye, &frontDir);
}

@end
