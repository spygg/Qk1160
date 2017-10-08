#include "hnserialport.h"


HNSerialPort::HNSerialPort(QObject *parent) :
    QSerialPort(parent)
{
#ifdef __MIPS_LINUX__
    QString portName("/dev/ttyS2");
#else
    QString portName("/dev/ttyS2");
#endif
    setPortName(portName);
    setBaudRate(QSerialPort::Baud115200);
    setDataBits(QSerialPort::Data8);
    setParity(QSerialPort::NoParity);
    setStopBits(QSerialPort::OneStop);
    setFlowControl(QSerialPort::NoFlowControl);


    if(open(QIODevice::ReadWrite)) //Open Port dev.
        pline() << QString("serial port %1 open success!").arg(portName);
    else
        pline() << QString("serial port %1 open failed! errcode =").arg(portName) << errorString();

    //connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(updateProgress(qint64)) );
    connect(this, SIGNAL(readyRead()), this, SLOT(readyReadData()) );
    //connect(this, SIGNAL(aboutToClose()), this, SLOT(aboutToClose()));
    //connect(this, SIGNAL(readChannelFinished()), this, SLOT(readChannelFinished()));
}

HNSerialPort::~HNSerialPort()
{
    close();
}

void HNSerialPort::readyReadData()
{
    static QByteArray m_blockOnNet;
    m_blockOnNet += readAll();

    do{
        quint16 nBlockLen = HNSerialMessage::parseBlockSize(m_blockOnNet);

        pline() << m_blockOnNet.size() << "..." << nBlockLen;


        if(nBlockLen < 0x0a || m_blockOnNet.length() < nBlockLen)
        {
            //数据不足
            pline() << nBlockLen << m_blockOnNet[0];
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

void HNSerialPort::dispatchRecvedMessage(QByteArray &blockOnNet)
{
    HNSerialMessage qMsg;
    qMsg.parse(blockOnNet);
    pline() << qMsg;
    switch(qMsg.cmd())
    {
    case _SERIAL_HAND:
        recvHandup(qMsg.data());
        break;
    case _SERIAL_CLOSE:
        recvClose(qMsg.data());
        break;
    case _SERIAL_WRITEDEVNO:
        recvWriteSerialNumber(qMsg.data());
        break;
    case _SERIAL_READDEVNO:
        recvReadSerial(qMsg.data());
        break;
    case _SERIAL_WRITEPASS:
        recvWritePassword(qMsg.data());
        break;
    case _SERIAL_READPASS:
        recvReadPassword(qMsg.data());
        break;
    default:
        pline() << "receive unknown command:" << hex << qMsg.cmd();
        break;
    }
}

void HNSerialPort::recvHandup(const QByteArray &l)
{
    sendHandupAck();
}

void HNSerialPort::sendHandupAck()
{
    //status c51 + local
    QByteArray s;
    s << quint8(0x00);
    QByteArray l;
    QTankHandupAck ack;
    ack.setData(s);
    ack.pack(l);
    write(l);
}

void HNSerialPort::recvClose(const QByteArray &l)
{
    sendCloseAck();
}

void HNSerialPort::sendCloseAck()
{
    QByteArray s;
    s << quint8(0x00);
    QByteArray l;
    QTankCloseAck ack;
    ack.setData(s);
    ack.pack(l);
    write(l);
}

void HNSerialPort::recvWriteSerialNumber(const QByteArray &l)
{
    QSettings set;
    set.setValue("Device/DeviceNo", l);
    set.sync();
    sendWriteSerialNumberAck();
    emit sigSerialUnlock();
}

void HNSerialPort::sendWriteSerialNumberAck()
{
    QTankWriteSerialNoAck ack;
    QSettings set;
    QByteArray sn = set.value("Device/DeviceNo").toByteArray();
    ack.setData(sn);
    QByteArray l;
    ack.pack(l);
    write(l);
}

void HNSerialPort::recvReadSerial(const QByteArray &l)
{
    sendReadSerialAck();
}

void HNSerialPort::sendReadSerialAck()
{
    QSettings set;
    QByteArray serial = set.value("Device/DeviceNo").toByteArray();
    QByteArray l;
    QTankReadSerialNoAck ack;

    if(serial.isEmpty())
        serial.fill('0', 18);

    ack.setData(serial);
    ack.pack(l);
    write(l);
}

void HNSerialPort::recvWritePassword(const QByteArray &l)
{
    QSettings set;
    set.setValue("Device/Password", l);
    set.sync();
    sendWritePasswordAck();
}

void HNSerialPort::sendWritePasswordAck()
{
    QTankWritePassAck ack;
    QSettings set;
    QByteArray sn = set.value("/Device/Password").toByteArray();
    ack.setData(sn);
    QByteArray l;
    ack.pack(l);
    write(l);
}

void HNSerialPort::  recvReadPassword(const QByteArray &l)
{
    sendReadPasswordAck();
}

void HNSerialPort::sendReadPasswordAck()
{
    QSettings set;
    QByteArray serial = set.value("Device/Password").toByteArray();
    QByteArray l;
    QTankReadPassAck ack;

    if(serial.isEmpty())
        serial.fill('0', 32);

    ack.setData(serial);
    ack.pack(l);
    write(l);
}

void HNSerialPort::sendExceptionAck()
{
    //机器运行出现异常自动通过这个串口上报
    QByteArray l;
    QTankExceptionAck ack;
    //ack.setData("");
    ack.pack(l);
    write(l);
}


HNSerialPort *HNSerialPortInstance(QObject *parent)
{
    static HNSerialPort* s2 = new HNSerialPort(parent);
    return s2;
}
