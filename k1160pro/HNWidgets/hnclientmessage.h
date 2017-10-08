#ifndef QMESSAGE_H
#define QMESSAGE_H

#include "HNDefine.h"
#include "hngui-qt.h"

#define _TCPCMD_TAGHEAD                   0xAA55
#define _TCPCMD_TAGTAIL                   0xCC33C33C

#define _TCPCMD_HEART                     0x0010
#define _TCPCMD_REGISTER                  0x0101
#define _TCPCMD_LOGIN                     0x0102
#define _TCPCMD_EXIT                      0x0104
#define _TCPCMD_VERIFYCODE                0x0105
#define _TCPCMD_NEXTAREA                  0x1010
#define _TCPCMD_NEXTMACHINE               0x1011

#define _TCPCMD_SEARCHDIR                 0x0200
#define _TCPCMD_ADDDIR                    0x0201
#define _TCPCMD_ALTERDIR                  0x0202
#define _TCPCMD_DELETEDIR                 0x0203
#define _TCPCMD_SEARCHFILE                0x0204
#define _TCPCMD_DELETEFILE                0x0205
#define _TCPCMD_SEARCHPUBLICDIR           0x0210
#define _TCPCMD_SEARCHPUBLICFILE          0x0211

#define _TCPCMD_SENDFILEINFO              0x0321
#define _TCPCMD_SENDFILEDATA              0x0322
#define _TCPCMD_CANCELSENDFILE            0x0323

#define _TCPCMD_DOWNLOADFILE              0x0303
#define _TCPCMD_DOWNLOADPUBFILE           0x0304
#define _TCPCMD_COMFIREFILEINFO           0x0311
#define _TCPCMD_CANCELREVFILE             0x0312
#define _TCPCMD_DOWNFILEOK                0x0313

#define _TCPCMD_CHECKVERSION              0x0400
#define _TCPCMD_DOWNUPGRADEFILE           0x0411

#define _TCPCMD_HEARTBEATRESP             0x8010
#define _TCPCMD_RECEIVEVERIFYBMP          0x8105
#define _TCPCMD_REGISTERRESUALT           0x8101
#define _TCPCMD_LOGINRESUALT              0x8102

#define _TCPCMD_RECEIVEDIRLIST            0x8200
#define _TCPCMD_RECEIVEADDRESUALT         0x8201
#define _TCPCMD_RECEIVEALTERRESUALT       0x8202
#define _TCPCMD_RECEIVEDELETERESUALT      0x8203
#define _TCPCMD_RECEIVEFILELIST           0x8204
#define _TCPCMD_RECEIVEPUBLICDIRLIST      0x8210
#define _TCPCMD_RECEIVEPUBLICFILELIST     0x8211

#define _TCPCMD_RECEIVEFILEINFO           0x8311
#define _TCPCMD_RECEIVEFILEDATA           0x8312
#define _TCPCMD_RECEIVECOMFIREFILEINFO    0x8321
#define _TCPCMD_RECEIVECOMFIREFILEDATA    0x8322
#define _TCPCMD_RECEIVECOMFIREFILE        0x8323

#define _TCPCMD_CHECKVERSIONRSP           0x8400

#define _TCPCMD_RECEIVEDIRYES             0x4f4b
#define _TCPCMD_RECEIVEDIRNO
#define _TCP_BLOCKDATA_SIZE                    0x400
#define _TCP_RECVBUFF_SIZE                      0x800

