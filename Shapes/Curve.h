#ifndef CURVE_H
#define CURVE_H
#include <Shapes/FoldLine.h>
#include <Algorithms/Bezier.h>
#include <Algorithms/DDA.h>
using namespace std;
#include <Canvas.h>
class Curve : public PixelSet
{
protected:
    vector<Point> vertexes;
    ALGORITHM algorithm;
    FoldLine* foldline;   //用于辅助示意的虚折线（此处注意：拷贝赋值的时候要额外处理）
    friend class Canvas;
public:
    Curve() { type = CURVE; }
    Curve(ALGORITHM algo,FoldLine * fl);
    Curve(const Curve& B, Canvas& canvas);
    ~Curve();
    void refresh();
    void paint(QImage *image);
    void translate(int dx,int dy);
    void rotate(int x, int y, int r);
    void scale(int x, int y, float s);
};
#endif // CURVE_H
