#include "hnclient.h"
#include "HNDefine.h"
#include "hnclientmessage.h"
#include "hnlinux.h"

#include "hnversion.h"

#define MAX_HEARDBEAT 10

HNClient::HNClient(QObject *parent) :
    QTcpSocket(parent)
{
    connect(this, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStateChanged(QAbstractSocket::SocketState)) );
    // connected
    connect(this, SIGNAL(connected()), this, SLOT(socketConnected()) );
    // disconnected
    connect(this, SIGNAL(disconnected()), this, SLOT(socketDisconnect()) );
    // domain
    connect(this, SIGNAL(hostFound()), this, SLOT(domainHostFound()));
    // error
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketErrorOccured(QAbstractSocket::SocketError)) );

    connect(this, SIGNAL(readyRead()), this, SLOT(readyReadData()));

    connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(updateProgress(qint64)));

    //心情很好，但是给自己带来麻烦顾虑，也不能给系统节约多少什么资源。
    //, Qt::QueuedConnection);

    connect(this, SIGNAL(signalSendData()), this, SLOT(sendUploadFileData()), Qt::QueuedConnection);
    connect(this, SIGNAL(signalDownData()), this, SLOT(sendDownFileData()), Qt::QueuedConnection);
    connect(this, SIGNAL(signalDownSucc()), this, SLOT(sendDownFileSuccess()), Qt::QueuedConnection );

    setSocketOption(QAbstractSocket::LowDelayOption, 0);
    setSocketOption(QAbstractSocket::KeepAliveOption, 0);
    setReadBufferSize(_TCP_RECVBUFF_SIZE);

    m_isLogined = false;
    m_heartCount = 0;
    m_UID = 0;
    m_PORT = 0;
    //启动连接
    eConType = E_LIANTONG;
    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(sendHeatBeatMessage()));
}

HNClient::~HNClient()
{
}

void HNClient::SendConnectMessage()
{
    pline() << isValid() << isOpen() << state();

    if(!isValid() || (isValid() && !isOpen()))
    {
        readConType();
        connectToSingelHost();
        return;
    }

    if        (state() == HostLookupState ||
             state() == ConnectingState)
    {
        emit signalConnecting();
        return;
    }

    if(state() == ConnectedState)
        emit signalConnectSucc();

        return;

}


int HNClient::SendDisConnectFromHost()
{
    pline() << isValid() << isOpen() << state();

    if(isValid() || isOpen() )
    {
        sendLogoutMessage();
        pline();
        disconnectFromHost();
        pline();
        shutdown(this->socketDescriptor(), SHUT_RDWR);
        close();
        pline();
        //此处引起卡顿
        waitForDisconnected();
    }

    emit signalLogoutSucc();
    emit signalDisConnectSucc();

    return true;
}

void HNClient::domainHostFound()
{
    pline();
}

/**
 * @brief HNClient::socketStateChanged
 * @param eSocketState
 * 状态函数
 */
void HNClient::socketStateChanged(QAbstractSocket::SocketState eSocketState)
{
    pline() << eSocketState;
    switch(eSocketState)
    {
    case QAbstractSocket::HostLookupState:
    case QAbstractSocket::ConnectingState:
        break;
    case QAbstractSocket::ConnectedState:
        break;
    case QAbstractSocket::ClosingState:
        break;
    case QAbstractSocket::UnconnectedState:
        saveConType();
        break;
    default:
        break;
    }
}

/**
 * @brief HNClient::socketErrorOccured
 * @param e
 * 状态函数
 */
void HNClient::socketErrorOccured(QAbstractSocket::SocketError e)
{
    //在错误状态下重新连接其他热点，直到确定连接类型，写入配置文件
    pline() << e;
    switch(e)
    {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
    default:
        emit signalConnectFail();
        break;
    }
}

/**
 * @brief HNClient::socketConnected
 * 功能接口
 */
void HNClient::socketConnected()
{
    pline() << peerName() << peerAddress().toString() << peerPort();
    //这个步骤，socket重建，资源重新开始
    m_heartCount = 0;    
    //TODO:心跳检测重连会不会引发这条消息？
    //如果连接还未成功开始发送心跳包，
    //QNativeSocketEngine::write() was not called in QAbstractSocket::ConnectedState
    timer->start(30 * 1000);
    emit signalConnectSucc();
    //和PC的协议中，不登陆不能进行任何操作，所以此处登陆；
    sendLoginMessage();
}

