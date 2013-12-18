#include <QApplication>

#include <mygl2.h>
#include <networklink.h>

#include <QDebug>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <GL/glut.h>
//#define SHOW
#define DEBUG84
#define CORE
#define LEN 9000
#define LENGTH_OF_CORE 84
//#define SOCKET
int flag = 199;

void search_core_data(char *buff);
void search_core_data2(char *buff);
int continueflag = 0;
int rest_num_comma = 0;
char out[LEN*5];
int outposition = 0;
int core_data_state = 0;//initail
int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    qDebug() << "This is in the MAIN class,the flag is : "<< flag << endl;



#ifdef CORE
/*
     mygl2 w1;
     w1.resize(800,600);
     w1.show();
     w1.setWindowTitle("CORE STATE");
*/

     NetworkLink w5;
     w5.resize(640,480);
     w5.show();

     mygl2 w6;
     w6.resize(640,480);
     w6.show();



#endif


    return app.exec();

}

