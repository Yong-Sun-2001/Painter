#ifndef LINE_H
#define LINE_H

#include <Algorithms/DDA.h>
using namespace std;
class Line : public PixelSet
{
protected:
    int x1,x2,y1,y2;
    ALGORITHM algorithm;
public:
    Line();
    Line(const Line& B);
    Line(int ix1, int iy1, int ix2, int iy2, ALGORITHM ialgorithm);
    void refresh();
    void paint(QImage *image);
    void translate(int dx,int dy);
    void rotate(int x, int y, int r);
    void scale(int x, int y, float s);
};
#endif // LINE_H
