#ifndef CANVAS_H
#define CANVAS_H


#include <vector>
#include <QImage>
#include <QColor>
#include <Shapes/PixelSet.h>
#include <Shapes/FoldLine.h>
#include <Shapes/Curve.h>
#include <Shapes/CtrlPoint.h>
#include <Shapes/Line.h>
#include<Shapes/Circle.h>

class Canvas{

protected:
    QColor color=0xFF0000;   //画笔颜色

public:
    Canvas():color(0, 0, 0) {}
    Canvas(const Canvas& B);
    const Canvas& operator=(const Canvas& B);
    ~Canvas();
    int id_counter = 0;   //图形编号
    std::vector<PixelSet *> PixelSets;   //画布上所有图形的集合
    int getID(int x, int y);
    int getType(int id);
    int getNewID();
    void delID(int id);
    void getImage(QImage *image);
    void drawCurve(int id,ALGORITHM algo, FoldLine *fl);
    void drawPoint(int id,Point pt);
    void drawLine(int id,ALGORITHM algo,Point *st,Point *ed);
    void drawCircle(int id,ALGORITHM algo,Point &center,int x);
    FoldLine* drawFoldLine(int id,const vector<Point>& vertexes);
    void drawCtrlPoint(int id,int index, FoldLine * fl);
    void setColor(int r, int g, int b);
    void setColor(QColor pcolor);
    void clear_all();
    void translate(int id, int dx, int dy);
    void rotate(int id, int x, int y, int r);
    void scale(int id, int x, int y, double s);
    void clip(int id, int ix1, int iy1, int ix2, int iy2, ALGORITHM algorithm = COHEN);
    void clipAll(int ix1, int iy1, int ix2, int iy2, ALGORITHM algorithm = COHEN);
    void clearPixelSet();
    PixelSet* getPixelSet(int id);
};
#endif //CANVAS_H
