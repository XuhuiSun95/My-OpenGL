//
//  primitive.cpp
//  myGL
//
//  Created by Xuhui Sun on 11/10/16.
//  Copyright © 2016 Xuhui Sun. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <algorithm>
#include "primitive.hpp"
using namespace std;

vector<vertex> vertices;
stack<double **> modelMatrixStack;
double modelMatrix[4][4];
double frustumLeft;
double frustumRight;
double frustumBottom;
double frustumTop;
double frustumNear;
double frustumFar;
gl_shape shapeType;
int *frameBuffer;
double *depthBuffer;
int dimx;
int dimy;
int frame = 0;

vertex modelTransform(vertex v){
    double ox = modelMatrix[0][0] * v.x + modelMatrix[0][1] * v.y + modelMatrix[0][2] * v.z + modelMatrix[0][3];
    double oy = modelMatrix[1][0] * v.x + modelMatrix[1][1] * v.y + modelMatrix[1][2] * v.z + modelMatrix[1][3];
    double oz = modelMatrix[2][0] * v.x + modelMatrix[2][1] * v.y + modelMatrix[2][2] * v.z + modelMatrix[2][3];
    double oc = modelMatrix[3][0] * v.x + modelMatrix[3][1] * v.y + modelMatrix[3][2] * v.z + modelMatrix[3][3];
    return vertex(ox/oc, oy/oc, oz/oc);
}

pixel projection(vertex v){
    double ox = v.x;
    double oy = v.y;
    return pixel(ox, oy, v.z);
}

void multiMatrix(double imat1[4][4], double imat2[4][4], double omat[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            omat[i][j] = 0;
            for(int k = 0; k < 4; k++)
                omat[i][j] += imat1[i][k] * imat2[k][j];
        }
    }
}

void inputBuffer(int x, int y, double zDepth){
    int pixel = (y - 1) * dimx + x;
    if(x > 0 && x <= dimx && y > 0 && y <= dimy && zDepth >= depthBuffer[pixel - 1]){
        frameBuffer[(pixel - 1)] = 0;
        depthBuffer[pixel - 1] = zDepth;
    }
}

void hidenSurface(int x, int y, double zDepth){
    int pixel = (y - 1) * dimx + x;
    if(x > 0 && x <= dimx && y > 0 && y <= dimy && zDepth >= depthBuffer[pixel - 1]){
        frameBuffer[(pixel - 1)] = 1;
        depthBuffer[pixel - 1] = zDepth;
    }
}

void lineCheck(pixel p1, pixel p2){
    int px, py;
    double zDepth;
    double px1 = dimx / 2 + dimx / (frustumRight - frustumLeft) * p1.x;
    double py1 = dimy / 2 - dimy / (frustumTop - frustumBottom) * p1.y;
    double px2 = dimx / 2 + dimx / (frustumRight - frustumLeft) * p2.x;
    double py2 = dimy / 2 - dimy / (frustumTop - frustumBottom) * p2.y;
    double dpx = px2 - px1;
    double dpy = py2 - py1;
    int steps = (fabs(dpx) > fabs(dpy))? fabs(dpx):fabs(dpy);
    double pxInc = dpx / steps;
    double pyInc = dpy / steps;
    double xInc = (p2.x - p1.x) / steps;
    double yInc = (p2.y - p1.y) / steps;
    for(int i = 0; i < steps; i++){
        px = round(px1 + pxInc * i);
        py = round(py1 + pyInc * i);
        if((p2.x - p1.x) != 0)
            zDepth = (p2.zDepth - p1.zDepth) / (p2.x - p1.x) * (xInc * i) + p1.zDepth;
        else
            zDepth = (p2.zDepth - p1.zDepth) / (p2.y - p1.y) * (yInc * i) + p1.zDepth;
        inputBuffer(px, py, zDepth);
    }
}

