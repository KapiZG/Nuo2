#include "gra.h"
#include "gracz.h"

Gra::Gra(QString *id, const Gracz *gracz, QWidget *parent)
    : QWidget{parent},
      idGry(id)
{
    qDebug() << "Utworzono gre " << *idGry << gracz->idGracza;
}
