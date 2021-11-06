#include<Algorithms/Midpoint.h>
//圆心
static int cx;
static int cy;

void midPointcircle(const int x0,const int y0,const int r,PixelSet& mySet)
{
    cx = x0;
    cy = y0;
    int x, y;
    x = 0;
    y = -r;
    int e = 1 - r;
    while (x <= -y)
    {
        if (e < 0)
            e += (2 * x + 3);
        else
        {
            e += (2 * (x + y) + 5);
            y++;//y move to bottom
        }
        x++;
        circlePoint(x, y, mySet);
    }
}
void circlePoint(int x,int y, PixelSet& mySet)
{
    mySet.add(x + cx, y + cy);       mySet.add(y + cx, x + cy);
    mySet.add(-x + cx, y + cy);      mySet.add(y + cx, -x + cy);
    mySet.add(x + cx, -y + cy);      mySet.add(-y + cx, x + cy);
    mySet.add(-x + cx, -y + cy);     mySet.add(-y + cx, -x + cy);
}