#define _TCP_SECTION_UPCODE                    "UPCODE"
#define _TCP_SECTION_ID                        "ID"
#define _TCP_SECTION_CODE                      "CODE"
#define _TCP_SECTION_NAME                      "NAME"
#define _TCP_SECTION_SIZE                      "SIZE"
#define _TCP_SECTION_DATE                      "DATE"
#define _TCP_SECTION_FILENO                    "FILENO"
#define _TCP_SECTION_LENGTH                    "LENGTH"
#define _TCP_RESULT_OK                          "OK"
#define _TCP_RESULT_FAIL                        "FF"
#define _TCP_RESULT_TRUE                        "TRUE"
#define _TCP_RESULT_FALSE                       "FALSE"
#define _TCP_SECTION_USERNAME                  "USERNAME"
#define _TCP_SECTION_PASSWORD                  "PASSWORD"
#define _TCP_SECTION_RESULE                     "RESULT"
#define _TCP_SECTION_SOFTWAREID                     "SOFTWAREID"
#define _TCP_SECTION_DEVICECODE                     "INSTRUMENTCODE"
#define _TCP_SECTION_SOFTWARECODE                     "SOFTWARECODE"
#define _TCP_SECTION_VERSION                     "VERSION"
#define _TCP_SECTION_NEWSOFTWAREID                     "NEWSOFTWAREID"
#define _TCP_SECTION_EXPLAIN                     "EXPLAIN"
#define _TCP_SECTION_RELEASESTAT                     "RELEASESTATUS"
#define _TCP_SECTION_RELEASEDATE                     "RELEASEDATE"
#define _TCP_SECTION_FILENAME                     "FILENAME"
#define _TCP_SECTION_FILEMD5                     "FILEMD5"
#define _TCP_SECTION_FILESIZE                     "FILESIZE"

typedef struct tagTankEmpty
{

}QTCloudBase;

typedef struct tagTankLogin
{
    QString m_name;
    QString m_password;
}QTCloudLogin;

typedef struct tagTankLoginReuslt
{
    quint8 m_result;
}QTCloudLoginResult;

typedef struct tagQTCloudListDir
{
    QString m_code;
}QTCloudListDir, QTCloudListFile, QTCloudListPubDir, QTCloudListPubFile;

typedef struct tag_QTCloudListDirResult
{
    QString m_id;
    QString m_code;
    QString m_name;
}_QTCloudListDirResult;

typedef struct tagQTCloudListDirResult
{
    QList<_QTCloudListDirResult> m_dir;
    QString m_upcode;
}QTCloudListDirResult, QTCloudListPubDirResult;

typedef struct tagTankAddDir
{
    QString m_upcode;
    QString m_code;
    QString m_name;
}QTCloudAddDir, QTCloudModDirName, QTCloudDelDir;

typedef struct tagQTCloudDelFile
{
    QString m_code;
    QString m_id;
}QTCloudDelFile;

typedef struct tagQTCloudAddDirResult
{
    QString m_upcode;
    QString m_result;
}QTCloudAddDirResult, QTCloudDelDirResult, QTCloudModDirNameResult;

typedef struct tag_QTCloudListFileResult
{
    QString m_id;
    QString m_name;
    QString m_size;
    QString m_date;
}_QTCloudListFileResult;

typedef struct tagQTCloudListFileResult
{
    QList<_QTCloudListFileResult> m_file;
    QString m_code;
}QTCloudListFileResult, QTCloudListPubFileResult;

typedef struct tagTankDownDevFile
{
    QString m_id;
}QTCloudDownDevFile, QTCloudDownPubFile;

typedef struct tagQTCloudDownFileData
{
    tagQTCloudDownFileData()
    {
        m_fileno = 0;
        m_dno = 0;
    }

    quint32 m_fileno;
    quint32 m_dno;
}QTCloudDownFileData, QTCloudUploadFileDataResult;

typedef struct tagQTCloudCancelDownFile
{
    quint32 m_fileno;
}QTCloudCancelDownFile, QTCloudDownFileSuccess, QTCloudCancelUploadFile, QTCloudUploadFileSuccess;

typedef struct tagQTCloudDownFileResult
{
    QString m_fileno;
    QString m_name;
    QString m_length;
    //local
    QString m_localfile;
}QTCloudDownDevFileResult, QTCloudDownPubFileResult;

typedef struct tagQTCloudDownFileDataResult
{
    tagQTCloudDownFileDataResult()
    {
        m_fileno = 0;
        m_dno = 0;
        m_addr = 0;
        m_dlen = 0;
        m_data.clear();
    }

    quint32 m_fileno;
    quint32 m_dno;
    quint32 m_addr;
    quint16 m_dlen;
    QByteArray m_data;
}QTCloudDownFileDataResult, QTCloudUploadFileData;

typedef struct tagTankUploadFile
{
    QString m_code;
    QString m_name;
    QString m_overwrite;
    QString m_length;
    //local
    QString m_localfile;
}QTCloudUploadFile;

typedef struct tagTankUploadFileResult
{
    tagTankUploadFileResult()
    {
        m_fileno = 0;
        m_state = 0;
    }

    quint32 m_fileno;
    quint8 m_state;
}QTCloudUploadFileResult;

