#ifndef CANVAS_H
#define CANVAS_H


#include <vector>
#include <QImage>
#include <QColor>
#include <Shapes/FoldLine.h>
#include <Shapes/Curve.h>
#include <Shapes/CtrlPoint.h>
#include <Shapes/Line.h>

class Canvas{

protected:
    QColor color=0xFF0000;   //画笔颜色

public:
    int id_counter = 0;   //图形编号
    std::vector<PixelSet *> PixelSets;   //画布上所有图形的集合
    int getID(int x, int y);
    int getNewID();
    void getImage(QImage *image);
    void drawCurve(ALGORITHM algo, FoldLine *fl);
    void drawPoint(Point pt);
    void drawLine(ALGORITHM algo,Point *st,Point *ed);
    FoldLine* drawFoldLine(const vector<Point>& vertexes);
    void drawCtrlPoint(int index, FoldLine * fl);
    void setColor(QColor pcolor);
    void clear_all();
};


#endif //CANVAS_H
