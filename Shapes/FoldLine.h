#ifndef FOLDLINE_H
#define FOLDLINE_H
#include <Shapes/PixelSet.h>
#include <QPainter>
#include <QPen>

using namespace std;
class FoldLine : public PixelSet
{
protected:
    vector<Point> vertexes;  //折线的转折点
    int width;   //折线的线宽
    friend class Curve;
    friend class CtrlPoint;
public:
    FoldLine(const vector<Point>& ivertexes);
    void setVertexes(const vector<Point>& ivertexs);
    void paint(QImage *image);
};

#endif // FOLDLINE_H
