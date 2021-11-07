#include <Shapes/PixelSet.h>
#include <QPainter>
#include <QPen>

void PixelSet::setColor(QColor pcolor)
{
    color=pcolor;
}
void PixelSet::setWidth(int iwidth)
{
    width=iwidth;
}
void PixelSet::setID(int pid)
{
    id=pid;
}

int PixelSet::getID(int x, int y)
{
    int res_ID = -1;
    for (size_t j = 0; j < points.size(); j++) {
        int ix = points[j].x;
        int iy = points[j].y;
        if ((ix - x)*(ix - x) + (iy - y)*(iy - y) <= 10 * 10) {
            return id;
        }
    }
    return res_ID;
}

void PixelSet::add(int x, int y)
{
    points.push_back(Point(x, y));
}

void PixelSet::paint(QImage *image)
{
    int x = image->size().width();
    int y = image->size().height();
    //设置画笔属性
    QPainter myPainter(image);
    QPen myPen(color);
    myPen.setWidth(width);
    myPen.setCapStyle(Qt::RoundCap); //可以设置为额外的PixelSet属性
    myPainter.setPen(myPen);

    //开始画
    foreach(const Point& var, points) {
        if (var.x >= x || var.y >= y || var.x < 0 || var.y < 0) continue; //跳过超过画布边界的点
        //image->setPixelColor(var.x, var.y, color);
        myPainter.drawPoint(var.x, var.y);
    }
}


void PixelSet::translate(int dx, int dy)
{
    for (auto var = points.begin(); var != points.end(); ++var) {
        var->x += dx;
        var->y += dy;
    }
}