/**
 * @brief HNClient::socketDisconnect
 * 功能接口
 */
void HNClient::socketDisconnect()
{
    pline();
    m_heartCount = MAX_HEARDBEAT + 1;
    timer->stop();
}

void HNClient::updateProgress(qint64 bytes)
{
    //pline() << bytes;
}

void HNClient::saveConType()
{
    QSettings setting;
    eConType = ( eConType + 1 ) % E_CONNMAX;
    setting.setValue("ConnType", eConType);
    setting.sync();
}

void HNClient::readConType()
{
    QSettings setting;
    eConType = setting.value("ConnType").toInt();
}

void HNClient::connectToSingelHost()
{
    switch(eConType)
    {
    case E_DIANXIN:
        connectToHost(QHostAddress("222.175.114.244"), m_PORT);
        break;
    case E_DOMAIN:
        connectToHost("www.hanonoo.com", m_PORT);
        break;
    case E_LIANTONG:
    default:
        connectToHost(QHostAddress("124.133.1.54"), m_PORT);
        break;
    }
    pline() << peerName() << m_PORT;
}

void HNClient::sendHeatBeatMessage()
{
    //断链判断 如果断链 TODO:
    if(m_heartCount > MAX_HEARDBEAT)
    {
#if 1
        //重连策略 30 * 2 s
        static int curp = 0;
        if(curp >= 2)
        {
            curp = 0;
            connectToSingelHost();
            return;
        }
        curp++;
#else
        //此处设置重连策略 30s 150s 300s 600s
        static int p[4] = {1, 5, 10, 20};
        static int curp = 0;
        static int curpos = 0;
        if(curp >= p[curpos])
        {
            curp = 0;
            curpos = (curpos + 1) % 4;
            connectToSingelHost();
            return;
        }
        curp++;
#endif
        return;
    }
    pline() << "HeartBeat Count:" << m_heartCount;
    m_heartCount++;
    HNClientMessage qMsg;
    qMsg.setUid(m_UID);
    qMsg.setCmd(_TCPCMD_HEART);
    qMsg.translate();
    pline() << qMsg;
    QByteArray b;
    HNClientParser::pack(b, qMsg);
    write(b);
    //waitForBytesWritten();
}

void HNClient::sendLoginMessage()
{
    //这个地方可能要改动，串口发过来的时字符串，不是hex
    QSettings set;
    QString name = set.value("Device/DeviceNo").toString();
    QString pwd = set.value("Device/Password").toString();

    m_isLogined = false;
    QTCloudLogin t;
    t.m_name = name;
    t.m_password = pwd;
    HNClientMessage qMsg;
    qMsg.setUid(m_UID);
    qMsg.setCmd(_TCPCMD_LOGIN);
    QByteArray d;
    QTankData::pack(d, _TCPCMD_LOGIN, t);
    qMsg.setData(d);
    qMsg.translate();
    pline() << qMsg;
    QByteArray b;
    HNClientParser::pack(b, qMsg);
    write(b);
}

void HNClient::sendLogoutMessage()
{
    m_isLogined = false;
    HNClientMessage qMsg;
    qMsg.setUid(m_UID);
    qMsg.setCmd(_TCPCMD_EXIT);
    qMsg.translate();
    pline() << qMsg;
    QByteArray b;
    HNClientParser::pack(b, qMsg);
    write(b);
}

void HNClient::sendListDirectory(QString code)
{
    QTCloudListDir t;
    t.m_code = code;
    quint16 _tcpcmd = _TCPCMD_SEARCHDIR;
    HNClientMessage qMsg;
    qMsg.setUid(m_UID);
    qMsg.setCmd(_tcpcmd);
    QByteArray d;
    QTankData::pack(d, _tcpcmd, t);
    qMsg.setData(d);
    qMsg.translate();
    pline() << qMsg;
    QByteArray b;
    HNClientParser::pack(b, qMsg);
    write(b);
}

void HNClient::sendAddDirectory()
{
    QTCloudAddDir t;
    t.m_upcode = "";
    t.m_code = "";
    t.m_name = "Method2";
    quint16 _tcpcmd = _TCPCMD_ADDDIR;
    sendMessage(_tcpcmd, t);
}

void HNClient::sendModDirectory()
{
    QTCloudModDirName t;
    t.m_upcode = "";
    t.m_code = "";
    t.m_name = "Method2";
    quint16 _tcpcmd = _TCPCMD_ALTERDIR;
    sendMessage(_tcpcmd, t);
}

