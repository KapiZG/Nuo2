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
    explicit WyborGry(QWidget *parent = nullptr);
    ~WyborGry();

private:
    Ui::WyborGry *ui;
};

#endif // WYBORGRY_H
