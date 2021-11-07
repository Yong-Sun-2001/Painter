#ifndef COMMONFUNCS_H
#define COMMONFUNCS_H

#include<QDebug>
#include<assert.h>
#include<math.h>

void rotatePoint(int &x, int &y, int xr, int yr, int r);
int getRotateR(int x1, int y1, int xr, int yr, int x2, int y2);
void scalePoint(int &x, int &y, int sx, int sy, double s);
double getScaleS(int x1, int y1, int sx, int sy, int x2, int y2);
void crossX(int x1,int y1,int x2,int y2,int x,int &y);
void crossY(int x1,int y1,int x2,int y2,int &x,int y);
#endif // COMMONFUNCS_H
