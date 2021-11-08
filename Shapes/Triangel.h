#ifndef TRIANGEL_H
#define TRIANGEL_H

#include "PixelSet.h"
#include <Algorithms/DDA.h>

class Triangel : public PixelSet
{
protected:
    int x1,y1,x2,y2,x3,y3;
    ALGORITHM algorithm;
public:
    Triangel();
    Triangel(const Triangel& B);
    Triangel(int ix1,int iy1,int ix2,int iy2,int ix3,int iy3,ALGORITHM ialgorithm);
    void refresh();
    void paint(QImage *image);
    void translate(int dx,int dy);
    void rotate(int x, int y, int r);
    void scale(int x, int y, float s);
};

#endif // TRIANGEL_H
