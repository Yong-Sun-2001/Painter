#ifndef FOLDLINE_H
#define FOLDLINE_H

#include <Shapes/PixelSet.h>
#include <QPainter>
#include <QPen>
using namespace std;
class Canvas;
class FoldLine : public PixelSet
{
protected:
    vector<Point> vertexes;  //折线的转折点
    int width;   //折线的线宽
    friend class Curve;
    friend class CtrlPoint;
    friend class Canvas;
public:
    FoldLine();
    FoldLine(const vector<Point>& ivertexs, int iwidth = 2, QColor icolor = Qt::blue);
    void setVertexes(const vector<Point>& ivertexs);
    void paint(QImage *image);
    void translate(int dx,int dy);
    void rotate(int x, int y, int r);
    void scale(int x, int y, float s);
};

#endif // FOLDLINE_H
