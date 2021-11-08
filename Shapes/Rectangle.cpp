#include <Shapes/Rectangle.h>
#include <Algorithms/CommonFuncs.h>
#include <QPainter>
#include <QPen>
using namespace std;
Rectangle::Rectangle()
{
    type = RECTANGLE;
}
Rectangle::Rectangle(const Rectangle& B) :PixelSet(B)
{
    x1 = B.x1; y1 = B.y1;
    x2 = B.x2; y2 = B.y2;
    width = B.width;
    type = RECTANGLE;
}
Rectangle::Rectangle(int ix1, int iy1, int ix2, int iy2, int iwidth, QColor icolor)
{
    x1 = min(ix1, ix2); x2 = max(ix1, ix2);
    y1 = min(iy1, iy2); y2 = max(iy1, iy2);
    width = iwidth; color = icolor;
    type = RECTANGLE;
}

void Rectangle::paint(QImage *image)
{
    refresh();
    PixelSet::paint(image);
}

void Rectangle::refresh()
{
    points.clear();
    if(x1>x2) swap(x1,x2);
    if(y1>y2) swap(y1,y2);
    for(int x=x1;x<=x2;x++){
        this->add(x,y1);
        this->add(x,y2);
    }
    for(int y=y1;y<=y2;y++){
        this->add(x1,y);
        this->add(x2,y);
    }
}

void Rectangle::rotate(int x, int y, int r)
{
    rotatePoint(x1, y1, x, y, r);
    rotatePoint(x2, y2, x, y, r);
    refresh();
}

void Rectangle::scale(int x, int y, float s)
{
    scalePoint(x1, y1, x, y, s);
    scalePoint(x2, y2, x, y, s);
    refresh();
}

void Rectangle::translate(int dx, int dy) {
    PixelSet::translate(dx, dy);
    x1 += dx; y1 += dy;
    x2 += dx; y2 += dy;
}


