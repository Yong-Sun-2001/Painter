#ifndef CTRLPOINT_H
#define CTRLPOINT_H
#include <Shapes/FoldLine.h>
#include <QColor>
class CtrlPoint : public PixelSet
{
protected:
    int width;//点的粗细
    size_t index;
    FoldLine *foldline;
    Point *pt;
    friend class Canvas;
public:
    CtrlPoint(size_t iindex, FoldLine *ifoldline,int iwidth = 10, QColor icolor = QColor(0xB2, 0xDF, 0xEE));
    CtrlPoint(size_t iindex, Point *p,int iwidth = 10, QColor icolor = QColor(0xB2, 0xDF, 0xEE));
    int getID(int x, int y);
    void paint(QImage *image);
};

#endif // CTRLPOINT_H
