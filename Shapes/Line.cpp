#include <Shapes/Line.h>
Line::Line(ALGORITHM algo,Point st,Point ed)
{
    algorithm=algo;
    x1=st.x;
    x2=ed.x;
    y1=st.y;
    y2=ed.y;
}

//void Line::SetAlgorithm(ALGORITHM algo)
//{
//    algorithm = algo;
//}

void Line::refresh()
{
    points.clear();
    if (algorithm == DDA) {
        drawLine_DDA(x1,x2,y1,y2, *this);
    }
}

void Line::translate(int dx, int dy) {
    //PixelSet::translate(dx, dy);
    x1 += dx; y1 += dy;
    x2 += dx; y2 += dy;
}

void Line::paint(QImage * image)
{
    refresh();
    PixelSet::paint(image);
}
