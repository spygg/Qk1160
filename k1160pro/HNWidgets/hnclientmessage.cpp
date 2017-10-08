#include "hnclientmessage.h"
#include "HNDefine.h"
#include <QBuffer>
#include "HNDefine.h"


HNClientMessage::HNClientMessage(QObject *parent) :
    QObject(parent)
{
    m_Head = _TCPCMD_TAGHEAD;
    m_Size = m_Cmd = m_Uid = m_Sum = 0;
    m_Data.clear();;
    m_Tail = _TCPCMD_TAGTAIL;
}

void HNClientMessage::translate()
{
    m_Size = m_Data.length() + 0x10;
    QByteArray qbaVerify;
    qbaVerify << m_Size << m_Cmd << m_Uid << m_Data;
    m_Sum = 0;
    // 校验码等错误 会导致服务器不回复消息
    // 如果不添加quint8 0x0112+0x0088=0x009a 单字节到二字节进位的位置看不懂
    for(int i = 0; i < qbaVerify.length(); i++)
        m_Sum += quint8(qbaVerify.at(i));
    //real verify
    //m_Sum = qChecksum(qbaVerify.data(), qbaVerify.length());
}

QDebug operator<<(QDebug dbg, const HNClientMessage &c)
{
    dbg.nospace() << "{" << hex << c.head() << "|" <<
                     hex << c.size() << "=" << dec << c.size() << "|" <<
                     hex << c.cmd() << "|" <<
                     hex << c.uid() << "|" <<
                     c.data().data() << "@" << dec << c.data().size() << "|" <<
                     hex << c.sum() << "|" <<
                     hex << c.tail() << "}";
    return dbg.space();
}

quint16 HNClientParser::parseBlockSize(const QByteArray &netData)
{
    QByteArray l = netData.left(4);
    quint16 b0 = 0, b1 = 0;
    l >> b0 >> b1;
    return b1;
}

void HNClientParser::parse(HNClientMessage &getter, const QByteArray &netData)
{
    QByteArray l = netData;
    quint16 b0 = 0, b1 = 0, b2 = 0, b5 = 0;
    quint32 b3 = 0, b6 = 0;
    QByteArray b4;
    l >> b0 >> b1 >> b2 >> b3;
    b4.resize(b1-0x10);
    l >> b4 >> b5 >> b6;
    getter.setHead(b0);
    getter.setSize(b1);
    getter.setCmd(b2);
    getter.setUid(b3);
    getter.setData(b4);
    getter.setSum(b5);
    getter.setTail(b6);
}

void HNClientParser::pack(QByteArray &netData, const HNClientMessage &setter)
{
    netData << setter.head();
    netData << setter.size();
    netData << setter.cmd();
    netData << setter.uid();
    netData << setter.data();
    netData << setter.sum();
    netData << setter.tail();
}

#define _TCPCMD_DATALOGIN                "USERNAME=\"%1\"PASSWORD=\"%2\""
#define _TCPCMD_DATAADDDIR               "UPCODE=\"%1\"CODE=\"%2\"NAME=\"%3\""
#define _TCPCMD_DATAALTERDIR             "UPCODE=\"%1\"ID=\"%2\"NAME=\"%3\""
#define _TCPCMD_DATADELETEDIR            "UPCODE=\"%1\"ID=\"%2\""
#define _TCPCMD_DATADELETEFILE           "CODE=\"%1\"ID=\"%2\""
#define _TCPCMD_DATASENDFILEINFO         "CODE=\"%1\"NAME=\"%2\"OVERWRITE=\"%3\"LENGTH=\"%4\""

void QTankData::packLoginData(QByteArray &l, const QTCloudLogin &t)
{
    l = QString(_TCPCMD_DATALOGIN).arg(t.m_name).arg(t.m_password).toAscii();
}

void QTankData::parseLoginResultData(QTCloudLoginResult &t, const QByteArray &l)
{
    QByteArray _l = l;
    _l >> t.m_result;
}

void QTankData::packListDirData(QByteArray &l, const QTCloudListDir &t)
{
    l = t.m_code.toAscii();
}

