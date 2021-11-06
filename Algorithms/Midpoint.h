#ifndef MIDPOINT_H
#define MIDPOINT_H
#include <Shapes/Point.h>
#include <Shapes/PixelSet.h>
#include <vector>
#include <Algorithms/AlgorithmBase.h>
#include <Shapes/Circle.h>
using namespace std;

void midPointcircle(const int x0,const int y0,const int r, PixelSet& myset);
void circlePoint(int x,int y,PixelSet& myset);
#endif // MIDPOINT_H
