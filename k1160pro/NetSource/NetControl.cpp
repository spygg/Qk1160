#include "NetControl.h"
#include <QImage>
#include <QPainter>

DirList::DirList(QString strUPCode, QString strID, QString strCode, QString strName)
{
    m_strUPCode = strUPCode;
    m_strID = strID;
    m_strCode = strCode;
    m_strName = strName;
}

FileList::FileList(QString strCode, QString strID, QString strName, QString strSize, QString strDate)
{
    m_strCode = strCode;
    m_strID = strID;
    m_strName = strName;
    m_strSize = strSize;
    m_strDate = strDate;
}

DownFileList::DownFileList(QString strFileNO, QString strName, QString strSize)
{
    m_strFileNO = strFileNO;
    m_strName = strName;
    m_strSize = strSize;
}

NetControl::NetControl(QObject *parent) :
    QObject(parent),
    //m_pTcpSocket(NULL),
    m_pSimpleNetWork(NULL),
    m_strAddrOfHost(""),
    m_iPortOfHost(NETDATAPORTISZERO),
    m_bFlag(true),
    m_bUserLogin(false),
    m_iMaxSize(0)
{

    if(NULL == m_pSimpleNetWork)
        m_pSimpleNetWork = new SimpleNetwork(NULL, this);

    m_CommandTempUserID.clear();

    connect(this, SIGNAL(emitVerifyCodeBmp(QByteArray)),
            this->parent(), SLOT(DrawVerifycodeBmp(QByteArray)));
    connect(this, SIGNAL(emitSendData(QByteArray, int)),
            this->parent(), SLOT(writeFile(QByteArray, int)));
    connect(this, SIGNAL(emitDirYESNO(bool)),
            this->parent(), SLOT(ReveiveDirYESNO(bool)));
    connect(this, SIGNAL(emitTest()),
            this->parent(), SLOT(RefreshTreeView()));
    connect(this, SIGNAL(emitStartSendData()),
            this->parent(), SLOT(StartSendFile()));
    connect(this, SIGNAL(emitSearchFile()),
            this->parent(), SLOT(SearchFile()));
    connect(this, SIGNAL(emitStartDownFileData()),
            this->parent(), SLOT(RequestData()));
    connect(this, SIGNAL(emitDataDNO()),
                    this->parent(), SLOT(StartSendFileDataDNO()));

}

NetControl::~NetControl()
{
    if(NULL != m_pSimpleNetWork)
    {
        CloseConection();
        qDebug() << "this 0";
        delete m_pSimpleNetWork;
    }
}

void NetControl::SetAddrOfHost(QString strHostAddr)
{
    m_strAddrOfHost = strHostAddr;
}

QString NetControl::GetAddrOfHost()
{
    return m_strAddrOfHost;
}

void NetControl::SetPortOfHost(qint32 iPort)
{
    m_iPortOfHost = iPort;
}

qint32 NetControl::GetPortOfHost()
{
    return m_iPortOfHost;
}

bool NetControl::ConnectToServer()
{
    if(m_strAddrOfHost.isEmpty())
        return false;
    qDebug() << "m_strAddrOfHost";
    if(NETDATAPORTISZERO == m_iPortOfHost)
        return false;
    qDebug() << "m_iPortOfHost";
    return m_pSimpleNetWork->connectToServer(m_strAddrOfHost, m_iPortOfHost);
}

void NetControl::CloseConection()
{
    return m_pSimpleNetWork->closeConection();
}

void NetControl::PackAndSendData(QByteArray pDataArry, NETCONTROLCOMMAND Command)
{
    m_CommandHead.clear();
    m_CommandSize.clear();
    m_CommandCmd.clear();
    m_CommandUserID.clear();
    m_CommandData.clear();
    m_CommandVerifyCode.clear();
    m_CommandTail.clear();

    SetCommandHead();
    SetCommandTail();
    SetCommandSize(pDataArry);
    SetCommandCmd(Command);
    SetCommandUserID();
    SetCommandData(pDataArry);
    SetVerifyCode();


    pDataArry.clear();
    pDataArry.append(m_CommandHead);
    pDataArry.append(m_CommandSize);
    pDataArry.append(m_CommandCmd);
    pDataArry.append(m_CommandUserID);
    pDataArry.append(m_CommandData);
    pDataArry.append(m_CommandVerifyCode);
    pDataArry.append(m_CommandTail);

    if(NULL != m_pSimpleNetWork)
       //m_pSimpleNetWork->TcpWrite(pDataArry);
       m_pSimpleNetWork->transmitData(0, pDataArry);
}


