#ifndef DDA_H
#define DDA_H
#include <Shapes/Point.h>
#include <Shapes/PixelSet.h>
#include <vector>
#include <Algorithms/AlgorithmBase.h>


void drawLine_DDA(const std::vector<Point>& vertexs, PixelSet& myset);

#endif // DDA_H
