//
//  main.cpp
//  myGL
//
//  Created by Xuhui Sun on 11/10/16.
//  Copyright © 2016 Xuhui Sun. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "primitive.hpp"
#include "myGL.hpp"
using namespace std;

void drawCube (double length, double height, double depth)
{
    // FRONT
    myBegin(POLYGON);
    myVertex3d(  0.5*length, -0.5*height, 0.5*depth );
    myVertex3d(  0.5*length,  0.5*height, 0.5*depth );
    myVertex3d( -0.5*length,  0.5*height, 0.5*depth );
    myVertex3d( -0.5*length, -0.5*height, 0.5*depth );
    myEnd();
    
    // BACK
    myBegin(POLYGON);
    myVertex3d(  0.5*length, -0.5*height, -0.5*depth );
    myVertex3d(  0.5*length,  0.5*height, -0.5*depth );
    myVertex3d( -0.5*length,  0.5*height, -0.5*depth);
    myVertex3d( -0.5*length, -0.5*height, -0.5*depth );
    myEnd();
    
    // RIGHT
    myBegin(POLYGON);
    myVertex3d( 0.5*length, -0.5*height, -0.5*depth );
    myVertex3d( 0.5*length,  0.5*height, -0.5*depth );
    myVertex3d( 0.5*length,  0.5*height,  0.5*depth );
    myVertex3d( 0.5*length, -0.5*height,  0.5*depth );
    myEnd();
    
    // LEFT
    myBegin(POLYGON);
    myVertex3d( -0.5*length, -0.5*height,  0.5*depth );
    myVertex3d( -0.5*length,  0.5*height,  0.5*depth );
    myVertex3d( -0.5*length,  0.5*height, -0.5*depth );
    myVertex3d( -0.5*length, -0.5*height, -0.5*depth );
    myEnd();
    
    // TOP
    myBegin(POLYGON);
    myVertex3d(  0.5*length,  0.5*height,  0.5*depth );
    myVertex3d(  0.5*length,  0.5*height, -0.5*depth );
    myVertex3d( -0.5*length,  0.5*height, -0.5*depth );
    myVertex3d( -0.5*length,  0.5*height,  0.5*depth );
    myEnd();
    
    // BOTTOM
    myBegin(POLYGON);
    myVertex3d(  0.5*length, -0.5*height, -0.5*depth );
    myVertex3d(  0.5*length, -0.5*height,  0.5*depth );
    myVertex3d( -0.5*length, -0.5*height,  0.5*depth );
    myVertex3d( -0.5*length, -0.5*height, -0.5*depth );
    myEnd();
}

