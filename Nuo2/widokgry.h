#ifndef WIDOKGRY_H
#define WIDOKGRY_H

#include <QWidget>

namespace Ui {
class WidokGry;
}

class WidokGry : public QWidget
{
    Q_OBJECT

public:
    explicit WidokGry(class QTcpSocket *socketGry,QWidget *parent = nullptr);
    ~WidokGry();

private:
    Ui::WidokGry *ui;
    class QTcpSocket *socket;
};

#endif // WIDOKGRY_H
