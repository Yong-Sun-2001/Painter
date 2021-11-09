#include<Shapes/Ellipse.h>
#include<Algorithms/CommonFuncs.h>
#include <Algorithms/Ellipse_Fill.h>
//画椭圆-中点椭圆生成算法
void drawEllipse(int x,int y,int rx,int ry, PixelSet& myset)
{

    //先绘制四个顶点
    myset.add(0,ry);myset.add(0,-ry);
    myset.add(rx,0);myset.add(-rx,0);

    bool flag=true;//为true表示ry<=rx,即正常的扁平型椭圆
    if(ry>rx){ //高瘦型椭圆，化为正常扁平型的：将作出的点，以y=x对称（也等价于旋转了90°）
        flag=false;
        int temp=rx;//交换rx ry
        rx=ry;
        ry=temp;
    }

    /* 先以原点(0,0)画，再平移；且以下仅需要在第一象限内考虑，其他三个象限可对称得到 */
    /* 椭圆区域1：切线斜率<=1 */
    double p1= ry*ry - rx*rx*ry + rx*rx*0.25; //区域1的决策参量及其初始值
    int xk=0,yk=ry;
    while(2*ry*ry*xk<2*rx*rx*yk){
        xk++;
        if(p1<0){
            p1+= (2*ry*ry*xk + ry*ry);
        }else{
            yk--;
            p1+= (2*ry*ry*xk + ry*ry - 2*rx*rx*yk);
        }
        if(flag){
            myset.add(xk,yk);myset.add(xk,-yk);myset.add(-xk,yk);myset.add(-xk,-yk);
        }else{ //将作出的点，以y=x对称（也等价于旋转了90°）
            myset.add(yk,xk);myset.add(yk,-xk);myset.add(-yk,xk);myset.add(-yk,-xk);
        }

    }
    /* 椭圆区域2：切线斜率>1 */
    double p2 = ry * ry*(xk + 0.5)*(xk + 0.5) + 1.0*rx * rx*(yk - 1)*(yk - 1) - 1.0*rx*rx*ry*ry;
    while(yk>1){ //循环到(rx,0)即可
        yk--;
        if(p2>0){
            p2+= (-2*rx*rx*yk + rx*rx);
        }else{
            xk++;
            p2+= (2*ry*ry*xk -2*rx*rx*yk + rx*rx);
        }
        if(flag){
            myset.add(xk,yk);myset.add(xk,-yk);myset.add(-xk,yk);myset.add(-xk,-yk);
        }else{ //将作出的点，以y=x对称（也等价于旋转了90°）
            myset.add(yk,xk);myset.add(yk,-xk);myset.add(-yk,xk);myset.add(-yk,-xk);
        }
    }
    //平移：(0,0)->(x,y)
    myset.PixelSet::translate(x,y);
}
Ellipse::Ellipse()
{
    type = ELLIPSE;
}
Ellipse::Ellipse(const Ellipse& B):PixelSet(B)
{
    type=ELLIPSE;
    fill_flag=B.fill_flag;
    x = B.x;
    y = B.y;
    rx = B.rx;
    ry = B.ry;
    r = B.r;
}
Ellipse::Ellipse(int ix, int iy, int irx, int iry)
{
    type = ELLIPSE;
    set(ix, iy, irx, iry);
    r = 0;
}
//参数设定
void Ellipse::set(int ix, int iy, int irx, int iry)
{
    x = ix; y = iy;
    rx = irx; ry = iry;
    r = 0;
}
void Ellipse::translate(int dx, int dy)
{
    PixelSet::translate(dx, dy);
    x += dx; y += dy;
}

void Ellipse::refresh()
{
    points.clear();
    if(fill_flag){
        drawEllipse(x, y, rx, ry, *this);
        ellipse_fill(x,y,rx,ry,*this);
        rotate(r);
    }
    else{
        drawEllipse(x, y, rx, ry, *this);
        rotate(r);
    }
}

void Ellipse::rotate(int ix, int iy, int ir)
{
    r += ir;
    rotatePoint(x, y, ix, iy, ir);
    refresh();
}

void Ellipse::rotate(int ir)
{
    size_t n = points.size();
    for (size_t i = 0; i < n; i++) {
        rotatePoint(points[i].x, points[i].y, x, y, ir);
    }
}

void Ellipse::scale(int ix, int iy, float s)
{
    scalePoint(x, y, ix, iy, s);
    rx = qRound(rx*s);
    ry = qRound(ry*s);
    refresh();
}

void Ellipse::fill(QColor fcolor)
{
    fill_flag=true;
    color=fcolor;
    refresh();
}
