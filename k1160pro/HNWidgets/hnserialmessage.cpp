#include "hnserialmessage.h"
#include "HNDefine.h"

HNSerialMessage::HNSerialMessage(QObject *parent) :
    QObject(parent)
{
    m_Head = _SERIAL_HEAD;
    m_Size = m_Cmd = m_Sum = 0;
    m_Data.clear();;
    m_Tail = _SERIAL_TAIL;
}

void HNSerialMessage::translate()
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

QDebug operator<<(QDebug dbg, const HNSerialMessage &c)
{
#if 1
    dbg.nospace() << "{" << hex << c.head() << "|" <<
                     hex << c.size() << "@@" << dec << c.size() << "|" <<
                     hex << c.cmd() << "|" <<
                     c.data().data() << "@" << dec << c.data().size() << "|" <<
                     hex << c.sum() << "|" <<
                     hex << c.tail() << "}";
#elif 0
    QByteArray a;
    c.pack(a);
    dbg.nospace() << a.toHex().toUpper();
#else
    QByteArray head;
    head << c.head();
    QByteArray size;
    size << c.size();
    QByteArray cmd;
    cmd << c.cmd();
    QByteArray data;
    data << c.data();
    QByteArray sum;
    sum << c.sum();
    QByteArray tail;
    tail << c.tail();
    dbg.nospace() << "{" << head.toHex().toUpper() << " " <<
                     size.toHex().toUpper() << "@" <<
                     dec << c.size() << " " <<
                     cmd.toHex().toUpper() << " " <<
                     data.toHex().toUpper() << "@" <<
                     dec << data.size() << " " <<
                     sum.toHex().toUpper() << " " <<
                     tail.toHex().toUpper() << "}";
#endif
    return dbg.space();
}

quint16 HNSerialMessage::parseBlockSize(const QByteArray &netData)
{
    QByteArray l = netData.left(4);
    quint16 b0 = 0, b1 = 0;
    l >> b0 >> b1;
    return b1;
}

void HNSerialMessage::parse(const QByteArray &netData)
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

void HNSerialMessage::pack(QByteArray &netData) const
{
    netData << head();
    netData << size();
    netData << cmd();
    netData << data();
    netData << sum();
    netData << tail();
}


void QTankWritePassAck::pack(QByteArray &l)
{
    setCmd(_SERIAL_WRITEPASSACK);
    translate();
    HNSerialMessage::pack(l);
}


void QTankWriteSerialNoAck::pack(QByteArray &l)
{
    setCmd(_SERIAL_WRITEDEVNOACK);
    translate();
    HNSerialMessage::pack(l);
}


void QTankHandupAck::pack(QByteArray &l)
{
    setCmd(_SERIAL_HANDACK);
    translate();
    HNSerialMessage::pack(l);
}


void QTankCloseAck::pack(QByteArray &l)
{
    setCmd(_SERIAL_CLOSEACK);
    translate();
    HNSerialMessage::pack(l);
}


void QTankReadSerialNoAck::pack(QByteArray &l)
{
    setCmd(_SERIAL_READDEVNOACK);
    translate();
    HNSerialMessage::pack(l);
}


void QTankReadPassAck::pack(QByteArray &l)
{
    setCmd(_SERIAL_READPASSACK);
    translate();
    HNSerialMessage::pack(l);
}


void QTankExceptionAck::pack(QByteArray &l)
{
    setCmd(_SERIAL_EXCEPTIONACK);
    translate();
    HNSerialMessage::pack(l);
}
