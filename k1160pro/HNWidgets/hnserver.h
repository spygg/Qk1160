#ifndef QTANKSERVER_H
#define QTANKSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include "hnserialmessage.h"

class HNServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit HNServer(QObject *parent = 0);
    ~HNServer();

signals:
    // QTcpServer interface
protected:
    void incomingConnection(int handle);
};

class HNClientConnection : public QTcpSocket
{
    Q_OBJECT
public:
    explicit HNClientConnection(QObject *parent = 0);
    ~HNClientConnection();

signals:

public slots:
    void dispatchRecvedMessage(QByteArray &blockOnNet);
    void readyReadData();
};

HNServer *HNSingleServer(QObject* parent);

#endif // QTANKSERVER_H
