#include <Shapes/Polygon.h>
#include <Algorithms/DDA.h>
#include <Algorithms/CommonFuncs.h>
#include <Algorithms/ScanLine_Fill.h>
Polygon::Polygon()
{
    type = POLYGON;
}
Polygon::Polygon(const Polygon& B) : PixelSet(B)
{
    vertexs.clear();
    vertexs.assign(B.vertexs.begin(), B.vertexs.end());
    fill_flag=B.fill_flag;
    algorithm = B.algorithm;
    fill_algorithm=B.fill_algorithm;
    polygon_closed = B.polygon_closed;
}
Polygon::Polygon(const vector<Point>& ivertexs, ALGORITHM ialgorithm)
{
    type = POLYGON;
    set(ivertexs, ialgorithm);
}
void Polygon::set(const vector<Point>& ivertexs, ALGORITHM ialgorithm)
{
    vertexs.assign(ivertexs.begin(), ivertexs.end());
    algorithm = ialgorithm;
}
void Polygon::translate(int dx, int dy)
{
    PixelSet::translate(dx, dy);
    for (int i = 0; i < vertexs.size(); i++) {
        vertexs[i].x += dx;
        vertexs[i].y += dy;
    }
}

void Polygon::refresh()
{
    points.clear();
    if (fill_flag){
        if (algorithm == DDA) {
            drawPolygon_DDA(vertexs, *this);
        }
        if (fill_algorithm==SCANLINE){
            FillPolygonScanline(vertexs,*this);
        }
    }
    else{
        if (algorithm == DDA) {
            drawPolygon_DDA(vertexs, *this);
        }
    }
}

void Polygon::rotate(int x, int y, int r)
{
    size_t n = vertexs.size();
    for (size_t i = 0; i < n; i++) {
        rotatePoint(vertexs[i].x, vertexs[i].y, x, y, r);
    }
    refresh();
}

void Polygon::scale(int x, int y, float s)
{
    size_t n = vertexs.size();
    for (size_t i = 0; i < n; i++) {
        scalePoint(vertexs[i].x, vertexs[i].y, x, y, s);
    }
    refresh();
}

void Polygon::fill(QColor fcolor)
{
    fill_flag=true;
    fill_algorithm=SCANLINE;
    color=fcolor;
    refresh();
}
