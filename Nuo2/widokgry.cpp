#include "widokgry.h"
#include "ui_widokgry.h"
#include <QTcpSocket>

WidokGry::WidokGry(QTcpSocket *socketGry, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidokGry)
{
    socket = socketGry;
    ui->setupUi(this);

}

WidokGry::~WidokGry()
{
    socket->close();
    delete ui;
}