void QTankData::parseListDirResultData(QTCloudListDirResult &r, const QByteArray &l)
{
    quint32 pos = 0;
    QByteArray b = l;
    QByteArray h;
    h = parseKeyWordInByteArray(b, _TCP_SECTION_UPCODE, pos);
    r.m_upcode = h;
    while(pos < b.length())
    {
        _QTCloudListDirResult _r;
        QByteArray __r;
        __r = parseKeyWordInByteArray(b, _TCP_SECTION_ID, pos);
        _r.m_id = __r;
        __r = parseKeyWordInByteArray(b, _TCP_SECTION_CODE, pos);
        _r.m_code = __r;
        __r = parseKeyWordInByteArray(b, _TCP_SECTION_NAME, pos);
        _r.m_name = __r;
        r.m_dir.push_back(_r);
    }
}

void QTankData::packAddDirData(QByteArray &l, const QTCloudAddDir &t)
{
    packKeyWordToByteArray(l, _TCP_SECTION_UPCODE, t.m_upcode);
    packKeyWordToByteArray(l, _TCP_SECTION_CODE, t.m_code);
    packKeyWordToByteArray(l, _TCP_SECTION_NAME, t.m_name);
}

void QTankData::parseAddDirResultData(QTCloudAddDirResult &t, const QByteArray &l)
{
    quint32 pos = 0;
    QByteArray b = l;
    t.m_upcode = parseKeyWordInByteArray(b, _TCP_SECTION_UPCODE, pos);
    t.m_result = parseKeyWordInByteArray(b, _TCP_SECTION_RESULE, pos);
}

void QTankData::packDelFileData(QByteArray &l, const QTCloudDelFile &t)
{
    packKeyWordToByteArray(l, _TCP_SECTION_CODE, t.m_code);
    packKeyWordToByteArray(l, _TCP_SECTION_ID, t.m_id);
}

void QTankData::parseListFileResultData(QTCloudListFileResult &r, const QByteArray &l)
{
    quint32 pos = 0;
    QByteArray b = l;
    QByteArray h;
    h = parseKeyWordInByteArray(b, _TCP_SECTION_CODE, pos);
    r.m_code = h;
    while(pos < b.length())
    {
        _QTCloudListFileResult _r;
        QByteArray __r;
        __r = parseKeyWordInByteArray(b, _TCP_SECTION_ID, pos);
        _r.m_id = __r;
        __r = parseKeyWordInByteArray(b, _TCP_SECTION_NAME, pos);
        _r.m_name = __r;
        __r = parseKeyWordInByteArray(b, _TCP_SECTION_SIZE, pos);
        _r.m_size = __r;
        __r = parseKeyWordInByteArray(b, _TCP_SECTION_DATE, pos);
        _r.m_date = __r;
        r.m_file.push_back(_r);
    }
}

void QTankData::packDownDevFileData(QByteArray &l, const QTCloudDownDevFile &t)
{
    l = t.m_id.toAscii();
}

void QTankData::parseDownDevFileResultData(QTCloudDownDevFileResult &t, const QByteArray &l)
{
    quint32 pos = 0;
    QByteArray b = l;
    t.m_fileno = parseKeyWordInByteArray(b, _TCP_SECTION_FILENO, pos);
    t.m_name = parseKeyWordInByteArray(b, _TCP_SECTION_NAME, pos);
    t.m_length = parseKeyWordInByteArray(b, _TCP_SECTION_LENGTH, pos);
}

void QTankData::packDownDevFileSuccessData(QByteArray &l, const QTCloudDownFileSuccess &t)
{
    l << t.m_fileno;
}

void QTankData::packDownDevFileDataData(QByteArray &l, const QTCloudDownFileData &t)
{
    l << t.m_fileno << t.m_dno;
}

void QTankData::parseDownDevFileDataResultData(QTCloudDownFileDataResult &t, const QByteArray &l)
{
    quint32 pos = 0;
    QByteArray b = l;
    b >> t.m_fileno >> t.m_dno >> t.m_addr >> t.m_dlen;
    t.m_data.resize(t.m_dlen);
    b >> t.m_data;
}

