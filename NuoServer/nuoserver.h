#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QSqlDatabase>

class QTcpSocket;

class NuoServer : public QTcpServer
{
public:
    NuoServer(QObject *parent);

public slots:
    void newConnection();
    void odczytajWiadomosc();

private:
    class QTcpServer *mojaServer;
    QSqlDatabase bazaDanych = QSqlDatabase::addDatabase("QMYSQL");
};

#endif // SERVER_H
