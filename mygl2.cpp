#include "mygl2.h"

#include <GL/glut.h>
#include <QKeyEvent>
#include <qapplication.h>
#include <stdlib.h>
#include <stdio.h>
#include <QFileInfo>
#include <QDebug>
#include <QTextCodec>
#include <QStringList>
#include <QDateTime>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include "QDebug"
#include <QtGui/QApplication>
#define DEBUG2840
#define CORE
#define LEN 9000
#define LENGTH_OF_CORE 84
#define SOCKET_REFRESH

int ifrecvd = 0;

char lastbuff[9000];
char buff[LEN];
char buff2[LEN];
char buff3[LEN];
char buff4[LEN];

socklen_t size;
int num;
sockaddr_in addrSrv,addrrcv;
sockaddr_in addrSrv2,addrrcv2;
sockaddr_in addrSrv3,addrrcv3;
sockaddr_in addrSrv4,addrrcv4;

int sockser,sockser2,sockser3,sockser4;
void search_core_data_mygl2(char *buff);
void search_core_data2_mygl2(char *buff);

void search_core_data_mygl2_2(char *buff);
void search_core_data2_mygl2_2(char *buff);

void search_core_data_mygl2_3(char *buff);
void search_core_data2_mygl2_3(char *buff);

void search_core_data_mygl2_4(char *buff);
void search_core_data2_mygl2_4(char *buff);


double charToint(char *start,int len);
int  charTohex(char c,int base);

int continueflag_mygl2 = 0;
int rest_num_comma_mygl2 = 0;
int continueflag_mygl2_2 = 0;
int rest_num_comma_mygl2_2 = 0;
int continueflag_mygl2_3 = 0;
int rest_num_comma_mygl2_3 = 0;
int continueflag_mygl2_4 = 0;
int rest_num_comma_mygl2_4 = 0;

char out_mygl2[LEN*5];
char out_mygl2_2[LEN*5];
char out_mygl2_3[LEN*5];
char out_mygl2_4[LEN*5];

int valid[4] = {0};


double map[4][4] = {0};
double visit[4][4] = {0};

int endmark = 0;
long int num_frame = 0;

void search_core_data_mygl2_a(char *buff);
void  search_core_data_mygl2_b(char *buff);
void  search_core_data_mygl2_c(char *buff);
void  search_core_data_mygl2_d(char *buff);

void search_core_data2_mygl2_a(char *buff);
double charToint_a(char *start,int len);
int  charTohex_a(char c,int base);
int continueflag_mygl2_a = 0;
int rest_num_comma_mygl2_a = 0;
int continueflag_mygl2_b = 0;
int rest_num_comma_mygl2_b = 0;

int continueflag_mygl2_c = 0;
int rest_num_comma_mygl2_c = 0;

int continueflag_mygl2_d = 0;
int rest_num_comma_mygl2_d = 0;


char out_mygl2_a[LEN*5];
char out_mygl2_b[LEN*5];
char out_mygl2_c[LEN*5];
char out_mygl2_d[LEN*5];
double map_a[4][5] = {0};
double map_b[4][5] = {0};
double map_c[4][5] = {0};
double map_d[4][5] = {0};



int endmark_a = 0;
int endmark_b = 0;
int endmark_c = 0;
int endmark_d = 0;

mygl2::mygl2(QWidget *parent) :
    QGLWidget(parent)
{
    qDebug() << "This is in the mygl2 class." << endl;
    InputManagement();
   cnt = 0;
    //initial socket
    int intsize=sizeof(sockaddr_in);
    sockser=socket(AF_INET,SOCK_DGRAM,0);
    addrSrv.sin_addr.s_addr=htonl(INADDR_ANY);
    addrSrv.sin_family=AF_INET;
    addrSrv.sin_port=htons(6001);//server : receive port number
    bind(sockser,(sockaddr*)&addrSrv,sizeof(sockaddr));

/*
 *
    char str[1000];
    recvfrom(sockser2,&str,9000,0,(struct sokaddr *)&addrrcv2,(socklen_t*)&intsize);
    qDebug() << str << endl;
*/
    translate = -7.0;
    xRot = yRot = zRot = 0.0;
    xRot += 20;
    yRot += 210;
    id1 = startTimer(100);
    setWindowTitle("FPGA Status");
}
void mygl2::InputManagement(){
    //QFile file("datain.txt");
    static int qpsk[2000][2] = {0};
    const char filename[10][100] = {"/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout1.txt",
                                   "/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout2.txt",
                                   "/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout3.txt",
                                   "/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout4.txt",
                                   "/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout5.txt",
                                   "/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout6.txt",
                                   "/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout7.txt",
                                   "/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout8.txt",
                                   "/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout9.txt",
                                   "/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout10.txt"
                            };
    for( int i = 0 ; i < 10 ; i++ ){
        QFile file(filename[i]);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << file.errorString();
        //qDebug() << QObject::tr("file text:") << endl << file.readAll();
        //char str[100];
        char str[4096*20];
        file.readLine(str,4096*20+1);
        //qDebug() << "first char is :"<<str[4096*20-1] ;
        file.close();
    }
}

void mygl2::initializeGL()
{
    glClearColor(0.8,0.8,0.8,0);//canvas
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);


/*
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
*/
    //glShadeModel(GL_FLAT);

}
void mygl2::resizeGL(int w, int h)
{
    glViewport(-10, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*LIGHT
    GLfloat pos0[] = {1.0,1.0,1.0,1.0};
    GLfloat dif0[] = {1.0,0.0,0.0,0.0};
    GLfloat spec0[] = {1.0,1.0,1.0,1.0};
    GLfloat amb0[] = {0.1,0.1,0.1,1.0};
    glLightfv(GL_LIGHT0,GL_POSITION,pos0);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,dif0);
    glLightfv(GL_LIGHT0,GL_SPECULAR,spec0);
    glLightfv(GL_LIGHT0,GL_AMBIENT,amb0);
    */
    //luPerspective(40.0, (GLfloat)w/(GLfloat)h, 2, 30.0);
    //gluPerspective(40,1.33, 2, 30.0);
    //glOrtho (-1.5 * ( GLfloat ) w / ( GLfloat ) h, 2.3* ( GLfloat ) w / ( GLfloat ) h, -2, 2, -15.0, 15.0);
     glFrustum (-1.5 * ( GLfloat ) w / ( GLfloat ) h, 2.3* ( GLfloat ) w / ( GLfloat ) h, -2, 2, 3.3, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Ⱦ
void mygl2::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glTranslatef(0.0, 0.0, translate);// translate is included in <QKeyEvent>
    glTranslatef(0.0, -0.5, 0.3);// translate is included in <QKeyEvent>

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);
    glBegin(GL_QUADS);

    glEnable (GL_LINE_SMOOTH );
    glHint (GL_POLYGON_SMOOTH , GL_NICEST);



    histoPlot11(map[3][0]);histoPlot12(map[3][1]);histoPlot13(map[2][0]);histoPlot14(map[2][1]);
    histoPlot21(map[3][2]);histoPlot22 (map[3][3]);histoPlot23(map[2][2]);histoPlot24(map[2][3]);
    histoPlot31(map[1][0]);histoPlot32(map[1][1]);histoPlot33(map[0][0]);histoPlot34( map[0][1]);
    histoPlot41(map[1][2]);histoPlot42(map[1][3]);histoPlot43(map[0][2]);histoPlot44(map[0][3]);
    //floor
    wallplot();
    glEnd();
}

