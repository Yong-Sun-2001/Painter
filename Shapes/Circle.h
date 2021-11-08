#ifndef CIRCLE_H
#define CIRCLE_H

//#include "PixelSet.h"
#include <vector>
#include <Algorithms/Midpoint.h>
#include <QPainter>


using namespace std;

class Circle : public PixelSet
{
public:
    Circle();
    Circle(const Circle& B);
    Circle(ALGORITHM algo,int x,int y,int r);
    void paint(QImage *image);
    void refresh();
    void fill(QColor fcolor);
protected:
    vector<Point> vertexes;
    ALGORITHM algorithm;
    int cx;
    int cy;
    int cr;
};

#endif // CIRCLE_H
