#include "jazminegui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JazmineGui w;
    w.show();

    return a.exec();
}