void NetControl::SetCommandHead()
{
    m_CommandHead.append(0xAA);
    m_CommandHead.append(0X55);
}

void NetControl::SetCommandSize(QByteArray pDataArry)
{
    if(pDataArry.isEmpty())
    {
        m_CommandSize.append((char)0x00);
        m_CommandSize.append(0x10);
    }
    else
    {
        qint32 iLen = pDataArry.size();
        iLen += 16;
        if(iLen > 255)
        {
            m_CommandSize.append(iLen >> 8);
            m_CommandSize.append(iLen & 0x00FF);
        }
        else
        {
            m_CommandSize.append((char)0x00);
            m_CommandSize.append(iLen);
        }

    }
}

void NetControl::SetCommandCmd(NETCONTROLCOMMAND Command)
{
    switch(Command)
    {
        case COMMANDREGISTER:
            m_CommandCmd.append(NETCOMMANDREGISTER >> 8);
            m_CommandCmd.append(NETCOMMANDREGISTER);
                break;
        case COMMANDLOGIN:
            m_CommandCmd.append(NETCOMMANDLOGIN >> 8);
            m_CommandCmd.append(NETCOMMANDLOGIN);
                break;
        case COMMANDEXIT:
            m_CommandCmd.append(NETCOMMANDEXIT >> 8);
            m_CommandCmd.append(NETCOMMANDEXIT);
                break;
        case COMMANDVERIFYCODE:
            m_CommandCmd.append(NETCOMMANDVERIFYCODE >> 8);
            m_CommandCmd.append(NETCOMMANDVERIFYCODE);
            break;
        case COMMANDNEXTAREA:
            m_CommandCmd.append(NETCOMMANDNEXTAREA >> 8);
            m_CommandCmd.append(NETCOMMANDNEXTAREA);
                break;
        case COMMANDNEXTMACHINE:
            m_CommandCmd.append(NETCOMMANDNEXTMACHINE >> 8);
            m_CommandCmd.append(NETCOMMANDNEXTMACHINE);
                break;
        case COMMANDADDDIR:
             m_CommandCmd.append(NETCOMMANDADDDIR >> 8);
             m_CommandCmd.append(NETCOMMANDADDDIR);
                break;
        case COMMANDSEARCHDIR:
            m_CommandCmd.append(NETCOMMANDSEARCHDIR >> 8);
            m_CommandCmd.append(NETCOMMANDSEARCHDIR);
            break;
        case COMMANDSEARCHFILE:
            m_CommandCmd.append(NETCOMMANDSEARCHFILE >> 8);
            m_CommandCmd.append(NETCOMMANDSEARCHFILE);
            break;
        case COMMANDSENDFILEINFO:
            m_CommandCmd.append(NETCOMMANDSENDFILEINFO >> 8);
            m_CommandCmd.append(NETCOMMANDSENDFILEINFO);
            break;
        case COMMANDSENDFILEDATA:
            m_CommandCmd.append(NETCOMMANDSENDFILEDATA >> 8);
            m_CommandCmd.append(NETCOMMANDSENDFILEDATA);
            break;
        case COMMANDCANCELFILEDATA:
            m_CommandCmd.append(NETCOMMANDCANCELSENDFILE >> 8);
            m_CommandCmd.append(NETCOMMANDCANCELSENDFILE);
            break;
        case COMMANDDOWNLOADFILE:
            m_CommandCmd.append(NETCOMMANDDOWNLOADFILE >> 8);
            m_CommandCmd.append(NETCOMMANDDOWNLOADFILE);
            break;
        case COMMANDDOWNLOADPUBFILE:
            m_CommandCmd.append(NETCOMMANDDOWNLOADPUBFILE >> 8);
            m_CommandCmd.append(NETCOMMANDDOWNLOADPUBFILE);
            break;
        case COMMANDDOWNCOMFIERFILEINFO:
            m_CommandCmd.append(NETCOMMANDCOMFIREFILEINFO >> 8);
            m_CommandCmd.append(NETCOMMANDCOMFIREFILEINFO);
            break;
        case COMMANDCANCEREVFILE:
            m_CommandCmd.append(NETCOMMADNCANCELREVFILE >> 8);
            m_CommandCmd.append(NETCOMMADNCANCELREVFILE);
            break;
        case COMMANDDOWNLOADFILEOK:
            m_CommandCmd.append(NETCOMMADNDOWNFILEOK >> 8);
            m_CommandCmd.append(NETCOMMADNDOWNFILEOK);
            break;
    default:
        break;
    }
}

