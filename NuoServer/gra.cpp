#include "gra.h"
#include "C:\Users\User\Desktop\QTPliki\NuoProject\Nuo2\gracz.h"
#include <QWidget>
//#include "C:\Users\User\Desktop\QTPliki\NuoProject\Nuo2\karta.h"

Gra::Gra(const QString *id, Gracz *gracz)
    :IDGry(*id)
{
    gracze[0] = gracz;
}
