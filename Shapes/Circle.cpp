#include <Shapes/Circle.h>

Circle::Circle(ALGORITHM algo,int x,int y,int r)
{
    cx = x;
    cy = y;
    cr = r;
    algorithm = algo;
}

void Circle::setColor(QColor color)
{
    ccolor = color ;
}

void Circle::refresh()
{
    points.clear();
    if (algorithm == MIDPOINT) {
        midPointcircle(cx,cy,cr,*this);
    }
}

void Circle::paint(QImage *image)
{
    refresh();
    PixelSet::paint(image);
}
