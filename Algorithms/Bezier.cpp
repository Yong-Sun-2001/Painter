#include <Algorithms/Bezier.h>
#include <QDebug>

static double **P_x = nullptr; //中间计算过程需要用到的二维数组
static double **P_y = nullptr; //中间计算过程需要用到的二维数组


//获得参数u对应的离散点（函数调用前需要保证P已分配了足够的空间）
Point getPoint_Bezier(double u, const std::vector<Point> &vertexs) {
    //初始化
    size_t n = vertexs.size();
    for (size_t i = 0; i < n; i++) {
        P_x[i][0] = vertexs[i].x;
        P_y[i][0] = vertexs[i].y;
    }
    //依次降阶计算（类似动态规划的计算过程）
    for (size_t r = 1; r < n; r++) {
        for (size_t i = 0; i < n - r; i++) {
            //P[i][r]=(1-u)*P[i][r-1]+u*P[i+1][r-1]; //递推式 - 关键
            P_x[i][r] = (1 - u)*P_x[i][r - 1] + u * P_x[i + 1][r - 1]; //注：此出处计算应该全程使用double类型，最终取点的时候再取整，否则误差很大，曲线不够光滑
            P_y[i][r] = (1 - u)*P_y[i][r - 1] + u * P_y[i + 1][r - 1];
        }
    }
    return Point(qRound(P_x[0][n - 1]), qRound(P_y[0][n - 1]));
}

//决策步长
double getStep_Bezier(const std::vector<Point> &vertexs) {
    double sum = 1;
    for (size_t i = 1; i < vertexs.size(); i++) {
        sum += sqrt((vertexs[i].x - vertexs[i - 1].x)*(vertexs[i].x - vertexs[i - 1].x) + (vertexs[i].y - vertexs[i - 1].y)*(vertexs[i].y - vertexs[i - 1].y));
    }
    return 1 / (sum*1.5);
}

//根据参数得出Bezier曲线
void drawCurve_Bezier(const std::vector<Point> &vertexs, PixelSet &myset)
{
    size_t n = vertexs.size();
    //分配空间
    P_x = new double*[n];
    P_y = new double*[n];
    for (size_t i = 0; i < n; i++) {
        P_x[i] = new double[n];
        P_y[i] = new double[n];
    }

    //以一定步长生成曲线上的离散点
    double STEP = getStep_Bezier(vertexs);
    for (double u = 0.0; u <= 1.0; u += STEP) {
        Point temp = getPoint_Bezier(u, vertexs);
        myset.add(temp.x, temp.y);
    }
    //释放空间
    for (size_t i = 0; i < n; i++) {
        delete[] P_x[i];
        delete[] P_y[i];
    }
    delete[] P_x;
    delete[] P_y;
}