void HNClient::sendDelDirectory()
{
    QTCloudDelDir t;
    t.m_upcode = "";
    t.m_code = "";
    t.m_name = "Method2";
    quint16 _tcpcmd = _TCPCMD_DELETEDIR;
    sendMessage(_tcpcmd, t);
}

void HNClient::sendListFiles(QString code)
{
    QTCloudListFile t;
    t.m_code = code;
    quint16 _tcpcmd = _TCPCMD_SEARCHFILE;
    sendMessage(_tcpcmd, t);
}

void HNClient::sendDelFile(QString code, QString id)
{
    QTCloudDelFile t;
    t.m_code = code;
    t.m_id = id;
    quint16 _tcpcmd = _TCPCMD_DELETEFILE;
    sendMessage(_tcpcmd, t);
    pline() << t.m_code << t.m_id;
}

void HNClient::sendListPubDirectory()
{
    QTCloudListPubDir t;
    t.m_code = "";
    quint16 _tcpcmd = _TCPCMD_SEARCHPUBLICDIR;
    sendMessage(_tcpcmd, t);
}

void HNClient::sendListPubFiles()
{
    QTCloudListPubFile t;
    t.m_code = "";
    quint16 _tcpcmd = _TCPCMD_SEARCHPUBLICFILE;
    sendMessage(_tcpcmd, t);
}

void HNClient::sendDownDevFiles(const QString& id, const QString& localfile)
{
    m_downfileresult.m_localfile = localfile;
    m_work = 1;
    QTCloudDownDevFile t;
    t.m_id = id;
    quint16 _tcpcmd = _TCPCMD_DOWNLOADFILE;
    sendMessage(_tcpcmd, t);
}

void HNClient::sendDownPubFiles()
{
    QTCloudDownPubFile t;
    _QTCloudListFileResult _result;
    foreach (_result, m_pubfiles.m_file) {
        break;
    }
    t.m_id = _result.m_id;
    quint16 _tcpcmd = _TCPCMD_DOWNLOADPUBFILE;
    sendMessage(_tcpcmd, t);
}

void HNClient::sendDownFileData()
{
    pline() << m_downfiledata.m_fileno << m_downfiledata.m_dno;
    quint16 _tcpcmd = _TCPCMD_COMFIREFILEINFO;
    sendMessage(_tcpcmd, m_downfiledata);
}

void HNClient::sendCancelDown()
{
    QTCloudCancelDownFile t;
    t.m_fileno = m_downfiledata.m_fileno;
    quint16 _tcpcmd = _TCPCMD_CANCELREVFILE;
    m_work = 0;
    emit signalCancelDown();;
    sendMessage(_tcpcmd, t);
}

void HNClient::sendDownFileSuccess()
{
    QTCloudDownFileSuccess t;
    t.m_fileno = m_downfiledata.m_fileno;
    quint16 _tcpcmd = _TCPCMD_DOWNFILEOK;
    sendMessage(_tcpcmd, t);
}

void HNClient::sendUploadFile(const QString& code, const QString& cloudname, const QString& localfile)
{
    m_uploadfile.m_code = code;
    m_uploadfile.m_name = cloudname;
    m_uploadfile.m_localfile = localfile;
    QFileInfo f(m_uploadfile.m_localfile);
    m_uploadfile.m_length = QString::number(f.size());
    m_uploadfile.m_overwrite = _TCP_RESULT_TRUE;
    quint16 _tcpcmd = _TCPCMD_SENDFILEINFO;
    HNClientMessage qMsg;
    qMsg.setUid(m_UID);
    qMsg.setCmd(_tcpcmd);
    QByteArray d;
    QTankData::pack(d, _tcpcmd, m_uploadfile);
    qMsg.setData(d);
    qMsg.translate();
    pline() << qMsg;
    QByteArray b;
    HNClientParser::pack(b, qMsg);
    write(b);
    //waitForBytesWritten(-1);
}

