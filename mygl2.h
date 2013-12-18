#ifndef MYGL_H
#define MYGL_H
#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glu.h>

class mygl2 : public QGLWidget
{

public:
    explicit mygl2(QWidget *parent = 0);

    void wallplot();
    void histoPlot1();
    void histoPlot2();
    void histoPlot3();
    void histoPlot4();

    void timerEvent(QTimerEvent *event);
    int id1;
    void InputManagement();
    void histoPlot41();
    void histoPlot42();
    void histoPlot43();
    void histoPlot44();
    void histoPlot31();
    void histoPlot32();
    void histoPlot33();
    void histoPlot34();
    void histoPlot23();
    void histoPlot22();
    void histoPlot21();
    void histoPlot24();
    void histoPlot11();
    void histoPlot12();
    void histoPlot13(double h);
    void histoPlot14();
    void histoPlot11(double h);
    void histoPlot12(double h);
    void histoPlot14(double h);
    void histoPlot21(double h);
    void histoPlot22(double h);
    void histoPlot23(double h);
    void histoPlot24(double h);
    void histoPlot31(double h);
    void histoPlot32(double h);
    void histoPlot33(double h);
    void histoPlot34(double h);
    void histoPlot41(double h);
    void histoPlot42(double h);
    void histoPlot43(double h);
    void histoPlot44(double h);
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *);
private:
    GLfloat translate, xRot, yRot, zRot;
    int cnt;
signals:

public slots:

};

#endif // MYGL_H
