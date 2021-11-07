#ifndef DDA_H
#define DDA_H
#include <Shapes/PixelSet.h>
#include <vector>
#include <Algorithms/AlgorithmBase.h>

using namespace std;
void drawLine_DDA(int x1,int x2,int y1,int y2, PixelSet& myset);
void drawPolygon_DDA(const vector<Point>& vertexs, PixelSet& myset);
#endif // DDA_H