void HNClient::sendUploadFileData()
{
    m_uploadfiledata.m_addr = m_uploadfiledata.m_dno * _TCP_BLOCKDATA_SIZE;
    QFile f(m_uploadfile.m_localfile);
    f.open( QIODevice::ReadOnly );
    if(f.isOpen())
    {
        f.seek(m_uploadfiledata.m_addr);
        m_uploadfiledata.m_data = f.read(_TCP_BLOCKDATA_SIZE);
    }
    f.close();
    m_uploadfiledata.m_dlen = m_uploadfiledata.m_data.length();
    quint16 _tcpcmd = _TCPCMD_SENDFILEDATA;
    HNClientMessage qMsg;
    qMsg.setUid(m_UID);
    qMsg.setCmd(_tcpcmd);
    QByteArray d;
    QTankData::pack(d, _tcpcmd, m_uploadfiledata);
    qMsg.setData(d);
    qMsg.translate();
    pline() << qMsg;
    QByteArray b;
    HNClientParser::pack(b, qMsg);
    writeData(b.data(), b.length());
    //waitForBytesWritten();
    pline() << m_uploadfile.m_name << m_uploadfile.m_localfile << m_uploadfiledata.m_fileno << m_uploadfiledata.m_dno << m_uploadfiledata.m_addr << m_uploadfiledata.m_dlen;
}

void HNClient::sendCancelUpload()
{
    QTCloudCancelUploadFile t;
    t.m_fileno = m_uploadfiledata.m_fileno;
    quint16 _tcpcmd = _TCPCMD_CANCELSENDFILE;
    sendMessage(_tcpcmd, t);
    emit signalCancelUpload();
}

void HNClient::sendCheckVersion()
{
    QTCheckVersion t;
    t.m_softwareid = "0";
    t.m_devicecode = "0601";
    t.m_softwarecode = "211100";
    t.m_version = VER_FILEVERSION_STR;
    quint16 _tcpcmd = _TCPCMD_CHECKVERSION;
    sendMessage(_tcpcmd, t);
}

void HNClient::sendCheckNewVersion()
{
    QTCheckVersion t;
    t.m_softwareid = m_versionresult.m_NewSoftwareID;
    t.m_devicecode = "";
    t.m_softwarecode = "";
    t.m_version = VER_FILEVERSION_STR;
    quint16 _tcpcmd = _TCPCMD_CHECKVERSION;
    sendMessage(_tcpcmd, t);
}

void HNClient::sendDownUpgradeFile(const QString &id, const QString &localfile)
{
    m_downfileresult.m_localfile = localfile;
    m_work = 1;
    QTCloudDownDevFile t;
    t.m_id = id;
    quint16 _tcpcmd = _TCPCMD_DOWNUPGRADEFILE;
    sendMessage(_tcpcmd, t);
}

void HNClient::readyReadData()
{
    // queued conn and queued package;
    // direct conn and ???
    static QByteArray m_blockOnNet;
    m_blockOnNet += readAll();
    //qint64 aaa = bytesAvailable();
    //pline() << aaa;
    //TODO:假设具备判断已经接受完全的装备
    do{
        quint16 nBlockLen = HNClientParser::parseBlockSize(m_blockOnNet);

        pline() << m_blockOnNet.size() << "..." << nBlockLen;

        if(m_blockOnNet.length() < nBlockLen)
        {
            return;
        }
        else if(m_blockOnNet.length() > nBlockLen)
        {
            //还没有处理完毕，数据已经接收到，异步信号处理出现这种异常
            pline() << "Stick package" << m_blockOnNet.length() << nBlockLen;
            QByteArray netData;
            netData.resize(nBlockLen);
            m_blockOnNet >> netData;
            //TODO:如果异步调用这个函数绘出现什么问题？正常情况，同步获取数据，异步处理；检测异步获取并且处理会有什么状况
            dispatchRecvedMessage(netData);
            continue;
        }
        dispatchRecvedMessage(m_blockOnNet);
        break;
    }while(1);

    m_blockOnNet.clear();
}

void HNClient::dispatchRecvedMessage(QByteArray &blockOnNet)
{
    HNClientMessage qMsg;
    HNClientParser::parse(qMsg, blockOnNet);
    pline() << qMsg;
    switch(qMsg.cmd())
    {
    case _TCPCMD_LOGINRESUALT:
        recvLoginResultMessage(qMsg);
        break;
    case _TCPCMD_HEARTBEATRESP:
        recvHeatBeatResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVEDIRLIST:
        recvListDirResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVEADDRESUALT:
        recvAddDirResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVEALTERRESUALT:
        recvModDirResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVEDELETERESUALT:
        recvDelDirResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVEFILELIST:
        recvListFilesResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVEPUBLICDIRLIST:
        recvListPubDirResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVEPUBLICFILELIST:
        recvListPubFilesResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVEFILEINFO:
        recvDownFileResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVEFILEDATA:
        recvDownFileDataResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVECOMFIREFILEINFO:
        recvUploadFileResult(qMsg);
        break;
    case _TCPCMD_RECEIVECOMFIREFILEDATA:
        recvUploadFileDataResult(qMsg);
        break;
    case _TCPCMD_RECEIVECOMFIREFILE:
        recvUploadFileSuccess(qMsg);
        break;
    case _TCPCMD_CHECKVERSIONRSP:
        recvCheckVersionResult(qMsg);
        break;
    default:
        pline() << "receive unknown command:" << hex << qMsg.cmd();
        break;
    }
}

