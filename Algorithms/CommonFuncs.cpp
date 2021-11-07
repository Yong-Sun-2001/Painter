#include <Algorithms/CommonFuncs.h>
const double PI=3.1415926535;
void rotatePoint(int &x, int &y, int xr, int yr, int r)
{
    double theta=r*PI/180.0;
    int x1,y1,x2,y2;
    x1=x-xr;
    y1=y-yr;
    x2=qRound(x1*cos(theta)-y1*sin(theta));
    y2=qRound(x1*sin(theta)+y1*cos(theta));
    x=x2+xr;
    y=y2+yr;
}
//利用数学公式 cos=(a2+b2-c2)/2ab（c为对边）
int getRotateR(int x1, int y1, int xr, int yr, int x2, int y2)
{
    x1 = x1 - xr;
    y1 = y1 - yr;
    x2 = x2 - xr;
    y2 = y2 - yr;
    double a2 = x1 * x1 + y1 * y1;
    double b2 = x2 * x2 + y2 * y2;
    double c2 = (x1-x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    double cos_temp = (a2 + b2 - c2) / (2 * sqrt(a2)*sqrt(b2));
    double theta = acos(cos_temp);
    if (x1*y2 < x2*y1) theta = -theta;
    int r = qRound(theta * 180 / PI);
    return r;
}

void scalePoint(int &x, int &y, int sx, int sy, double s)
{
    int x1,y1,x2,y2;
    x1=x-sx;
    y1=y-sy;
    x2=qRound(x1*s);
    y2=qRound(y1*s);
    x=x2+sx;
    y=y2+sy;
}

double getScaleS(int x1, int y1, int sx, int sy, int x2, int y2)
{
    x1 -= sx;
    y1 -= sy;
    x2 -= sx;
    y2 -= sy;
    double res = 1;
    double x1y1 = (x1 * x1 + y1 * y1);
    double x2y2 = (x2 * x2 + y2 * y2);
    res = sqrt(x2y2 / x1y1);
    return res;
}

//求交点
void crossX(int x1,int y1,int x2,int y2,int x,int &y){
    double a=x;
    y=qRound((y2-y1)*(a-x1)/(x2-x1)+y1);
}
void crossY(int x1,int y1,int x2,int y2,int &x,int y){
    double b=y;
    x=qRound((x2-x1)*(b-y1)/(y2-y1)+x1);
}
