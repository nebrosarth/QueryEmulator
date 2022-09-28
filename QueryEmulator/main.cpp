#include "QueueEmulator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QueueEmulator w;
    w.show();
    return a.exec();
}
