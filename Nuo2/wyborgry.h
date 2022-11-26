#ifndef WYBORGRY_H
#define WYBORGRY_H

#include <QWidget>

namespace Ui {
class WyborGry;
}

class WyborGry : public QWidget
{
    Q_OBJECT

public:
    explicit WyborGry(const class Gracz *id, QWidget *parent = nullptr);
    ~WyborGry();



private:
    Ui::WyborGry *ui;
    class QTcpSocket *socket;
    const class Gracz *zalogowanyGracz;
    void tworzenieGry();
};

#endif // WYBORGRY_H
