#include <Shapes/PixelSet.h>

void PixelSet::setColor(int pcolor)
{
    color=pcolor;
}

void PixelSet::setID(int pid)
{
    id=pid;
}

void PixelSet::add(int x, int y)
{
    points.push_back(Point(x, y));
}

void PixelSet::paint(QImage *image)
{
    int x = image->size().width();
    int y = image->size().height();
    foreach(const Point& var, points) {
        if (var.x >= x || var.y >= y || var.x < 0 || var.y < 0) continue; //跳过超过画布边界的点
        image->setPixelColor(var.x, var.y, color);
    }
}

int PixelSet::getid(){
    return id;
}

void PixelSet::scale()
{

}

void PixelSet::rotate()
{

}

void PixelSet::refresh()
{
}


