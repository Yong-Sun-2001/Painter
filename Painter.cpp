#include "Painter.h"        //自定义应用窗口
#include "ui_mainwindow.h"  //ui自动生成文件，ui具体类名看这个头文件
#include <QDebug>

#include <QPainter>

Painter::Painter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //鼠标追踪,这部分代码可以放到ui的setupui函数中，目前为了保持直观，不对自动生成的ui文件修改
    this->setMouseTracking(true);
    this->centralWidget()->setMouseTracking(true);


    //状态栏显示鼠标位置
    statusLabel = new QLabel();
    statusLabel->resize(100, 30);
    ui->statusbar->addPermanentWidget(statusLabel);
}

Painter::~Painter()
{
    delete ui;
}

void Painter::refreshStateLabel()
{
    //状态栏展示鼠标位置
    QString str = "(" + QString::number(mouse_x) + "," + QString::number(mouse_y) + ")";
    statusLabel->setText(str);
}

void Painter::setState(Draw_State s)
{
    state=s;
}

void Painter::mouseMoveEvent(QMouseEvent *event)       //mouseMoveEvent为父类的父类QWidget虚函数函数名，下同
{
    //鼠标当前位置
    int x = event->pos().x();
    int y = event->pos().y();
    mouse_x = x;
    mouse_y = y;

    refreshStateLabel();
}

void Painter::mousePressEvent(QMouseEvent *event)
{
    //鼠标当前位置
    int x = event->pos().x();
    int y = event->pos().y();
    mouse_x = x;
    mouse_y = y;

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
                    FoldLine* p = bufCanvas.drawFoldLine( curve_points);
                    for (size_t i = 0; i < curve_points.size(); i++) {
                        bufCanvas.drawCtrlPoint(i, p);
                    }
                    update();
                }
                else if (event->button() == Qt::RightButton) {
                    if (curve_points.size() > 2) { //点的个数小于3时，曲线没有意义
                        realCanvas=bufCanvas;
                        buf=false;
                        FoldLine *p = realCanvas.drawFoldLine(curve_points);
                        for (size_t i = 0; i < curve_points.size(); i++) {
                            realCanvas.drawCtrlPoint(i, p);
                        }
                        algorithm=ALGORITHM::BEZIER;
                        realCanvas.drawCurve(algorithm, p);
                    }

//                    setState(NOT_DRAWING);
                    update();
                }
        }

        case NOT_DRAWING:
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