void HNClient::recvLoginResultMessage(HNClientMessage& qMsg)
{
    m_UID = qMsg.uid();
    QTCloudLoginResult qtLoginResult;
    QTankData::parse(qtLoginResult, qMsg.cmd(), qMsg.data());
    switch(qtLoginResult.m_result)
    {
    case 0x00:
        {
            pline() << "Login success id:" << hex << m_UID;
            m_isLogined = true;
            emit signalLoginSucc();
        }
        return;
    case 0x10:
        pline() << "Other user logined";
        break;
    case 0x11:
        pline() << "User unexisted";
        break;
    case 0x12:
        pline() << "Password error upflowed";
        break;
    case 0x23:
    case 0x22:
    case 0x21:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
        pline() << "Password error" << hex << qtLoginResult.m_result;
        break;
    case 0xFF:
    default:
        pline() << "unknown error" << qtLoginResult.m_result;
        break;
    }

    emit signalLoginFail();
}

void HNClient::recvHeatBeatResultMessage(HNClientMessage &)
{
    m_heartCount = 0;
    pline() << "HeartBeat Callback";
}

void HNClient::recvListDirResultMessage(HNClientMessage &qMsg)
{
    m_dirs.m_upcode = "";
    m_dirs.m_dir.clear();
    QTankData::parse(m_dirs, qMsg.cmd(), qMsg.data());
    pline() << m_dirs.m_upcode;
    _QTCloudListDirResult _result;
    foreach (_result, m_dirs.m_dir) {
        //这里保存到model中
        pline() << _result.m_id << _result.m_code << _result.m_name;
    }
    emit signalListDirOK();
}

void HNClient::recvListFilesResultMessage(HNClientMessage &qMsg)
{
    m_files.m_code = "";
    m_files.m_file.clear();
    QTankData::parse(m_files, qMsg.cmd(), qMsg.data());
    pline() << m_files.m_code;
    _QTCloudListFileResult _result;
    foreach (_result, m_files.m_file) {
        //这里保存到model中
        pline() << _result.m_id << _result.m_name << _result.m_size << _result.m_date;
    }
    emit signalListFileOK();
}

void HNClient::recvListPubDirResultMessage(HNClientMessage &qMsg)
{
    m_pubdirs.m_upcode = "";
    m_pubdirs.m_dir.clear();
    QTankData::parse(m_pubdirs, qMsg.cmd(), qMsg.data());
    pline() << m_pubdirs.m_upcode;
    _QTCloudListDirResult _result;
    foreach (_result, m_pubdirs.m_dir) {
        //这里保存到model中
        pline() << _result.m_id << _result.m_code << _result.m_name;
    }
}

void HNClient::recvListPubFilesResultMessage(HNClientMessage &qMsg)
{
    m_pubfiles.m_code = "";
    m_pubfiles.m_file.clear();
    QTankData::parse(m_pubfiles, qMsg.cmd(), qMsg.data());
    pline() << m_pubfiles.m_code;
    _QTCloudListFileResult _result;
    foreach (_result, m_pubfiles.m_file) {
        //这里保存到model中
        pline() << _result.m_id << _result.m_name << _result.m_size << _result.m_date;
    }
}

void HNClient::recvDownFileResultMessage(HNClientMessage &qMsg)
{
    QTankData::parse(m_downfileresult, qMsg.cmd(), qMsg.data());
    pline() << m_downfileresult.m_fileno << m_downfileresult.m_name << m_downfileresult.m_length;
    m_downfiledata.m_fileno = m_downfileresult.m_fileno.toInt();

    QString tmpFile = m_downfileresult.m_localfile;

#ifdef __MIPS_LINUX__
    system(QString("touch %1").arg(tmpFile).toAscii().data());
#endif

    QFile f(tmpFile);
    f.open( QIODevice::WriteOnly | QIODevice::Truncate );
    pline() << tmpFile << f.size();
    f.close();
    emit signalUpdateProgress(0);
    emit signalDownData();
}

