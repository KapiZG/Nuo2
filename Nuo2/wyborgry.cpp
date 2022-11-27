#include "wyborgry.h"
#include "gracz.h"
#include <QTcpSocket>
#include "ui_wyborgry.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>
#include "widokgry.h"

WyborGry::WyborGry(const Gracz *id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WyborGry)
{
    ui->setupUi(this);

    zalogowanyGracz = id;

    ui->DolaczID->setPlaceholderText("Wpisz ID gry");


    //Połączenie z bazą
    socket = new QTcpSocket();
    socket->connectToHost("89.72.109.193", 6969);
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
    connect(ui->Dolacz, &QPushButton::pressed, this, &WyborGry::dolaczDoGry);

}

WyborGry::~WyborGry()
{
    delete ui;
}


void WyborGry::tworzenieGry()
{
    const char alfabet[] ="0123456789""ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    QString *idGry = new QString();

    do
    {
        *idGry = NULL;
        for(int i = 0; i < 5; i++) {
            *idGry += alfabet[rand() % (sizeof(alfabet) - 1)];
        }
        QJsonObject *jsonObject = new QJsonObject();
        QJsonDocument *jsonDocument = new QJsonDocument();
        jsonObject->insert("Typ", "C");
        jsonObject->insert("IDGry", *idGry);
        jsonObject->insert("IDGracza", zalogowanyGracz->getIDGracza());
        jsonDocument->setObject(*jsonObject);
        QByteArray *jsonByte = new QByteArray(jsonDocument->toJson(QJsonDocument::Compact));

        socket->write(*jsonByte);
        socket->flush();
        if(socket->waitForReadyRead(100))
        {
            QTcpSocket *socketGry = new QTcpSocket(this);
            socketGry->connectToHost("89.72.109.193", 6970);
            if(socketGry->waitForConnected(1000))
            {
                WidokGry *widokGry = new WidokGry(socketGry);
                widokGry->show();
                this->close();
                break;
            }
            else
            {
                qDebug() << "jest Problem";
            }
        }
        else
        {
            qDebug() << "Idk w sumie";
        }
        qDebug() << *idGry;
    }
    while(socket->readAll() == "t");

//    Gra *nowaGra = new Gra(idGry, zalogowanyGracz);
//    nowaGra->show();
}


void WyborGry::dolaczDoGry()
{
    QString dolaczID = ui->DolaczID->text();

    QJsonObject *jsonObject = new QJsonObject();
    QJsonDocument *jsonDocument = new QJsonDocument();
    jsonObject->insert("Typ", "J");
    jsonObject->insert("ID", dolaczID);
    jsonDocument->setObject(*jsonObject);
    QByteArray *jsonByte = new QByteArray(jsonDocument->toJson(QJsonDocument::Compact));
    socket->write(*jsonByte);
    socket->flush();

    socket->waitForReadyRead(100);
    if(socket->readAll() == "t")
    {
        qDebug() << "dolaczono";
    }
    else
    {
        qDebug() << "Nie ma takiej gry";
    }


}
