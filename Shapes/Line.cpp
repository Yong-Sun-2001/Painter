#include <Shapes/Line.h>
#include <Algorithms/CommonFuncs.h>
Line::Line()
{
    type = LINE;
}

Line::Line(const Line& B) :PixelSet(B)
{
    x1 = B.x1;
    y1 = B.y1;
    x2 = B.x2;
    y2 = B.y2;
    algorithm = B.algorithm;
}
Line::Line(int ix1, int iy1, int ix2, int iy2, ALGORITHM ialgorithm)
{
    type = LINE;
    x1 = ix1; y1 = iy1;
    x2 = ix2; y2 = iy2;
    algorithm = ialgorithm;
}
void Line::refresh()
{
    points.clear();
    if (algorithm == DDA) {
        drawLine_DDA(x1, x2, y1, y2, *this);
    }
}

void Line::rotate(int x, int y, int r)
{
    rotatePoint(x1, y1, x, y, r);
    rotatePoint(x2, y2, x, y, r);
    refresh();
}

void Line::scale(int x, int y, float s)
{
    scalePoint(x1, y1, x, y, s);
    scalePoint(x2, y2, x, y, s);
    refresh();
}

void Line::translate(int dx, int dy) {
    PixelSet::translate(dx, dy);
    x1 += dx; y1 += dy;
    x2 += dx; y2 += dy;
}

void Line::paint(QImage * image)
{
    refresh();
    PixelSet::paint(image);
}
