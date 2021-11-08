#include <Algorithms/DDA.h>
#include <QDebug>

void drawLine_DDA(int x0,int x1,int y0,int y1, PixelSet& myset){
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

void drawPolygon_DDA(const vector<Point>& vertexs, PixelSet& myset)
{
    size_t n=vertexs.size();
    for(size_t i=0;i<n-1;i++){
        drawLine_DDA(vertexs[i].x,vertexs[i+1].x,vertexs[i].y,vertexs[i+1].y,myset);
    }
}

void drawTriangel_DDA(int x1,int y1,int x2,int y2,int x3,int y3,PixelSet& myset)
{
    drawLine_DDA(x1, x2, y1, y2, myset);
    drawLine_DDA(x2, x3, y2, y3, myset);
    drawLine_DDA(x3, x1, y3, y1, myset);
}
