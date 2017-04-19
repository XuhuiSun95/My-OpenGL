//
//  myGL.cpp
//  myGL
//
//  Created by Xuhui Sun on 11/10/16.
//  Copyright © 2016 Xuhui Sun. All rights reserved.
//
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include "primitive.hpp"
#include "myGL.hpp"
using namespace std;

void myInit(int length, int width){
    dimx = length;
    dimy = width;
    frameBuffer = new int[dimx*dimy];
    depthBuffer = new double[dimx*dimy];
    myLoadIdentity();
}

void myFrustum(double left, double right, double bottom, double top, double zNear, double zFar){
    frustumLeft = left;
    frustumRight = right;
    frustumBottom = bottom;
    frustumTop = top;
    frustumNear = zNear;
    frustumFar = zFar;
}

void myLoadIdentity(){
    modelMatrix[0][0] = 1; modelMatrix[0][1] = 0; modelMatrix[0][2] = 0; modelMatrix[0][3] = 0;
    modelMatrix[1][0] = 0; modelMatrix[1][1] = 1; modelMatrix[1][2] = 0; modelMatrix[1][3] = 0;
    modelMatrix[2][0] = 0; modelMatrix[2][1] = 0; modelMatrix[2][2] = 1; modelMatrix[2][3] = 0;
    modelMatrix[3][0] = 0; modelMatrix[3][1] = 0; modelMatrix[3][2] = 0; modelMatrix[3][3] = 1;
}

void myLookAt(double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ, double upX, double upY, double upZ){
    double fx, fy, fz;
    double rlf, rls;
    double sx, sy, sz;
    double ux, uy, uz;
    fx = centerX - eyeX;
    fy = centerY - eyeY;
    fz = centerZ - eyeZ;
    
    rlf = 1.0f / sqrt(fx * fx + fy * fy + fz * fz);
    fx *= rlf;
    fy *= rlf;
    fz *= rlf;
    
    sx = fy * upZ - fz * upY;
    sy = fz * upX - fx * upZ;
    sz = fx * upY - fy * upX;
    
    rls = 1.0f / sqrt(sx * sx + sy * sy + sz * sz);
    sx *= rls;
    sy *= rls;
    sz *= rls;
    
    ux = sy * fz - sz * fy;
    uy = sz * fx - sx * fz;
    uz = sx * fy - sy * fx;
    
    double matrix[4][4], omatrix[4][4];
    matrix[0][0] = sx; matrix[0][1] = sy; matrix[0][2] = sz; matrix[0][3] = 0;
    matrix[1][0] = ux; matrix[1][1] = uy; matrix[1][2] = uz; matrix[1][3] = 0;
    matrix[2][0] = -fx; matrix[2][1] = -fy; matrix[2][2] = -fz; matrix[2][3] = 0;
    matrix[3][0] = 0; matrix[3][1] = 0; matrix[3][2] = 0; matrix[3][3] = 1;
    multiMatrix(modelMatrix, matrix, omatrix);
    for(int i = 0; i < 4; i ++){
        for(int j = 0; j < 4; j ++)
            modelMatrix[i][j] = omatrix[i][j];
    }
    myTranslated(-eyeX, -eyeY, -eyeZ);
}

void mySetBackground(){
    for(int i = 0; i < dimx*dimy; i++){
        frameBuffer[i] = 1;
        depthBuffer[i] = frustumFar;
    }
}

void myTranslated(double x, double y, double z){
    double matrix[4][4], omatrix[4][4];
    matrix[0][0] = 1; matrix[0][1] = 0; matrix[0][2] = 0; matrix[0][3] = x;
    matrix[1][0] = 0; matrix[1][1] = 1; matrix[1][2] = 0; matrix[1][3] = y;
    matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = 1; matrix[2][3] = z;
    matrix[3][0] = 0; matrix[3][1] = 0; matrix[3][2] = 0; matrix[3][3] = 1;
    multiMatrix(modelMatrix, matrix, omatrix);
    for(int i = 0; i < 4; i ++){
        for(int j = 0; j < 4; j ++)
            modelMatrix[i][j] = omatrix[i][j];
    }
}

