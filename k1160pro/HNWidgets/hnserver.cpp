#include "hnserver.h"
#include "HNDefine.h"


HNServer::HNServer(QObject *parent) :
    QTcpServer(parent)
{
    listen(QHostAddress::Any, 8000);
}

HNServer::~HNServer()
{
    close();
}

void HNServer::incomingConnection(int handle)
{
    HNClientConnection* clientSocket = new HNClientConnection(this);
    clientSocket->setSocketDescriptor(handle);
}

HNClientConnection::HNClientConnection(QObject *parent) :
    QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readyReadData()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}

HNClientConnection::~HNClientConnection()
{

}

void HNClientConnection::dispatchRecvedMessage(QByteArray &blockOnNet)
{
    HNSerialMessage qMsg;
    qMsg.parse(blockOnNet);
    pline() << qMsg;
}

void HNClientConnection::readyReadData()
{
    static QByteArray m_blockOnNet;
    m_blockOnNet += readAll();

    do{
        quint16 nBlockLen = HNSerialMessage::parseBlockSize(m_blockOnNet);

        pline() << m_blockOnNet.size() << "..." << nBlockLen;

        if(m_blockOnNet.length() < nBlockLen)
        {
            return;
        }
        else if(m_blockOnNet.length() > nBlockLen)
        {
            pline() << "Stick package" << m_blockOnNet.length() << nBlockLen;
            QByteArray netData;
            netData.resize(nBlockLen);
            m_blockOnNet >> netData;
            dispatchRecvedMessage(netData);
            continue;
        }
        dispatchRecvedMessage(m_blockOnNet);
        break;
    }while(1);

    m_blockOnNet.clear();
}


HNServer *HNSingleServer(QObject *parent)
{
    static HNServer* s = new HNServer(parent);
    return s;
}

