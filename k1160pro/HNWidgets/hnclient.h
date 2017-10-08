/**************************************************
 * QTankClient
 * 在一个工程当中仅仅存在一个实例，通过调用HNClient实现。
 **************************************************/
#ifndef QTANKCLIENT_H
#define QTANKCLIENT_H

#include <QTcpSocket>
#include <QHostInfo>
#include "hnclientmessage.h"
#include <QTimer>
#include <QThread>
#include "HNDefine.h"

#define TANK_Q_TCP_SOCKET 0
#define TANK_Q_SOCKET 1
#define TANK_Q_THREAD 0
/**
 * @brief The HNClient class
 * 建立连接，管理登陆，
 * 提供云功能
 */
class HNClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit HNClient(QObject *parent = 0);
    virtual ~HNClient();

    void setServPort(quint32 p = 7079) { m_PORT = p; }
    void SendConnectMessage();
    int SendDisConnectFromHost();
    inline bool isLogined() { return m_isLogined; }

    QTCloudListDirResult& GetDirList() { return m_dirs; }
    QTCloudListFileResult& GetListedFiles() { return m_files; }
    QTCheckVersionResult& GetVersionResult() { return m_versionresult; }
signals:
    void signalConnecting();
    void signalConnectSucc();
    void signalConnectFail();//
    void signalLoginSucc();//
    void signalLoginFail();
    void signalLogoutSucc();
    void signalLogoutFail();//？
    void signalDisConnectSucc();//maybe
    void signalDisConnectFail();//？

    void signalCancelDown();
    void signalDownSucc();
    void signalListDirOK();
    void signalListFileOK();

    void signalCancelUpload();
    void signalUploadSucc();
    void signalCheckVersionResult();
public slots:
    //服务器需要解析收到的命令，而此处不需要，所以客户端和服务器代码分开编写。
    void sendHeatBeatMessage();
    void sendLoginMessage();
    void sendLogoutMessage();
    void sendListDirectory(QString code = "");
    void sendAddDirectory();
    void sendModDirectory();
    void sendDelDirectory();
    void sendListFiles(QString code = "001");
    void sendDelFile(QString code, QString id);
    void sendListPubDirectory();
    void sendListPubFiles();
    /**
     * @brief sendDownDevFiles
     * @param path 文件下载下来保存的路径
     * @param id
     * @param local 文件下载下来保存的名字
     */
    void sendDownDevFiles(const QString& id, const QString& localfile);
    void sendDownPubFiles();
    void sendCancelDown();
    void sendUploadFile(const QString& code, const QString& cloudname, const QString& localfile);
    void sendCancelUpload();
    void sendCheckVersion();
    void sendCheckNewVersion();
    void sendDownUpgradeFile(const QString& id, const QString& localfile);
private:
    enum {
        E_LIANTONG,
        E_DIANXIN,
        E_DOMAIN,
        E_CONNMAX,
    };
    //TODO:如果文件传输影响到了UI线程，那么需要将QTcpSocket局部变量化
    //阻塞UI不必考虑此处
    //非阻塞UI，UI却工作很慢，考虑此处。
    //QTcpSocket* m_sock;
    quint8 eConType;
    quint32 m_UID;
    qint8 m_heartCount;
    quint32 m_PORT;
    QTimer* timer;
    quint8 m_work;
    bool m_isLogined;
    void saveConType();
    void readConType();
    void connectToSingelHost();
    //TODO:public for debug
    template <typename T>
    void sendMessage(quint16 cmd, const T &t)
    {
        HNClientMessage qMsg;
        qMsg.setUid(m_UID);
        qMsg.setCmd(cmd);
        QByteArray d;
        QTankData::pack(d, cmd, t);
        qMsg.setData(d);
        qMsg.translate();
        pline() << qMsg;
        QByteArray b;
        HNClientParser::pack(b, qMsg);
        write(b);
        /*
        qint64 bb = bytesToWrite();
        bool cc = waitForBytesWritten();
        qint64 dd = bytesToWrite();
        pline() << cc << bb << dd;
        */
    }
    QTCloudUploadFile m_uploadfile;
    QTCloudUploadFileData m_uploadfiledata;
    QTCloudListDirResult m_dirs;
    QTCloudListFileResult m_files;
    QTCloudListPubDirResult m_pubdirs;
    QTCloudListPubFileResult m_pubfiles;
    QTCloudDownDevFileResult m_downfileresult;
    QTCloudDownFileData m_downfiledata;
    QTCheckVersionResult m_versionresult;
signals:
    void signalSendData();
    void signalDownData();
    void signalUpdateProgress(int value);
private slots:
    void domainHostFound();
    void socketStateChanged(QAbstractSocket::SocketState);
    void socketErrorOccured(QAbstractSocket::SocketError);
    void socketConnected();
    void socketDisconnect();
    void updateProgress(qint64);
private slots:
    void sendUploadFileData();
    void sendDownFileData();
    void sendDownFileSuccess();
    void readyReadData();
    void dispatchRecvedMessage(QByteArray& blockOnNet);
    void recvLoginResultMessage(HNClientMessage&);
    void recvHeatBeatResultMessage(HNClientMessage&);
    void recvConnPoolFullMessage(HNClientMessage&){}
    void recvListDirResultMessage(HNClientMessage&);
    void recvAddDirResultMessage(HNClientMessage&){}
    void recvDelDirResultMessage(HNClientMessage&){}
    void recvModDirResultMessage(HNClientMessage&){}
    void recvListFilesResultMessage(HNClientMessage&);
    void recvListPubDirResultMessage(HNClientMessage&);
    void recvListPubFilesResultMessage(HNClientMessage&);
    void recvDownFileResultMessage(HNClientMessage&);
    void recvDownFileDataResultMessage(HNClientMessage&);
    void recvUploadFileResult(HNClientMessage&);
    void recvUploadFileDataResult(HNClientMessage&);
    void recvUploadFileSuccess(HNClientMessage&);
    void recvCheckVersionResult(HNClientMessage&);
};

HNClient *HNClientInstance(QObject *parent = 0);
HNClient *HNUpgradeClientInstance(QObject *parent = 0);


#endif // QTANKCLIENT_H
