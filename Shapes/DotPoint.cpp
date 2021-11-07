#include <Shapes/DotPoint.h>
#include <QPainter>
#include <QPen>
DotPoint::DotPoint()
{
    type = DOTPOINT;
}
DotPoint::DotPoint(const DotPoint& B) :PixelSet(B)
{
    x = B.x; y = B.y;
    width = B.width;
}
DotPoint::DotPoint(int ix, int iy, int iwidth, QColor icolor )
{
    x = ix; y = iy;
    width = iwidth;
    color = icolor;
    type = DOTPOINT;
}
void DotPoint::paint(QImage * image)
{
    QPainter myPainter(image);
    QPen myPen(color);
    myPen.setWidth(width);
    myPen.setCapStyle(Qt::RoundCap);
    myPainter.setPen(myPen);
    myPainter.drawPoint(x, y);
}
