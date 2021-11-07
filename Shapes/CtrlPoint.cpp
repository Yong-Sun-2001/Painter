#include <Shapes/CtrlPoint.h>

CtrlPoint::CtrlPoint(int iindex, FoldLine *ifoldline,int iwidth, QColor icolor)
{
    type = CTRLPOINT;
    index = iindex;
    foldline = ifoldline;
    width = iwidth;
    color = icolor;
}

int CtrlPoint::getID(int x, int y)
{
    if (clear_flag) return -1;
    int ix = foldline->vertexes[index].x;
    int iy = foldline->vertexes[index].y;
    if ((ix - x)*(ix - x) + (iy - y)*(iy - y) <= ((width + 2) * (width + 2))/4) {
        return id;
    }
    else {
        return -1;
    }
}

void CtrlPoint::translate(int dx, int dy)
{
    if (clear_flag) return;
    foldline->vertexes[index].x+=dx;
    foldline->vertexes[index].y+=dy;
}

void CtrlPoint::paint(QImage * image)
{
    if (clear_flag) return;
    if (foldline->clear_flag) {
        clear_flag = true;
        return;
    }
    int x = foldline->vertexes[index].x;
    int y = foldline->vertexes[index].y;
    QPainter myPainter(image);
    QPen myPen(color);
    myPen.setWidth(width);
    myPen.setCapStyle(Qt::RoundCap);
    myPainter.setPen(myPen);
    myPainter.drawPoint(x, y);
}

CtrlPoint::CtrlPoint(const CtrlPoint & B, Canvas & canvas) :PixelSet(B) {
    type = CTRLPOINT;
    width = B.width;
    index = B.index;
    clear_flag = B.clear_flag;
    if (clear_flag) return;
    foldline = (FoldLine*)(canvas.getPixelSet(B.foldline->id));
    assert(foldline != nullptr);
}

