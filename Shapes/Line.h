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
    Line(ALGORITHM algo,Point start,Point end);
    void refresh();
    void paint(QImage *image);
    //平移

};
#endif // LINE_H
