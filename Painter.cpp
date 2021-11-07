#include "Painter.h"        //自定义应用窗口
#include "ui_mainwindow.h"  //ui自动生成文件，ui具体类名看这个头文件
#include <QDebug>

#include <QPainter>
//This is a pull request test
Painter::Painter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //鼠标追踪,这部分代码可以放到ui的setupui函数中，目前为了保持直观，不对自动生成的ui文件修改
    this->setMouseTracking(true);
    this->centralWidget()->setMouseTracking(true);


    //状态栏显示鼠标位置
    statusLabel_pos = new QLabel();
    statusLabel_pos->resize(100, 30);
    ui->statusbar->addPermanentWidget(statusLabel_pos);

    statusLabel_state = new QLabel();
    statusLabel_state->resize(100, 30);
    ui->statusbar->addPermanentWidget(statusLabel_state);
}

Painter::~Painter()
{
    delete ui;
}

int Painter::getNewID()
{
    return ID_Counter++;
}

void Painter::refreshStateLabel()
{
    //状态栏展示鼠标位置
    QString pos_str = "(" + QString::number(mouse_x) + "," + QString::number(mouse_y) + ") id:" +QString::number(u_id)+" ";
    QString buf_flag=buf==true? "bufCanvas":"realCanvas";
    QString state_str= state_info+algo_info+"画布："+buf_flag;

    statusLabel_pos->setText(pos_str);
    statusLabel_state->setText(state_str);
}

void Painter::setState(Draw_State s)
{
    state=s;
    switch (state)
    {
    case NOT_DRAWING:
        state_info = "状态：NOT_DRAWING ";
        algo_info = "算法：无 ";
        break;
    case DRAW_LINE:
        state_info = "状态：DRAW_LINE ";
        algo_info = "算法：DDA ";
        break;
    case DRAW_CURVE:
        state_info = "状态：DRAW_CURVE ";
        algo_info = "算法：Bezier ";
        //curve_points.clear();
        break;
    case DRAW_CIRCLE:
        state_info = "状态：DRAW_CIRCLE ";
        algo_info = "算法：Midpoint ";
        break;
    default:
        break;
    }
}

void Painter::mouseMoveEvent(QMouseEvent *event)       //mouseMoveEvent为父类的父类QWidget虚函数函数名，下同
{
    //鼠标当前位置
    int x = event->pos().x();
    int y = event->pos().y();
    mouse_x = x;
    mouse_y = y;

    /*设置cursor检测当前浮于图形的id*/
    this->setCursor(Qt::ArrowCursor);
    on_curve=false;
    u_id=0;
    int tempid=0;
    if (buf) {
        if ((tempid=bufCanvas.getID(x, y)) != -1) {
            setCursor(Qt::PointingHandCursor);
            u_id=tempid;
        }
        else {
            setCursor(Qt::ArrowCursor);
            u_id=0;
        }
    }
    else {
        if ((tempid=realCanvas.getID(x, y)) != -1) {
            setCursor(Qt::PointingHandCursor);
            u_id=tempid;
        }
        else {
            setCursor(Qt::ArrowCursor);
            u_id=0;
        }
    }

    /*状态检测*/
     switch (state){
        case NOT_DRAWING: {
            if (trans_state==TRANS_START) {
                realCanvas.translate(trans_ID, x - trans_ix, y - trans_iy);
                update();
            }
            break;
        }
        default:
         break;
     }

    refreshStateLabel();
}

void Painter::mousePressEvent(QMouseEvent *event)
{
    //鼠标当前位置
    int x = event->pos().x();
    int y = event->pos().y();
    mouse_x = x;
    mouse_y = y;

    switch (state){
        case NOT_DRAWING: {
            if (event->button() == Qt::LeftButton) {
                if (trans_state == TRANS_NON) {
                    trans_ID = realCanvas.getID(x, y);
                    if (trans_ID != -1) {
                        trans_ix = x; trans_iy = y;
                        trans_state = TRANS_START;
                    }
                }
            }
            update();
        }
        default:
            break;
     }

    refreshStateLabel();
}