void drawCurve(float radian, float radius, float width, float depth, float samplingRate)
{
    // FRONT
    myBegin(QUAD_STRIP);
    for(int i=0; i<samplingRate; i++) {
        myVertex3d(-(radius-width)*cosf(i*radian/samplingRate), (radius-width)*sinf(i*radian/samplingRate), 0.5*depth);
        myVertex3d(-radius*cosf(i*radian/samplingRate), radius*sinf(i*radian/samplingRate), 0.5*depth);
        myVertex3d(-(radius-width)*cosf((i+1)*radian/samplingRate), (radius-width)*sinf((i+1)*radian/samplingRate), 0.5*depth);
        myVertex3d(-radius*cosf((i+1)*radian/samplingRate), radius*sinf((i+1)*radian/samplingRate), 0.5*depth);
    }
    myEnd();
    
    // BACK
    myBegin(QUAD_STRIP);
    for(int i=0; i<samplingRate; i++) {
        myVertex3d(-(radius-width)*cosf(i*radian/samplingRate), (radius-width)*sinf(i*radian/samplingRate), -0.5*depth);
        myVertex3d(-radius*cosf(i*radian/samplingRate), radius*sinf(i*radian/samplingRate), -0.5*depth);
        myVertex3d(-(radius-width)*cosf((i+1)*radian/samplingRate), (radius-width)*sinf((i+1)*radian/samplingRate), -0.5*depth);
        myVertex3d(-radius*cosf((i+1)*radian/samplingRate), radius*sinf((i+1)*radian/samplingRate), -0.5*depth);
        
    }
    myEnd();
    
    // LEFT
    myBegin(POLYGON);
    myVertex3d(-radius, 0.0 , -0.5*depth);
    myVertex3d(-radius, 0.0 , 0.5*depth);
    myVertex3d(-(radius-width), 0.0, 0.5*depth);
    myVertex3d(-(radius-width), 0.0, -0.5*depth);
    myEnd();
    
    // RIGHT
    myBegin(POLYGON);
    myVertex3d(-radius*cosf(radian), radius*sinf(radian), 0.5*depth);
    myVertex3d(-radius*cosf(radian), radius*sinf(radian), -0.5*depth);
    myVertex3d(-(radius-width)*cosf(radian), (radius-width)*sinf(radian), -0.5*depth);
    myVertex3d(-(radius-width)*cosf(radian), (radius-width)*sinf(radian), 0.5*depth);
    myEnd();
    
    // TOP
    myBegin(QUAD_STRIP);
    for(int i=0; i<samplingRate; i++) {
        myVertex3d(-radius*cosf(i*radian/samplingRate), radius*sinf(i*radian/samplingRate), 0.5*depth);
        myVertex3d(-radius*cosf(i*radian/samplingRate), radius*sinf(i*radian/samplingRate), -0.5*depth);
        myVertex3d(-radius*cosf((i+1)*radian/samplingRate), radius*sinf((i+1)*radian/samplingRate), 0.5*depth);
        myVertex3d(-radius*cosf((i+1)*radian/samplingRate), radius*sinf((i+1)*radian/samplingRate), -0.5*depth);
    }
    myEnd();
    
    // BOTTOM
    myBegin(QUAD_STRIP);
    for(int i=0; i<samplingRate; i++) {
        myVertex3d(-(radius-width)*cosf(i*radian/samplingRate), (radius-width)*sinf(i*radian/samplingRate), -0.5*depth);
        myVertex3d(-(radius-width)*cosf(i*radian/samplingRate), (radius-width)*sinf(i*radian/samplingRate), 0.5*depth);
        myVertex3d(-(radius-width)*cosf((i+1)*radian/samplingRate), (radius-width)*sinf((i+1)*radian/samplingRate), -0.5*depth);
        myVertex3d(-(radius-width)*cosf((i+1)*radian/samplingRate), (radius-width)*sinf((i+1)*radian/samplingRate), 0.5*depth);
    }
    myEnd();
    
}

