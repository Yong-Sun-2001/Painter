#include <Algorithms/line.h>
#include <QDebug>
#include <vector>

void drawLine_DDA(const std::vector<Point>& vertexs, PixelSet& myset){
    size_t n = vertexs.size();
    for(unsigned int it=0;it<n-1;it+=1){
        myset.setColor(Qt::blue);
        int x0=vertexs[it].x;
        int y0=vertexs[it].y;
        int x1=vertexs[it+1].x;
        int y1=vertexs[it+1].y;
        int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
        int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
        int err = (dx>dy ? dx : -dy)/2, e2;
        for(;;){
           myset.add(x0,y0);
           if (x0==x1 && y0==y1) break;
           e2 = err;
           if (e2 >-dx) { err -= dy; x0 += sx; }
           if (e2 < dy) { err += dx; y0 += sy; }
         }
    }
}
