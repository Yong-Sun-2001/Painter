#include <Algorithms/Ellipse_Fill.h>

void ellipse_fill(int x,int y,int rx,int ry, PixelSet& myset)
{
    for(int i = y;i<y+ry;++i)
    {
        for(int j = x;;++j)
        {
            if(((j-x)*(j-x))*(ry*ry)+((i-y)*(i-y))*(rx*rx)< (ry*ry)*(rx*rx))
            {
                myset.add(j,i);
                myset.add(j,2*y-i);
                myset.add(2*x-j,i);
                myset.add(2*x-j,2*y-i);
            }
            else
                break;
        }
    }
}
