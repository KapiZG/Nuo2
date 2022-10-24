#include "ekran.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ekran w;
    w.show();
    return a.exec();
}
