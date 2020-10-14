#include "pagination.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pagination w;
    w.show();
    return a.exec();
}
