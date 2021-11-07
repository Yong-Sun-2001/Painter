#include <Shapes/FoldLine.h>
#include <Algorithms/CommonFuncs.h>
class Canvas;
FoldLine::FoldLine()
{
    type = FOLDLINE;
}

FoldLine::FoldLine(const vector<Point>& ivertexs, int iwidth, QColor icolor) {
    setVertexes(ivertexs);
    type = FOLDLINE;
    color = icolor;
    width = iwidth;
}
void FoldLine::setVertexes(const vector<Point>& ivertexes)
{
    vertexes = ivertexes;
}

void FoldLine::paint(QImage * image)
{
    QPainter myPainter(image);
    QPen myPen(color);
    myPen.setWidth(width);
    myPen.setStyle(Qt::DashLine);
    myPainter.setPen(myPen);
    for (size_t i = 1; i < vertexes.size(); i++) {
        myPainter.drawLine(vertexes[i - 1].x, vertexes[i - 1].y, vertexes[i].x, vertexes[i].y);
    }
}

void FoldLine::translate(int dx, int dy) {
    for (int i = 0; i < vertexes.size(); i++) {
        vertexes[i].x += dx;
        vertexes[i].y += dy;
    }
}

void FoldLine::rotate(int x, int y, int r)
{
    size_t n = vertexes.size();
    for (size_t i = 0; i < n; i++) {
        rotatePoint(vertexes[i].x, vertexes[i].y, x, y, r);
    }
}

void FoldLine::scale(int x, int y, float s)
{
    size_t n = vertexes.size();
    for (size_t i = 0; i < n; i++) {
        scalePoint(vertexes[i].x, vertexes[i].y, x, y, s);
    }
}

