#ifndef KARTA_H
#define KARTA_H

#include <QObject>
#include <QMouseEvent>
#include <QEvent>
#include <QLabel>

class Karta : public QLabel
{
protected:
    QString grafikaKarty;
    QString idKarty;
};

#endif // KARTA_H
