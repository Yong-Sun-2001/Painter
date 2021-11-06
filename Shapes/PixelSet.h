#ifndef PIXELSET_H
#define PIXELSET_H

#include <Shapes/Point.h>
#include <vector>
#include <QImage>
#include <QColor>

class PixelSet{

protected:
    int id;
    QColor color=0xFF0000;   //图形的颜色
    std::vector<Point> points;
    int width = 1;
public:
    void setID(int pid);
    int getID(int x,int y);
    void setColor(QColor pcolor);
    void setWidth(int iwidth);
    int getid();
    void add(int x,int y);
    void translate();
    virtual void paint(QImage *image);
    virtual void scale();
    virtual void rotate();
    virtual void refresh();

};

#endif // PIXELSET_H
