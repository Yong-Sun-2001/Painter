#include <Algorithms/ScanLine_Fill.h>
using namespace std;
MyPolygon::MyPolygon(const vector<Point>& vertexs){
    PolygonNum = vertexs.size();
    xmin = INT_MAX;
    xmax = INT_MIN;
    ymin = INT_MAX;
    ymax = INT_MIN;
    for (int i = 0; i < PolygonNum; i++)
    {
        vertexces[i].x = vertexs[i].x;
        vertexces[i].y = vertexs[i].y;
        if (vertexs[i].x>xmax)
        {
            xmax = vertexs[i].x;
        }
        if (vertexs[i].y > ymax)
        {
            ymax = vertexs[i].y;
        }
        if (vertexs[i].x < xmin)
        {
            xmin = vertexs[i].x;
        }
        if (vertexs[i].y < ymin)
        {
            ymin = vertexs[i].y;
        }
    }
}
void FillPolygonScanline(const vector<Point>& vertexs, PixelSet& myset) {
    MyPolygon P1(vertexs);
    MyPolygon *P(&P1);
    MyEdge* pET[720];
    MyEdge* AET;

    for (int i = 0; i < P->ymax; i++)
    {
        pET[i] = new MyEdge();
        pET[i]->nextEdge = nullptr;
    }
    AET = new MyEdge();
    AET->nextEdge = nullptr;

    //建立边表ET
    for (int i = 0; i < P->PolygonNum; i++)
    {
        //取出当前点1前后相邻的共4个点，点1与点2的连线作为本次循环处理的边，另外两个点点0和点3用于计算奇点
        int x0 = P->vertexces[(i - 1 + P->PolygonNum) % P->PolygonNum].x;
        int x1 = P->vertexces[i].x;
        int x2 = P->vertexces[(i + 1) % P->PolygonNum].x;
        int x3 = P->vertexces[(i + 2) % P->PolygonNum].x;
        int y0 = P->vertexces[(i - 1 + P->PolygonNum) % P->PolygonNum].y;
        int y1 = P->vertexces[i].y;
        int y2 = P->vertexces[(i + 1) % P->PolygonNum].y;
        int y3 = P->vertexces[(i + 2) % P->PolygonNum].y;
        //水平线直接舍弃
        if (y1 == y2)
            continue;
        //分别计算下端点y坐标、上端点y坐标、下端点x坐标和斜率倒数
        int ymin = y1 > y2 ? y2 : y1;
        int ymax = y1 > y2 ? y1 : y2;
        float x = y1 > y2 ? x2 : x1;
        float dx = (x1 - x2) * 1.0f / (y1 - y2);
        //奇点特殊处理，若点2->1->0的y坐标单调递减则y1为奇点，若点1->2->3的y坐标单调递减则y2为奇点
        if (((y1 < y2) && (y1 > y0)) || ((y2 < y1) && (y2 > y3)))
        {
            ymin++;
            x += dx;
        }
        //创建新边，插入边表ET
        MyEdge* q = new MyEdge();
        q->ymax = ymax;
        q->x = x;
        q->deltax = dx;
        q->nextEdge = pET[ymin]->nextEdge;
        pET[ymin]->nextEdge = q;
    }

    //扫描线从下往上扫描，y坐标每次加1
    for (int i = P->ymin; i < P->ymax; i++)
    {
        //取出ET中当前扫描行的所有边并按x的递增顺序（若x相等则按dx的递增顺序）插入AET
        while (pET[i]->nextEdge)
        {
            //取出ET中当前扫描行表头位置的边
            MyEdge* pInsert = pET[i]->nextEdge;
            MyEdge* p = AET;
            //在AET中搜索合适的插入位置
            while (p->nextEdge)
            {
                if (pInsert->x > p->nextEdge->x)
                {
                    p = p->nextEdge;
                    continue;
                }
                if (pInsert->x == p->nextEdge->x && pInsert->deltax > p->nextEdge->deltax)
                {
                    p = p->nextEdge;
                    continue;
                }
                //找到位置
                break;
            }
            //将pInsert从ET中删除，并插入AET的当前位置
            pET[i]->nextEdge = pInsert->nextEdge;
            pInsert->nextEdge = p->nextEdge;
            p->nextEdge = pInsert;
        }

        //AET中的边两两配对并填色
        MyEdge* p = AET;
        while (p->nextEdge && p->nextEdge->nextEdge)
        {
            for (int x = p->nextEdge->x; x < p->nextEdge->nextEdge->x; x++)
            {
                myset.add(x,i);
            }
            p = p->nextEdge->nextEdge;
        }

        //删除AET中满足y=ymax的边
        p = AET;
        while (p->nextEdge)
        {
            if (p->nextEdge->ymax == i)
            {
                MyEdge* pDelete = p->nextEdge;
                p->nextEdge = pDelete->nextEdge;
                pDelete->nextEdge = nullptr;
                delete pDelete;
            }
            else
            {
                p = p->nextEdge;
            }
        }

        //更新AET中边的x值，进入下一循环
        p = AET;
        while (p->nextEdge)
        {
            p->nextEdge->x += p->nextEdge->deltax;
            p = p->nextEdge;
        }

    }
}
