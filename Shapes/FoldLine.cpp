#include <Shapes/FoldLine.h>

FoldLine::FoldLine(const vector<Point>& ivertexes)
{
    setVertexes(ivertexes);
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

