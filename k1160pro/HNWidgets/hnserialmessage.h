#ifndef QTANKSERIALMESSAGE_H
#define QTANKSERIALMESSAGE_H

#include <QDebug>

#define _SERIAL_HEAD            0xAA55
#define _SERIAL_TAIL            0xCC33

#define _SERIAL_HAND            0x0001
#define _SERIAL_HANDACK         0x8001
#define _SERIAL_CLOSE           0x0002
#define _SERIAL_CLOSEACK        0x8002
#define _SERIAL_WRITEDEVNO      0x0003
#define _SERIAL_WRITEDEVNOACK   0x8003
#define _SERIAL_READDEVNO       0x0004
#define _SERIAL_READDEVNOACK    0x8004
#define _SERIAL_WRITEPASS       0x0005
#define _SERIAL_WRITEPASSACK    0x8005
#define _SERIAL_READPASS        0x0006
#define _SERIAL_READPASSACK     0x8006
#define _SERIAL_EXCEPTIONACK    0x800F

class HNSerialMessage : public QObject
{
    Q_OBJECT
public:
    explicit HNSerialMessage(QObject *parent = 0);

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
    void pack(QByteArray& netData) const;

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

QDebug operator<< (QDebug dbg, const HNSerialMessage &c);

class QTankHandupAck : public HNSerialMessage
{
    Q_OBJECT
public:
    explicit QTankHandupAck(QObject *parent = 0) : HNSerialMessage(parent){}

    void pack(QByteArray& l);
};

class QTankCloseAck : public HNSerialMessage
{
    Q_OBJECT
public:
    explicit QTankCloseAck(QObject *parent = 0) : HNSerialMessage(parent){}

    void pack(QByteArray &l);
};

class QTankWriteSerialNoAck : public HNSerialMessage
{
    Q_OBJECT
public:
    explicit QTankWriteSerialNoAck(QObject *parent = 0) : HNSerialMessage(parent){}

    void pack(QByteArray& l);
};

class QTankReadSerialNoAck : public HNSerialMessage
{
    Q_OBJECT
public:
    explicit QTankReadSerialNoAck(QObject *parent = 0) : HNSerialMessage(parent){}

    void pack(QByteArray& l);
};

class QTankWritePassAck : public HNSerialMessage
{
    Q_OBJECT
public:
    explicit QTankWritePassAck(QObject *parent = 0) : HNSerialMessage(parent){}

    void pack(QByteArray &l);
};


class QTankReadPassAck : public HNSerialMessage
{
    Q_OBJECT
public:
    explicit QTankReadPassAck(QObject *parent = 0) : HNSerialMessage(parent){}

    void pack(QByteArray &l);
};


class QTankExceptionAck : public HNSerialMessage
{
    Q_OBJECT
public:
    explicit QTankExceptionAck(QObject *parent = 0) : HNSerialMessage(parent){}

    void pack(QByteArray &l);
};

#endif // QTANKSERIALMESSAGE_H