void QTankData::packUploadFileData(QByteArray &l, const QTCloudUploadFile &t)
{    
    //utf-8 - gbk
    QString _name = QTextCodec::codecForName("utf-8")->toUnicode(t.m_name.toAscii());
    QString name = QTextCodec::codecForName("gbk")->toUnicode(_name.toAscii());

    l = QString(_TCPCMD_DATASENDFILEINFO)
            .arg(t.m_code)
            .arg(name)
            .arg(t.m_overwrite)
            .arg(t.m_length)
            .toAscii();
}

void QTankData::parseUploadFileResultData(QTCloudUploadFileResult &t, const QByteArray &l)
{
    QByteArray b = l;
    b >> t.m_fileno >> t.m_state;
}

void QTankData::packUploadFileDataData(QByteArray &l, const QTCloudUploadFileData &t)
{
    l << t.m_fileno << t.m_dno << t.m_addr << t.m_dlen << t.m_data;
}

void QTankData::parseUploadFileDataResultData(QTCloudUploadFileDataResult &t, const QByteArray &l)
{
    QByteArray b = l;
    b >> t.m_fileno >> t.m_dno;
}

void QTankData::parseUploadFileSuccessData(QTCloudUploadFileSuccess &t, const QByteArray &l)
{
    QByteArray b = l;
    b >> t.m_fileno;
}

void QTankData::packCheckVersionData(QByteArray &l, const QTCheckVersion &t)
{
    packKeyWordToByteArray(l, _TCP_SECTION_SOFTWAREID, t.m_softwareid);
    packKeyWordToByteArray(l, _TCP_SECTION_DEVICECODE, t.m_devicecode);
    packKeyWordToByteArray(l, _TCP_SECTION_SOFTWARECODE, t.m_softwarecode);
    packKeyWordToByteArray(l, _TCP_SECTION_VERSION, t.m_version);
}

void QTankData::parseCheckVersionResultData(QTCheckVersionResult &t, const QByteArray &l)
{
    quint32 pos = 0;
    QByteArray b = l;
    t.m_softwareid = parseKeyWordInByteArray(b, _TCP_SECTION_SOFTWAREID, pos);
    t.m_devicecode = parseKeyWordInByteArray(b, _TCP_SECTION_DEVICECODE, pos);
    t.m_softwarecode = parseKeyWordInByteArray(b, _TCP_SECTION_SOFTWARECODE, pos);
    t.m_version = parseKeyWordInByteArray(b, _TCP_SECTION_VERSION, pos);
    t.m_NewSoftwareID = parseKeyWordInByteArray(b, _TCP_SECTION_NEWSOFTWAREID, pos);

    //和公共文件区域的一样，郑工服务器端按照
    QByteArray m_Explain = parseKeyWordInByteArray(b, _TCP_SECTION_EXPLAIN, pos);
    QTextCodec *Codec = QTextCodec::codecForName("gbk");
    t.m_Explain = Codec->toUnicode(m_Explain);

    t.m_ReleaseStatus = parseKeyWordInByteArray(b, _TCP_SECTION_RELEASESTAT, pos);
    t.m_ReleaseDate = parseKeyWordInByteArray(b, _TCP_SECTION_RELEASEDATE, pos);
    t.m_FileName = parseKeyWordInByteArray(b, _TCP_SECTION_FILENAME, pos);
    t.m_FileMD5 = parseKeyWordInByteArray(b, _TCP_SECTION_FILEMD5, pos);
    t.m_FileSize = parseKeyWordInByteArray(b, _TCP_SECTION_FILESIZE, pos);
}

QByteArray& QTankData::packKeyWordToByteArray(QByteArray &array, const QString& key, const QString &value)
{
    return array << key.toAscii() << "=\"" << value.toAscii() << "\"";
}

QByteArray QTankData::parseKeyWordInByteArray(const QByteArray &array, const QByteArray &section, quint32& pos)
{
    int index = pos, indexTemp = 0;

    index = array.indexOf(section, index);
    index = array.indexOf('\"', index);
    indexTemp = array.indexOf('\"', index+1);
    pos = indexTemp + 1;
    return array.mid(index + 1, (indexTemp - index-1));
}
