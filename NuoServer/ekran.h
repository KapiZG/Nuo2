#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Ekran; }
QT_END_NAMESPACE

class Ekran : public QWidget
{
    Q_OBJECT

public:
    Ekran(QWidget *parent = nullptr);
    ~Ekran();
    void polaczenieZBaza();

private:
    Ui::Ekran *ui;
    class NuoServer *mojaServer;
};
#endif // EKRAN_H
