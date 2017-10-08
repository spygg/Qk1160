#ifndef QTANKSERIALPORT_H
#define QTANKSERIALPORT_H

#include <QtSerialPort/QSerialPort>
#include "hnserialmessage.h"
#include "HNDefine.h"

//生产部门使用这个串口操作机器
class HNSerialPort : public QSerialPort
{
    Q_OBJECT
public:
    explicit HNSerialPort(QObject *parent = 0);
    ~HNSerialPort();

signals:
    void sigSerialUnlock();

public slots:

private slots:
    void readyReadData();
    void dispatchRecvedMessage(QByteArray &blockOnNet);
    void recvHandup(const QByteArray& l);
    void sendHandupAck();
    void recvClose(const QByteArray& l);
    void sendCloseAck();
    void recvWriteSerialNumber(const QByteArray& l);
    void sendWriteSerialNumberAck();
    void recvReadSerial(const QByteArray& l);
    void sendReadSerialAck();
    void recvWritePassword(const QByteArray& l);
    void sendWritePasswordAck();
    void recvReadPassword(const QByteArray& l);
    void sendReadPasswordAck();
    void sendExceptionAck();
private:
};

HNSerialPort *HNSerialPortInstance(QObject* parent = 0);

#endif // QTANKSERIALPORT_H
