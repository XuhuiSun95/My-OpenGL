//
//  myGL.hpp
//  myGL
//
//  Created by Xuhui Sun on 11/10/16.
//  Copyright © 2016 Xuhui Sun. All rights reserved.
//

#ifndef myGL_hpp
#define myGL_hpp

#include <stdio.h>

void myInit(int length, int width);
void myFrustum(double left, double right, double bottom, double top, double zNear, double zFar);
void myLoadIdentity();
void myLookAt(double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ, double upX, double upY, double upZ);
void mySetBackground();
void myTranslated(double x, double y, double z);
void myScaled(double x, double y, double z);
void myRotated(double angle, double x, double y, double z);
void myBegin(gl_shape type);
void myVertex3d(double x, double y, double z);
void myEnd();
void myPushMatrix();
void myPopMatrix();
void mySwapBuffers();

#endif /* myGL_hpp */
