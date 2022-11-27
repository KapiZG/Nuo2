#include "knumer.h"
#include <QCoreApplication>
#include <iostream>

KNumer::KNumer()
{
    grafikaKarty = QCoreApplication::applicationDirPath();

    int numerKarty = rand() % 10;
    int numerKoloru = rand() % 5;
    QString *kolor = new QString();
    switch(numerKoloru)
    {
        case 1:
            *kolor = 'r';
            break;
        case 2:
            *kolor = 'g';
            break;
        case 3:
            *kolor = 'b';
            break;
        case 4:
            *kolor = 'y';
            break;
        default:
            *kolor = 'y';

    }

    idKarty = *kolor + QString::number(numerKarty);
    grafikaKarty += "/karty/" + idKarty + ".png";
    this->setPixmap(grafikaKarty);
    this->setScaledContents(true);
    qDebug() << grafikaKarty;
}