void Painter::mouseReleaseEvent(QMouseEvent *event)
{
    //鼠标当前位置
    int x = event->pos().x();
    int y = event->pos().y();
    mouse_x = x;
    mouse_y = y;
    switch (state){
        case DRAW_CURVE:{
                if (event->button() == Qt::LeftButton) {
                    curve_points.push_back(Point(x, y));
                    bufCanvas = realCanvas;
                    buf= true;
                    FoldLine* p = bufCanvas.drawFoldLine(curve_points);
                    for (size_t i = 0; i < curve_points.size(); i++) {
                        bufCanvas.drawCtrlPoint(i, p);
                    }
                    update();
                }
                else if (event->button() == Qt::RightButton) {
                    if (curve_points.size() > 2) { //点的个数小于3时，曲线没有意义
                        realCanvas=bufCanvas;
                        buf=false;
                        FoldLine *p = bufCanvas.drawFoldLine(curve_points);
                        for (size_t i = 0; i < curve_points.size(); i++) {
                            realCanvas.drawCtrlPoint(i, p);
                        }
                        algorithm=ALGORITHM::BEZIER;
                        realCanvas.drawCurve(getNewID(),algorithm, p);
                        curve_points.clear();
                        //setState(NOT_DRAWING);
                    }
                    update();
                }
                break;
        }
        case DRAW_LINE: {
                if (event->button() == Qt::LeftButton){
                    Point pt=Point(x, y);
                    line_points.push_back(pt);
                    realCanvas.drawPoint(getNewID(),pt);   //此处需要一个drawPoint函数显示选中的直线端点
                    update();
                    if(line_points.size() == 2){
                        algorithm=ALGORITHM::DDA;
                        realCanvas.drawLine(getNewID(),algorithm, &line_points[0], &line_points[1]);
                        line_points.clear();
                        //setState(NOT_DRAWING);
                    }
                    update();
                }
                break;
        }
        case DRAW_CIRCLE:{
                    if (event->button() == Qt::LeftButton) {
                        if(circle_state == CIRCLE_NON){
                            circle_center.x = x;
                            circle_center.y = y;//圆心
                            circle_state = CIRCLE_FINISH;
                        }
                        else if(circle_state == CIRCLE_FINISH)
                        {
                            float distense = sqrt((x-circle_center.x)*(x-circle_center.x)+
                                                  (y-circle_center.y)*(y-circle_center.y));
                            circle_r = qRound(distense);
                            algorithm=ALGORITHM::MIDPOINT;
                            bufCanvas = realCanvas;
                            buf= true;
                            bufCanvas.drawCircle(getNewID(),algorithm,circle_center,circle_r);
                            update();
                            realCanvas = bufCanvas;
                            buf =false;
                            realCanvas.drawCircle(getNewID(),algorithm,circle_center,circle_r);
                            update();
                            circle_state = CIRCLE_NON;
                        }
                    }
                        break;
          }
        case NOT_DRAWING:{
                if (event->button() == Qt::LeftButton) {
                    if (trans_state == TRANS_START) {
                        trans_state = TRANS_NON;
                        update();
                    }
                }
                break;
        }
        default:
            break;
    }
    refreshStateLabel();
}

void Painter::mouseDoubleClickEvent(QMouseEvent *event)
{
    //鼠标当前位置
    int x = event->pos().x();
    int y = event->pos().y();
    mouse_x = x;
    mouse_y = y;
    if(event->button() == Qt::RightButton){//右键双击清空
        clear_all();
    }
    refreshStateLabel();
}

void Painter::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    QImage *image;
    image = new QImage(geometry().width(), geometry().height(), QImage::Format_RGB888);
    if (!buf) {
        realCanvas.getImage(image);
    }
    else {
        bufCanvas.getImage(image);
    }
    paint.drawImage(0, 0, *image);
    delete image;
}

void Painter::clear_all(){
    realCanvas.clear_all();
    bufCanvas.clear_all();
    curve_points.clear();
    line_points.clear();
    setState(NOT_DRAWING);
    update();
}

void Painter::on_toolButton_clicked(){setState(DRAW_CURVE);}
void Painter::on_toolButton_2_clicked(){setState(DRAW_LINE);}
void Painter::on_toolButton_3_clicked(){setState(NOT_DRAWING);}
void Painter::on_toolButton_4_clicked(){setState(DRAW_CIRCLE);}

