#ifndef LINE_H
#define LINE_H
#include <Shapes/Point.h>
#include <Shapes/PixelSet.h>
#include <vector>
#include <Algorithms/AlgorithmBase.h>


void drawCurve_Line(const std::vector<Point>& vertexs, PixelSet& myset);

#endif // LINE_H