typedef struct tagQTCheckVersion
{
    QString m_softwareid;
    QString m_devicecode;
    QString m_softwarecode;
    QString m_version;
}QTCheckVersion;

typedef struct tagQTCheckVersionResult
{
    QString m_softwareid;
    QString m_devicecode;
    QString m_softwarecode;
    QString m_version;
    QString m_NewSoftwareID;
    QString m_Explain;
    QString m_ReleaseStatus;
    QString m_ReleaseDate;
    QString m_FileName;
    QString m_FileMD5;
    QString m_FileSize;
}QTCheckVersionResult;

class HNClientMessage : public QObject
{
    Q_OBJECT
public:
    explicit HNClientMessage(QObject *parent = 0);

    const quint16& head() const { return m_Head; }
    void setHead(quint16 head) { m_Head = head; }
    const quint16& size() const { return m_Size; }
    void setSize(quint16 size) { m_Size = size; }
    const quint16& cmd() const { return m_Cmd; }
    void setCmd(quint16 cmd) { m_Cmd = cmd; }
    const quint32& uid() const { return m_Uid; }
    void setUid(quint32 uid) { m_Uid = uid; }
    const QByteArray& data() const { return m_Data; }
    void setData(QByteArray& data) { m_Data = data; }
    const quint16& sum() const { return m_Sum; }
    void setSum(quint16 sum) { m_Sum = sum; }
    const quint32& tail() const { return m_Tail; }
    void setTail(quint32 tail) { m_Tail = tail; }
    void translate();

signals:

public slots:

private:
    quint16 m_Head;
    quint16 m_Size;
    quint16 m_Cmd;
    quint32 m_Uid;
    QByteArray m_Data;
    quint16 m_Sum;
    quint32 m_Tail;
};

QDebug operator<< (QDebug dbg, const HNClientMessage &c);

class HNClientParser : public QObject
{
public:
    explicit HNClientParser(QObject *parent = 0) : QObject(parent) {}

    static quint16 parseBlockSize(const QByteArray &netData);
    static void parse(HNClientMessage& getter, const QByteArray &netData);
    static void pack(QByteArray& netData, const HNClientMessage& setter);

private:
};

class QTankData : public QObject
{
    Q_OBJECT
public:
    explicit QTankData(QObject *parent = 0) : QObject(parent) {}

    template <typename T>
    static void pack(QByteArray& l, quint16 cmd, const T& t)
    {
        switch(cmd)
        {
        case _TCPCMD_LOGIN:
            packLoginData(l, (QTCloudLogin&)t);
            break;
        case _TCPCMD_SEARCHDIR:
        case _TCPCMD_SEARCHFILE:
        case _TCPCMD_SEARCHPUBLICDIR:
        case _TCPCMD_SEARCHPUBLICFILE:
            packListDirData(l, (QTCloudListDir&)t);
            break;
        case _TCPCMD_ADDDIR:
        case _TCPCMD_ALTERDIR:
        case _TCPCMD_DELETEDIR:
            packAddDirData(l, (QTCloudAddDir&)t);
            break;
        case _TCPCMD_DELETEFILE:
            packDelFileData(l, (QTCloudDelFile&)t);
            break;
        case _TCPCMD_SENDFILEINFO:
            packUploadFileData(l, (QTCloudUploadFile&)t);
            break;
        case _TCPCMD_SENDFILEDATA:
            packUploadFileDataData(l, (QTCloudUploadFileData&)t);
            break;
        case _TCPCMD_CANCELSENDFILE:
        case _TCPCMD_CANCELREVFILE:
        case _TCPCMD_DOWNFILEOK:
            packDownDevFileSuccessData(l, (QTCloudDownFileSuccess&)t);
            break;
        case _TCPCMD_DOWNLOADFILE:
        case _TCPCMD_DOWNLOADPUBFILE:
        case _TCPCMD_DOWNUPGRADEFILE:
            packDownDevFileData(l, (QTCloudDownDevFile&)t);
            break;
        case _TCPCMD_COMFIREFILEINFO:
            packDownDevFileDataData(l, (QTCloudDownFileData&)t);
            break;
        case _TCPCMD_CHECKVERSION:
            packCheckVersionData(l, (QTCheckVersion&)t);
            break;
        default:
            pline() << "pack unknown data" << hex << cmd;
            break;
        }
    }

