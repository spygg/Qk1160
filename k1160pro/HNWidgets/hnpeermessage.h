#ifndef QTANKPEERMESSAGE_H
#define QTANKPEERMESSAGE_H

#include <QDebug>

#define _PEER_HEAD 0XAA55
#define _PEER_TAIL 0XCC33

#define _PEER_CONC51       0x0000
#define _PEER_CONC51ACK    0x0001
#define _PEER_CMDNACK      0x0002
#define _PEER_HEAT         0x0003
#define _PEER_PAUSE        0x0004
#define _PEER_STOP         0x0005

#define _HEAT_STANDARD      0x02
#define _HEAT_RAMP          0x01
#define _HEAT_PRESS         0x03
#define _HEAT_EXTRACT       0x01

class HNPeerMessage : public QObject
{
    Q_OBJECT
public:
    explicit HNPeerMessage(QObject *parent = 0);

    const quint16& head() const { return m_Head; }
    void setHead(quint16 head) { m_Head = head; }
    const quint16& size() const { return m_Size; }
    void setSize(quint16 size) { m_Size = size; }
    //user
    const quint16& cmd() const { return m_Cmd; }
    void setCmd(quint16 cmd) { m_Cmd = cmd; }
    //user
    const QByteArray& data() const { return m_Data; }
    void setData(QByteArray& data) { m_Data = data; }
    const quint16& sum() const { return m_Sum; }
    void setSum(quint16 sum) { m_Sum = sum; }
    const quint16& tail() const { return m_Tail; }
    void setTail(quint16 tail) { m_Tail = tail; }

    static quint16 parseBlockSize(const QByteArray &netData);
    void parse(const QByteArray &netData);
    void translate();
    void pack(QByteArray& netData);

signals:

public slots:

private:
    quint16 m_Head;
    quint16 m_Size;
    quint16 m_Cmd;
    QByteArray m_Data;
    quint16 m_Sum;
    quint16 m_Tail;
};

QDebug operator<< (QDebug dbg, const HNPeerMessage &c);

class QTankConnC51Struct : public HNPeerMessage
{
    Q_OBJECT
public:
    explicit QTankConnC51Struct(QObject *parent = 0) : HNPeerMessage(parent){}

    void pack(QByteArray& l);
};

class QTankHeatStandardStruct : public HNPeerMessage
{
    Q_OBJECT
public:
    explicit QTankHeatStandardStruct(QObject *parent = 0) : HNPeerMessage(parent){}

    void setStage(quint8 arg) {uStage = arg;}
    void setVessel(quint8 arg) {uVessel = arg;}
    void setTempture(quint16 arg) {wTempture = arg;}
    void setHold(quint16 arg) {wHold = arg;}
    void pack(QByteArray& l);
private:
    quint8 uStage;
    quint8 uVessel;
    quint16 wTempture;
    quint16 wHold;
};

class QTankHeatPressStruct : public HNPeerMessage
{
    Q_OBJECT
public:
    explicit QTankHeatPressStruct(QObject *parent = 0) : HNPeerMessage(parent){}

    void setStage(quint8 arg) {uStage = arg;}
    void setVessel(quint8 arg) {uVessel = arg;}
    void setPress(quint16 arg) {wPress = arg;}
    void pack(QByteArray& l);
private:
    quint8 uStage;
    quint8 uVessel;
    quint16 wPress;
};

class QTankHeatRAMPStruct : public HNPeerMessage
{
    Q_OBJECT
public:
    explicit QTankHeatRAMPStruct(QObject *parent = 0) : HNPeerMessage(parent){}

    quint8 stage() { return uStage; }
    quint8 vessel() { return uVessel; }
    quint8 ramp() { return wRamp; }
    quint8 press() { return wPress; }
    quint8 tempture() { return wTempture; }
    quint8 hold() { return wHold; }

    void setStage(quint8 arg) {uStage = arg;}
    void setVessel(quint8 arg) {uVessel = arg;}
    void setRamp(quint16 arg) {wRamp = arg;}
    void setPress(quint16 arg) {wPress = arg;}
    void setTempture(quint16 arg) {wTempture = arg;}
    void setHold(quint16 arg) {wHold = arg;}
    void pack(QByteArray& l);
private:
    quint8 uStage;
    quint8 uVessel;
    quint16 wRamp;
    quint16 wPress;
    quint16 wTempture;
    quint16 wHold;
};

class QTankHeatExtractStruct : public HNPeerMessage
{
    Q_OBJECT
public:
    explicit QTankHeatExtractStruct(QObject *parent = 0) : HNPeerMessage(parent){}

    void setStage(quint8 arg) {uStage = arg;}
    void setTempture(quint16 arg) {wTempture = arg;}
    void setHold(quint16 arg) {wHold = arg;}
    void pack(QByteArray& l);
private:
    quint8 uStage;
    quint16 wTempture;
    quint16 wHold;
};

class QTankPauseStruct : public HNPeerMessage
{
    Q_OBJECT
public:
    explicit QTankPauseStruct(QObject *parent = 0) : HNPeerMessage(parent){}

    void pack(QByteArray& l);
};

class QTankStopStruct : public HNPeerMessage
{
    Q_OBJECT
public:
    explicit QTankStopStruct(QObject *parent = 0) : HNPeerMessage(parent){}

    void pack(QByteArray& l);
};

class QTankCmd2C51Ack : public HNPeerMessage
{
    Q_OBJECT
public:
    explicit QTankCmd2C51Ack(QObject *parent = 0) : HNPeerMessage(parent){}

    void parse(const QByteArray& l);
};


#endif // QTANKPEERMESSAGE_H