void NetControl::AnalysisProtocol(QByteArray &pArry)
{
    if(pArry.isEmpty())
        return;

    if(pArry.size() < 16)
        return;

    unsigned char j = (int)pArry.at(4);
    unsigned int jj = (int)j;
    j = (int)pArry.at(5);
    jj = jj << 8;
    jj = jj | j;

    qDebug() << "NetControl AnalysisProtocol";
    switch(jj)
    {
     case NETCOMMANDRECEIVEVERIFYBMP:
        {
            GetVerifyCodeBmp(pArry);
        }
        break;
    case NETCOMMANDREGISTERRESUALT:
        {
            //GetYESNOResualt(pArry);
        }
        break;
    case NETCOMMANDLOGINRESUALT:
        {
            m_bUserLogin = true;
            GetUserID(pArry);
        }
        break;
    case NETCOMMANDRECEIVEDIRLIST:
        {
            GetDirList(pArry);
        }
        break;
    case NETCOMMANDRECEIVEADDRESUALT:
        {
            GetDirYESNOResualt(pArry);
        }
        break;
    case NETCOMMANDRECEIVEALTERRESUALT:
        {
            GetDirYESNOResualt(pArry);
        }
        break;
    case NETCOMMANDRECEIVEDELETERESUALT:
        {
            GetDirYESNOResualt(pArry);
        }
        break;
    case NETCOMMANDRECEIVEFILELIST:
        {
            GetFileList(pArry);
        }
        break;
    case NETCOMMANDRECEIVECOMFIREFILEINFO:
        {
            GetFileInfoResualt(pArry);
        }
        break;
    case NETCOMMANDRECEIVECOMFIREFILEDATA:
        {
            GetFileIDataResualt(pArry);
        }
        break;
    case NETCOMMANDRECEIVECOMFIREFILE:
        {
            GetFileIComfire(pArry);
        }
        break;
    case NETCOMMANDRECEIVEFILEINFO:
        {
            GetFileInfo(pArry);
        }
        break;
    case NETCOMMANDRECEIVEFILEDATA:
        {
            GetFileData(pArry);
        }
        break;
    default:
        break;
    }

}



void NetControl::SetCommandUserID()
{
    if(m_CommandTempUserID.isEmpty())
    {
        m_CommandUserID.append((char)0x00);
        m_CommandUserID.append((char)0x00);
        m_CommandUserID.append((char)0x00);
        m_CommandUserID.append((char)0x00);
    }
    else
    {
       m_CommandUserID = m_CommandTempUserID;
    }

}

void NetControl::SetCommandData(QByteArray pDataArry)
{
    if(!pDataArry.isEmpty())
    {
        m_CommandData.append(pDataArry);
    }
}

