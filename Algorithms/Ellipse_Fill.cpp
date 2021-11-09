#include <Algorithms/Ellipse_Fill.h>

void ellipse_fill(int x,int y,int rx,int ry, PixelSet& myset)
{
    for(int i=x;i<=x+rx;++i){
        for(int j=y;j<=y+ry;++j){
            if(((i-x)*(i-x)/rx/rx+(j-y)*(j-y)/ry) <= (rx*rx+ry*ry)){
                myset.add(i,j);
                myset.add(2*rx-i,j);
                myset.add(i,2*ry-j);
                myset.add(2*rx-i,2*ry-j);
            }
            else
                break;
        }
    }
}
