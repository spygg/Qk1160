#include "qcloudform.h"
#include "ui_qcloudform.h"
#include "DataDef.h"
#include "qmainscreen.h"
#include "NetSource/simplenetwork.h"
#include "NetSource/NetDataCode.h"
#include "NetSource/NetControl.h"

QCloudForm::QCloudForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QCloudForm),
    m_model(NULL),
    m_iconfolder(NULL),
    m_iconfile(NULL),
    m_pQStandardItemModel(NULL),
    m_VectorDownFileList(NULL),
    m_iFileIndex(0),
    m_iFileNo(0),
    m_isize(0),
    m_bfileFlag(true)
{
    ui->setupUi(this);
    m_ptc =  QTextCodec::codecForName("UTF-8");
    QMainScreen *pWidget = static_cast<QMainScreen *>(this->parent());
    m_pNetControl = pWidget->m_pNetControl;
    InitOCX();
    InitSings();

    //this->setWindowModality(Qt::WindowModal);

}

QCloudForm::~QCloudForm()
{
    delete ui;
}


void QCloudForm::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("QWidget#QCloudForm{image:url(:/images/bk/bk_net.png)}""QCloudForm{background-color:transparent;}");

    ui->pb_downfile ->setFlat(true);
    //ui->pb_downfile->setFocusPolicy(Qt::NoFocus);
    ui->pb_downfile->setGeometry(729,588,108,44);
    ui->pb_downfile->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_down_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_down_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_down_press.png);}");

    ui->label_cloud->setGeometry(28,5,111,36);
    ui->label_cloud->setText(m_ptc->toUnicode("云服务"));
    ui->label_cloud->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

   m_iconfolder = new QIcon(":/images/bt/wenjianjia.ico");
   m_iconfile = new QIcon(":/images/bt/file.ico");
    //m_iconfolder = new QIcon(tr(":/treeItemIcon/res_treeItemIcon/Project.png"));
    ui->treeView->setGeometry(38, 41, 837, 526);
    m_model   =   new QStandardItemModel();
#ifdef _MIPS_LINUX_ENV_
    m_model->setHorizontalHeaderLabels(QStringList() << "");
    QStandardItem* itemProjectdata = new QStandardItem(*m_iconfolder, "Method");
    QStandardItem* itemProjectmetoh = new QStandardItem(*m_iconfolder, "Data");
    m_model->appendRow(itemProjectdata);
    m_model->appendRow(itemProjectmetoh);
    ui->treeView->setModel(m_model);
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
#else
    m_model->setHorizontalHeaderLabels(QStringList() << tr(""));
    QStandardItem* itemProjectdata = new QStandardItem(*m_iconfolder, tr("Method"));
    QStandardItem* itemProjectmetoh = new QStandardItem(*m_iconfolder, tr("Data"));
    m_model->appendRow(itemProjectdata);
    m_model->appendRow(itemProjectmetoh);
    ui->treeView->setModel(m_model);
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
#endif


 }

void QCloudForm::InitSings()
{

}




void QCloudForm::SearchDir()
{
    QByteArray by;
    by.clear();
    QString strData = "";
    strData = QString(NETCOMMANDDATASEARCHDIR).arg("");
    by.append(strData);
    m_pNetControl->PackAndSendData(by,COMMANDSEARCHDIR);
}

void QCloudForm::RefreshTreeView()
{
    QList<QStandardItem *> item;

    item.clear();
    m_model->clear();
    m_VectorDirList.clear();
    m_VectorFileList.clear();
    DirList *pdr1;
    DirList *pdr2;
    pdr1 = new DirList("", "1", "001", "Method");
    pdr2 = new DirList("", "1", "002", "Data");

    m_VectorDirList.append(pdr1);
    m_VectorDirList.append(pdr2);
   // m_VectorDirList = m_pNetControl->ReturnDirList();
   //strlist.append("Method");

    m_VectorFileList = m_pNetControl->ReturnFileList();
    //QStandardItem* itemProjectmetoh = new QStandardItem(*m_iconfolder, tr("Method"));
    qDebug() <<"m_VectorFileList"<< m_VectorFileList.size();
   // m_pQStandardItemModel = new QStandardItemModel(m_VectorDirList.size(),1);
   //m_model->setHeaderData(0, Qt::Horizontal, tr("Path"));

    m_model->setHorizontalHeaderLabels(QStringList() << "");
    //int j = m_VectorDirList.size();

    for(int i = 0; i < 2; i++)
    {
        item.append(new QStandardItem(*m_iconfolder, m_VectorDirList.at(i)->m_strName));

        m_model->setItem(i, item.at(i));

        for(int j = 0; j < m_VectorFileList.size(); j++)
        {
          if(m_VectorDirList.at(i)->m_strCode == m_VectorFileList.at(j)->m_strCode)
          {
              item.at(i)->appendRow(new QStandardItem(*m_iconfile, m_VectorFileList.at(j)->m_strName));
          }
        }
    }
}

