#include "SelectareLunaFereastra.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SelectareLunaFereastra w(nullptr);
    w.show();

    return a.exec();
}
