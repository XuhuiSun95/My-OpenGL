//
//  primitive.hpp
//  myGL
//
//  Created by Xuhui Sun on 11/10/16.
//  Copyright © 2016 Xuhui Sun. All rights reserved.
//

#ifndef primitive_hpp
#define primitive_hpp

#include <stdio.h>
#include <vector>
#include <stack>
#define PI 3.14159265
using namespace std;

struct vertex{
    double x;
    double y;
    double z;
    vertex(double a, double b, double c) : x(a), y(b), z(c){}
};

struct pixel{
    double x;
    double y;
    double zDepth;
    pixel(){}
    pixel(double a, double b, double c) : x(a), y(b), zDepth(c){}
    bool operator<(pixel const& a){
        return x < a.x;
    }
};

enum gl_shape{
    POLYGON,
    QUAD_STRIP
};

struct line{
    pixel p1;
    pixel p2;
    line(pixel a, pixel b) : p1(a), p2(b){}
};

extern vector<vertex> vertices;
extern stack<double **> modelMatrixStack;
extern double modelMatrix[4][4];
extern double frustumLeft;
extern double frustumRight;
extern double frustumBottom;
extern double frustumTop;
extern double frustumNear;
extern double frustumFar;
extern gl_shape shapeType;
extern int *frameBuffer;
extern double *depthBuffer;
extern int dimx;
extern int dimy;
extern int frame;

vertex modelTransform(vertex v);
pixel projection(vertex v);
void multiMatrix(double imat1[4][4], double imat2[4][4], double omat[4][4]);
void inputBuffer(int x, int y, double zDepth);
void hidenSurface(int x, int y, double zDepth);
void lineCheck(pixel p1, pixel p2);
void surfaceCheck(vector<pixel> pointList);

#endif /* primitive_hpp */
