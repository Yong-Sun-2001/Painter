#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <Algorithms/DDA.h>

class Triangle : public PixelSet
{
protected:
    int x1,y1,x2,y2,x3,y3;
    ALGORITHM algorithm;
    ALGORITHM fill_algorithm;
    vector<Point> vertexs;
public:
    Triangle();
    Triangle(const Triangle& B);
    Triangle(int ix1,int iy1,int ix2,int iy2,int ix3,int iy3,ALGORITHM ialgorithm);
    void refresh();
    void paint(QImage *image);
    void translate(int dx,int dy);
    void rotate(int x, int y, int r);
    void scale(int x, int y, float s);
    void fill(QColor fcolor);
};

#endif // TRIANGLE_H