void HNClient::recvDownFileDataResultMessage(HNClientMessage &qMsg)
{
    if(0 == m_work)
        return;
    QTCloudDownFileDataResult result;
    QTankData::parse(result, qMsg.cmd(), qMsg.data());
    pline() << result.m_fileno << result.m_dno << result.m_addr <<
               result.m_dlen;// << m_downfiledata.m_data;
    int nFileSize = 0;
    QString tmpFile = m_downfileresult.m_localfile;
    QFile f(tmpFile);
    f.open( QIODevice::WriteOnly | QIODevice::Append );
    f.write(result.m_data);
    nFileSize = f.size();
    f.close();
    pline() << nFileSize << m_downfileresult.m_length;
    int percent = 0;
    if(nFileSize > 0)
        percent = 100 * nFileSize / m_downfileresult.m_length.toInt();
    emit signalUpdateProgress(percent);
    pline() << percent;
    if(nFileSize < m_downfileresult.m_length.toInt())
    {
        m_downfiledata.m_dno++;
        emit signalDownData();
    }
    else
    {
        m_downfiledata.m_dno = 0;
        emit signalDownSucc();
    }
}

void HNClient::recvUploadFileResult(HNClientMessage &qMsg)
{
    QTCloudUploadFileResult result;
    QTankData::parse(result, qMsg.cmd(), qMsg.data());
    pline() << result.m_fileno << result.m_state;
    perr(result.m_state, 0x00) << "ok to send file data";
    perr(result.m_state, 0x01) << "unsupport file type";
    perr(result.m_state, 0x02) << "file too length";
    perr(result.m_state, 0x03) << "too much file";
    perr(result.m_state, 0x04) << "files too long";
    perr(result.m_state, 0x14) << "no much storage";

    if(result.m_state == 0x00)
    {
        m_uploadfiledata.m_fileno = result.m_fileno;
        m_uploadfiledata.m_dno = 0;
        //使用Timer确认不是网络速率的原因。
        emit signalUpdateProgress(0);
        emit signalSendData();
    }
}

void HNClient::recvUploadFileDataResult(HNClientMessage &qMsg)
{
    QTCloudUploadFileDataResult result;

    QTankData::parse(result, qMsg.cmd(), qMsg.data());
    pline() << result.m_fileno << result.m_dno << result.m_dno * _TCP_BLOCKDATA_SIZE << m_uploadfile.m_length.toInt();

    //不需要发空串
    m_uploadfiledata.m_dno = result.m_dno + 1;
    int percent = 0;
    if(m_uploadfile.m_length.toInt() > 0)
        percent = 100 * m_uploadfiledata.m_dno * _TCP_BLOCKDATA_SIZE /
                m_uploadfile.m_length.toInt();

    if(m_uploadfiledata.m_dno * _TCP_BLOCKDATA_SIZE < m_uploadfile.m_length.toInt())
    {
        emit signalSendData();
        emit signalUpdateProgress(percent);
    }
}

void HNClient::recvUploadFileSuccess(HNClientMessage &qMsg)
{
    QTCloudUploadFileSuccess result;
    QTankData::parse(result, qMsg.cmd(), qMsg.data());
    pline() << result.m_fileno << m_uploadfiledata.m_dno << m_uploadfiledata.m_dno * _TCP_BLOCKDATA_SIZE << m_uploadfile.m_length.toInt() << "upload success";
    emit signalUpdateProgress(100);
    emit signalUploadSucc();
}

void HNClient::recvCheckVersionResult(HNClientMessage &qMsg)
{
    QTankData::parse(m_versionresult, qMsg.cmd(), qMsg.data());
    emit signalCheckVersionResult();
}

static HNClient* gSingleClient = NULL;

HNClient *HNClientInstance(QObject* parent)
{
    if(!gSingleClient)
    {
        gSingleClient = new HNClient(parent);
        gSingleClient->setServPort(7079);
    }
    return gSingleClient;
}

HNClient *HNUpgradeClientInstance(QObject *parent)
{
    static HNClient* sClient = NULL;
    if(!sClient)
    {
        sClient = new HNClient(parent);
        sClient->setServPort(8089);
    }
    return sClient;
}