void drawLetter(char c)
{
    switch (c) {
        case 'a':
            drawCube(0.2, 0.08, 0.05);
            myPushMatrix();
            myTranslated(-0.115, 0.0, 0.0);
            myRotated(70.0, 0.0, 0.0, 1.0);
            drawCube(0.7, 0.08, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.115, 0.0, 0.0);
            myRotated(-70.0, 0.0, 0.0, 1.0);
            drawCube(0.7, 0.08, 0.05);
            myPopMatrix();
            break;
        case 'b':
            myPushMatrix();
            myTranslated(-0.18, 0.0, 0.0);
            myScaled(2.0, 1.0, 1.0);
            drawCube(0.06, 0.8, 0.05);
            myPushMatrix();
            myTranslated(0.0, 0.18, 0.0);
            myRotated(-90, 0.0, 0.0, 1.0);
            drawCurve(M_PI, 0.22, 0.08, 0.05, 20.0);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.0, -0.18, 0.0);
            myRotated(-90, 0.0, 0.0, 1.0);
            drawCurve(M_PI, 0.22, 0.08, 0.05, 20.0);
            myPopMatrix();
            myPopMatrix();
            break;
        case 'd':
            myPushMatrix();
            myTranslated(-0.18, 0.0, 0.0);
            drawCube(0.08, 0.8, 0.05);
            myPushMatrix();
            myRotated(-90, 0.0, 0.0, 1.0);
            drawCurve(M_PI, 0.4, 0.08, 0.05, 20.0);
            myPopMatrix();
            myPopMatrix();
            break;
        case 'e':
            drawCube(0.4, 0.08, 0.05);
            myPushMatrix();
            myTranslated(0.0, 0.36, 0.0);
            drawCube(0.4, 0.08, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.0, -0.36, 0.0);
            drawCube(0.4, 0.08, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(-0.16, 0.0, 0.0);
            drawCube(0.08, 0.8, 0.05);
            myPopMatrix();
            break;
        case 'f':
            drawCube(0.4, 0.08, 0.05);
            myPushMatrix();
            myTranslated(0.0, 0.36, 0.0);
            drawCube(0.4, 0.08, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(-0.16, 0.0, 0.0);
            drawCube(0.08, 0.8, 0.05);
            myPopMatrix();
            break;
        case 'h':
            drawCube(0.5, 0.08, 0.05);
            myPushMatrix();
            myTranslated(-0.21, 0.0, 0.0);
            drawCube(0.08, 0.8, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.21, 0.0, 0.0);
            drawCube(0.08, 0.8, 0.05);
            myPopMatrix();
            break;
        case 'i':
            drawCube(0.1, 0.8, 0.05);
            myPushMatrix();
            myTranslated(0.0, 0.36, 0.0);
            drawCube(0.3, 0.08, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.0, -0.36, 0.0);
            drawCube(0.3, 0.08, 0.05);
            myPopMatrix();
            break;
        case 'k':
            myPushMatrix();
            myTranslated(-0.16, 0.0, 0.0);
            drawCube(0.1, 0.8, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.04, 0.15, 0.0);
            myRotated(-45.0, 0.0, 0.0, 1.0);
            drawCube(0.1, 0.6, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.04, -0.15, 0.0);
            myRotated(45.0, 0.0, 0.0, 1.0);
            drawCube(0.1, 0.6, 0.05);
            myPopMatrix();
            break;
        case 'l':
            myPushMatrix();
            myTranslated(-0.2, 0.0, 0.0);
            drawCube(0.1, 0.8, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.0, -0.35, 0.0);
            drawCube(0.5, 0.1, 0.05);
            myPopMatrix();
            break;
        case 'm':
            myPushMatrix();
            myTranslated(-0.27, 0.0, 0.0);
            drawCube(0.1, 0.8, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(-0.125, 0.0, 0.0);
            myRotated(20.0, 0.0, 0.0, 1.0);
            drawCube(0.1, 0.78, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.125, 0.0, 0.0);
            myRotated(-20.0, 0.0, 0.0, 1.0);
            drawCube(0.1, 0.78, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.27, 0.0, 0.0);
            drawCube(0.1, 0.8, 0.05);
            myPopMatrix();
            break;
        case 'n':
            myPushMatrix();
            myRotated(27.0, 0.0, 0.0, 1.0);
            drawCube(0.1, 0.83, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(-0.2, 0.0, 0.0);
            drawCube(0.1, 0.8, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.2, 0.0, 0.0);
            drawCube(0.1, 0.8, 0.05);
            myPopMatrix();
            break;
        case 0:
            myScaled(0.5, 1.0, 1.0);
            drawCurve(2*M_PI, 0.4, 0.1, 0.05, 20.0);
            break;
        case 1:
            drawCube(0.1, 0.8, 0.05);
            myPushMatrix();
            myTranslated(0.0, -0.36, 0.0);
            drawCube(0.3, 0.08, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(-0.05, 0.4-0.1/cosf(M_PI/6), 0.0);
            myRotated(60.0, 0.0, 0.0, 1.0);
            drawCube(0.2, 0.2*tanf(M_PI/6), 0.05);
            myPopMatrix();
            break;
        case 2:
            myPushMatrix();
            myTranslated(0.0, 0.2, 0.0);
            drawCurve(6*M_PI/5, 0.2, 0.08, 0.05, 20.0);
            myPopMatrix();
            myPushMatrix();
            myTranslated(-0.02, -0.12, 0.0);
            myRotated(56.0, 0.0, 0.0, 1.0);
            drawCube(0.54, 0.08, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.0, -0.36, 0.0);
            drawCube(0.4, 0.08, 0.05);
            myPopMatrix();
            break;
        case 3:
            drawCube(0.12, 0.08, 0.05);
            myPushMatrix();
            myTranslated(0.0, 0.18, 0.0);
            drawCurve(3*M_PI/2, 0.22, 0.08, 0.05, 20.0);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.0, -0.18, 0.0);
            myRotated(-90, 0.0, 0.0, 1.0);
            drawCurve(3*M_PI/2, 0.22, 0.08, 0.05, 20.0);
            myPopMatrix();
            break;
        case 4:
            myPushMatrix();
            myTranslated(0.05, 0.0, 0.0);
            drawCube(0.1, 0.8, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.0, -0.1, 0.0);
            drawCube(0.5, 0.08, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(-0.09, 0.15, 0.0);
            myRotated(61.0, 0.0, 0.0, 1.0);
            drawCube(0.52, 0.08, 0.05);
            myPopMatrix();
            break;
        case 5:
            myPushMatrix();
            myTranslated(0.0, 0.36, 0.0);
            drawCube(0.4, 0.08, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(-0.18, 0.2, 0.0);
            drawCube(0.08, 0.4, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(-0.10, 0.0, 0.0);
            drawCube(0.24, 0.08, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.0, -0.18, 0.0);
            myRotated(-90, 0.0, 0.0, 1.0);
            drawCurve(3*M_PI/2, 0.22, 0.08, 0.05, 20.0);
            myPopMatrix();
            break;
        case 6:
            myPushMatrix();
            myTranslated(-0.04, 0.1, 0.0);
            myRotated(60.0, 0.0, 0.0, 1.0);
            drawCube(0.55, 0.08, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.0, -0.18, 0.0);
            drawCurve(2*M_PI, 0.22, 0.08, 0.05, 20.0);
            myPopMatrix();
            break;
        case 7:
            myPushMatrix();
            myTranslated(0.0, 0.36, 0.0);
            drawCube(0.4, 0.08, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.01, 0.01, 0.0);
            myRotated(65, 0.0, 0.0, 1.0);
            drawCube(0.7, 0.08, 0.05);
            myPopMatrix();
            break;
        case 8:
            myPushMatrix();
            myTranslated(0.0, 0.18, 0.0);
            drawCurve(2*M_PI, 0.22, 0.08, 0.05, 20.0);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.0, -0.18, 0.0);
            drawCurve(2*M_PI, 0.22, 0.08, 0.05, 20.0);
            myPopMatrix();
            break;
        case 9:
            myPushMatrix();
            myTranslated(0.04, -0.1, 0.0);
            myRotated(60.0, 0.0, 0.0, 1.0);
            drawCube(0.55, 0.08, 0.05);
            myPopMatrix();
            myPushMatrix();
            myTranslated(0.0, 0.18, 0.0);
            drawCurve(2*M_PI, 0.22, 0.08, 0.05, 20.0);
            myPopMatrix();
            break;
            
        default:
            break;
    }
}

void drawBlock(float length, float height, float depth, char front, char back, char top , char bot, char left, char right)
{
    //draw inner cube
    drawCube(0.9*length, 0.9*height, 0.9*depth);
    
    //draw edges
    myPushMatrix();
    myTranslated(0.0, 0.475*height, 0.475*depth);
    drawCube(1.0*length, 0.05*height, 0.05*depth);
    myPopMatrix();
    
    myPushMatrix();
    myTranslated(0.0, -0.475*height, 0.475*depth);
    drawCube(1.0*length, 0.05*height, 0.05*depth);
    myPopMatrix();
    
    myPushMatrix();
    myTranslated(0.0, 0.475*height, -0.475*depth);
    drawCube(1.0*length, 0.05*height, 0.05*depth);
    myPopMatrix();
    
    myPushMatrix();
    myTranslated(0.0, -0.475*height, -0.475*depth);
    drawCube(1.0*length, 0.05*height, 0.05*depth);
    myPopMatrix();
    
    myPushMatrix();
    myTranslated(0.475*length, 0.0, 0.475*depth);
    drawCube(0.05*length, 1.0*height, 0.05*depth);
    myPopMatrix();
    
    myPushMatrix();
    myTranslated(-0.475*length, 0.0, 0.475*depth);
    drawCube(0.05*length, 1.0*height, 0.05*depth);
    myPopMatrix();
    
    myPushMatrix();
    myTranslated(-0.475*length, 0.0, -0.475*depth);
    drawCube(0.05*length, 1.0*height, 0.05*depth);
    myPopMatrix();
    
    myPushMatrix();
    myTranslated(0.475*length, 0.0, -0.475*depth);
    drawCube(0.05*length, 1.0*height, 0.05*depth);
    myPopMatrix();
    
    myPushMatrix();
    myTranslated(0.475*length, 0.475*height, 0.0);
    drawCube(0.05*length, 0.05*height, 1.0*depth);
    myPopMatrix();
    
    myPushMatrix();
    myTranslated(-0.475*length, 0.475*height, 0.0);
    drawCube(0.05*length, 0.05*height, 1.0*depth);
    myPopMatrix();
    
    myPushMatrix();
    myTranslated(0.475*length, -0.475*height, 0.0);
    drawCube(0.05*length, 0.05*height, 1.0*depth);
    myPopMatrix();
    
    myPushMatrix();
    myTranslated(-0.475*length, -0.475*height, 0.0);
    drawCube(0.05*length, 0.05*height, 1.0*depth);
    myPopMatrix();

    // FRONT
    myPushMatrix();
    myTranslated(0.0, 0.0, 0.475*depth);
    myScaled(length, height, depth);
    drawLetter(front);
    myPopMatrix();
    
    // BACK
    myPushMatrix();
    myTranslated(0.0, 0.0, -0.475*depth);
    myRotated(180.0, 0.0, 1.0, 0.0);
    myScaled(length, height, depth);
    drawLetter(back);
    myPopMatrix();
    
    // TOP
    myPushMatrix();
    myTranslated(0.0, 0.475*height, 0.0);
    myRotated(-90.0, 1.0, 0.0, 0.0);
    myScaled(length, height, depth);
    drawLetter(top);
    myPopMatrix();
    
    // BOTTOM
    myPushMatrix();
    myTranslated(0.0, -0.475*height, 0.0);
    myRotated(90.0, 1.0, 0.0, 0.0);
    myScaled(length, height, depth);
    drawLetter(bot);
    myPopMatrix();
    
    // LEFT
    myPushMatrix();
    myTranslated(-0.475*length, 0.0, 0.0);
    myRotated(90.0, 0.0, -1.0, 0.0);
    myScaled(length, height, depth);
    drawLetter(left);
    myPopMatrix();
    
    // RIGHT
    myPushMatrix();
    myTranslated(0.475*length, 0.0, 0.0);
    myRotated(90.0, 0.0, 1.0, 0.0);
    myScaled(length, height, depth);
    drawLetter(right);
    myPopMatrix();
}

void init(void)
{
    myInit(500, 500);
    myFrustum(-1.0, 1.0, -1.0, 1.0, -1.5, -20.0);
}

void display(void)
{
    myLoadIdentity();
    myLookAt(0.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    myScaled(0.15,0.15,0.15);
    
    for(int i = 0; i < 200; i++){
        mySetBackground();
        
        // Blocks
        myPushMatrix();
        myTranslated(-5.0, 0.0, 0.0);
        myRotated(45.0+2*i, 0.0, 1.0, 0.0);
        drawBlock(1.0, 1.0, 1.0, 'a', 3, 6, 8, 'h', 'i');
        myPopMatrix();
        
        myPushMatrix();
        myTranslated(-2.5, 0.0, 0.0);
        myRotated(30.0-2*i, 0.0, 1.0, 0.0);
        drawBlock(1.0, 1.0, 1.0, 4, 1, 9, 'b', 'd', 0);
        myPopMatrix();
        
        myPushMatrix();
        myRotated(2*i, 0.0, 1.0, 0.0);
        drawBlock(1.0, 1.0, 1.0, 'k', 5, 'l', 2, 'e', 'f');
        myPopMatrix();
        
        myPushMatrix();
        myTranslated(2.5, 0.0, 0.0);
        myRotated(-30.0-2*i, 0.0, 1.0, 0.0);
        drawBlock(1.0, 1.0, 1.0, 1, 6, 2, 4, 5, 3);
        myPopMatrix();
        
        myPushMatrix();
        myTranslated(5.0, 0.0, 0.0);
        myRotated(-45.0+2*i, 0.0, 1.0, 0.0);
        drawBlock(1.0, 1.0, 1.0, 'm', 2, 5, 4, 1, 7);
        myPopMatrix();

        // Numbers
	int j = i%20;
	
        myPushMatrix();
        myTranslated(-10.0+j, 2.0, 10.0-j);
        drawLetter(0);
        myPopMatrix();
        
        myPushMatrix();
        myTranslated(11.0-j, 2.0, 11.0-j);
        drawLetter(1);
        myPopMatrix();
        
        myPushMatrix();
        myTranslated(-12.0+j, 2.0, 12.0-j);
        drawLetter(2);
        myPopMatrix();
        
        myPushMatrix();
        myTranslated(13.0-j, 2.0, 13.0-j);
        drawLetter(3);
        myPopMatrix();
        
        myPushMatrix();
        myTranslated(-14.0+j, 2.0, 14.0-j);
        drawLetter(4);
        myPopMatrix();
        
        myPushMatrix();
        myTranslated(15.0-j, 2.0, 15.0-j);
        drawLetter(5);
        myPopMatrix();
        
        myPushMatrix();
        myTranslated(-16.0+j, 2.0, 16.0-j);
        drawLetter(6);
        myPopMatrix();
        
        myPushMatrix();
        myTranslated(17.0-j, 2.0, 17.0-j);
        drawLetter(7);
        myPopMatrix();
        
        myPushMatrix();
        myTranslated(-18.0+j, 2.0, 18.0-j);
        drawLetter(8);
        myPopMatrix();
        
        myPushMatrix();
        myTranslated(19.0-j, 2.0, 19.0-j);
        drawLetter(9);
        myPopMatrix();
        
        mySwapBuffers();
    }

}

int main()
{
    init ();
    display();
    return 0;
}
