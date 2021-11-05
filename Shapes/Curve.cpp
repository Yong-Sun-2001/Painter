#include <Shapes/Curve.h>
Curve::Curve(ALGORITHM algo,FoldLine * fl)
{
    algorithm=algo;
    foldline = fl;
}

//void Curve::SetAlgorithm(ALGORITHM algo)
//{
//    algorithm = algo;
//}

void Curve::refresh()
{
    points.clear();
    vertexes = foldline->vertexes;
    if (algorithm == BEZIER) {
        drawCurve_Bezier(vertexes, *this);
    }
    else if(algorithm == LINE){
        drawCurve_Line(vertexes, *this);
    }
}

void Curve::paint(QImage * image)
{
    vertexes = foldline->vertexes;
    refresh();
    PixelSet::paint(image);
}
