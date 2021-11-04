#ifndef BEZIER_H
#define BEZIER_H
#include <Shapes/Point.h>
#include <Shapes/PixelSet.h>
#include <vector>
#include <Algorithms/AlgorithmBase.h>

Point getPoint_Bezier(double u, const std::vector<Point> &vertexs);
double getStep_Bezier(const std::vector<Point> &vertexs);
void drawCurve_Bezier(const std::vector<Point>& vertexs, PixelSet& myset);

#endif //BEZIER_H