void NetControl::SetVerifyCode()
{
    uchar *p = NULL;
    int iSeek = 0;
    uint iSum = 0;

    if(m_CommandData.isEmpty())
    {
        p = new uchar[6];
        memset(p, 0, 6);
    }
    else
    {
        int ilen = m_CommandData.size();
        p = new uchar[6 + ilen + 1];
        memset(p, 0, 6 + ilen+1);
    }

    for(int i = 0; i < m_CommandSize.size(); i++)
    {
        p[iSeek] = m_CommandSize.at(i);
        iSeek++;
    }

    for(int i = 0; i < m_CommandCmd.size(); i++)
    {
        p[iSeek] = m_CommandCmd.at(i);
        iSeek++;
    }

    for(int i = 0; i < m_CommandUserID.size(); i++)
    {
        p[iSeek] = m_CommandUserID.at(i);
        iSeek++;
    }

    if(!m_CommandData.isEmpty())
    {
        for(int i = 0; i < m_CommandData.size(); i++)
        {
            p[iSeek] = m_CommandData.at(i);
            iSeek++;
        }
    }


    for(int i = 0; i < iSeek; i++)
    {
        iSum += p[i];
    }

    if(iSum > 255)
    {
        int n;
        iSum = iSum & 0x00000000FFFF;
        n = iSum >> 8;
        iSum = iSum & 0x00FF;
        m_CommandVerifyCode.append(n);
        m_CommandVerifyCode.append(iSum);
    }
    else
    {
        m_CommandVerifyCode.append(char(0x00));
        m_CommandVerifyCode.append(iSum);
    }

}

void NetControl::SetCommandTail()
{
    m_CommandTail.append(0xCC);
    m_CommandTail.append(0X33);
    m_CommandTail.append(0xC3);
    m_CommandTail.append(0X3C);
}
void NetControl::ReceiveBytes()
{

    unsigned char j = 0;
    unsigned int jj = 0;
    QByteArray by;
    by.clear();
    //m_ReadBytes.clear();
    by = m_pSimpleNetWork->ReadBytesAll();
    qDebug() << "NetControl ReceiveBytes";
    if(true == m_bFlag)
    {
       m_bFlag = false;

       j = (int)by.at(2);
       jj = (int)j;
       j = (int)by.at(3);
       jj = jj << 8;
       jj = jj | j;
       m_iMaxSize = jj;
    }


    if(m_ReadBytes.size() < m_iMaxSize )
    {
        m_ReadBytes.append(by);
    }

    if(m_ReadBytes.size() == m_iMaxSize )
    {
         AnalysisProtocol(m_ReadBytes);
         m_ReadBytes.clear();
         m_iMaxSize = 0;
         m_bFlag = true;
    }

}



void NetControl::GetVerifyCodeBmp(QByteArray &pArry)
{
    if(pArry.isEmpty())
        return;

    QByteArray by;

    int iLen = pArry.size() - 16;
    for(int i = 10; i < iLen + 10; i++)
    {
        by.append(pArry.at(i));
    }

    emit emitVerifyCodeBmp(by);
}

void NetControl::GetUserID(QByteArray &pArry)
{
    m_CommandTempUserID.clear();

    for(int i = 6; i < 10; i++)
    {
        m_CommandTempUserID.append(pArry.at(i));
    }

}


