#include <Canvas.h>
int Canvas::getNewID()
{
    return ++id_counter;
}

void Canvas::getImage(QImage* image)
{
   // clearPixelSet();//输出前，先清除无效图元
    image->fill(Qt::white);
    for (int i = 0; i < PixelSets.size(); i++) {
        PixelSets[i]->paint(image);
    }
}

int Canvas::getID(int x, int y)
{
    for (int i = 0; i < PixelSets.size(); i++) {
        int res=PixelSets[i]->getID(x, y);
        if (res != -1) return res;
    }
    return -1;
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

void Canvas::drawLine(ALGORITHM algo,Point *st,Point *ed )
{
    size_t id=getNewID();
    Point startp(st->x,st->y);
    Point endp(ed->x,ed->y);
    PixelSet *p = new Line(algo, startp, endp);  //用点构造曲线
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


void Canvas::drawCtrlPoint(int index, FoldLine * foldline)
{
    int id= getNewID();
    PixelSet *p = new CtrlPoint(index, foldline);
    p->setID(id);
    PixelSets.push_back(p);
}

void Canvas::drawPoint(Point pt)
{
    int id=getNewID();
    PixelSet *p=new PixelSet;
    p->setColor(QColor(0xB2, 0xDF, 0xEE));
    p->add(pt.x,pt.y);
    p->setID(id);
    p->setWidth(10);
    PixelSets.push_back(p);
}
void Canvas::setColor(QColor pcolor)
{
    color=pcolor;
}

void Canvas::drawCircle(ALGORITHM algo,Point &center,int r)
{
    int id = getNewID();
    PixelSet *p = new Circle(algo,center.x,center.y,r);
    p->refresh();
    p->setID(id);
    PixelSets.push_back(p);
}

void Canvas::clear_all(){
    PixelSets.clear();
    id_counter = 0;
}
