#ifndef NETCONTROL_H
#define NETCONTROL_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include "simplenetwork.h"
#include "NetDataCode.h"

class DirList{
public:
    DirList(QString strUPCode, QString strID, QString strCode, QString strName);
public:
    QString m_strUPCode;
    QString m_strID;
    QString m_strCode;
    QString m_strName;
};
class FileList{
public:
    FileList(QString strCode, QString strID, QString strName, QString strSize, QString strDate);
public:
    QString m_strCode;
    QString m_strID;
    QString m_strName;
    QString m_strSize;
    QString m_strDate;
};

class DownFileList{
public:
    DownFileList(QString m_strFileNO, QString m_strName, QString m_strSize);
public:
    QString m_strFileNO;
    QString m_strName;
    QString m_strSize;
};
class NetControl : public QObject
{
    Q_OBJECT
public:
    explicit NetControl(QObject *parent = 0);
    ~NetControl();
    void SetAddrOfHost(QString strHostAddr);
    QString GetAddrOfHost();
    void SetPortOfHost(qint32 iPort);
    qint32 GetPortOfHost();
    bool ConnectToServer();
    void CloseConection();
    void PackAndSendData(QByteArray pDataArry, NETCONTROLCOMMAND Command);
    QVector<FileList *>  ReturnFileList();
    QVector<DirList *>  ReturnDirList();
    QVector<DownFileList *> ReturnDownFileList();
    QByteArray GetDNOAndAddress(int iNum);
    QByteArray GetDataLen(int iLen);

    QByteArray  m_CommandFileID;
    bool        m_bUserLogin;
private:
    void SetCommandHead();
    void SetCommandSize(QByteArray pDataArry);
    void SetCommandCmd(NETCONTROLCOMMAND Command);
    void SetCommandUserID();
    void SetCommandData(QByteArray pDataArry);
    void SetVerifyCode();
    void SetCommandTail();
    void AnalysisProtocol(QByteArray &pArry);
    void GetVerifyCodeBmp(QByteArray &pArry);
    void GetUserID(QByteArray &pArry);
    void GetDirList(QByteArray &pArry);
    void GetFileList(QByteArray &pArry);
    void GetDirYESNOResualt(QByteArray &pArry);
    void GetFileInfoResualt(QByteArray &pArry);
    void GetFileIDataResualt(QByteArray &pArry);
    void GetFileIComfire(QByteArray &pArry);
    void GetFileInfo(QByteArray &pArry);
    void GetFileData(QByteArray &pArry);
private:
    bool        m_bFlag;

    int         m_iMaxSize;
    SimpleNetwork   *m_pSimpleNetWork;
    QString     m_strAddrOfHost;
    qint32      m_iPortOfHost;
    QByteArray  m_CommandHead;
    QByteArray  m_CommandSize;
    QByteArray  m_CommandCmd;
    QByteArray  m_CommandUserID;
    QByteArray  m_CommandTempUserID;
//    QByteArray  m_CommandFileID;
    QByteArray  m_CommandData;
    QByteArray  m_CommandVerifyCode;
    QByteArray  m_CommandTail;
    QByteArray  m_ReadBytes;
    QVector<DirList *> m_VectorDirList;
    QVector<FileList *> m_VectorFileList;
    QVector<DownFileList *> m_VectorDownFileList;
signals:
    void emitVerifyCodeBmp(QByteArray);
    void emitTest();
    void emitDirYESNO(bool);
    void emitStartSendData();
    void emitSearchFile();
    void emitDataDNO();
    void emitStartDownFileData();
    //void emitStartSendFileData();
    void emitSendData(QByteArray, int);
public slots:
    //
    void ReceiveBytes();

};

#endif // NETCONTROL_H
