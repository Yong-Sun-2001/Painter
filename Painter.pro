QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Algorithms/Circle_Fill.cpp \
    Algorithms/CommonFuncs.cpp \
    Algorithms/DDA.cpp \
    Algorithms/Ellipse_Fill.cpp \
    Algorithms/Midpoint.cpp \
    Algorithms/ScanLine_Fill.cpp \
    Shapes/Circle.cpp \
    Shapes/CtrlPoint.cpp \
    Shapes/Curve.cpp \
    Shapes/DotPoint.cpp \
    Shapes/Ellipse.cpp \
    Shapes/FoldLine.cpp \
    Shapes/Line.cpp \
    Shapes/Point.cpp \
    Shapes/Polygon.cpp \
    Shapes/Rectangle.cpp \
    Shapes/Triangle.cpp \
    main.cpp \
    Painter.cpp \
    Shapes/PixelSet.cpp \
    Canvas.cpp \
    Algorithms/Bezier.cpp

HEADERS += \
    Algorithms/AlgorithmBase.h \
    Algorithms/Circle_Fill.h \
    Algorithms/CommonFuncs.h \
    Algorithms/DDA.h \
    Algorithms/Ellipse_Fill.h \
    Algorithms/Midpoint.h \
    Algorithms/ScanLine_Fill.h \
    Canvas.h \
    Painter.h \
    Shapes/Circle.h \
    Shapes/CtrlPoint.h \
    Shapes/Curve.h \
    Shapes/DotPoint.h \
    Shapes/Ellipse.h \
    Shapes/FoldLine.h \
    Shapes/Line.h \
    Shapes/PixelSet.h \
    Algorithms/Bezier.h \
    Shapes/Point.h \
    Shapes/Polygon.h \
    Shapes/Rectangle.h \
    Shapes/Triangle.h

FORMS += \
    mainwindow.ui


CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
