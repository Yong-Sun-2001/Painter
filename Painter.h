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
    Canvas tempCanvas;

//=====================================================================
// 状态及数据
    /*画布状态*/
    bool buf=false;

    /*标签*/
    QLabel* statusLabel;
    void refreshStateLabel();

    /*编辑状态*/
    enum Draw_State{DRAW_CURVE,DRAW_LINE,NOT_DRAWING};
    Draw_State state=NOT_DRAWING;
    void setState(Draw_State s);

    /*曲线*/
    std::vector<Point> curve_points;

    /*直线*/
    std::vector<Point> line_points;

    /*算法*/
    ALGORITHM algorithm;

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


//=====================================================================
    void on_toolButton_clicked();
    void on_toolButton_2_clicked();
    void on_toolButton_3_clicked();
};
#endif // PAINTER_H
