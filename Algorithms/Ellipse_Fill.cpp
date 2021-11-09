#include <Algorithms/Ellipse_Fill.h>

void ellipse_fill(int x,int y,int rx,int ry, PixelSet& myset)
{
    for(int i=x;i<=x+rx;++i){
        for(int j=y;j<=y+ry;++j){
            if(((i-x)*(i-x)/rx/rx+(j-y)*(j-y)/ry/ry) <=1 ){
                myset.add(i,j);
                myset.add(2*x-i,j);
                myset.add(i,2*y-j);
                myset.add(2*x-i,2*y-j);
            }
            else
                break;
        }
    }
}
