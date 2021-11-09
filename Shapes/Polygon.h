#ifndef POLYGON_H
#define POLYGON_H
#include <Shapes/PixelSet.h>
using namespace std;
class Polygon :public PixelSet
{
    //图元的参数
    vector<Point> vertexs;
    ALGORITHM algorithm;
    bool polygon_closed = true;
    ALGORITHM fill_algorithm;
public:
    Polygon();
    Polygon(const Polygon& B);
    Polygon(const vector<Point>& ivertexs, ALGORITHM ialgorithm);
    void set(const vector<Point>& ivertexs, ALGORITHM ialgorithm);
    void refresh();
    void translate(int dx, int dy) ;
    void rotate(int x, int y, int r);
    void scale(int x, int y, float s);
    void fill(QColor fcolor);
};
#endif // POLYGON_H
