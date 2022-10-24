#include "ekran.h"
#include "./ui_ekran.h"
#include "nuoserver.h"
#include <QMessageBox>

Ekran::Ekran(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Ekran)
{
    ui->setupUi(this);
    mojaServer = new NuoServer(this);
}

Ekran::~Ekran()
{
    delete ui;
}

void Ekran::polaczenieZBaza()
{

}