void NetControl::GetFileList(QByteArray &pArry)
{
    qDebug() <<"GetFileList";
    QString strData = "";
    QString strCode = "";
    QString strID = "";
    QString strSize = "";
    QString strDate = "";
    QString strName = "";

    int index = 0;
    int indexTemp = 0;
    QTextCodec *Codec = QTextCodec::codecForName("KOI8-R");
    QString str = Codec->toUnicode(pArry);
    m_VectorFileList.clear();

    index = str.lastIndexOf(NETSTRINGSMYBOL);
    strData = str.mid(10,index);
    int iSize = strData.size();

    index = strData.indexOf(NETSTRINGCODE);
    index = strData.indexOf(NETSTRINGSMYBOL, index);
    indexTemp = strData.indexOf(NETSTRINGSMYBOL, index+1);
    if(1 == (indexTemp - index))
     {
        strCode = "";
     }
     else
     {
        strCode = strData.mid(index+1, (indexTemp - index-1));
     }

    while (iSize - indexTemp)
    {
        index = strData.indexOf(NETSTRINGID,indexTemp);
        if(-1 == index)
            break;
        index = strData.indexOf(NETSTRINGSMYBOL, index);
        indexTemp = strData.indexOf(NETSTRINGSMYBOL, index+1);
        strID = strData.mid(index+1, (indexTemp - index-1));

        index = strData.indexOf(NETSTRINGNAME,indexTemp);
        index = strData.indexOf(NETSTRINGSMYBOL, index);
        indexTemp = strData.indexOf(NETSTRINGSMYBOL, index+1);
        strName = strData.mid(index+1, (indexTemp - index-1));

        index = strData.indexOf(NETSTRINGSIZE,indexTemp);
        index = strData.indexOf(NETSTRINGSMYBOL, index);
        indexTemp = strData.indexOf(NETSTRINGSMYBOL, index+1);
        strSize = strData.mid(index+1, (indexTemp - index-1));

        index = strData.indexOf(NETSTRINGDATE,indexTemp);
        index = strData.indexOf(NETSTRINGSMYBOL, index);
        indexTemp = strData.indexOf(NETSTRINGSMYBOL, index+1);
        strDate = strData.mid(index+1, (indexTemp - index-1));
        m_VectorFileList.append(new FileList(strCode, strID, strName, strSize, strDate));

    }
    emit emitTest();
}

void NetControl::GetDirList(QByteArray &pArry)
{
    QString strData = "";
    QString strUPCode = "";
    QString strID = "";
    QString strCode = "";
    QString strName = "";

    int index = 0;
    int indexTemp = 0;
    QTextCodec *Codec = QTextCodec::codecForName("KOI8-R");
    QString str = Codec->toUnicode(pArry);

    m_VectorDirList.clear();
    index = str.lastIndexOf(NETSTRINGSMYBOL);
    strData = str.mid(10,index);
    int iSize = strData.size();

    index = strData.indexOf(NETSTRINGUPCODE);
    index = strData.indexOf(NETSTRINGSMYBOL, index);
    indexTemp = strData.indexOf(NETSTRINGSMYBOL, index+1);
    if(1 == (indexTemp - index))
    {
        strUPCode = "";
    }
    else
    {
        strUPCode = strData.mid(index+1, (indexTemp - index-1));
    }
    while (iSize - indexTemp)
    {
        index = strData.indexOf(NETSTRINGID,indexTemp);
        if(-1 == index)
            break;
        index = strData.indexOf(NETSTRINGSMYBOL, index);
        indexTemp = strData.indexOf(NETSTRINGSMYBOL, index+1);
        strID = strData.mid(index+1, (indexTemp - index-1));


        index = strData.indexOf(NETSTRINGCODE,indexTemp);
        index = strData.indexOf(NETSTRINGSMYBOL, index);
        indexTemp = strData.indexOf(NETSTRINGSMYBOL, index+1);
        strCode = strData.mid(index+1, (indexTemp - index-1));


        index = strData.indexOf(NETSTRINGNAME,indexTemp);
        index = strData.indexOf(NETSTRINGSMYBOL, index);
        indexTemp = strData.indexOf(NETSTRINGSMYBOL, index+1);
        strName = strData.mid(index+1, (indexTemp - index-1));
        m_VectorDirList.append(new DirList(strUPCode, strID, strCode, strName));
    }
    qDebug() << m_VectorDirList.size();
    emit emitTest();
}

