#include "nuoserver.h"
#include <QTextStream>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QSqlDatabase>
#include <QtSql>

NuoServer::NuoServer(QObject *parent)
    : QTcpServer(parent)
{
    //Utworzenie servera
    mojaServer = new QTcpServer(this);
    connect(mojaServer, &QTcpServer::newConnection, this, &NuoServer::newConnection);

    //Połączenie z bazą danych
    bazaDanych.setHostName("127.0.0.130");
    bazaDanych.setUserName("root");
    bazaDanych.setPassword("");
    bazaDanych.setDatabaseName("db_nuo");

    //Sprawdzenie czy wszystko działa
    if(mojaServer->listen(QHostAddress::Any, 6969) && bazaDanych.open()){
        qDebug()<<"Działa byczku";
    } else {
        qDebug() << "ERROR";
    }



}

//Test Połączenia
void NuoServer::newConnection()
{
    QTcpSocket *socket = mojaServer->nextPendingConnection();

    socket->waitForReadyRead(200);
    qDebug()<<"Test: "<<socket->readAll();

    socket->write("Połączono z Bazą");
    socket->waitForBytesWritten(200);

    connect(socket, &QIODevice::readyRead, this, [socket]()
    {
        QByteArray *wiadomosc = new QByteArray(socket->readAll());
        QJsonDocument *json = new QJsonDocument(QJsonDocument::fromJson(*wiadomosc));

        if(!json->isEmpty())
        {
            QJsonObject *jsonObject = new QJsonObject(json->object());

            qDebug() << *jsonObject;
            if(jsonObject->value("Typ").toString() == "R")
            {
                QString *nazwa = new QString(jsonObject->value("Nazwa").toString());
                QString *haslo = new QString(jsonObject->value("Haslo").toString());

                QSqlQuery *insertUser = new QSqlQuery("Insert into users value (null, \"" + *nazwa + "\", \"" + *haslo + "\");");
                if(insertUser->exec())
                {
                    socket->write("t");
                }
                else
                {
                    socket->write("f");
                }
            }
        }
    });


//    Rozłączenie z serverem
    connect(socket, &QAbstractSocket::disconnected, this, [socket]()
    {
        qDebug()<<"Rozłączono";
        socket->close();
    });
}

void NuoServer::odczytajWiadomosc()
{

}
