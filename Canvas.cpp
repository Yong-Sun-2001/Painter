#include <Canvas.h>

Canvas::~Canvas()
{
    for (int i = 0; i < PixelSets.size(); i++) {
        delete PixelSets[i];
    }
}
Canvas::Canvas(const Canvas & B)
{
    if (this != &B) {
        color = B.color;
        PixelSets.clear();
        for (int i = 0; i < B.PixelSets.size(); i++) {
            //TODO:图元复制
            PixelSet *p=nullptr;
            switch (B.PixelSets[i]->type)
            {
            case LINE:
                p = new Line(*((Line*)B.PixelSets[i]));
                break;
            case CURVE:
                p = new Curve(*((Curve*)B.PixelSets[i]), *this);
                break;
            case FOLDLINE:
                p = new FoldLine(*((FoldLine*)B.PixelSets[i]));
                break;
            default:
                break;
            }
            if (p != nullptr)
                PixelSets.push_back(p);
        }
    }
}

const Canvas & Canvas::operator=(const Canvas & B)
{
    if (this != &B) {
        color = B.color;
        PixelSets.clear();
        for (int i = 0; i < B.PixelSets.size(); i++) {
            //TODO:图元复制
            PixelSet *p;
            switch (B.PixelSets[i]->type)
            {
            case LINE:
                p = new Line(*((Line*)B.PixelSets[i]));
                break;
            case CURVE:
                p = new Curve(*((Curve*)B.PixelSets[i]), *this);
                break;
            case FOLDLINE:
                p = new FoldLine(*((FoldLine*)B.PixelSets[i]));
                break;
            case CTRLPOINT:
                p = new CtrlPoint(*((CtrlPoint*)B.PixelSets[i]), *this);
                break;
            default:
                p = nullptr;
                break;
            }
            if (p!=nullptr)
                PixelSets.push_back(p);
        }
    }
    return *this;
}

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
void Canvas::translate(int id, int dx, int dy)
{
    for (size_t i = 0; i < PixelSets.size(); i++) {
        if (PixelSets[i]->id == id) {
            PixelSets[i]->translate(dx, dy);
            return;
        }
    }
}
void Canvas::rotate(int id, int x, int y, int r)
{
    for (auto i = PixelSets.begin(); i != PixelSets.end(); i++) {
        if ((*i)->id == id) {
            (*i)->rotate(x, y, r);
            return;
        }
    }
}

void Canvas::scale(int id, int x, int y, double s)
{
    for (auto i = PixelSets.begin(); i != PixelSets.end(); i++) {
        if ((*i)->id == id) {
            (*i)->scale(x, y, s);
            return;
        }
    }
}
void Canvas::drawCurve(int id, ALGORITHM algorithm, FoldLine *foldline)
{
    PixelSet *p = new Curve(algorithm, foldline);
    p->setID(id);
    p->setColor(color);
    PixelSets.push_back(p);
}

void Canvas::drawLine(int id,ALGORITHM algo,Point *st,Point *ed)
{
    Point startp(st->x,st->y);
    Point endp(ed->x,ed->y);
    PixelSet *p = new Line(algo, startp, endp);  //用点构造曲线
    p->refresh();
    p->setID(id);
    p->setColor(color);
    PixelSets.push_back(p);
}

FoldLine* Canvas::drawFoldLine(int id,const vector<Point>& vertexes)
{
    FoldLine *res = new FoldLine(vertexes);
    PixelSet *p = res;
    p->refresh();
    p->setID(id);
    PixelSets.push_back(p);
    return res;
}


void Canvas::drawCtrlPoint(int id, int index, FoldLine * foldline)
{
    PixelSet *p = new CtrlPoint(index, foldline);
    p->setID(id);
    PixelSets.push_back(p);
}

void Canvas::drawPoint(int id,Point pt)
{
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

void Canvas::drawCircle(int id,ALGORITHM algo,Point &center,int r)
{
    PixelSet *p = new Circle(algo,center.x,center.y,r);
    p->refresh();
    p->setID(id);
    PixelSets.push_back(p);
}

void Canvas::clear_all(){
    PixelSets.clear();
    id_counter = 0;
}

void Canvas::setColor(int r, int g, int b)
{
    color.setRgb(r, g, b);
}

int Canvas::getType(int id)
{
    for (size_t i = 0; i < PixelSets.size(); i++) {
        if (PixelSets[i]->id == id) {
            return PixelSets[i]->type;
        }
    }
    return -1;
}

void Canvas::delID(int id)
{
    for (auto it = PixelSets.begin(); it != PixelSets.end();) {
        if ((*it)->id == id) {
            if ((*it)->type == CURVE) {
                delete (Curve*)(*it);
            }
            else{
                delete (*it);
            }
            it = PixelSets.erase(it);
            return;
        }
        else {
            ++it;
        }
    }
    return;
}

PixelSet * Canvas::getPixelSet(int id)
{
    for (size_t i = 0; i < PixelSets.size(); i++) {
        if (PixelSets[i]->id == id) {
            return PixelSets[i];
        }
    }
    return nullptr;
}

void Canvas::clearPixelSet()
{
    for (auto it = PixelSets.begin(); it != PixelSets.end();) {
        if ((*it)->clear_flag == true) {
            delete (*it);
            it = PixelSets.erase(it);
        }
        else {
            ++it;
        }
    }
    return;
}

void Canvas::clip(int id, int ix1, int iy1, int ix2, int iy2, ALGORITHM algorithm)
{
    int x1 = min(ix1, ix2); int x2 = max(ix1, ix2);
    int y1 = min(iy1, iy2); int y2 = max(iy1, iy2);
    for (auto i = PixelSets.begin(); i != PixelSets.end(); i++) {
        if ((*i)->id == id) {
            (*i)->clip(x1, y1, x2, y2, algorithm);
            return;
        }
    }
}

void Canvas::clipAll(int ix1, int iy1, int ix2, int iy2, ALGORITHM algorithm)
{
    int x1 = min(ix1, ix2); int x2 = max(ix1, ix2);
    int y1 = min(iy1, iy2); int y2 = max(iy1, iy2);
    for (auto i = PixelSets.begin(); i != PixelSets.end(); i++) {
        (*i)->clip(x1, y1, x2, y2, algorithm);
    }
}