    template <typename T>
    static void parse(T& t, quint16 cmd, const QByteArray& l)
    {
        switch(cmd)
        {
        case _TCPCMD_LOGINRESUALT:
            parseLoginResultData((QTCloudLoginResult&)t, l);
            break;
        case _TCPCMD_RECEIVEDIRLIST:
        case _TCPCMD_RECEIVEPUBLICDIRLIST:
            parseListDirResultData((QTCloudListDirResult&)t, l);
            break;
        case _TCPCMD_RECEIVEADDRESUALT:
        case _TCPCMD_RECEIVEALTERRESUALT:
        case _TCPCMD_RECEIVEDELETERESUALT:
            parseAddDirResultData((QTCloudAddDirResult&)t, l);
            break;
        case _TCPCMD_RECEIVEFILELIST:
        case _TCPCMD_RECEIVEPUBLICFILELIST:
            parseListFileResultData((QTCloudListFileResult&)t, l);
            break;
        case _TCPCMD_RECEIVEFILEINFO:
            parseDownDevFileResultData((QTCloudDownDevFileResult&)t, l);
            break;
        case _TCPCMD_RECEIVEFILEDATA:
            parseDownDevFileDataResultData((QTCloudDownFileDataResult&)t, l);
            break;
        case _TCPCMD_RECEIVECOMFIREFILEINFO:
            parseUploadFileResultData((QTCloudUploadFileResult&)t, l);
            break;
        case _TCPCMD_RECEIVECOMFIREFILEDATA:
            parseUploadFileDataResultData((QTCloudUploadFileDataResult&)t, l);
            break;
        case _TCPCMD_RECEIVECOMFIREFILE:
            parseUploadFileSuccessData((QTCloudUploadFileSuccess&)t, l);
            break;
        case _TCPCMD_CHECKVERSIONRSP:
            parseCheckVersionResultData((QTCheckVersionResult&)t, l);
            break;
        default:
            pline() << "parse unknown data" << hex << cmd;
            break;
        }
    }

    static void packLoginData(QByteArray& l, const QTCloudLogin& t);
    static void parseLoginResultData(QTCloudLoginResult& t, const QByteArray& l);

    static void packListDirData(QByteArray& l, const QTCloudListDir& t);
    static void parseListDirResultData(QTCloudListDirResult& r, const QByteArray& l);

    static void packAddDirData(QByteArray& l, const QTCloudAddDir& t);
    static void parseAddDirResultData(QTCloudAddDirResult& r, const QByteArray& l);

    static void packDelFileData(QByteArray& l, const QTCloudDelFile& t);

    static void parseListFileResultData(QTCloudListFileResult& r, const QByteArray& l);

    static void packDownDevFileData(QByteArray& l, const QTCloudDownDevFile& t);
    static void parseDownDevFileResultData(QTCloudDownDevFileResult& r, const QByteArray& l);

    static void packDownDevFileSuccessData(QByteArray& l, const QTCloudDownFileSuccess& t);

    static void packDownDevFileDataData(QByteArray& l, const QTCloudDownFileData& t);
    static void parseDownDevFileDataResultData(QTCloudDownFileDataResult& r, const QByteArray& l);

    static void packUploadFileData(QByteArray& l, const QTCloudUploadFile& t);
    static void parseUploadFileResultData(QTCloudUploadFileResult& r, const QByteArray& l);

    static void packUploadFileDataData(QByteArray& l, const QTCloudUploadFileData& t);
    static void parseUploadFileDataResultData(QTCloudUploadFileDataResult& t, const QByteArray& l);

    static void parseUploadFileSuccessData(QTCloudUploadFileSuccess& t, const QByteArray& l);

    static void packCheckVersionData(QByteArray& l, const QTCheckVersion& t);
    static void parseCheckVersionResultData(QTCheckVersionResult& t, const QByteArray& l);

signals:
public slots:
protected:
private:
    static QByteArray& packKeyWordToByteArray(QByteArray &array, const QString &key, const QString& value);
    static QByteArray  parseKeyWordInByteArray(const QByteArray& array, const QByteArray &section, quint32 &pos);
};

#endif // QMESSAGE_H
