#pragma once

#include <QMainWindow>
#include <QMouseEvent>
#include <QLabel>
#include <Canvas.h>
#include <vector>
#include <Shapes/PixelSet.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }   //声明应用窗口需要使用的Ui
QT_END_NAMESPACE

class Painter : public QMainWindow   //应用窗口
{
    Q_OBJECT

public:
    Painter(QWidget *parent = nullptr);
    ~Painter();

private:
    Ui::MainWindow *ui;
    Canvas realCanvas;
    Canvas bufCanvas;

//=====================================================================
// 状态及数据
    /*颜色*/
    void refresh_ColorIcon_pen();
    void refresh_ColorIcon_fill();
    QColor penColor=Qt::black;
    QColor fillColor=Qt::red;

    /*画布状态*/
    bool buf=false;

    /*id管理*/
    int ID_Counter = 0;
    int getNewID();

    /*标签*/
    QLabel* statusLabel_pos;
    QLabel* statusLabel_state;
    void refreshStateLabel();

    /*编辑状态*/
    enum Draw_State{DRAW_CURVE,DRAW_LINE,NOT_DRAWING,DRAW_CIRCLE,DRAW_ROTATE,
                    DRAW_SCALE,DRAW_POLYGON,DRAW_RECTANGLE,DRAW_TRIANGLE};
    Draw_State state=NOT_DRAWING;
    void setState(Draw_State s);
    QString state_info="状态：NOT_DRAWING ";

    /*选中*/
    int selected_ID;

    /*旋转*/
    enum ROTATE_STATE { ROTATE_NON, ROTATE_READY, ROTATE_BEGIN };
    ROTATE_STATE rotate_state = ROTATE_NON;
    int rotate_rx, rotate_ry;
    int init_x, init_y;

    /*缩放*/
    enum SCALE_STATE { SCALE_NON, SCALE_READY, SCALE_BEGIN };
    SCALE_STATE scale_state = SCALE_NON;
    int scale_rx, scale_ry;

    /*矩形*/
    int rec_x1, rec_y1, rec_x2, rec_y2;
    enum REC_STATE { REC_NON_POINT, REC_POINTA };
    REC_STATE rec_state = REC_NON_POINT;

    /*多边形*/
    int startX, startY;
    vector<Point> poly_points;
    vector<Point> bufpoly_points;
    int poly_id;
    enum POLY_STATE { POLY_NON_POINT, POLY_PAINTING };
    POLY_STATE poly_state = POLY_NON_POINT;
    int AUTO_BIAS = 15; //多边形绘图自动贴合开启的距离（圆形区域的半径）
    bool autoPoly(int &nowx, int &nowy);

    /*曲线*/
    std::vector<Point> curve_points;
    enum CURVE_STATE { CURVE_NON, CURVE_BEGIN };
    CURVE_STATE curve_state = CURVE_NON;

    /*直线*/
    int line_Ax, line_Ay, line_Bx, line_By;
    enum LINE_STATE { LINE_NON_POINT, LINE_POINTA };
    LINE_STATE line_state = LINE_NON_POINT;

    /*圆*/
    Point circle_center;
    int circle_r;//半径
    enum CIRCLE_STATE {CIRCLE_NON,CIRCLE_FINISH};
    CIRCLE_STATE circle_state = CIRCLE_NON;

    /*三角形*/
    int tri_Ax, tri_Ay, tri_Bx, tri_By, tri_Cx, tri_Cy;
    enum TRIANGLE_STATE { TRI_NON,TRI_A,TRI_B,TRI_C};
    TRIANGLE_STATE triangle_state = TRI_NON;

    /*平移*/
    enum TRANS_STATE {TRANS_NON,TRANS_START};
    TRANS_STATE trans_state=TRANS_NON;
    int trans_ID=-1;
    int trans_ix=0;
    int trans_iy=0;

    /*算法*/
    ALGORITHM algorithm=NONE;
    QString algo_info="算法：无 ";

//=====================================================================

//=====================================================================
// 鼠标行为+绘制行为

    int mouse_x = 0, mouse_y = 0;int u_id=0;//鼠标位置
    int l_x=0,l_y=0;
    bool on_curve=false;
    //鼠标按下
    void mousePressEvent(QMouseEvent *event);
    //鼠标移动
    void mouseMoveEvent(QMouseEvent *event);
    //鼠标释放
    void mouseReleaseEvent(QMouseEvent *event);
    //鼠标双击
    void mouseDoubleClickEvent(QMouseEvent *event);
    //重绘事件
    void paintEvent(QPaintEvent *event);
    void clear_all();
//=====================================================================

//=====================================================================
// 槽函数

private slots:

    void action_to_delete();
    void action_to_fill();
    void action_to_set_color_pen();
    void action_to_set_color_fill();
//=====================================================================
    void on_toolButton_clicked();
    void on_toolButton_2_clicked();
    void on_toolButton_3_clicked();
    void on_toolButton_4_clicked();
    void on_toolButton_5_clicked();
    void on_toolButton_6_clicked();
    void on_toolButton_7_clicked();
    void on_toolButton_8_clicked();
    void on_toolButton_9_clicked();
    void on_setPenWidth_valueChanged(int value);
};

