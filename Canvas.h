#ifndef CANVAS_H
#define CANVAS_H


#include <vector>
#include <QImage>
#include <Shapes/FoldLine.h>
#include <Shapes/Curve.h>
#include <Shapes/CtrlPoint.h>
#include <Shapes/Line.h>

class Canvas{

protected:
    size_t color=0xFF0000;   //画笔颜色

public:
    size_t id_counter = 0;   //图形编号
    std::vector<PixelSet *> PixelSets;   //画布上所有图形的集合
   // void getid();
    int getNewID();
    void getImage(QImage *image);
    void drawCurve(ALGORITHM algo, FoldLine *fl);
    void drawLine(ALGORITHM algo,Point *st,Point *ed);
    FoldLine* drawFoldLine(const vector<Point>& vertexes);
    void drawCtrlPoint(size_t index,Point *p);
    void drawCtrlPoint(size_t index, FoldLine * fl);
    void set_color(size_t pcolor);
    void clear_all();
};


#endif //CANVAS_H
