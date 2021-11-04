#ifndef PAINTER_H
#define PAINTER_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QLabel>
#include <Canvas.h>
#include <vector>

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
    /*画布状态*/
    bool buf=false;

    /*标签*/
    QLabel* statusLabel;
    void refreshStateLabel();

    /*编辑状态*/
    enum Draw_State{DRAW_CURVE,NOT_DRAWING};
    Draw_State state=DRAW_CURVE;
    void setState(Draw_State s);

    /*曲线*/
    std::vector<Point> curve_points;
    enum CURVE_STATE { CURVE_NON, CURVE_BEGIN };
    CURVE_STATE curve_state = CURVE_NON;

    /*算法*/
    ALGORITHM algorithm;

//=====================================================================

//=====================================================================
// 鼠标行为+绘制行为

    int mouse_x = 0, mouse_y = 0;//鼠标位置
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
//=====================================================================

//=====================================================================
// 槽函数

private slots:


//=====================================================================

};
#endif // PAINTER_H
