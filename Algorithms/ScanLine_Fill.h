#ifndef SCANLINE_FILL_H
#define SCANLINE_FILL_H
#include <Algorithms/AlgorithmBase.h>
#include <Shapes/PixelSet.h>
#define MAX 100
using namespace std;
struct MyPoint {
    int   x;
    int y;
    MyPoint() {}
    MyPoint(int x1, int y1) {
        x = x1;
        y = y1;
    }
};

struct MyEdge
{
    int ymax;
    float x, deltax;
    struct MyEdge* nextEdge;
    MyEdge(){}
};

struct MyPolygon {
    int   PolygonNum;        // 多边形顶点个数
    MyPoint vertexces[MAX];   //多边形顶点数组
    int xmin;
    int xmax;
    int ymin;
    int ymax;
    MyPolygon(const vector<Point>& vertexs);
};
void FillPolygonScanline(const vector<Point>& vertexs, PixelSet& myset);

#endif // SCANLINE_FILL_H
