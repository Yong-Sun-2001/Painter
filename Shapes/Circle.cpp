#include <Shapes/Circle.h>
Circle::Circle()
{
    type = CIRCLE;
}
Circle::Circle(const Circle& B):PixelSet(B)
{
    type=CIRCLE;
    cx=B.cx;
    cy=B.cy;
    cr=B.cr;
    ccolor=B.ccolor;
    vertexes.clear();
    vertexes.assign(B.vertexes.begin(), B.vertexes.end());
    algorithm = B.algorithm;
}
Circle::Circle(ALGORITHM algo,int x,int y,int r)
{
    type=CIRCLE;
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
    if(fill_flag){
        if (algorithm == MIDPOINT) {
            midPointcircle(cx,cy,cr,*this);
        }
        //fillCircle();
    }
    else{
        if (algorithm == MIDPOINT) {
            midPointcircle(cx,cy,cr,*this);
        }
    }
}

void Circle::paint(QImage *image)
{
    refresh();
    PixelSet::paint(image);
}

void Circle::fill(QColor fcolor)
{
    fill_flag=true;
    color=fcolor;
    refresh();
}
