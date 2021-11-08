#ifndef PIXELSET_H
#define PIXELSET_H

#include <Shapes/Point.h>
#include <vector>
#include <QImage>
#include <QColor>
#include <Algorithms/AlgorithmBase.h>

enum PS_TYPE
{
    LINE, POLYGON, ELLIPSE, DOTPOINT, RECTANGLE, CURVE, FOLDLINE, CTRLPOINT,CIRCLE,TRIANGLE
};

class PixelSet{

protected:
    int id;
    QColor color=0xFF0000;   //图形的颜色
    std::vector<Point> points;
    int width = 1;
    bool clear_flag = false;//标记是否无效，需要被清除
    friend class Canvas;
public:
    PS_TYPE type;//图元类型
    int CLICK_BIAS = 3; //允许的误差范围（圆形区域的半径）
    PixelSet(int i = 0, QColor icolor = Qt::black){ id = i; color = icolor; }
    PixelSet(const PixelSet& B) {
        id = B.id;
        color = B.color;
        type=B.type;
        points.clear();
        points.assign(B.points.begin(), B.points.end());
    }
    void setID(int pid);
    void setColor(QColor pcolor);
    void setWidth(int iwidth);
    void add(int x,int y);
    virtual void translate(int dx, int dy);
    virtual int getID(int x, int y);
    virtual void paint(QImage *image);
    virtual void scale(int x, int y, float s){}
    virtual void rotate(int x, int y, int r){}
    virtual void refresh(){}
    virtual void clip(int x1, int y1, int x2, int y2, ALGORITHM algorithm) {}
    virtual void fill(QColor fcolor){};
};
#endif // PIXELSET_H
