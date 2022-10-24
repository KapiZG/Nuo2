#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class QTcpSocket;

class NuoServer : public QTcpServer
{
public:
    NuoServer(QObject *parent);

public slots:
    void newConnection();

private:
    class QTcpServer *mojaServer;
};

#endif // SERVER_H
