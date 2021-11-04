#include <Painter.h>
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);   //定义应用
    Painter w;    //定义应用窗口
    w.show();
    return a.exec();
}
