#include <Shapes/Curve.h>
Curve::Curve(ALGORITHM algo,FoldLine * fl)
{
    type = CURVE;
    algorithm=algo;
    foldline = fl;
}
Curve::Curve(const Curve & B, Canvas & canvas) : PixelSet(B)
{
    vertexes = B.vertexes;
    algorithm = B.algorithm;
    foldline = (FoldLine*)(canvas.getPixelSet(B.foldline->id));
    assert(foldline != nullptr);
}

void Curve::refresh()
{
    points.clear();
    if (algorithm == BEZIER) {
        drawCurve_Bezier(vertexes, *this);
    }
}

void Curve::translate(int dx, int dy) {
    foldline->translate(dx, dy);
}

void Curve::paint(QImage * image)
{
    vertexes = foldline->vertexes;
    refresh();
    PixelSet::paint(image);
}

void Curve::rotate(int x, int y, int r)
{
    foldline->rotate(x, y, r);
}
void Curve::scale(int x, int y, float s)
{
    foldline->scale(x, y, s);
}
Curve::~Curve()
{
    foldline->clear_flag = true;
}


