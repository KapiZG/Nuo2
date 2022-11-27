#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QSqlDatabase>
#include <vector>

class QTcpSocket;

class NuoServer : public QTcpServer
{
public:
    NuoServer(QObject *parent);

public slots:
    void newConnection();
    void newGraConnection();
    void odczytajWiadomosc();

private:
    class QTcpServer *mojaServer;
    class QTcpServer *serverGry;
    QSqlDatabase bazaDanych = QSqlDatabase::addDatabase("QMYSQL");
    std::vector<class Gra> aktywneGry;
};

#endif // SERVER_H
