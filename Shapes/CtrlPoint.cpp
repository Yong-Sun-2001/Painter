#include <Shapes/CtrlPoint.h>

CtrlPoint::CtrlPoint(int iindex, FoldLine *ifoldline,int iwidth, QColor icolor)
{
    index = iindex;
    foldline = ifoldline;
    width = iwidth;
    color = icolor;
}

int CtrlPoint::getID(int x, int y)
{
    int ix = foldline->vertexes[index].x;
    int iy = foldline->vertexes[index].y;
    if ((ix - x)*(ix - x) + (iy - y)*(iy - y) <= ((width + 2) * (width + 2))/4) {
        return id;
    }
    else {
        return -1;
    }
}

void CtrlPoint::paint(QImage * image)
{
    int x=0,y=0;
    if(foldline){
         x = foldline->vertexes[index].x;
         y = foldline->vertexes[index].y;
    }
    QPainter myPainter(image);
    QPen myPen(color);
    myPen.setWidth(width);
    myPen.setCapStyle(Qt::RoundCap);
    myPainter.setPen(myPen);
    myPainter.drawPoint(x, y);
}
