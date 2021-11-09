#ifndef CTRLPOINT_H
#define CTRLPOINT_H
#include <Shapes/FoldLine.h>
#include <QColor>
#include <Canvas.h>

class CtrlPoint : public PixelSet
{
protected:
    int width;//点的粗细
    int index;
    FoldLine *foldline;
    friend class Canvas;

public:
    CtrlPoint() { type = CTRLPOINT; }
    CtrlPoint(const CtrlPoint& B, Canvas&canvas);
    CtrlPoint(int iindex, FoldLine *ifoldline,int iwidth = 10, QColor icolor = Qt::green);
    int getID(int x, int y);
    void paint(QImage *image);
    void translate(int dx,int dy);
};

#endif // CTRLPOINT_H
