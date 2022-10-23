#ifndef KARTA_H
#define KARTA_H

#include <QObject>
#include <QMouseEvent>
#include <QEvent>
#include <QLabel>

class Karta : public QLabel
{
    Q_OBJECT
    int numer;
    char kolor;
public:
    Karta();

signals:


};

#endif // KARTA_H
