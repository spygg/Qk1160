#include "hnpeermessage.h"
#include "HNDefine.h"

HNPeerMessage::HNPeerMessage(QObject *parent) :
    QObject(parent)
{
    m_Head = _PEER_HEAD;
    m_Size = m_Cmd = m_Sum = 0;
    m_Data.clear();;
    m_Tail = _PEER_TAIL;
}

void HNPeerMessage::translate()
{
    m_Size = m_Data.length() + 0x0A;
    QByteArray qbaVerify;
    qbaVerify << m_Size << m_Cmd << m_Data;
    m_Sum = 0;
    // 校验码等错误 会导致服务器不回复消息
    // 如果不添加quint8 0x0112+0x0088=0x009a 单字节到二字节进位的位置看不懂
    for(int i = 0; i < qbaVerify.length(); i++)
        m_Sum += quint8(qbaVerify.at(i));
}

QDebug operator<<(QDebug dbg, const HNPeerMessage &c)
{
    dbg.nospace() << "{" << hex << c.head() << "|" <<
                     hex << c.size() << "@@" << dec << c.size() << "|" <<
                     hex << c.cmd() << "|" <<
                     c.data().data() << "@" << dec << c.data().size() << "|" <<
                     hex << c.sum() << "|" <<
                     hex << c.tail() << "}";
    return dbg.space();
}

quint16 HNPeerMessage::parseBlockSize(const QByteArray &netData)
{
    QByteArray l = netData.left(4);
    quint16 b0 = 0, b1 = 0;
    l >> b0 >> b1;
    return b1;
}

void HNPeerMessage::parse(const QByteArray &netData)
{
    QByteArray l = netData;
    quint16 b0 = 0, b1 = 0, b2 = 0, b4 = 0, b5 = 0;
    QByteArray b3;
    l >> b0 >> b1 >> b2;
    b3.resize(b1-0x0A);
    l >> b3 >> b4 >> b5;
    setHead(b0);
    setSize(b1);
    setCmd(b2);
    setData(b3);
    setSum(b4);
    setTail(b5);
}

void HNPeerMessage::pack(QByteArray &netData)
{
    netData << head();
    netData << size();
    netData << cmd();
    netData << data();
    netData << sum();
    netData << tail();
}


void QTankConnC51Struct::pack(QByteArray &l)
{
    setCmd(_PEER_CONC51);
    translate();
    HNPeerMessage::pack(l);
}


void QTankCmd2C51Ack::parse(const QByteArray &l)
{
    HNPeerMessage::parse(l);
}


void QTankHeatStandardStruct::pack(QByteArray &l)
{
    //02	XX	XX	0000	0000	XXXX XXXX
    setCmd(_PEER_HEAT);
    QByteArray d;
    d << quint8(_HEAT_STANDARD) << uStage << uVessel <<
         quint16(0x0000) << quint16(0x0000) << wTempture << wHold;
    setData(d);
    translate();
    HNPeerMessage::pack(l);
}


void QTankPauseStruct::pack(QByteArray &l)
{
    setCmd(_PEER_PAUSE);
    translate();
    HNPeerMessage::pack(l);
}


void QTankStopStruct::pack(QByteArray &l)
{
    setCmd(_PEER_STOP);
    translate();
    HNPeerMessage::pack(l);
}


void QTankHeatPressStruct::pack(QByteArray &l)
{
    //03	XX	XX	0000	XXXX	0000 0000
    setCmd(_PEER_HEAT);
    QByteArray d;
    d << quint8(_HEAT_PRESS) << uStage << uVessel <<
         quint16(0x0000) << wPress << quint16(0x0000) << quint16(0x0000);
    setData(d);
    translate();
    HNPeerMessage::pack(l);
}


void QTankHeatRAMPStruct::pack(QByteArray &l)
{
    //01	XX	XX	XXXX	XXXX	XXXX XXXX
    setCmd(_PEER_HEAT);
    QByteArray d;
    d << quint8(_HEAT_RAMP) << uStage << uVessel <<
         wRamp << wPress << wTempture  << wHold;
    setData(d);
    translate();
    HNPeerMessage::pack(l);
}


void QTankHeatExtractStruct::pack(QByteArray &l)
{
    //04	XX	00	0000	0000	XXXX XXXX
    setCmd(_PEER_HEAT);
    QByteArray d;
    d << quint8(_HEAT_EXTRACT) << uStage << quint8(0x00) <<
         quint16(0x0000) << quint16(0x0000) << wTempture << wHold;
    setData(d);
    translate();
    HNPeerMessage::pack(l);
}