void QCloudForm::on_pb_dir_clicked()
{
    //SearchDir();
}

void QCloudForm::on_treeView_pressed(const QModelIndex &index)
{
    QString strindex = index.data().toString();

    m_iFileIndex = index.row();
    QString strData = "";
    QByteArray by;
    QString strM = "Method";
    QString strD = "Data";

    if(strM == strindex)
    {
        strData = QString(NETCOMMANDDATASEARCHFILE).arg("001");
        m_bfileFlag = true;
    }
    else if (strD == strindex)
    {
        strData = QString(NETCOMMANDDATASEARCHFILE).arg("002");
        m_bfileFlag = false;
    }
    else
    {
        return;
    }

    by.clear();
    by.append(strData);
    m_pNetControl->PackAndSendData(by,COMMANDSEARCHFILE);
    qDebug() << "strData = "<< strData;
}

void QCloudForm::on_pb_downfile_clicked()
{
    if(m_VectorFileList.isEmpty())
    {
        return;
    }

    QByteArray by;
    by.clear();
    QString strData = "";
    strData = QString(NETCOMMADNDATAGETFILEBYID).arg(m_VectorFileList.at(m_iFileIndex)->m_strID);
    by.append(strData);
    m_pNetControl->PackAndSendData(by,COMMANDDOWNLOADFILE);

}
void QCloudForm::RequestData()
{
    QByteArray by;
    int iDNO = 0;
    int iFileNo = 0;
    m_FileData.clear();
    m_iFileNo = 0;
    m_isize = 0;
    m_VectorDownFileList = m_pNetControl->ReturnDownFileList();

    iFileNo = m_VectorDownFileList.at(0)->m_strFileNO.toInt();

    by.clear();
    by.append(m_pNetControl->GetDNOAndAddress(iFileNo));
    by.append(m_pNetControl->GetDNOAndAddress(iDNO));
    m_pNetControl->PackAndSendData(by,COMMANDDOWNCOMFIERFILEINFO);
}

void QCloudForm::writeFile(QByteArray parry, int isize)
{

    QByteArray by;
    QFile file;
    int iFileNo = 0;
    int iFileSize = 0;

    m_VectorDownFileList = m_pNetControl->ReturnDownFileList();
    iFileNo = m_VectorDownFileList.at(0)->m_strFileNO.toInt();
    iFileSize = m_VectorDownFileList.at(0)->m_strSize.toInt();

    m_isize += isize;
    if(m_isize <= iFileSize)
    {
        m_iFileNo += 1;
        m_FileData.append(parry);
        by.clear();
        by.append(m_pNetControl->GetDNOAndAddress(iFileNo));
        by.append(m_pNetControl->GetDNOAndAddress(m_iFileNo));
        m_pNetControl->PackAndSendData(by,COMMANDDOWNCOMFIERFILEINFO);
    }

    if(m_isize == iFileSize)
    {
        QDir dir;
        QString strPath = "";
        strPath = dir.currentPath();
        file.setFileName(strPath+"/"+ m_VectorDownFileList.at(0)->m_strName);
       if(true == file.open(QIODevice::WriteOnly))
       {
            int iSize = file.write(m_FileData);
       }
       file.close();
       by.clear();
       iFileNo = m_VectorDownFileList.at(0)->m_strFileNO.toInt();
       by.append(m_pNetControl->GetDNOAndAddress(iFileNo));
       m_pNetControl->PackAndSendData(by,COMMANDDOWNLOADFILEOK);

       QString strTo = "";
       if(true == m_bfileFlag)
       {
           strTo = "./db/hanon.db";
       }
       else
       {
           strTo = "./db/Data/SampleResult.db";
       }

       QFile::remove(strTo);
       if(!QFile::copy(file.fileName(), strTo))
       {
           return;
       }
    }



}


