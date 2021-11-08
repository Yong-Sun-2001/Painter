#include <Shapes/Triangle.h>
#include <Algorithms/CommonFuncs.h>

Triangle::Triangle()
{
    type = TRIANGLE;
}

Triangle::Triangle(const Triangle& B)
{
    x1 = B.x1;
    y1 = B.y1;
    x2 = B.x2;
    y2 = B.y2;
    x3 = B.x3;
    y3 = B.y3;
    algorithm = B.algorithm;
}

Triangle::Triangle(int ix1,int iy1,int ix2,int iy2,int ix3,int iy3,ALGORITHM ialgorithm)
{
    type = TRIANGLE;
    x1 = ix1; y1 = iy1;
    x2 = ix2; y2 = iy2;
    x3 = ix3; y3 = iy3;
    algorithm = ialgorithm;
}

void Triangle::refresh()
{
    points.clear();
    if (algorithm == DDA) {
        drawLine_DDA(x1, x2, y1, y2, *this);
        drawLine_DDA(x2, x3, y2, y3, *this);
        drawLine_DDA(x3, x1, y3, y1, *this);
    }
}

void Triangle::rotate(int x, int y, int r)
{
    rotatePoint(x1, y1, x, y, r);
    rotatePoint(x2, y2, x, y, r);
    rotatePoint(x3, y3, x, y, r);
    refresh();
}

void Triangle::scale(int x, int y, float s)
{
    scalePoint(x1, y1, x, y, s);
    scalePoint(x2, y2, x, y, s);
    scalePoint(x3, y3, x, y, s);
    refresh();
}

void Triangle::translate(int dx, int dy) {
    PixelSet::translate(dx, dy);
    x1 += dx; y1 += dy;
    x2 += dx; y2 += dy;
    x3 += dx; y3 += dy;
}

void Triangle::paint(QImage * image)
{
    refresh();
    PixelSet::paint(image);
}
