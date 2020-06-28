#include"initialwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InitialWindow w;  //初始界面
    w.show();

    return a.exec();

   //

}