void myScaled(double x, double y, double z){
    double matrix[4][4], omatrix[4][4];
    matrix[0][0] = x; matrix[0][1] = 0; matrix[0][2] = 0; matrix[0][3] = 0;
    matrix[1][0] = 0; matrix[1][1] = y; matrix[1][2] = 0; matrix[1][3] = 0;
    matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = z; matrix[2][3] = 0;
    matrix[3][0] = 0; matrix[3][1] = 0; matrix[3][2] = 0; matrix[3][3] = 1;
    multiMatrix(modelMatrix, matrix, omatrix);
    for(int i = 0; i < 4; i ++){
        for(int j = 0; j < 4; j ++)
            modelMatrix[i][j] = omatrix[i][j];
    }
}

void myRotated(double angle, double x, double y, double z){
    double l = sqrt(x * x + y * y + z * z);
    x /= l;
    y /= l;
    z /= l;
    double c = cos(angle * PI / 180);
    double s = sin(angle * PI / 180);
    double matrix[4][4], omatrix[4][4];
    matrix[0][0] = x*x*(1-c)+c; matrix[0][1] = x*y*(1-c)-z*s; matrix[0][2] = x*z*(1-c)+y*s; matrix[0][3] = 0;
    matrix[1][0] = y*x*(1-c)+z*s; matrix[1][1] = y*y*(1-c)+c; matrix[1][2] = y*z*(1-c)-x*s; matrix[1][3] = 0;
    matrix[2][0] = x*z*(1-c)-y*s; matrix[2][1] = y*z*(1-c)+x*s; matrix[2][2] = z*z*(1-c)+c; matrix[2][3] = 0;
    matrix[3][0] = 0; matrix[3][1] = 0; matrix[3][2] = 0; matrix[3][3] = 1;
    multiMatrix(modelMatrix, matrix, omatrix);
    for(int i = 0; i < 4; i ++){
        for(int j = 0; j < 4; j ++)
            modelMatrix[i][j] = omatrix[i][j];
    }
}

void myBegin(gl_shape type){
    shapeType = type;
    vertices.clear();
}

void myVertex3d(double x, double y, double z){
    vertex v(x, y, z);
    vertices.push_back(v);
}

void myEnd(){
    switch(shapeType){
        case POLYGON:{
            vector<pixel> points;
            for(vector<vertex>::iterator it = vertices.begin(); it != vertices.end(); it++){
                vertex v = modelTransform(*it);
                points.push_back(projection(v));
            }
            surfaceCheck(points);
            break;
        }
        case QUAD_STRIP:{
            vector<pixel> pointsOdd;
            vector<pixel> pointsEven;
            for(int i = 0; i < vertices.size(); i++){
                vertex v = modelTransform(vertices[i]);
                if(i % 2 == 0)
                    pointsEven.push_back(projection(v));
                else
                    pointsOdd.push_back(projection(v));
            }
            reverse(pointsOdd.begin(), pointsOdd.end());
            pointsEven.insert(pointsEven.end(), pointsOdd.begin(), pointsOdd.end());
            surfaceCheck(pointsEven);
            break;
        }
    }
}

void myPushMatrix(){
    double** matrix = new double*[4];
    matrix[0] = new double[4];
    matrix[1] = new double[4];
    matrix[2] = new double[4];
    matrix[3] = new double[4];
    for(int i = 0; i < 4; i ++){
        for(int j = 0; j < 4; j ++)
            matrix[i][j] = modelMatrix[i][j];
    }
    modelMatrixStack.push(matrix);
}

void myPopMatrix(){
    double** top = modelMatrixStack.top();
    for(int i = 0; i < 4; i ++){
        for(int j = 0; j < 4; j ++)
            modelMatrix[i][j] = top[i][j];
    }
    delete top;
    modelMatrixStack.pop();
}

void mySwapBuffers(){
    char s[10];
    sprintf(s, "%03d.ppm", frame);
    FILE *fp = fopen(s, "wb");
    (void) fprintf(fp, "P1\n%d %d\n", dimx, dimy);
    for(int i = 0; i < dimx*dimy; i++){
        (void) fprintf(fp, "%d", frameBuffer[i]);
    }
    frame++;
}
