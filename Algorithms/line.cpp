#include <Algorithms/line.h>
#include <QDebug>
#include <vector>

void drawCurve_Line(const std::vector<Point>& vertexs, PixelSet& myset){
    size_t n = vertexs.size();
    for(unsigned int it=0;it<n;it+=2){
        myset.add(vertexs[it].x,vertexs[it].y);
    }
}
