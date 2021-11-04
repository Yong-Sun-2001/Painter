#ifndef CANVAS_H
#define CANVAS_H


#include <vector>
#include <QImage>
#include <Shapes/FoldLine.h>
#include <Shapes/Curve.h>
#include <Shapes/CtrlPoint.h>

class Canvas{

protected:
    size_t color;   //画笔颜色
    std::vector<PixelSet *> PixelSets;   //画布上所有图形的集合
    size_t id_counter = 0;   //图形编号

public:
   // void getid();
    int getNewID();
    void getImage(QImage *image);
    void drawCurve(ALGORITHM algo, FoldLine *fl);
    FoldLine* drawFoldLine(const vector<Point>& vertexes);
    void drawCtrlPoint(size_t index, FoldLine * fl);
};


#endif //CANVAS_H