void surfaceCheck(vector<pixel> pointList){
    vector<line> edgeList;
    vector<pixel>::iterator it=pointList.begin();
    double xmin = it -> x, xmax = it -> x, ymin = it -> y, ymax = it -> y, zvalueAverage = it -> zDepth;
    for (; it != pointList.end() - 1; it++){
        line e(*it, *(it + 1));
        edgeList.push_back(e);
        lineCheck(*it, *(it + 1));
        if(it -> x < xmin)	xmin = it -> x;
        if(it -> x > xmax)	xmax = it -> x;
        if(it -> y < ymin)	ymin = it -> y;
        if(it -> y > ymax)	ymax = it -> y;
        zvalueAverage += it -> zDepth;
    }
    it = pointList.end() - 1;
    if(it -> x < xmin)	xmin = it -> x;
    if(it -> x > xmax)	xmax = it -> x;
    if(it -> y < ymin)	ymin = it -> y;
    if(it -> y > ymax)	ymax = it -> y;
    line e(*(pointList.end()-1), *pointList.begin());
    edgeList.push_back(e);
    lineCheck(*(pointList.end()-1), *pointList.begin());
    zvalueAverage /= pointList.size();
    int numLine = (ymax - ymin) / (frustumTop - frustumBottom) * dimy;
    double xInc = (frustumRight - frustumLeft) / dimx, yInc = (frustumTop - frustumBottom) / dimy, x, y, x1, y1, x2, y2;
    vector<pixel> insecPoint;
    pixel pleft, pright;
    double x_1 = pointList[0].x;
    double y_1 = pointList[0].y;
    double z_1 = pointList[0].zDepth;
    double x_2 = pointList[1].x;
    double y_2 = pointList[1].y;
    double z_2 = pointList[1].zDepth;
    double x_3 = pointList[2].x;
    double y_3 = pointList[2].y;
    double z_3 = pointList[2].zDepth;
    double xvalue = x_1 * y_2 - x_2 * y_1 - x_1 * y_3 + x_3 * y_1 + x_2 * y_3 - x_3 * y_2;
    double avalue, bvalue, cvalue;
    if(xvalue != 0){
        avalue = - (y_1 * z_2 - y_2 * z_1 - y_1 * z_3 + y_3 * z_1 + y_2 * z_3 - y_3 * z_2) / xvalue;
        bvalue = (x_1 * z_2 - x_2 * z_1 - x_1 * z_3 + x_3 * z_1 + x_2 * z_3 - x_3 * z_2) / xvalue;
        cvalue = (x_1 * y_2 * z_3 - x_1 * y_3 * z_2 - x_2 * y_1 * z_3 + x_2 * y_3 * z_1 + x_3 * y_1 * z_2 - x_3 * y_2 * z_1) / xvalue;
    }
    for(int i = 1; i < numLine; i++){
        insecPoint.clear();
        y = ymin + yInc * i;
        for(vector<line>::iterator it = edgeList.begin(); it != edgeList.end(); it++){
            x1 = it -> p1.x;
            x2 = it -> p2.x;
            y1 = it -> p1.y;
            y2 = it -> p2.y;
            if((y >= y1 && y <= y2) || (y <= y1 && y >= y2)){
                x = (x2 - x1) / (y2 - y1) * (y - y1) + x1;
                insecPoint.push_back(pixel(x, y, 1));
            }
        }
        sort(insecPoint.begin(), insecPoint.end());
        for(int i = 0; i < insecPoint.size() - 1; i++){
            if(fabs(insecPoint[i].x - insecPoint[i+1].x) <= xInc)
                insecPoint.erase(insecPoint.begin()+i+1);
        }
        for(int i = 0; i < insecPoint.size() / 2; i++){
            pleft = insecPoint[2*i];
            pright = insecPoint[2*i + 1];
            x = pleft.x;
            int pxleft  = round(dimx / 2 + dimx / (frustumRight - frustumLeft) * pleft.x);
            int pxright  = round(dimx / 2 + dimx / (frustumRight - frustumLeft) * pright.x);
            while(x < pright.x){
                x += xInc;
                int px = round(dimx / 2 + dimx / (frustumRight - frustumLeft) * x);
                int py = round(dimy / 2 - dimy / (frustumTop - frustumBottom) * y);
                double zDepth = -100;
                if(xvalue != 0)
                    zDepth = avalue * x + bvalue * y + cvalue;
                if(px < (pxright - 1) && px > (pxleft + 1))
                    hidenSurface(px, py, zDepth);
            }
        }
    }
}
