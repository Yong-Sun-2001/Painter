#include <Shapes/Polygon.h>
#include <Algorithms/DDA.h>
#include <Algorithms/CommonFuncs.h>
Polygon::Polygon()
{
    type = POLYGON;
}
Polygon::Polygon(const Polygon& B) : PixelSet(B)
{
    vertexs.clear();
    vertexs.assign(B.vertexs.begin(), B.vertexs.end());
    fill_flag=B.fill_flag;
    algorithm = B.algorithm;
    polygon_closed = B.polygon_closed;
}
Polygon::Polygon(const vector<Point>& ivertexs, ALGORITHM ialgorithm)
{
    type = POLYGON;
    set(ivertexs, ialgorithm);
}
void Polygon::set(const vector<Point>& ivertexs, ALGORITHM ialgorithm)
{
    vertexs.assign(ivertexs.begin(), ivertexs.end());
    algorithm = ialgorithm;
}
void Polygon::translate(int dx, int dy)
{
    PixelSet::translate(dx, dy);
    for (int i = 0; i < vertexs.size(); i++) {
        vertexs[i].x += dx;
        vertexs[i].y += dy;
    }
}

void Polygon::refresh()
{
    points.clear();
    if (fill_flag){
        /*
        size_t n=vertexs.size();
        int maxx=0;
        for(size_t i=0;i<n-1;i++){
            if(vertexs[i].x>maxx){
                maxx=vertexs[i].x;
            }
        }
        for(size_t i=0;i<n-1;i++){
            int Ymax=(vertexs[i].y>vertexs[(i+1)%n].y)? vertexs[i].y:vertexs[(i+1)%n].y;
            int Ymin=(vertexs[i].y<=vertexs[(i+1)%n].y)? vertexs[i].y:vertexs[(i+1)%n].y;
            for (int y = Ymin; y < Ymax; y++){
                int x=(y - vertexs[i].y) * (vertexs[(i+1)%n].x-vertexs[i].x) / (vertexs[(i+1)%n].y -vertexs[i].y) +vertexs[i].x;
                while (x <= maxx)
                {
                    bool in=false;
                    for(auto j=vertexs.begin();j!=vertexs.end();){
                        if(j->x==x&&j->y==y){
                            j=vertexs.erase(j);
                            in=true;
                            break;
                        }
                        else{
                            j++;
                        }
                    }
                    if(!in){
                        this->add(x,y);
                    }
                    x++;
                }
            }
        }
        */
    }
    else{
        if (algorithm == DDA) {
            drawPolygon_DDA(vertexs, *this);
        }
    }
}

void Polygon::rotate(int x, int y, int r)
{
    size_t n = vertexs.size();
    for (size_t i = 0; i < n; i++) {
        rotatePoint(vertexs[i].x, vertexs[i].y, x, y, r);
    }
    refresh();
}

void Polygon::scale(int x, int y, float s)
{
    size_t n = vertexs.size();
    for (size_t i = 0; i < n; i++) {
        scalePoint(vertexs[i].x, vertexs[i].y, x, y, s);
    }
    refresh();
}

void Polygon::fill(QColor fcolor)
{
    fill_flag=true;
    color=fcolor;
    refresh();
}
