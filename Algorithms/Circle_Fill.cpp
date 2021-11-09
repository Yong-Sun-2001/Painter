#include <Algorithms/Circle_Fill.h>

void circle_fill(int cx,int cy,int cr,PixelSet& myset){
    for(int i=cx;i<=cx+cr;++i){
        for(int j=cy;j<=cy+cr;++j){
            if((cx-i)*(cx-i)+(cy-j)*(cy-j)<=cr*cr){
                myset.add(i,j);
                myset.add(2*cx-i,j);
                myset.add(i,2*cy-j);
                myset.add(2*cx-i,2*cy-j);
            }
            else
                break;
        }
    }
}
