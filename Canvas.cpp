#include <Canvas.h>

int Canvas::getNewID()
{
    return ++id_counter;
}

void Canvas::getImage(QImage* image)
{
   // clearPixelSet();//输出前，先清除无效图元
    image->fill(Qt::yellow);
    for (int i = 0; i < PixelSets.size(); i++) {
        PixelSets[i]->paint(image);
    }
}


void Canvas::drawCurve(ALGORITHM algo, FoldLine *fl)
{
    size_t id=getNewID();
    PixelSet *p = new Curve(algo, fl);  //用折线构造曲线
    p->refresh();
    p->setID(id);
    p->setColor(color);
    PixelSets.push_back(p);
}


FoldLine* Canvas::drawFoldLine(const vector<Point>& vertexes)
{
    int id=getNewID();
    FoldLine *res = new FoldLine(vertexes);
    PixelSet *p = res;
    p->refresh();
    p->setID(id);
    PixelSets.push_back(p);
    return res;
}

void Canvas::drawCtrlPoint(size_t index, FoldLine * foldline)
{
    int id= getNewID();
    PixelSet *p = new CtrlPoint(index, foldline);
    p->setID(id);
    PixelSets.push_back(p);
}

void Canvas::clear_all(){
    PixelSets.clear();
    id_counter = 0;
}
