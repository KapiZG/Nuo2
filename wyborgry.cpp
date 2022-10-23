#include "wyborgry.h"
#include "ui_wyborgry.h"

WyborGry::WyborGry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WyborGry)
{
    ui->setupUi(this);
}

WyborGry::~WyborGry()
{
    delete ui;
}
