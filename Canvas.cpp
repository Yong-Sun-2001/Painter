#include <Canvas.h>
#include <Shapes/FoldLine.h>
#include <Shapes/Curve.h>
#include <Shapes/CtrlPoint.h>
#include <Shapes/Line.h>
#include<Shapes/Circle.h>
#include <Shapes/Triangle.h>
#include <Shapes/Ellipse.h>
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
            case CIRCLE:
                p = new Circle(*((Circle*)B.PixelSets[i]));
                break;
            case TRIANGLE:
                p = new Triangle(*((Triangle*)B.PixelSets[i]));
                break;
            case ELLIPSE:
                p = new Ellipse(*((Ellipse*)B.PixelSets[i]));
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
            case POLYGON:
                p = new Polygon(*((Polygon*)B.PixelSets[i]));
                break;
            case CIRCLE:
                p = new Circle(*((Circle*)B.PixelSets[i]));
                break;
            case RECTANGLE:
                p=new Rectangle(*((Rectangle*)B.PixelSets[i]));
                break;
            case TRIANGLE:
                p = new Triangle(*((Triangle*)B.PixelSets[i]));
                break;
            case ELLIPSE:
                p = new Ellipse(*((Ellipse*)B.PixelSets[i]));
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
    clearPixelSet();//输出前，先清除无效图元
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
    p->setWidth(penWidth);
    PixelSets.push_back(p);
}

void Canvas::drawLine(int id, int x1, int y1, int x2, int y2, ALGORITHM algorithm)
{
    PixelSet *p;
    switch (algorithm)
    {
    case DDA:
        p = new Line(x1, y1, x2, y2, DDA);
        break;
    default:
        p = new Line(x1, y1, x2, y2, DDA);
        break;
    }
    p->refresh();
    p->setID(id);
    p->setColor(color);
    p->setWidth(penWidth);
    PixelSets.push_back(p);
}

void Canvas::drawRectangle(int id, int x1, int y1, int x2, int y2)
{
    PixelSet *p;
    p = new Rectangle(x1, y1, x2, y2);
    p->refresh();
    p->setID(id);
    p->setColor(color);
    p->setWidth(penWidth);
    PixelSets.push_back(p);
}

void Canvas::drawEllipse(int id, int x, int y, int rx, int ry)
{
    PixelSet *p = new Ellipse(x, y, rx, ry);
    p->refresh();
    p->setID(id);
    p->setColor(color);
    p->setWidth(penWidth);
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

void Canvas::drawDotPoint(int id, int x, int y, int iwidth, QColor icolor)
{
    PixelSet *p = new DotPoint(x, y, iwidth, icolor);
    p->setID(id);
    PixelSets.push_back(p);
}

void Canvas::drawPolygon(int id, const vector<Point> &vertexs, ALGORITHM algorithm)
{
    bool hasID = false;
    int keyIndex = -1;
    for (int i = 0; i < PixelSets.size(); i++) {
        if (PixelSets[i]->id == id) {
            hasID = true; keyIndex = i;
        }
    }
    if (hasID) { //已有，则重画
        delete PixelSets[keyIndex];
        if (algorithm == DDA)
            PixelSets[keyIndex] = new Polygon(vertexs, DDA);
        PixelSets[keyIndex]->refresh();
        PixelSets[keyIndex]->setID(id);
        PixelSets[keyIndex]->setColor(color);
        PixelSets[keyIndex]->setWidth(penWidth);
    }
    else {
        PixelSet *p;
        if (algorithm == DDA)
            p = new Polygon(vertexs, DDA);
        p->refresh();
        p->setID(id);
        p->setColor(color);
        p->setWidth(penWidth);
        PixelSets.push_back(p);
    }
}

void Canvas::setColor_pen(QColor pcolor)
{
    color=pcolor;
}

void Canvas::setColor_fill(QColor pcolor)
{
    fill_color=pcolor;
}

void Canvas::setPen_width(int w)
{
    penWidth = w;
}

void Canvas::drawCircle(int id,ALGORITHM algo,Point &center,int r)
{
    PixelSet *p = new Circle(algo,center.x,center.y,r);
    p->refresh();
    p->setID(id);
    p->setColor(color);
    p->setWidth(penWidth);
    PixelSets.push_back(p);
}

void Canvas::drawTriangle(int id, int x1, int y1, int x2, int y2,int x3,int y3, ALGORITHM algorithm)
{
    PixelSet *p;
    switch (algorithm)
    {
    case DDA:
        p = new Triangle(x1, y1, x2, y2, x3, y3, DDA);
        break;
    default:
        p = new Triangle(x1, y1, x2, y2, x3, y3, DDA);
        break;
    }
    p->refresh();
    p->setID(id);
    p->setColor(color);
    p->setWidth(penWidth);
    PixelSets.push_back(p);
}

void Canvas::clear_all(){
    PixelSets.clear();
    id_counter = 0;
}

void Canvas::setColor_pen(int r, int g, int b)
{
    color.setRgb(r, g, b);
}

void Canvas::setColor_fill(int r, int g, int b)
{
    fill_color.setRgb(r, g, b);
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
    for (auto it = PixelSets.begin(); it != PixelSets.end();++it) {
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
    }
    return;
}

void Canvas::fill(int id)
{
    for (auto it = PixelSets.begin(); it != PixelSets.end();++it) {
        if ((*it)->id == id) {
            (*it)->fill(fill_color);
            return;
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
