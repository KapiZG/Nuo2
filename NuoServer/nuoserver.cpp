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
            //System rejestracji
            if(jsonObject->value("Typ").toString() == "R")
            {
                QString *nazwa = new QString(jsonObject->value("Nazwa").toString());
                QString *haslo = new QString(jsonObject->value("Haslo").toString());

                QSqlQuery *selectUser = new QSqlQuery("Select * from users where nazwa = \"" + *nazwa + "\" and haslo = \"" + *haslo + "\";");
                selectUser->exec();
                if(!selectUser->next())
                {
                    QSqlQuery *insertUser = new QSqlQuery();
                    if(insertUser->exec("Insert into users value (null, \"" + *nazwa + "\", \"" + *haslo + "\")"))
                    {
                        socket->write("t");
                        socket->flush();
                    }
                    else
                    {
                        socket->write("f");
                        socket->flush();
                    }
                }
                else
                {
                    qDebug() << "Taki użytkownik już istnieje";
                }
            }
            //System logowania
            else if(jsonObject->value("Typ").toString() == "L")
            {
                QString *nazwa = new QString(jsonObject->value("Nazwa").toString());
                QString *haslo = new QString(jsonObject->value("Haslo").toString());

                QSqlQuery *selectUser = new QSqlQuery("Select * from users where nazwa = \"" + *nazwa + "\" and haslo = \"" + *haslo + "\";");
                if(selectUser->next())
                {
                    QJsonDocument *jsUser = new QJsonDocument;
                    QJsonObject *jsoUser = new QJsonObject;
                    jsoUser->insert("ID", selectUser->value("id").toInt());
                    jsoUser->insert("Bool", "t");
                    jsUser->setObject(*jsoUser);
                    QByteArray *jsonByte = new QByteArray(jsUser->toJson(QJsonDocument::Compact));
                    socket->write(*jsonByte);
                    socket->flush();
                }
                else
                {
                    socket->write("f");
                    socket->flush();
                }
            }
            //System Tworzenia gry
            else if(jsonObject->value("Typ").toString() == "C")
            {
                QString *idGry = new QString(jsonObject->value("IDGry").toString());

                QSqlQuery *selectIDGry = new QSqlQuery("Select * from aktywnegry where idGry = \"" + *idGry + "\";");
                if(!selectIDGry->next())
                {
                    QSqlQuery *insertIDGry = new QSqlQuery();
                    if(insertIDGry->exec("Insert into aktywnegry value (\"" + *idGry + "\", default);"))
                    {
                        socket->write("t");
                        socket->flush();
                    }
                }
                else
                {
                    socket->write("f");
                    socket->flush();
                }
            }
        }
        else
        {
            qDebug() << "Nie jest to json file";
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
