#ifndef CURVE_H
#define CURVE_H
#include <Shapes/FoldLine.h>
#include <Algorithms/Bezier.h>
#include <Algorithms/DDA.h>
using namespace std;
class Curve : public PixelSet
{
protected:
    vector<Point> vertexes;
    ALGORITHM algorithm;
    FoldLine* foldline;   //用于辅助示意的虚折线（此处注意：拷贝赋值的时候要额外处理）
public:
    Curve(ALGORITHM algo,FoldLine * fl);
    //void SetAlgorithm(ALGORITHM algo);
    void refresh();
    void paint(QImage *image);
    //平移

};
#endif // CURVE_H
