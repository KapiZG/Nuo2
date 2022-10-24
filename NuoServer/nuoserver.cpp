#include "nuoserver.h"
#include <QTextStream>
#include <QTcpSocket>


NuoServer::NuoServer(QObject *parent)
    : QTcpServer(parent)
{
    mojaServer = new QTcpServer(this);

    connect(mojaServer, &QTcpServer::newConnection, this, &NuoServer::newConnection);

    if(!mojaServer->listen(QHostAddress::Any, 6969)){
        qDebug()<<"Error";
    } else {
        qDebug()<<"Działa byczku";
    }
}

//Test Połączenia
void NuoServer::newConnection()
{
    QTcpSocket *socket = mojaServer->nextPendingConnection();

    socket->waitForReadyRead(200);
    qDebug()<<"Test: "<<socket->readAll();

    socket->write("Odpowiedz z servera");
    socket->waitForBytesWritten(200);

    socket->close();
}
