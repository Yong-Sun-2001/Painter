#include "Painter.h"        //自定义应用窗口
#include "ui_mainwindow.h"  //ui自动生成文件，ui具体类名看这个头文件
#include <QDebug>
#include <QPainter>
#include <Algorithms/CommonFuncs.h>
#include <QColorDialog>
Painter::Painter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refresh_ColorIcon_pen();
    refresh_ColorIcon_fill();
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

void Painter::refresh_ColorIcon_pen()
{
    QImage icon(30, 30, QImage::Format_RGB32);
    icon.fill(penColor);
    ui->actionPen->setIcon(QPixmap::fromImage(icon));
}

void Painter::refresh_ColorIcon_fill()
{
    QImage icon(30, 30, QImage::Format_RGB32);
    icon.fill(fillColor);
    ui->actionFill->setIcon(QPixmap::fromImage(icon));
}

void Painter::setState(Draw_State s)
{
    state=s;
    buf =false;
    update();
    switch (state)
    {
    case NOT_DRAWING:
        state_info = "状态：NOT_DRAWING ";
        algo_info = "算法：无 ";
        algorithm=NONE;
        break;
    case DRAW_LINE:
        state_info = "状态：DRAW_LINE ";
        algo_info = "算法：DDA ";
        algorithm=DDA;
        line_state = LINE_NON_POINT;
        break;
    case DRAW_CURVE:
        state_info = "状态：DRAW_CURVE ";
        algo_info = "算法：Bezier ";
        algorithm=BEZIER;
        curve_points.clear();
        curve_state = CURVE_NON;
        break;
    case DRAW_CIRCLE:
        state_info = "状态：DRAW_CIRCLE ";
        algo_info = "算法：Midpoint ";
        algorithm=MIDPOINT;
        break;
    case DRAW_ROTATE:
        state_info = "状态：DRAW_ROTATE ";
        algo_info = "算法：无 ";
        algorithm=NONE;
        rotate_state = ROTATE_NON;
        break;
    case DRAW_SCALE:
        state_info = "状态：DRAW_SCALE ";
        algo_info = "算法：无 ";
        algorithm=NONE;
        scale_state = SCALE_NON;
        break;
    case DRAW_POLYGON:
        state_info = "状态：DRAW_POLYGON ";
        algo_info = "算法：DDA ";
        algorithm=DDA;
        poly_state = POLY_NON_POINT;
        poly_points.clear();
        poly_id = getNewID();
        break;
    case DRAW_RECTANGLE:
        state_info = "状态：DRAW_RECTANGLE ";
        algo_info = "算法：无 ";
        algorithm=NONE;
        rec_state = REC_NON_POINT;
        break;
    case DRAW_TRIANGLE:
        state_info = "状态：DRAW_TRIANGLE ";
        algo_info = "算法：DDA ";
        algorithm=DDA;
        triangle_state = TRI_A;
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
         case DRAW_POLYGON:{
             if (poly_state == POLY_PAINTING) {
                 autoPoly(x, y);//自动贴合修正
                 bufpoly_points = poly_points;
                 bufpoly_points.push_back(Point(x, y));
                 bufCanvas.drawPolygon(poly_id, bufpoly_points, algorithm);
                 buf = true;
                 update();
             }
         }
        case NOT_DRAWING: {
             if (trans_state==TRANS_START) {
                 bufCanvas = realCanvas;
                 buf = true;
                 bufCanvas.translate(trans_ID, x - trans_ix, y - trans_iy);
                 update();
             }
            break;
        }
         case DRAW_LINE: {
             if (line_state == LINE_POINTA) {
                 bufCanvas = realCanvas;
                 buf = true;
                 bufCanvas.drawLine(-1, line_Ax, line_Ay, x, y, algorithm);
                 update();
             }
             break;
         }
     case DRAW_RECTANGLE: {
         if (rec_state == REC_POINTA) {
             bufCanvas = realCanvas;
             buf = true;
             bufCanvas.drawRectangle(-1, rec_x1, rec_y1, x, y);
             update();
         }
         break;
     }
     case DRAW_CIRCLE:{
         if(circle_state == CIRCLE_FINISH){
             bufCanvas = realCanvas;
             buf = true;
             float distense = sqrt((x-circle_center.x)*(x-circle_center.x)+
                                   (y-circle_center.y)*(y-circle_center.y));
             circle_r = qRound(distense);
             bufCanvas.drawCircle(-1,algorithm,circle_center,circle_r);
             update();
         }
         break;
     }
     case DRAW_TRIANGLE: {
         if (triangle_state == TRI_B) {
             bufCanvas = realCanvas;
             buf = true;
             bufCanvas.drawLine(-1, tri_Ax, tri_Ay, x, y, algorithm);
             update();
         }
         else if (triangle_state == TRI_C) {
             bufCanvas = realCanvas;
             buf = true;
             bufCanvas.drawTriangle(-1,tri_Ax, tri_Ay, tri_Bx, tri_By,x,y,algorithm);
             update();
         }
         break;
     }
         case DRAW_ROTATE:{
             if (rotate_state == ROTATE_BEGIN && (event->buttons() & Qt::LeftButton)) {
                 int r = getRotateR(init_x, init_y, rotate_rx, rotate_ry, x, y);
                 bufCanvas = realCanvas;
                 bufCanvas.drawDotPoint(-1, rotate_rx, rotate_ry);
                 bufCanvas.rotate(selected_ID, rotate_rx, rotate_ry, r);
                 buf = true;
                 update();
             }
             break;
         }
         case DRAW_SCALE:{
             if (scale_state == SCALE_BEGIN && (event->buttons() & Qt::LeftButton)) {
                 double s = getScaleS(init_x, init_y, scale_rx, scale_ry, x, y);
                 bufCanvas = realCanvas;
                 bufCanvas.drawDotPoint(-1, scale_rx, scale_ry);
                 bufCanvas.scale(selected_ID, scale_rx, scale_ry, s);
                 buf = true;
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
                        bufCanvas = realCanvas;
                        trans_state = TRANS_START;
                    }
                }
            }
        }
        case DRAW_ROTATE: {
            if (event->button() == Qt::LeftButton) {
                if (rotate_state == ROTATE_READY && realCanvas.getID(x, y) != -1) {
                    selected_ID = realCanvas.getID(x, y);
                    init_x = x; init_y = y;
                    rotate_state = ROTATE_BEGIN;
                }
            }
            break;
        }
        case DRAW_SCALE: {
            if (event->button() == Qt::LeftButton) {
                if (scale_state == SCALE_READY && realCanvas.getID(x, y) != -1) {
                    selected_ID = realCanvas.getID(x, y);
                    init_x = x; init_y = y;
                    scale_state = SCALE_BEGIN;
                }
            }
            break;
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

    if (state != NOT_DRAWING && state != DRAW_CURVE) {
        if (event->button() == Qt::RightButton) {
            setState(NOT_DRAWING);
            return;
        }
    }

    switch (state){
        case DRAW_CURVE:{
            if (event->button() == Qt::LeftButton) {
                curve_points.push_back(Point(x, y));
                bufCanvas = realCanvas;
                buf = true;
                FoldLine* p = bufCanvas.drawFoldLine(-1, curve_points);
                for (size_t i = 0; i < curve_points.size(); i++) {
                    bufCanvas.drawCtrlPoint(-1, i, p);
                }
                update();
            }
            else if (event->button() == Qt::RightButton) {
                if (curve_points.size() > 2) { //点的个数小于3时，曲线没有意义
                    FoldLine *p = realCanvas.drawFoldLine(getNewID(), curve_points);
                    realCanvas.drawCurve(getNewID(), algorithm, p);
                    for (size_t i = 0; i < curve_points.size(); i++) {
                        realCanvas.drawCtrlPoint(getNewID(), i, p);
                    }
                    setState(NOT_DRAWING);
                    update();
                }
                else {
                    setState(NOT_DRAWING);
                    update();
                }
            }
                break;
        }

         case DRAW_LINE: {
            if (event->button() == Qt::LeftButton) {
                if (line_state == LINE_NON_POINT) {
                    line_Ax = event->pos().x();
                    line_Ay = event->pos().y();
                    line_state = LINE_POINTA;
                }
                else if (line_state == LINE_POINTA) {
                    line_Bx = event->pos().x();
                    line_By = event->pos().y();
                    realCanvas.drawLine(getNewID(), line_Ax, line_Ay, line_Bx, line_By, algorithm);
                    setState(NOT_DRAWING);
                }
            }
            break;
        }
    case DRAW_RECTANGLE: {
       if (event->button() == Qt::LeftButton) {
           if (rec_state == REC_NON_POINT) {
               rec_x1 = event->pos().x();
               rec_y1 = event->pos().y();
               rec_state = REC_POINTA;
           }
           else if (rec_state == REC_POINTA) {
               rec_x2 = event->pos().x();
               rec_y2 = event->pos().y();
               realCanvas.drawRectangle(getNewID(), rec_x1, rec_y1, rec_x2, rec_y2);
               setState(NOT_DRAWING);
           }
       }
       break;
   }
    case DRAW_CIRCLE:{
                if (event->button() == Qt::LeftButton) {
                    if(circle_state == CIRCLE_NON){
                        circle_center.x = event->pos().x();
                        circle_center.y = event->pos().y();//圆心
                        circle_state = CIRCLE_FINISH;
                    }
                    else if(circle_state == CIRCLE_FINISH)
                    {
                        float distense = sqrt((event->pos().x()-circle_center.x)*(event->pos().x()-circle_center.x)+
                                              (event->pos().y()-circle_center.y)*(event->pos().y()-circle_center.y));
                        circle_r = qRound(distense);
                        algorithm=ALGORITHM::MIDPOINT;
                        realCanvas.drawCircle(getNewID(),algorithm,circle_center,circle_r);
                        //update();
                        circle_state = CIRCLE_NON;
                        setState(NOT_DRAWING);
                    }
                }
                    break;
      }

    case DRAW_TRIANGLE: {
        if (event->button() == Qt::LeftButton) {
            if (triangle_state == TRI_A) {
                tri_Ax = event->pos().x();
                tri_Ay = event->pos().y();
                triangle_state = TRI_B;
            }
            else if (triangle_state == TRI_B) {
                tri_Bx = event->pos().x();
                tri_By = event->pos().y();
                triangle_state = TRI_C;
            }
            else if(triangle_state == TRI_C) {
                tri_Cx = event->pos().x();
                tri_Cy = event->pos().y();
                realCanvas.drawTriangle(getNewID(), tri_Ax, tri_Ay, tri_Bx, tri_By, tri_Cx, tri_Cy,algorithm);
                setState(NOT_DRAWING);
            }
        }
        break;
    }
       case DRAW_ROTATE: {
            if (event->button() == Qt::LeftButton) {
                if (rotate_state == ROTATE_NON) {
                    rotate_rx = x; rotate_ry = y;
                    rotate_state = ROTATE_READY;
                    bufCanvas = realCanvas;
                    bufCanvas.drawDotPoint(-1, rotate_rx, rotate_ry);
                    buf = true;
                    update();
                }else if (rotate_state == ROTATE_BEGIN) {
                    rotate_state = ROTATE_READY;
                    realCanvas = bufCanvas;
                }
            }
            break;
        }
       case DRAW_SCALE:{
            if (event->button() == Qt::LeftButton) {
                if (scale_state == SCALE_NON) {
                    scale_rx = x; scale_ry = y;
                    scale_state = SCALE_READY;
                    bufCanvas = realCanvas;
                    bufCanvas.drawDotPoint(-1, scale_rx, scale_ry);
                    buf = true;
                    update();
                }
                else if (scale_state == SCALE_BEGIN) {
                    scale_state = SCALE_READY;
                    realCanvas = bufCanvas;
                }
            }
            break;
        }

        case NOT_DRAWING:{
            if (event->button() == Qt::LeftButton) {
                if (trans_state == TRANS_START) {
                    trans_state = TRANS_NON;
                    realCanvas = bufCanvas;
                    buf = false;
                    update();
                }
            }
            else if(event->button() == Qt::RightButton){
                //正常状态下，右键单击，弹出菜单
                selected_ID = realCanvas.getID(x, y);
                if (selected_ID != -1 && realCanvas.getType(selected_ID) != CTRLPOINT) {
                    switch (realCanvas.getType(selected_ID)){
                        case RECTANGLE:{
                            QMenu menu;
                            QAction* actionDelete = new QAction(tr(u8"删除"));  //删除图元Action
                            connect(actionDelete, &QAction::triggered, this, &Painter::action_to_delete);
                            menu.addAction(actionDelete);

                            QAction* actionFill = new QAction(tr(u8"填充"));  //删除填充图元Action
                            connect(actionFill, &QAction::triggered, this, &Painter::action_to_fill);
                            menu.addAction(actionFill);
                            menu.exec(QCursor::pos());
                            break;
                        }
                        case POLYGON:{
                                QMenu menu;
                                QAction* actionDelete = new QAction(tr(u8"删除"));  //删除图元Action
                                connect(actionDelete, &QAction::triggered, this, &Painter::action_to_delete);
                                menu.addAction(actionDelete);

                                QAction* actionFill = new QAction(tr(u8"填充"));  //删除填充图元Action
                                connect(actionFill, &QAction::triggered, this, &Painter::action_to_fill);
                                menu.addAction(actionFill);
                                menu.exec(QCursor::pos());
                                break;
                        }
                        case CIRCLE:{
                                QMenu menu;
                                QAction* actionDelete = new QAction(tr(u8"删除"));  //删除图元Action
                                connect(actionDelete, &QAction::triggered, this, &Painter::action_to_delete);
                                menu.addAction(actionDelete);

                                QAction* actionFill = new QAction(tr(u8"填充"));  //删除填充图元Action
                                connect(actionFill, &QAction::triggered, this, &Painter::action_to_fill);
                                menu.addAction(actionFill);
                                menu.exec(QCursor::pos());
                                break;
                        }
                    case TRIANGLE:{
                                QMenu menu;
                                QAction* actionDelete = new QAction(tr(u8"删除"));  //删除图元Action
                                connect(actionDelete, &QAction::triggered, this, &Painter::action_to_delete);
                                menu.addAction(actionDelete);

                                QAction* actionFill = new QAction(tr(u8"填充"));  //删除填充图元Action
                                connect(actionFill, &QAction::triggered, this, &Painter::action_to_fill);
                                menu.addAction(actionFill);
                                menu.exec(QCursor::pos());
                                break;
                    }
                        default:{
                                QAction* actionDelete = new QAction(tr(u8"删除"));  //删除图元Action
                                connect(actionDelete, &QAction::triggered, this, &Painter::action_to_delete);
                                QMenu menu;menu.addAction(actionDelete);
                                menu.exec(QCursor::pos());
                                break;
                        }
                }
            }
        }
    }
    case DRAW_POLYGON:{
        if (event->button() == Qt::LeftButton) {
            if (poly_state == POLY_NON_POINT) {
                startX = event->pos().x();
                startY = event->pos().y();
                bufCanvas = realCanvas;
                poly_points.push_back(Point(startX, startY));
                poly_state = POLY_PAINTING;
            }
            else if (poly_state == POLY_PAINTING) {
                if (autoPoly(x, y)) {//是否自动贴合判断
                    poly_points.push_back(Point(x, y));
                    realCanvas.drawPolygon(poly_id, poly_points, algorithm);
                    setState(NOT_DRAWING);
                }
                else {
                    poly_points.push_back(Point(x, y));
                }
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
    setState(NOT_DRAWING);
    update();
}

void Painter::on_toolButton_clicked(){setState(DRAW_CURVE);}
void Painter::on_toolButton_2_clicked(){setState(DRAW_LINE);}
void Painter::on_toolButton_3_clicked(){setState(NOT_DRAWING);}
void Painter::on_toolButton_4_clicked(){setState(DRAW_CIRCLE);}
void Painter::on_toolButton_5_clicked(){setState(DRAW_ROTATE);}
void Painter::on_toolButton_6_clicked(){setState(DRAW_SCALE);}
void Painter::on_toolButton_7_clicked(){setState(DRAW_POLYGON);}
void Painter::on_toolButton_8_clicked(){setState(DRAW_RECTANGLE);}
void Painter::on_toolButton_9_clicked(){setState(DRAW_TRIANGLE);}

void Painter::action_to_delete()
{
    realCanvas.delID(selected_ID);
    update();
}

void Painter::action_to_fill()
{
    realCanvas.fill(selected_ID);
    update();
}

bool Painter::autoPoly(int & nowx, int & nowy)
{
    if ((nowx - startX)*(nowx - startX) + (nowy - startY)*(nowy - startY) < AUTO_BIAS*AUTO_BIAS) {
        nowx = startX; nowy = startY;
        return true;
    }
    return false;
}

void Painter::action_to_set_color_pen() {
    penColor = QColorDialog::getColor(Qt::black,this,u8"绘图颜色选择");
    realCanvas.setColor_pen(penColor);
    refresh_ColorIcon_pen();
}

void Painter::action_to_set_color_fill() {
    fillColor = QColorDialog::getColor(Qt::black,this,u8"绘图颜色选择");
    realCanvas.setColor_fill(fillColor);
    refresh_ColorIcon_fill();
}








void Painter::on_setPenWidth_valueChanged(int value)
{
    bufCanvas.setPen_width(value);
    realCanvas.setPen_width(value);
}

