#include "wyborgry.h"
#include "gracz.h"
#include <QTcpSocket>
#include "ui_wyborgry.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>
#include "gra.h"

WyborGry::WyborGry(const Gracz *id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WyborGry)
{
    ui->setupUi(this);

    zalogowanyGracz = id;

    ui->DolaczID->setPlaceholderText("Wpisz ID gry");


    //Połączenie z bazą
    socket = new QTcpSocket();
    socket->connectToHost("localhost", 6969);
    if(socket->waitForConnected(10000))
    {
        socket->waitForReadyRead(300);
        qDebug() << socket->readAll();
    }
    else
    {
        QMessageBox::critical(this, "Error", socket->errorString());
    }

    connect(ui->StworzGre, &QPushButton::pressed, this, &WyborGry::tworzenieGry);


}

WyborGry::~WyborGry()
{
    delete ui;
}


void WyborGry::tworzenieGry()
{
    const char alfabet[] ="0123456789""ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    QString *idGry = new QString();
    for(int i = 0; i < 5; i++) {
        *idGry += alfabet[rand() % (sizeof(alfabet) - 1)];
    }

    do
    {
        QJsonObject *jsonObject = new QJsonObject();
        QJsonDocument *jsonDocument = new QJsonDocument();
        jsonObject->insert("Typ", "C");
        jsonObject->insert("IDGry", *idGry);
        jsonDocument->setObject(*jsonObject);
        QByteArray *jsonByte = new QByteArray(jsonDocument->toJson(QJsonDocument::Compact));

        socket->write(*jsonByte);
        socket->flush();
        socket->waitForReadyRead(100);
    }
    while(socket->readAll() == "t");

    Gra *nowaGra = new Gra(idGry, zalogowanyGracz);
    nowaGra->show();
}
