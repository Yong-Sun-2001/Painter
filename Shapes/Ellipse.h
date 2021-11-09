#ifndef ELLIPSE_H
#define ELLIPSE_H
#include <Shapes/PixelSet.h>
class Ellipse :public PixelSet
{
    int x, y;
    int rx, ry;
    int r = 0;
    //ALGORITHM fill_algorithm;
public:
    Ellipse();
    Ellipse(const Ellipse& B);
    Ellipse(int ix, int iy, int irx, int iry);
    void set(int ix, int iy, int irx, int iry);
    void refresh();
    void translate(int dx, int dy);
    void rotate(int ix, int iy, int ir); //绕点(ix,iy旋转)顺时针
    void rotate(int ir); //绕自身中心旋转
    void scale(int x, int y, float s);
    void fill(QColor fcolor);
};

#endif // ELLIPSE_H