void mygl2::wallplot(){
    double point2[8][3] = {{2,2,2},{-2,2,2},{-2,2,-2},{2,2,-2},{2,-1.1,2},{-4,-1.1,2},{-4,-1.1,-4},{2,-1.1,-4}};//  mid is height
    glColor4f(0, 0, 0,0.2);
    glVertex3f(point2[4][0], point2[4][1], point2[4][2]);
    glVertex3f(point2[5][0], point2[5][1], point2[5][2]);
    glVertex3f(point2[6][0], point2[6][1], point2[6][2]);
    glVertex3f(point2[7][0], point2[7][1], point2[7][2]);
}
void mygl2::histoPlot11(double h){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
   // double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};// fluctuate
    double delta[] = {0,0,0,0,0,0,0,0,0,0};// fluctuate

    double brown[3][3] = {{0.588235,0.313725,0.117647},{0.529412,0.254902,0.058824},{0.529412,0.254902,0.058824}};
    int rand1 = qrand() % 10;//random

    for( int i = 0 ; i < 4 ; i++){
       // point[i][1] += (delta[rand1]/10);
        point[i][1] = h/65536; //map 3 0
        point[i][1] --;

    }



    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(brown[0][0],brown[0][1],brown[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
     glColor3f(brown[0][0],brown[0][1],brown[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
     glColor3f(brown[1][0],brown[1][1],brown[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(brown[1][0],brown[1][1],brown[1][2]);//250,5,5
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(brown[2][0],brown[2][1],brown[2][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //right
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(brown[2][0],brown[2][1],brown[2][2]);//250,5,5
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
}
void mygl2::histoPlot12(double h){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};// fluctuate
    double brown[3][3] = {{0.588235,0.313725,0.117647},{0.529412,0.254902,0.058824},{0.529412,0.254902,0.058824}};
    int rand1 = qrand() % 10;//random

    for( int i = 0 ; i < 4 ; i++){
        //point[i][1] += (delta[rand1]/10);
        point[i][1] = h/65536;//3 1
        point[i][1] --;

    }


    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }
    for( int i = 0 ; i < 8 ; i++){// move back for h12
        point[i][0] -= 1;
    }

    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h12
        for( int j = 0 ; j < 3 ; j++){
            brown[i][j] *= 1.1;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(brown[0][0],brown[0][1],brown[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
     glColor3f(brown[0][0],brown[0][1],brown[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
     glColor3f(brown[1][0],brown[1][1],brown[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(brown[1][0],brown[1][1],brown[1][2]);//250,5,5
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(brown[2][0],brown[2][1],brown[2][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //right
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(brown[2][0],brown[2][1],brown[2][2]);//250,5,5
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
}
void mygl2::histoPlot13(double h){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};// fluctuate
    double brown[3][3] = {{0.588235,0.313725,0.117647},{0.529412,0.254902,0.058824},{0.529412,0.254902,0.058824}};
    int rand1 = qrand() % 10;//random

    for( int i = 0 ; i < 4 ; i++){
        //point[i][1] += (delta[rand1]/10);
        point[i][1] = h/65536;  //2 0
        point[i][1] --;

    }


    for( int i = 0 ; i < 8 ; i++ ){// move left
        point[i][2] += 1;
    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }

    for( int i = 0 ; i < 8 ; i++){// move back for h43
        point[i][0] -= 0;
    }

    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h12
        for( int j = 0 ; j < 3 ; j++){
            brown[i][j] *= 1.15;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(brown[0][0],brown[0][1],brown[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
     glColor3f(brown[0][0],brown[0][1],brown[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
     glColor3f(brown[1][0],brown[1][1],brown[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(brown[1][0],brown[1][1],brown[1][2]);//250,5,5
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(brown[2][0],brown[2][1],brown[2][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //right
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(brown[2][0],brown[2][1],brown[2][2]);//250,5,5
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
}

void mygl2::histoPlot14(double h){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};// fluctuate
    double brown[3][3] = {{0.588235,0.313725,0.117647},{0.529412,0.254902,0.058824},{0.529412,0.254902,0.058824}};
    int rand1 = qrand() % 10;//random

    for( int i = 0 ; i < 4 ; i++){
        //point[i][1] += (delta[rand1]/10);
        point[i][1] = h /65536  ;// 2 1
        point[i][1] --;

    }


    for( int i = 0 ; i < 8 ; i++ ){// move left
        point[i][2] += 1;
    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }

    for( int i = 0 ; i < 8 ; i++){// move back for h43
        point[i][0] -= 1;
    }


    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h12
        for( int j = 0 ; j < 3 ; j++){
            brown[i][j] *= 1.2;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(brown[0][0],brown[0][1],brown[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
     glColor3f(brown[0][0],brown[0][1],brown[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
     glColor3f(brown[1][0],brown[1][1],brown[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(brown[1][0],brown[1][1],brown[1][2]);//250,5,5
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(brown[2][0],brown[2][1],brown[2][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //right
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(brown[2][0],brown[2][1],brown[2][2]);//250,5,5
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
}


void mygl2::histoPlot21(double h){  // 3 2
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    double red[3][3]={{0.8765625,0.01953125,0.01953125},{0.64546875, 0.0390625, 0.0390625},{0.7421875, 0.01953125, 0.01953125}};
    int rand1 = qrand() % 10;

    for( int i = 0 ; i < 4 ; i++){
       // point[i][1] += (delta[rand1]/10);
        point[i][1] =h/65536;
        point[i][1] --;

    }



    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }
    for( int i = 0 ; i < 8 ; i++){// move back for h12
        point[i][0] -= 2;
    }
    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h43
        for( int j = 0 ; j < 3 ; j++){
            red[i][j] *= 0.85;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(red[0][0],red[0][1],red[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
     glColor3f(red[0][0],red[0][1],red[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(red[1][0],red[1][1],red[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(red[1][0],red[1][1],red[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(red[2][0],red[2][1],red[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(red[2][0],red[2][1],red[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}

void mygl2::histoPlot22(double h){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    double red[3][3]={{0.8765625,0.01953125,0.01953125},{0.64546875, 0.0390625, 0.0390625},{0.7421875, 0.01953125, 0.01953125}};
    int rand1 = qrand() % 10;

    for( int i = 0 ; i < 4 ; i++){
        //point[i][1] += (delta[rand1]/10);
        point[i][1] = h/65536;
        point[i][1] --;

    }


    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }
    for( int i = 0 ; i < 8 ; i++){// move back for h12
        point[i][0] -= 3;
    }
    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h43
        for( int j = 0 ; j < 3 ; j++){
            red[i][j] *= 0.9;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(red[0][0],red[0][1],red[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
     glColor3f(red[0][0],red[0][1],red[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(red[1][0],red[1][1],red[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(red[1][0],red[1][1],red[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(red[2][0],red[2][1],red[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(red[2][0],red[2][1],red[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}

void mygl2::histoPlot23(double h){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    double red[3][3]={{0.8765625,0.01953125,0.01953125},{0.64546875, 0.0390625, 0.0390625},{0.7421875, 0.01953125, 0.01953125}};
    int rand1 = qrand() % 10;

    for( int i = 0 ; i < 4 ; i++){
       // point[i][1] += (delta[rand1]/10);
        point[i][1] = h/65536;
        point[i][1] --;

    }

    for( int i = 0 ; i < 8 ; i++ ){// move left
        point[i][2] += 1;
    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }

    for( int i = 0 ; i < 8 ; i++){// move back for h43
        point[i][0] -= 2;
    }

    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h43
        for( int j = 0 ; j < 3 ; j++){
            red[i][j] *= 1;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(red[0][0],red[0][1],red[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
     glColor3f(red[0][0],red[0][1],red[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(red[1][0],red[1][1],red[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(red[1][0],red[1][1],red[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(red[2][0],red[2][1],red[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(red[2][0],red[2][1],red[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}
void mygl2::histoPlot24(double h){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    double red[3][3]={{0.8765625,0.01953125,0.01953125},{0.64546875, 0.0390625, 0.0390625},{0.7421875, 0.01953125, 0.01953125}};
    int rand1 = qrand() % 10;

    for( int i = 0 ; i < 4 ; i++){
        //point[i][1] += (delta[rand1]/10);
        point[i][1] = h/65536;
        point[i][1] --;

    }

    for( int i = 0 ; i < 8 ; i++ ){// move left
        point[i][2] += 1;
    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }

    for( int i = 0 ; i < 8 ; i++){// move back for h43
        point[i][0] -= 3;
    }

    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h43
        for( int j = 0 ; j < 3 ; j++){
            red[i][j] *= 1.1;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(red[0][0],red[0][1],red[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
     glColor3f(red[0][0],red[0][1],red[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(red[1][0],red[1][1],red[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(red[1][0],red[1][1],red[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(red[2][0],red[2][1],red[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(red[2][0],red[2][1],red[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}


void mygl2::histoPlot31(double h){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    double orange[3][3] = {{1,0.490196,0},{0.784314, 0.333333, 0.039216},{0.901961, 0.411765, 0.019608}};//light-up dark-left mid-front
    int rand1 = qrand() % 10;

    for( int i = 0 ; i < 4 ; i++){
        //point[i][1] += (delta[rand1]/10);
        point[i][1] =  h/65536;
        point[i][1] --;

    }

    for( int i = 0 ; i < 8 ; i++ ){
        point[i][2] += 2;

    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }
    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(orange[0][0],orange[0][1],orange[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(orange[0][0],orange[0][1],orange[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(orange[1][0],orange[1][1],orange[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(orange[1][0],orange[1][1],orange[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(orange[2][0],orange[2][1],orange[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(orange[2][0],orange[2][1],orange[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}
void mygl2::histoPlot32(double h){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    double orange[3][3] = {{1,0.490196,0},{0.784314, 0.333333, 0.039216},{0.901961, 0.411765, 0.019608}};//light-up dark-left mid-front
    int rand1 = qrand() % 10;

    for( int i = 0 ; i < 4 ; i++){
        //point[i][1] += (delta[rand1]/10);
        point[i][1] = h/65536;
        point[i][1] --;

    }



    for( int i = 0 ; i < 8 ; i++ ){
        point[i][2] += 2;

    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }
    for( int i = 0 ; i < 8 ; i++){// move back for h43
        point[i][0] -= 1;
    }

    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h43
        for( int j = 0 ; j < 3 ; j++){
            orange[i][j] *= 1.1;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(orange[0][0],orange[0][1],orange[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(orange[0][0],orange[0][1],orange[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(orange[1][0],orange[1][1],orange[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(orange[1][0],orange[1][1],orange[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(orange[2][0],orange[2][1],orange[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(orange[2][0],orange[2][1],orange[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}
void mygl2::histoPlot33(double h){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    double orange[3][3] = {{1,0.490196,0},{0.784314, 0.333333, 0.039216},{0.901961, 0.411765, 0.019608}};//light-up dark-left mid-front
    int rand1 = qrand() % 10;

    for( int i = 0 ; i < 4 ; i++){
        //point[i][1] += (delta[rand1]/10);
        point[i][1] = h/65536;
        point[i][1] --;

    }



    for( int i = 0 ; i < 8 ; i++ ){//left
        point[i][2] += 3;

    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }

    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h43
        for( int j = 0 ; j < 3 ; j++){
            orange[i][j] *= 1.15;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(orange[0][0],orange[0][1],orange[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(orange[0][0],orange[0][1],orange[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(orange[1][0],orange[1][1],orange[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(orange[1][0],orange[1][1],orange[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(orange[2][0],orange[2][1],orange[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(orange[2][0],orange[2][1],orange[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}
void mygl2::histoPlot34(double h){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    double orange[3][3] = {{1,0.490196,0},{0.784314, 0.333333, 0.039216},{0.901961, 0.411765, 0.019608}};//light-up dark-left mid-front
    int rand1 = qrand() % 10;

    for( int i = 0 ; i < 4 ; i++){
        //point[i][1] += (delta[rand1]/10);
        point[i][1] = h/65536;

        point[i][1] --;

    }




    for( int i = 0 ; i < 8 ; i++ ){
        point[i][2] += 3;

    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }

    for( int i = 0 ; i < 8 ; i++){// move back for h42
        point[i][0] -= 1;
    }

    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h43
        for( int j = 0 ; j < 3 ; j++){
            orange[i][j] *= 1.2;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(orange[0][0],orange[0][1],orange[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(orange[0][0],orange[0][1],orange[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(orange[1][0],orange[1][1],orange[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(orange[1][0],orange[1][1],orange[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(orange[2][0],orange[2][1],orange[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(orange[2][0],orange[2][1],orange[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}
void mygl2::histoPlot41(double h){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    GLdouble yellow[3][3] = {{0.980392,0.745098,0.019608},{0.72549, 0.529412, 0.137255},{0.862745, 0.627451, 0.098039}};//light dark middle
    int rand1 = qrand() % 10;

    for( int i = 0 ; i < 4 ; i++){
        //point[i][1] += (delta[rand1]/10);
        point[i][1] = h/65536;
        point[i][1] --;

    }




    for( int i = 0 ; i < 8 ; i++ ){//left
        point[i][2] += 2;

    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }
    for( int i = 0 ; i < 8 ; i++){// move back for h43
        point[i][0] -= 2;
    }
    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(yellow[0][0],yellow[0][1],yellow[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(yellow[0][0],yellow[0][1],yellow[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
   glColor3f(yellow[1][0],yellow[1][1],yellow[1][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(yellow[1][0],yellow[1][1],yellow[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
   glColor3f(yellow[2][0],yellow[2][1],yellow[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(yellow[2][0],yellow[2][1],yellow[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}

void mygl2::histoPlot42(double h){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    GLdouble yellow[3][3] = {{0.980392,0.745098,0.019608},{0.72549, 0.529412, 0.137255},{0.862745, 0.627451, 0.098039}};//light dark middle
    int rand1 = qrand() % 10;


    for( int i = 0 ; i < 4 ; i++){
        //point[i][1] += (delta[rand1]/10);
        point[i][1] = h/65536;
        point[i][1] --;

    }






    for( int i = 0 ; i < 8 ; i++ ){//left
        point[i][2] += 2;

    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }
    for( int i = 0 ; i < 8 ; i++){// move back for h43
        point[i][0] -= 3;
    }
    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h42
        for( int j = 0 ; j < 3 ; j++){
            yellow[i][j] *= 1.1;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(yellow[0][0],yellow[0][1],yellow[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(yellow[0][0],yellow[0][1],yellow[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
   glColor3f(yellow[1][0],yellow[1][1],yellow[1][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(yellow[1][0],yellow[1][1],yellow[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
   glColor3f(yellow[2][0],yellow[2][1],yellow[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(yellow[2][0],yellow[2][1],yellow[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}

void mygl2::histoPlot43(double h){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    GLdouble yellow[3][3] = {{0.980392,0.745098,0.019608},{0.72549, 0.529412, 0.137255},{0.862745, 0.627451, 0.098039}};//light dark middle
    int rand1 = qrand() % 10;


    for( int i = 0 ; i < 4 ; i++){
        //point[i][1] += (delta[rand1]/10);
        point[i][1] = h/65536;
        point[i][1] --;

    }


    for( int i = 0 ; i < 8 ; i++ ){
        point[i][2] += 3;

    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }

    for( int i = 0 ; i < 8 ; i++){// move back for h43
        point[i][0] -= 2;
    }

    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h43
        for( int j = 0 ; j < 3 ; j++){
            yellow[i][j] *= 1.2;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(yellow[0][0],yellow[0][1],yellow[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(yellow[0][0],yellow[0][1],yellow[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
   glColor3f(yellow[1][0],yellow[1][1],yellow[1][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(yellow[1][0],yellow[1][1],yellow[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
   glColor3f(yellow[2][0],yellow[2][1],yellow[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(yellow[2][0],yellow[2][1],yellow[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}

void mygl2::histoPlot44(double h){
    /*
     * remember : adjust position and color
     *move back in x-axis and set color lighter
     */

    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    GLdouble yellow[3][3] = {{0.980392,0.745098,0.019608},{0.72549, 0.529412, 0.137255},{0.862745, 0.627451, 0.098039}};//light dark middle
    int rand1 = qrand() % 10;


    for( int i = 0 ; i < 4 ; i++){
        //point[i][1] += (delta[rand1]/10);
        point[i][1] = map[0][3]/65536;
        point[i][1] --;

    }


    for( int i = 0 ; i < 8 ; i++ ){
        point[i][2] += 3;

    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }

    for( int i = 0 ; i < 8 ; i++){// move back for h43
        point[i][0] -= 3;
    }

    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h43
        for( int j = 0 ; j < 3 ; j++){
            yellow[i][j] *= 1.23;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(yellow[0][0],yellow[0][1],yellow[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(yellow[0][0],yellow[0][1],yellow[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
   glColor3f(yellow[1][0],yellow[1][1],yellow[1][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(yellow[1][0],yellow[1][1],yellow[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
   glColor3f(yellow[2][0],yellow[2][1],yellow[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(yellow[2][0],yellow[2][1],yellow[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}

void mygl2::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up :
        xRot += 10;
        break;
    case Qt::Key_Left :
        yRot += 10;
        break;
    case Qt::Key_Right :
        zRot += 10;
        break;
    case Qt::Key_Down :
        translate -= 1;
        if (translate <= -20)
            translate = -1;
        break;
    }
    updateGL();
    QGLWidget::keyPressEvent(event);
}

void reducemap(){
    for( int i = 0 ; i < 4 ; i++ ){
        for( int j = 0 ; j < 4 ; j++){
            map[i][j] *= 0.5;
        }
    }


}
void mygl2::timerEvent(QTimerEvent *event){
    //socket run
     //int num_comma = 0;//counter of comma



      memset(out_mygl2,0,LEN*5);
      int intsize=sizeof(sockaddr_in);






      memcpy(lastbuff,buff,LEN);
      fd_set fdR;
      struct timeval timeout = {1,0};
      FD_ZERO(&fdR);
      FD_SET(sockser,&fdR);
      switch( select(sockser+1,&fdR,NULL,NULL,&timeout) ){
          case -1: break;
          case 0: ifrecvd = -1;memcpy(buff,lastbuff,LEN);break;
          default:ifrecvd = 1;
                 recvfrom(sockser,&buff,9000,0,(struct sockaddr *)&addrrcv,(socklen_t*)&intsize);break;
      }
      if(ifrecvd == 1){
      //recvfrom(sockser,&buff,9000,0,(struct sockaddr *)&addrrcv,(socklen_t*)&intsize);
      //qDebug() << buff;
      qDebug() << "Counter is " << cnt++ << endl;

      search_core_data_mygl2_a(buff);// to out_mygl2_net_A
      if(endmark_a == 1){
         endmark_a = 0;
         //swap the order
          for( int i = 0 ; i < 84 ; i ++){ //84*6=504
             int position = i * 6;
             char tmp;
             //swap
             tmp = out_mygl2_a[position];
             out_mygl2_a[position] = out_mygl2_a[position+3];
             out_mygl2_a[position+3] = tmp;
             //swap
             position ++;
             tmp = out_mygl2_a[position];
             out_mygl2_a[position] = out_mygl2_a[position+3];
             out_mygl2_a[position+3] = tmp;
          }//for

          qDebug() << out_mygl2_a << endl;
      }
      for(int i = 1 ; i <= 20; i++ ){  // 20*4=80
          char mark[2];
          mark[0] = out_mygl2_a[i*12];
          mark[1] = out_mygl2_a[i*12+1];
          if( mark[0] == '1' && mark[1] == '4'){
             map[2][3] = charToint(&out_mygl2_a[i*12+3],9)*4;
          }else if( mark[0] == '2' && mark[1] == '4' ){
             map[3][2] = charToint(&out_mygl2_a[i*12+3],9)*4;
          }else if( mark[0] == '3' && mark[1] == '4' ){
             map[3][3] = charToint(&out_mygl2_a[i*12+3],9)*4;
          }else if( mark[0] == '0' && mark[1] == '4' ){
             map[2][2] = charToint(&out_mygl2_a[i*12+3],9)*4;
          }
      }//for i.
      memset(out_mygl2_a,0,9000);

      search_core_data_mygl2_b(buff);// to out_mygl2_net_B
      if(endmark_b == 1){
         endmark_b = 0;
         //swap the order
          for( int i = 0 ; i < 84 ; i ++){
             int position = i * 6;
             char tmp;
             //swap
             tmp = out_mygl2_b[position];
             out_mygl2_b[position] = out_mygl2_b[position+3];
             out_mygl2_b[position+3] = tmp;
             //swap
             position ++;
             tmp = out_mygl2_b[position];
             out_mygl2_b[position] = out_mygl2_b[position+3];
             out_mygl2_b[position+3] = tmp;
          }//for

          qDebug() << out_mygl2_b << endl;
      }
      for(int i = 1 ; i <= 20; i++ ){
          char mark[2];
          mark[0] = out_mygl2_b[i*12];
          mark[1] = out_mygl2_b[i*12+1];
          if( mark[0] == '4' && mark[1] == '4'){
             map[2][0] = charToint(&out_mygl2_b[i*12+3],9)*4;

          }else if( mark[0] == '5' && mark[1] == '4' ){
             map[2][1] = charToint(&out_mygl2_b[i*12+3],9)*4;

          }else if( mark[0] == '6' && mark[1] == '4' ){
             map[3][0] = charToint(&out_mygl2_b[i*12+3],9)*4;

          }else if( mark[0] == '7' && mark[1] == '4' ){
             // qDebug() <<  out_mygl2_b[i*12+3]  << out_mygl2_b[i*12+4] << out_mygl2_b[i*12+5]  << out_mygl2_b[i*12+6]  << out_mygl2_b[i*12+7] <<endl;
             map[3][1] = charToint(&out_mygl2_b[i*12+3],9)*4;
          }
      }//for i


      memset(out_mygl2_b,0,9000);

      search_core_data_mygl2_c(buff);// to out_mygl2_net_C
      if(endmark_c == 1){
         endmark_c = 0;
         //swap the order
          for( int i = 0 ; i < 84 ; i ++){
             int position = i * 6;
             char tmp;
             //swap
             tmp = out_mygl2_c[position];
             out_mygl2_c[position] = out_mygl2_c[position+3];
             out_mygl2_c[position+3] = tmp;
             //swap
             position ++;
             tmp = out_mygl2_c[position];
             out_mygl2_c[position] = out_mygl2_c[position+3];
             out_mygl2_c[position+3] = tmp;
          }//for

          qDebug() << out_mygl2_c << endl;
      }

      for(int i = 1 ; i <= 20; i++ ){
          char mark[2];
          mark[0] = out_mygl2_c[i*12];
          mark[1] = out_mygl2_c[i*12+1];
          if( mark[0] == '8' && mark[1] == '4'){
             map[0][0] = charToint(&out_mygl2_c[i*12+3],9)*4;
             visit[0][0] ++;
          }else if( mark[0] == '9' && mark[1] == '4' ){
             map[0][1] = charToint(&out_mygl2_c[i*12+3],9)*4;
             visit[0][1] ++;
          }else if( mark[0] == 'a' && mark[1] == '4' ){
             map[1][0] = charToint(&out_mygl2_c[i*12+3],9)*4;
             visit[1][0] ++;
          }else if( mark[0] == 'b' && mark[1] == '4' ){
            //  qDebug() <<  out_mygl2_2[i*12+3]  << out_mygl2_2[i*12+4] << out_mygl2_2[i*12+5]  << out_mygl2_2[i*12+6]  << out_mygl2_2[i*12+7] <<endl;
             map[1][1] = charToint(&out_mygl2_c[i*12+3],9)*4;
             visit[1][1] ++;
          }
      }//for i
      memset(out_mygl2_c,0,9000);

      search_core_data_mygl2_d(buff);// to out_mygl2_net_d
      if(endmark_d == 1){
         endmark_d = 0;
         //swap the order
          for( int i = 0 ; i < 84 ; i ++){
             int position = i * 6;
             char tmp;
             //swap
             tmp = out_mygl2_d[position];
             out_mygl2_d[position] = out_mygl2_d[position+3];
             out_mygl2_d[position+3] = tmp;
             //swap
             position ++;
             tmp = out_mygl2_d[position];
             out_mygl2_d[position] = out_mygl2_d[position+3];
             out_mygl2_d[position+3] = tmp;
          }//for

          qDebug() << out_mygl2_d << endl;
      }


      for(int i = 1 ; i <= 20; i++ ){
          char mark[2];
          mark[0] = out_mygl2_d[i*12];
          mark[1] = out_mygl2_d[i*12+1];
          if( mark[0] == 'c' && mark[1] == '4'){
             map[0][2] = charToint(&out_mygl2_d[i*12+3],9)*4;

          }else if( mark[0] == 'd' && mark[1] == '4' ){
             map[0][3] = charToint(&out_mygl2_d[i*12+3],9)*4;

          }else if( mark[0] == 'e' && mark[1] == '4' ){
             map[1][2] = charToint(&out_mygl2_d[i*12+3],9)*4;

          }else if( mark[0] == 'f' && mark[1] == '4' ){
            //  qDebug() <<  out_mygl2_2[i*12+3]  << out_mygl2_2[i*12+4] << out_mygl2_2[i*12+5]  << out_mygl2_2[i*12+6]  << out_mygl2_2[i*12+7] <<endl;
             map[1][3] = charToint(&out_mygl2_d[i*12+3],9)*4;

          }
      }//for i



      memset(out_mygl2_d,0,9000);

      qDebug() << "map[0][0] is :" << map[0][0];
      qDebug() << "map[0][1] is :" << map[0][1];
      qDebug() << "map[0][2] is :" << map[0][2];
      qDebug() << "map[0][3] is :" << map[0][3];

      qDebug() << "map[1][0] is :" << map[1][0];
      qDebug() << "map[1][1] is :" << map[1][1];
      qDebug() << "map[1][2] is :" << map[1][2];
      qDebug() << "map[1][3] is :" << map[1][3] <<endl;
      qDebug() << "map[2][0] is :" << map[2][0];
      qDebug() << "map[2][1] is :" << map[2][1];
      qDebug() << "map[2][2] is :" << map[2][2];
      qDebug() << "map[2][3] is :" << map[2][3] <<endl;
      qDebug() << "map[3][0] is :" << map[3][0];
      qDebug() << "map[3][1] is :" << map[3][1];
      qDebug() << "map[3][2] is :" << map[3][2];
      qDebug() << "map[3][3] is :" << map[3][3] <<endl;

      }else if( ifrecvd == -1 ){
          reducemap();

      }

/*
     while(1){
         char str[1000];
         recvfrom(sockser,&buff,9000,0,(struct sockaddr *)&addrrcv,(socklen_t*)&intsize);//port 9000 recv PE data from server
        // recvfrom(sockser2,&buff2,9000,0,(struct sockaddr *)&addrrcv2,(socklen_t*)&intsize);
         if( continueflag_mygl2 == 0 ){
             if(out_mygl2[0] != '\0'){//get a whole 84-frame
                 num_frame ++;
                 memset(out_mygl2,0,LEN*5);
                 //if(num_frame == 24){file.close();}
             }//if
             search_core_data_mygl2(buff);
         }else if(continueflag_mygl2reducemap == 1){
             search_core_data2_mygl2(buff);
         }//elif
         //qDebug() << buff << endl;
         if(endmark == 1 ){
            endmark = 0;//reset the flag
            qDebug() << "The number of frame is : "<< num_frame ;
            for( int i = 0 ; i < LENGTH_OF_CORE ; i ++){
               int position = i *6;
               char tmp;
               //swap
               tmp = out_mygl2[position];
               out_mygl2[position] = out_mygl2[position+3];
               out_mygl2[position+3] = tmp;
               //swap
               position ++;
               tmp = out_mygl2[position];
               out_mygl2[position] = out_mygl2[position+3];
               out_mygl2[position+3] = tmp;
            }//for

            //qDebug() << out_mygl2 <<endl ;
            //file.write(out,84);
            //qDebug() << "---------------------------------------------------------------------------------------------------------" << endl;

            break;
         }
     }//while


     memset(out_mygl2_2,0,LEN*5);

     while(1){
         char str[1000];reducemap
         recvfrom(sockser,&buff,9000,0,(struct sockaddr *)&addrrcv,(socklen_t*)&intsize);
        // recvfrom(sockser2,&buff2,9000,0,(struct sockaddr *)&addrrcv2,(socklen_t*)&intsize);
         if( continueflag_mygl2_2 == 0 ){
             if(out_mygl2_2[0] != '\0'){//get a whole 84-frame
                 num_frame ++;
                 memset(out_mygl2_2,0,LEN*5);
                 //if(num_frame == 24){file.close();}
             }//if
             search_core_data_mygl2_2(buff);
         }else if(continueflag_mygl2_2 == 1){
             search_core_data2_mygl2_2(buff);
         }//elif
         //qDebug() << buff << endl;
         if(endmark == 1 ){
            endmark = 0;//reset the flag

            qDebug() << "The number of frame is : "<< num_frame ;

            for( int i = 0 ; i < LENGTH_OF_CORE ; i ++){
               int position = i *6;
               char tmp;
               //swap
               tmp = out_mygl2_2[position];
               out_mygl2_2[position] = out_mygl2_2[position+3];
               out_mygl2_2[position+3] = tmp;
               //swap
               position ++;
               tmp = out_mygl2_2[position];
               out_mygl2_2[position] = out_mygl2_2[position+3];
               out_mygl2_2[position+3] = tmp;
            }//for

            //qDebug() << out_mygl2_2 <<endl ;
            //file.write(out,84);
            //qDebug() << "---------------------------------------------------------------------------------------------------------" << endl;

            break;
         }
     }//while


     while(1){
         char str[1000];
         recvfrom(sockser,&buff,9000,0,(struct sockaddr *)&addrrcv,(socklen_t*)&intsize);
        // recvfrom(sockser2,&buff2,9000,0,(struct sockaddr *)&addrrcv2,(socklen_t*)&intsize);
         if( continueflag_mygl2_3 == 0 ){
             if(out_mygl2_2[0] != '\0'){//get a whole 84-frame
                 num_frame ++;
                 memset(out_mygl2_3,0,LEN*5);
                 //if(num_frame == 24){file.close();}
             }//if
             search_core_data_mygl2_3(buff);
         }else if(continueflag_mygl2_3 == 1){
             search_core_data2_mygl2_3(buff);
         }//elif
         //qDebug() << buff << endl;
         if(endmark == 1 ){
            endmark = 0;//reset the flag

            qDebug() << "The number of frame is : "<< num_frame ;

            for( int i = 0 ; i < LENGTH_OF_CORE ; i ++){
               int position = i *6;
               char tmp;
               //swap
               tmp = out_mygl2_3[position];
               out_mygl2_3[position] = out_mygl2_3[position+3];
               out_mygl2_3[position+3] = tmp;
               //swap
               position ++;
               tmp = out_mygl2_3[position];
               out_mygl2_3[position] = out_mygl2_3[position+3];
               out_mygl2_3[position+3] = tmp;
            }//for

            //qDebug() << out_mygl2_3 <<endl ;
            //file.write(out,84);
            //qDebug() << "---------------------------------------------------------------------------------------------------------" << endl;

            break;
         }
     }//while


     while(1){
         char str[1000];
         recvfrom(sockser,&buff,9000,0,(struct sockaddr *)&addrrcv,(socklen_t*)&intsize);
        // recvfrom(sockser2,&buff2,9000,0,(struct sockaddr *)&addrrcv2,(socklen_t*)&intsize);
         if( continueflag_mygl2_4 == 0 ){
             if(out_mygl2_2[0] != '\0'){//get a whole 84-frame
                 num_frame ++;
                 memset(out_mygl2_4,0,LEN*5);
                 //if(num_frame == 24){file.close();}
             }//if
             search_core_data_mygl2_4(buff);
         }else if(continueflag_mygl2_4 == 1){
             search_core_data2_mygl2_4(buff);
         }//elif
         //qDebug() << buff << endl;
         if(endmark == 1 ){
            endmark = 0;//reset the flag

            qDebug() << "The number of frame is : "<< num_frame ;

            for( int i = 0 ; i < LENGTH_OF_CORE ; i ++){
               int position = i *6;
               char tmp;
               //swap
               tmp = out_mygl2_4[position];
               out_mygl2_4[position] = out_mygl2_4[position+3];
               out_mygl2_4[position+3] = tmp;
               //swap
               position ++;
               tmp = out_mygl2_4[position];
               out_mygl2_4[position] = out_mygl2_4[position+3];out_mygl2_a
               out_mygl2_4[position+3] = tmp;
            }//for

            //qDebug() << out_mygl2_4 <<endl ;
            //file.write(out,84);
            //qDebug() << "---------------------------------------------------------------------------------------------------------" << endl;

            break;
         }
     }//while
reducemap


     memset(visit,0,sizeof(int)*16);
     for(int i = 1 ; i <= 20; i++ ){
         char mark[2];
         mark[0] = out_mygl2[i*12];
         mark[1] = out_mygl2[i*12+1];
         if( mark[0] == '1' && mark[1] == '4'){
            map[2][3] = charToint(&out_mygl2[i*12+3],9);
            visit[2][3] ++;
         }else if( mark[0] == '2' && mark[1] == '4' ){
            map[3][2] = charToint(&out_mygl2[i*12+3],9);
            visit[3][2] ++;
         }else if( mark[0] == '3' && mark[1] == '4' ){
            map[3][3] = charToint(&out_mygl2[i*12+3],9);
            visit[3][3] ++;out_mygl2_a
         }else if( mark[0] == '0' && mark[1] == '4' ){
            map[2][2] = charToint(&out_mygl2[i*12+3],9);
            visit[2][2] ++;
         }
     }//for i


     for(int i = 1 ; i <= 20; i++ ){
         char mark[2];
         mark[0] = out_mygl2_2[i*12];
         mark[1] = out_mygl2_2[i*12+reducemap1];
         if( mark[0] == '4' && mark[1] == '4'){
            map[2][0] = charToint(&out_mygl2_2[i*12+3],9);
            visit[2][0] ++;
         }else if( mark[0] == '5' && mark[1] == '4' ){
            map[2][1] = charToint(&out_mygl2_2[i*12+3],9);
            visit[2][1]++;
         }else if( mark[0] == '6' && mark[1] == '4' ){
            map[3][0] = charToint(&out_mygl2_2[i*12+3],9);
            visit[3][0] ++;
         }else if( mark[0] == '7' && mark[1] == '4' ){
            // qDebug() <<  out_mygl2_2[i*12+3]  << out_mygl2_2[i*12+4] << out_mygl2_2[i*12+5]  << out_mygl2_2[i*12+6]  << out_mygl2_2[i*12+7] <<endl;
            map[3][1] = charToint(&out_mygl2_2[i*12+3],9);
            visit[3][1] ++;
         }
     }//for i

     for(int i = 1 ; i <= 20; i++ ){
         char mark[2];
         mark[0] = out_mygl2_3[i*12];
         mark[1] = out_mygl2_3[i*12+1];
         if( mark[0] == '8' && mark[1] == '4'){
            map[0][0] = charToint(&out_mygl2_3[i*12+3],9);
            visit[0][0] ++;
         }else if( mark[0] == '9' && mark[1] == '4' ){
            map[0][1] = charToint(&out_mygl2_3[i*12+3],9);
            visit[0][1] ++;
         }else if( mark[0] == 'a' && mark[1] == '4' ){
            map[1][0] = charToint(&out_mygl2_3[i*12+3],9);
            visit[1][0] ++;
         }else if( mark[0] == 'b' && mark[1] == '4' ){
           //  qDebug() <<  out_mygl2_2[i*12+3]  << out_mygl2_2[i*12+4] << out_mygl2_2[i*12+5]  << out_mygl2_2[i*12+6]  << out_mygl2_2[i*12+7] <<endl;
            map[1][1] = charToint(&out_mygl2_3[i*12+3],9);
            visit[1][1] ++;
         }
     }//for i

     for(int i = 1 ; i <= 20; i++ ){
         char mark[2];
         mark[0] = out_mygl2_4[i*12];
         mark[1] = out_mygl2_4[i*12+1];
         if( mark[0] == 'c' && mark[1] == '4'){
            map[0][2] = charToint(&out_mygl2_4[i*12+3],9);
            visit[0][2] ++;
         }else if( mark[0] == 'd' && mark[1] == '4' ){
            map[0][3] = charToint(&out_mygl2_4[i*12+3],9);
            visit[0][3] ++;
         }else if( mark[0] == 'e' && mark[1] == '4' ){
            map[1][2] = charToint(&out_mygl2_4[i*12+3],9);
            visit[1][2] ++;
         }else if( mark[0] == 'f' && mark[1] == '4' ){
           //  qDebug() <<  out_mygl2_2[i*12+3]  << out_mygl2_2[i*12+4] << out_mygl2_2[i*12+5]  << out_mygl2_2[i*12+6]  << out_mygl2_2[i*12+7] <<endl;
            map[1][3] = charToint(&out_mygl2_4[i*12+3],9);
            visit[1][3] ++;
         }
     }//for i

     int flag = 0;
     for(int i = 0 ; i < 4 && !flag; i++ ){
         for(int j = 0 ; j < 4 && !flag; j++){
             if(visit[i][j] != 1){
                 flag = 1;
                 break;
             }reducemap
         }
     }
     for(int i = 0 ; i < 4 ; i++ ){
         for(int j = 0 ; j < 4 ; j++){
             if(map[i][j] >= 80000 ){
                   map[i][j] = 0;
             }
         }
     }



     if( flag == 1 ) {
         /*
     qDebug() << "map[0][0] is :" << map[0][0];
     qDebug() << "map[0][1] is :" << map[0][1];
     qDebug() << "map[1][0] is :" << map[1][0];
     qDebug() << "map[1][1] is :" << map[1][1] <<endl;

     qDebug() << "map[1][2] is :" << map[1][2];
     qDebug() << "map[1][3] is :" << map[1][3];
     qDebug() << "map[2][2] is :" << map[2][2];
     qDebug() << "map[2][3] is :" << map[2][3] <<endl;

     qDebug() << "map[2][2] is :" << map[2][2];
     qDebug() << "map[2][3] is :" << map[2][3];
     qDebug() << "map[3][2] is :" << map[3][2];
     qDebug() << "map[3][3] is :" << map[3][3] <<endl;

     qDebug() << "map[2][0] is :" << map[2][0];
     qDebug() << "map[2][1] is :" << map[2][1];
     qDebug() << "map[3][0] is :" << map[3][0];
     qDebug() << "map[3][1] is :" << map[3][1] <<endl;
*/


 //plot the histogram





    glBegin(GL_QUADS);

    glEnable (GL_LINE_SMOOTH );
    glHint (GL_POLYGON_SMOOTH , GL_NICEST);

        histoPlot11(map[3][0]);histoPlot12(map[3][1]);histoPlot13(map[2][0]);histoPlot14(map[2][1]);
        histoPlot21(map[3][2]);histoPlot22 (map[3][3]);histoPlot23(map[2][2]);histoPlot24(map[2][3]);
        histoPlot31(map[1][0]);histoPlot32(map[1][1]);histoPlot33(map[0][0]);histoPlot34( map[0][1]);
        histoPlot41(map[1][2]);histoPlot42(map[1][3]);histoPlot43(map[0][2]);histoPlot44(map[0][3]);
        wallplot();
        glEnd();
        updateGL();

    //floor


    //qDebug()<< "timer event in mygl2 Class!" << endl;
}

double charToint(char *start,int len){
    double res = 0;
    long int res2 = 0;
    long int base = 1048576;//16^6
    //qDebug() << " Start is :"<< start[3] <<start[4] <<endl;
    res2 +=  charTohex(start[0],base);
    base /= 16;
    res2 += charTohex(start[1],base);
    base /= 16;

    res2 += charTohex(start[3],base);
    base /= 16;
    res2 += charTohex(start[4],base);
    base /= 16;

    res2 += charTohex(start[6],base);
    base /= 16;
    res2 += charTohex(start[7],base);

    return res2;
}


int  charTohex(char c,int base){
    int res = 0;
    if( c >= 'a' && c <= 'f'){
        res = c - 'a' + 10;
    }else if( c >= '0' && c <= '9'){
        res = c-'0';
    }
    //qDebug() << res;
    return res*base;
}


void search_core_data_mygl2(  char* buff ){
    int i;
    int find = 0;//consider that there is no header?
    for( i = 0 ; i < LEN - 10 ; i++ ){
        //search the header of the core-frame

        if(buff[i] == 'a' && buff[i+1] == 'a' && buff[i+2] == ',' && buff[i+3] == 'a' && buff[i+4] == '0' && buff[i+5] == ',' && buff[i+6] == '2' && buff[i+7] == '8' && buff[i+8] == ',' && buff[i+9] == '4' && buff[i+10] == '0'){

            find = 1;
            break;
        }
    }//for
    if( find == 0 ){
        return ;
    }
    char bottle[LEN] = {0};
    int cnt = 0;
    int cnt_comma = 0;
    //outposition = 0;
    for( int j = i ;  ; j++){
        if( buff[j] != '-' && buff[j] != '\n'){
            bottle[cnt++]  = buff[j];
            //out[outposition++] = buff[j];
        }//if

        if( buff[j] == ',' ){
            cnt_comma ++;
        }

        if( cnt_comma == LENGTH_OF_CORE  && buff[j+1] == ',' && buff[j+2] == 'a' && buff[j+3] == 'a' && buff[j+4] == ',' && buff[j+1] == ','){
           rest_num_comma_mygl2 = 0;
           continueflag_mygl2 = 0;
           endmark = 1;//find a total frame

           break;
        }
        else if( j == LEN){
            rest_num_comma_mygl2 = LENGTH_OF_CORE - cnt_comma;
            continueflag_mygl2 = 1; //there is still some frames in the later buffer
            break;
        }
    }//for j
    //qDebug() <<"FIRST :" <<bottle <<endl;
    strcat(out_mygl2,bottle);
}

void search_core_data2_mygl2(  char* buff ){ // continue to send the data

    char bottle[LEN] = {0};
    int cnt = 0;
    int cnt_comma = 0;

    for( int j = 0 ;  ; j++){
        if( buff[j] != '-' && buff[j] != '\n'){
            bottle[cnt++]  = buff[j];
            //out[outposition++] = buff[j];
        }//if
        if( buff[j] == ',' ){
            cnt_comma ++;
            rest_num_comma_mygl2 --;
        }
        if( rest_num_comma_mygl2 == 0){// the end of the later frame
            continueflag_mygl2 = 0;
            endmark = 1;
            //qDebug() << "rest is zero."<<endl;
            break;
        }
        else if( rest_num_comma_mygl2 > 0 && j == LEN){
            continueflag_mygl2 = 1; //there is still some frames in the later buffer
            break;
        }
    }//for j
    //qDebug() <<" (next)" <<bottle ;
    strcat(out_mygl2,bottle);
}



void search_core_data_mygl2_2(  char* buff ){
    int i;
    int find = 0;//consider that there is no header?
    for( i = 0 ; i < LEN - 10 ; i++ ){
        //search the header of the core-frame

        if(buff[i] == 'a' && buff[i+1] == 'a' && buff[i+2] == ',' && buff[i+3] == 'a' && buff[i+4] == '0' && buff[i+5] == ',' && buff[i+6] == '2' && buff[i+7] == '8' && buff[i+8] == ',' && buff[i+9] == '6' && buff[i+10] == '0'){

            find = 1;
            break;
        }
    }//for
    if( find == 0 ){
        return ;
    }
    char bottle[LEN] = {0};
    int cnt = 0;
    int cnt_comma = 0;
    //outposition = 0;
    for( int j = i ;  ; j++){
        if( buff[j] != '-' && buff[j] != '\n'){
            bottle[cnt++]  = buff[j];
            //out[outposition++] = buff[j];
        }//if

        if( buff[j] == ',' ){
            cnt_comma ++;
        }

        if( cnt_comma == LENGTH_OF_CORE ){
           rest_num_comma_mygl2_2 = 0;
           continueflag_mygl2_2 = 0;
           endmark = 1;//find a total frame
           break;
        }
        else if( j == LEN){
            rest_num_comma_mygl2_2 = LENGTH_OF_CORE - cnt_comma;
            continueflag_mygl2_2 = 1; //there is still some frames in the later buffer
            break;
        }
    }//for j
    //qDebug() <<"FIRST :" <<bottle <<endl;
    strcat(out_mygl2_2,bottle);
}

void search_core_data2_mygl2_2(  char* buff ){ // continue to send the data

    char bottle[LEN] = {0};
    int cnt = 0;
    int cnt_comma = 0;

    for( int j = 0 ;  ; j++){
        if( buff[j] != '-' && buff[j] != '\n'){
            bottle[cnt++]  = buff[j];
            //out[outposition++] = buff[j];
        }//if
        if( buff[j] == ',' ){
            cnt_comma ++;
            rest_num_comma_mygl2_2 --;
        }
        if( rest_num_comma_mygl2_2 == 0){// the end of the later frame
            continueflag_mygl2_2 = 0;
            endmark = 1;
            //qDebug() << "rest is zero."<<endl;
            break;
        }
        else if( rest_num_comma_mygl2_2 > 0 && j == LEN){
            continueflag_mygl2_2 = 1; //there is still some frames in the later buffer
            break;
        }
    }//for j
    //qDebug() <<" (next)" <<bottle ;
    strcat(out_mygl2_2,bottle);
}




void search_core_data_mygl2_3(  char* buff ){
    int i;
    int find = 0;//consider that there is no header?
    for( i = 0 ; i < LEN - 10 ; i++ ){
        //search the header of the core-frame

        if(buff[i] == 'a' && buff[i+1] == 'a' && buff[i+2] == ',' && buff[i+3] == 'a' && buff[i+4] == '0' && buff[i+5] == ',' && buff[i+6] == '2' && buff[i+7] == '8' && buff[i+8] == ',' && buff[i+9] == '8' && buff[i+10] == '0'){

            find = 1;
            break;
        }
    }//for
    if( find == 0 ){
        return ;
    }
    char bottle[LEN] = {0};
    int cnt = 0;
    int cnt_comma = 0;
    //outposition = 0;
    for( int j = i ;  ; j++){
        if( buff[j] != '-' && buff[j] != '\n'){
            bottle[cnt++]  = buff[j];
            //out[outposition++] = buff[j];
        }//if

        if( buff[j] == ',' ){
            cnt_comma ++;
        }

        if( cnt_comma == LENGTH_OF_CORE ){
           rest_num_comma_mygl2_3 = 0;
           continueflag_mygl2_3 = 0;
           endmark = 1;//find a total frame
           break;
        }
        else if( j == LEN){
            rest_num_comma_mygl2_3 = LENGTH_OF_CORE - cnt_comma;
            continueflag_mygl2_3 = 1; //there is still some frames in the later buffer
            break;
        }
    }//for j
    //qDebug() <<"FIRST :" <<bottle <<endl;
    strcat(out_mygl2_3,bottle);
}

void search_core_data2_mygl2_3(  char* buff ){ // continue to send the data

    char bottle[LEN] = {0};
    int cnt = 0;
    int cnt_comma = 0;

    for( int j = 0 ;  ; j++){
        if( buff[j] != '-' && buff[j] != '\n'){
            bottle[cnt++]  = buff[j];
            //out[outposition++] = buff[j];
        }//if
        if( buff[j] == ',' ){
            cnt_comma ++;
            rest_num_comma_mygl2_3 --;
        }
        if( rest_num_comma_mygl2_3 == 0){// the end of the later frame
            continueflag_mygl2_3 = 0;
            endmark = 1;
            //qDebug() << "rest is zero."<<endl;
            break;
        }
        else if( rest_num_comma_mygl2_3 > 0 && j == LEN){
            continueflag_mygl2_3 = 1; //there is still some frames in the later buffer
            break;
        }
    }//for j
    //qDebug() <<" (next)" <<bottle ;
    strcat(out_mygl2_3,bottle);
}




void search_core_data_mygl2_4(  char* buff ){
    int i;
    int find = 0;//consider that there is no header?
    for( i = 0 ; i < LEN - 10 ; i++ ){
        //search the header of the core-frame

        if(buff[i] == 'a' && buff[i+1] == 'a' && buff[i+2] == ',' && buff[i+3] == 'a' && buff[i+4] == '0' && buff[i+5] == ',' && buff[i+6] == '2' && buff[i+7] == '8' && buff[i+8] == ',' && buff[i+9] == '9' && buff[i+10] == '0'){

            find = 1;
            break;
        }
    }//for
    if( find == 0 ){
        return ;
    }
    char bottle[LEN] = {0};
    int cnt = 0;
    int cnt_comma = 0;
    //outposition = 0;
    for( int j = i ;  ; j++){
        if( buff[j] != '-' && buff[j] != '\n'){
            bottle[cnt++]  = buff[j];
            //out[outposition++] = buff[j];
        }//if

        if( buff[j] == ',' ){
            cnt_comma ++;
        }

        if( cnt_comma == LENGTH_OF_CORE ){
           rest_num_comma_mygl2_4 = 0;
           continueflag_mygl2_4 = 0;
           endmark = 1;//find a total frame
           break;
        }
        else if( j == LEN){
            rest_num_comma_mygl2_4 = LENGTH_OF_CORE - cnt_comma;
            continueflag_mygl2_4 = 1; //there is still some frames in the later buffer
            break;
        }
    }//for j
    //qDebug() <<"FIRST :" <<bottle <<endl;
    strcat(out_mygl2_4,bottle);
}

void search_core_data2_mygl2_4(  char* buff ){ // continue to send the data

    char bottle[LEN] = {0};
    int cnt = 0;
    int cnt_comma = 0;

    for( int j = 0 ;  ; j++){
        if( buff[j] != '-' && buff[j] != '\n'){
            bottle[cnt++]  = buff[j];
            //out[outposition++] = buff[j];
        }//if
        if( buff[j] == ',' ){
            cnt_comma ++;
            rest_num_comma_mygl2_4 --;
        }
        if( rest_num_comma_mygl2_4 == 0){// the end of the later frame
            continueflag_mygl2_4 = 0;
            endmark = 1;
            //qDebug() << "rest is zero."<<endl;
            break;
        }
        else if( rest_num_comma_mygl2_4 > 0 && j == LEN){
            continueflag_mygl2_4 = 1; //there is still some frames in the later buffer
            break;
        }
    }//for j
    //qDebug() <<" (next)" <<bottle ;
    strcat(out_mygl2_4,bottle);
}

void search_core_data_mygl2_a(  char* buff ){ // FPGA_A
    int i;
    int find = 0;//consider that there is no header???
    for( i = 0 ; i < LEN - 500 ; i++ ){
        //search the header of the core-frame
        if(buff[i] == 'a' && buff[i+1] == 'a' && buff[i+2] == ',' && buff[i+3] == 'a' && buff[i+4] == '0' && buff[i+5] == ',' && buff[i+6] == '2' && buff[i+7] == '8' && buff[i+8] == ',' && buff[i+9] == '4' && buff[i+10] == '0'){
            find = 1;
            break;
        }
    }//for
    if( find == 0 ){
        return ;
    }
    char bottle[LEN] = {0};
    int cnt = 0;
    int cnt_comma = 0;
    //outposition = 0;
    for( int j = i ;  ; j++){// i is the start of data without header-a0aa2840
        if( buff[j] != '-' && buff[j] != '\n'){  // avoid - and \n
            bottle[cnt++]  = buff[j];
            //out[outposition++] = buff[j];
        }//if

        if( buff[j] == ',' ){// counter
            cnt_comma ++;
        }

        if( cnt_comma == LENGTH_OF_CORE  ){ // reach the end of one frame
           rest_num_comma_mygl2_a = 0;
           continueflag_mygl2_a = 0;
           endmark_a = 1;//find a total frame

           break;
        }
        else if( j == LEN){
            rest_num_comma_mygl2_a = LENGTH_OF_CORE - cnt_comma;
            continueflag_mygl2_a = 1; //there is still some frames in the later buffer
            break;
        }
    }//for j
    //qDebug() <<"FIRST :" <<bottle <<endl;
    strcat(out_mygl2_a,bottle); // out_mygl2_a <------ bottle
}


void search_core_data_mygl2_b(  char* buff ){ // FPGA_A
    int i;
    int find = 0;//consider that there is no header?
    for( i = 0 ; i < LEN - 500 ; i++ ){
        //search the header of the core-frame
        if(buff[i] == 'a' && buff[i+1] == 'a' && buff[i+2] == ',' && buff[i+3] == 'a' && buff[i+4] == '0' && buff[i+5] == ',' && buff[i+6] == '2' && buff[i+7] == '8' && buff[i+8] == ',' && buff[i+9] == '6' && buff[i+10] == '0'){
            find = 1;
            break;
        }
    }//for
    if( find == 0 ){
        return ;
    }
    char bottle[LEN] = {0};
    int cnt = 0;
    int cnt_comma = 0;
    //outposition = 0;
    for( int j = i ;  ; j++){
        if( buff[j] != '-' && buff[j] != '\n'){
            bottle[cnt++]  = buff[j];
            //out[outposition++] = buff[j];
        }//if

        if( buff[j] == ',' ){
            cnt_comma ++;
        }

        if( cnt_comma == LENGTH_OF_CORE  ){
           rest_num_comma_mygl2_b = 0;
           continueflag_mygl2_b = 0;
           endmark_b = 1;//find a total frame

           break;
        }
        else if( j == LEN){
            rest_num_comma_mygl2_b = LENGTH_OF_CORE - cnt_comma;
            continueflag_mygl2_b = 1; //there is still some frames in the later buffer
            break;
        }
    }//for j
    //qDebug() <<"FIRST :" <<bottle <<endl;
    strcat(out_mygl2_b,bottle);
}

void search_core_data_mygl2_c(  char* buff ){ // FPGA_A
    int i;
    int find = 0;//consider that there is no header?
    for( i = 0 ; i < LEN - 500 ; i++ ){
        //search the header of the core-frame
        if(buff[i] == 'a' && buff[i+1] == 'a' && buff[i+2] == ',' && buff[i+3] == 'a' && buff[i+4] == '0' && buff[i+5] == ',' && buff[i+6] == '2' && buff[i+7] == '8' && buff[i+8] == ',' && buff[i+9] == '8' && buff[i+10] == '0'){
            find = 1;
            break;
        }
    }//for
    if( find == 0 ){
        return ;
    }
    char bottle[LEN] = {0};
    int cnt = 0;
    int cnt_comma = 0;
    //outposition = 0;
    for( int j = i ;  ; j++){
        if( buff[j] != '-' && buff[j] != '\n'){
            bottle[cnt++]  = buff[j];
            //out[outposition++] = buff[j];
        }//if

        if( buff[j] == ',' ){
            cnt_comma ++;
        }

        if( cnt_comma == LENGTH_OF_CORE  ){
           rest_num_comma_mygl2_c = 0;
           continueflag_mygl2_c = 0;
           endmark_c = 1;//find a total frame

           break;
        }
        else if( j == LEN){
            rest_num_comma_mygl2_c = LENGTH_OF_CORE - cnt_comma;
            continueflag_mygl2_c = 1; //there is still some frames in the later buffer
            break;
        }
    }//for j
    //qDebug() <<"FIRST :" <<bottle <<endl;
    strcat(out_mygl2_c,bottle);
}

void search_core_data_mygl2_d(  char* buff ){ // FPGA_A
    int i;
    int find = 0;//consider that there is no header?
    for( i = 0 ; i < LEN - 500 ; i++ ){
        //search the header of the core-frame
        if(buff[i] == 'a' && buff[i+1] == 'a' && buff[i+2] == ',' && buff[i+3] == 'a' && buff[i+4] == '0' && buff[i+5] == ',' && buff[i+6] == '2' && buff[i+7] == '8' && buff[i+8] == ',' && buff[i+9] == 'a' && buff[i+10] == '0'){
            find = 1;
            break;
        }
    }//for
    if( find == 0 ){
        return ;
    }
    char bottle[LEN] = {0};
    int cnt = 0;
    int cnt_comma = 0;
    //outposition = 0;
    for( int j = i ;  ; j++){
        if( buff[j] != '-' && buff[j] != '\n'){
            bottle[cnt++]  = buff[j];
            //out[outposition++] = buff[j];
        }//if

        if( buff[j] == ',' ){
            cnt_comma ++;
        }

        if( cnt_comma == LENGTH_OF_CORE  ){
           rest_num_comma_mygl2_d = 0;
           continueflag_mygl2_d = 0;
           endmark_d = 1;//find a total frame

           break;
        }
        else if( j == LEN){  // LEN is 9000
            rest_num_comma_mygl2_d = LENGTH_OF_CORE - cnt_comma;
            continueflag_mygl2_d = 1; //there is still some frames in the later buffer
            break;
        }
    }//for j
    //qDebug() <<"FIRST :" <<bottle <<endl;
    strcat(out_mygl2_d,bottle);
}
