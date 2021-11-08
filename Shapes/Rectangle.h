#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <Shapes/PixelSet.h>
//矩形框（用于剪裁时的示意剪裁窗口）
class Rectangle :public PixelSet {
    int x1, y1;
    int x2, y2;
    int width;
public:
    Rectangle();
    Rectangle(const Rectangle& B);
    Rectangle(int ix1, int iy1, int ix2, int iy2, int iwidth = 5, QColor icolor = QColor(0xB2, 0xDF, 0xEE));
    void paint(QImage *image);
    void refresh();
    void translate(int dx,int dy);
    void scale(int x, int y, float s);
    void rotate(int x, int y, int r);
    void fill(QColor fcolor);
};
#endif // RECTANGLE_H
