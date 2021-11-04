#ifndef PIXELSET_H
#define PIXELSET_H

#include <Shapes/Point.h>
#include <vector>
#include <QImage>
#include <QColor>

class PixelSet{

protected:
    int id;
    QColor color;
    std::vector<Point> points;

public:
    void setID(int pid);
    void setColor(int pcolor);
    void getid();
    void add(int x,int y);
    void translate();
    virtual void paint(QImage *image);
    virtual void scale();
    virtual void rotate();
    virtual void refresh();

};

#endif // PIXELSET_H