void NetControl::GetFileInfo(QByteArray &pArry)
{
    QString strData = "";
    QString strFILENO = "";
    QString strLength = "";
    QString strName = "";

    int index = 0;
    int indexTemp = 0;
    QTextCodec *Codec = QTextCodec::codecForName("KOI8-R");
    QString str = Codec->toUnicode(pArry);
    m_VectorDownFileList.clear();

    index = str.lastIndexOf(NETSTRINGSMYBOL);
    strData = str.mid(10,index);
    int iSize = strData.size();

    index = strData.indexOf(NETSTRINGFILENO,indexTemp);
    index = strData.indexOf(NETSTRINGSMYBOL, index);
    indexTemp = strData.indexOf(NETSTRINGSMYBOL, index+1);
    strFILENO = strData.mid(index+1, (indexTemp - index-1));

    index = strData.indexOf(NETSTRINGNAME,indexTemp);
    index = strData.indexOf(NETSTRINGSMYBOL, index);
    indexTemp = strData.indexOf(NETSTRINGSMYBOL, index+1);
    strName = strData.mid(index+1, (indexTemp - index-1));

    index = strData.indexOf(NETSTRINGLENGTH,indexTemp);
    index = strData.indexOf(NETSTRINGSMYBOL, index);
    indexTemp = strData.indexOf(NETSTRINGSMYBOL, index+1);
    strLength = strData.mid(index+1, (indexTemp - index-1));
    m_VectorDownFileList.append(new DownFileList(strFILENO, strName, strLength));
    emit emitStartDownFileData();
}

void NetControl::GetDirYESNOResualt(QByteArray &pArry)
{
    unsigned char j = (int)pArry.at(27);
    unsigned int jj = (int)j;
    j = (int)pArry.at(28);
    jj = jj << 8;
    jj = jj | j;

    if(jj == NETCOMMANDRECEIVEDIRYES)
    {
        emit emitDirYESNO(true);
    }
    else
    {
        emit emitDirYESNO(false);
    }
}

void NetControl::GetFileInfoResualt(QByteArray &pArry)
{
    unsigned char j = (int)pArry.at(14);
    unsigned int jj = (int)j;

    switch(jj)
    {
     case 0x00:
      {

        m_CommandFileID.clear();

        for(int i = 10; i < 14; i++)
        {
            m_CommandFileID.append(pArry.at(i));
        }
        emit emitStartSendData();
      }
      break;
     case 0x11:
      {
      }
      break;
     case 0x12:
      {
      }
      break;
     case 0x13:
      {
      }
      break;
     case 0x14:
      {
      }
      break;
    default:
        break;
    }

}

void NetControl::GetFileIDataResualt(QByteArray &pArry)
{
    emit emitDataDNO();
}

void NetControl::GetFileIComfire(QByteArray &pArry)
{
    emit emitSearchFile();
}

 QVector<DirList *>  NetControl::ReturnDirList()
{
    return m_VectorDirList;
}

 void NetControl::GetFileData(QByteArray &pArry)
 {
     QByteArray by;
     unsigned char j = (int)pArry.at(22);
     unsigned int jj = (int)j;
     j = (int)pArry.at(23);
     jj = jj << 8;
     jj = jj | j;

     unsigned char i = (int)pArry.at(2);
     unsigned int ii = (int)i;
     i = (int)pArry.at(3);
     ii = ii << 8;
     ii = ii | i;

    for(int i = 0; i < jj/*pArry.size() - 30*/; i++)
    {
       by.append(pArry.at(i+24));
    }

    emit emitSendData(by, jj);
 }

QVector<FileList*>  NetControl::ReturnFileList()
{
    return m_VectorFileList;
}

QVector<DownFileList*>  NetControl::ReturnDownFileList()
{
    return m_VectorDownFileList;
}

QByteArray NetControl::GetDNOAndAddress(int iNum)
{
    QByteArray by;
    if(iNum < 256)
    {
        by.append(char(0x00));
        by.append(char(0x00));
        by.append(char(0x00));
        by.append(iNum);
    }

    if(iNum > 256)
    {
        if(iNum < 65536)
        {
            by.append(char(0x00));
            by.append(char(0x00));
            by.append(iNum/256);
            by.append(iNum%256);
        }
        else
        {
            int iHight = 0;
            int iLow = 0;
            iHight = iNum/65536;
            iLow = iNum%65536;
            by.append(iHight/256);
            by.append(iHight%256);
            by.append(iLow/256);
            by.append(iLow%256);
        }
    }
    return by;
}

QByteArray NetControl::GetDataLen(int iLen)
{
    QByteArray by;
    if(iLen < 256)
    {
        by.append(char(0x00));
        by.append(iLen);
    }
    else
    {
        by.append(iLen/256);
        by.append(iLen%256);
    }
    return by;
}
