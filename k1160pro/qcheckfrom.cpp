#include <QMessageBox>
#include "qcheckfrom.h"
#include "ui_qcheckfrom.h"
#include <QDebug>

QCheckFrom::QCheckFrom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QCheckFrom),
    m_pCheckProcessTimer(NULL),
    m_pSerialCheckopro(NULL)
{
    ui->setupUi(this);
    InitOCX();
}

QCheckFrom::QCheckFrom(QWidget *parent, QWidget *parent1) :
    QWidget(parent),
    ui(new Ui::QCheckFrom),
    m_pCheckProcessTimer(NULL),
    m_pSerialCheckopro(NULL)
{
    ui->setupUi(this);
    InitOCX();
    m_ptc =  QTextCodec::codecForName("UTF-8");
    //m_pScreen = static_cast<QMainScreen *>parent1;
   m_pScreen =  static_cast<QMainScreen*>(parent1);


   m_pSerialCheckopro = m_pScreen->m_pSerialProtcol;

   if(NULL != m_pSerialCheckopro)
   {
       m_Serialcmd.clear();
       m_Serialdata.clear();
       m_Serialcmd.append(0x02);
       m_Serialcmd.append((char)0x00);
       m_Serialdata.append((char)0x00);
       m_pSerialCheckopro->TransmitData(m_Serialcmd, m_Serialdata);
   }

   if(NULL == m_pCheckProcessTimer)
   {
       m_pCheckProcessTimer = new QTimer();
       connect(m_pSerialCheckopro->m_pReadThread, SIGNAL(emitReadData(QByteArray)),this, SLOT(AnalysisData(QByteArray)));
       connect(m_pCheckProcessTimer,SIGNAL(timeout()),this,SLOT(CheckStateShow()));
   }

   ui->prb_checkdlg_process->setPixMap("://images/bk/bk_progress_background.png", "://images/bk/bk_progress_chunk.png");
    ui->prb_checkdlg_process->setRange(0, 5);
    ui->prb_checkdlg_process->setValue(0);
/*
    QString str = "";
    QString strjieshoubei = "接收杯检测通过\n";
    QString strzhengliu = "蒸馏检测通过\n";
    QString strlengningshui = "冷凝水检测通过\n";
    QString strdiding = "滴定检测通过\n";
    str = strjieshoubei + strzhengliu + strlengningshui + strdiding;
    QMessageBox::StandardButton rb  = QMessageBox::question(this, m_ptc->toUnicode(""), str, QMessageBox::Yes | QMessageBox::No);
    if(rb == QMessageBox::Yes)
    {
        m_pScreen->show();
    }

    if(rb == QMessageBox::No)
    {

    }
*/
}


QCheckFrom::~QCheckFrom()
{
    delete ui;
}

void QCheckFrom::AnalysisData(QByteArray pData)
{
    unsigned char j = (int)pData.at(4);
    unsigned int jj = (int)j;
    j = (int)pData.at(5);
    jj = jj << 8;
    jj = jj | j;

    qDebug() << QString("QCheckFrom ReadThread back. %1").arg(jj);
    switch (jj) {
    case _SERIALCMD_MCU_CHECKSTART_:
        {
            qDebug("_SERIALCMD_MCU_START_");
            m_pCheckProcessTimer->start(1000);
        }
        break;
    case _SERIALCMD_MCU_CHECKSTATE_:
        {
            StateProcess(pData);
        }
        break;
    case _SERIALCMD_MCU_CHECKRESUALT_:
        {
            StateResualt(pData);
        }
        break;
    case 0x8204:
        {
            qDebug("_SERIALCMD_MCU_CLEAN_HUANSUAN_");
            ui->label->setText(m_ptc->toUnicode("正在进行换酸清洗..."));
        }
        break;
    case 0x8214:
        {
            qDebug("_SERIALCMD_MCU_CLEAN_STOP_");
            ui->prb_checkdlg_process->setValue(5);
            m_Serialcmd.clear();
            m_Serialdata.clear();
            m_Serialcmd.append(0x02);
            m_Serialcmd.append(0x03);
            m_Serialdata.append((char)0x00);

            m_pSerialCheckopro->TransmitData(m_Serialcmd, m_Serialdata);
            pline();
            ui->label->setText(m_ptc->toUnicode("请稍后..."));
        }
        break;

    default:
        break;
    }
}

void QCheckFrom::StateProcess(QByteArray pData)
{
    qDebug("StateProcess");
    int iProcess = -1;
    switch (pData[6]) {
    case 0x01:
        iProcess = 0;
        ui->label->setText(m_ptc->toUnicode("检测接收杯... "));
        break;
    case 0x02:
        iProcess = 1;
         ui->label->setText(m_ptc->toUnicode("检测蒸馏... "));
        break;
    case 0x03:
        iProcess = 2;
         ui->label->setText(m_ptc->toUnicode("检测冷凝水..."));
        break;
    case 0x04:
        iProcess = 3;
         ui->label->setText(m_ptc->toUnicode("检测滴定..."));
        break;
    case 0x00:
        iProcess = 4;
        ui->label->setText(m_ptc->toUnicode("请稍后..."));
        break;
    default:
        break;
    }

    ui->prb_checkdlg_process->setValue(iProcess);


    if(iProcess == 4)
    {
        m_pCheckProcessTimer->stop();

        QSettings set;
        int huansuan = set.value("Machine/zijianhouhuansuan", 1).toInt();

        if(huansuan != 0)
        {
            m_Serialcmd.clear();
            m_Serialdata.clear();
            m_Serialcmd.append(0x02);
            m_Serialcmd.append(0x04);
            m_pSerialCheckopro->TransmitData(m_Serialcmd, m_Serialdata);
            pline();
        }
        else
        {
            ui->prb_checkdlg_process->setValue(5);
            m_Serialcmd.clear();
            m_Serialdata.clear();
            m_Serialcmd.append(0x02);
            m_Serialcmd.append(0x03);
            m_Serialdata.append((char)0x00);

            m_pSerialCheckopro->TransmitData(m_Serialcmd, m_Serialdata);
            pline();
            ui->label->setText(m_ptc->toUnicode("请稍后..."));
        }

    }
}

void QCheckFrom::StateResualt(QByteArray pData)
{
    QString str = "";
    QString strjieshoubei = "";
    QString strzhengliu = "";
    QString strlengningshui = "";
    QString strdiding = "";
    switch (pData[6]) {
    case 0x00:
        strjieshoubei = m_ptc->toUnicode("接收杯检测通过\n");
        break;
    case 0x01:
        strjieshoubei = m_ptc->toUnicode("接收杯未检测\n");
        break;
    case 0x02:
        strjieshoubei = m_ptc->toUnicode("接收杯检测未通过\n");
        break;
    default:
        break;
    }

    switch (pData[7]) {
    case 0x00:
        strzhengliu = m_ptc->toUnicode("蒸馏检测通过\n");
        break;
    case 0x01:
        strzhengliu = m_ptc->toUnicode("蒸馏未检测\n");
        break;
    case 0x02:
        strzhengliu = m_ptc->toUnicode("蒸馏检测未通过\n");
        break;
    default:
        break;
    }

    switch (pData[8]) {
    case 0x00:
        strlengningshui = m_ptc->toUnicode("冷凝水检测通过\n");
        break;
    case 0x01:
        strlengningshui = m_ptc->toUnicode("冷凝水未检测\n");
        break;
    case 0x02:
        strlengningshui = m_ptc->toUnicode("冷凝水检测未通过\n");
        break;
    default:
        break;
    }

    switch (pData[9]) {
    case 0x00:
        strdiding = m_ptc->toUnicode("滴定检测通过\n");
        break;
    case 0x01:
        strdiding = m_ptc->toUnicode("滴定未检测\n");
        break;
    case 0x02:
        strdiding = m_ptc->toUnicode("滴定检测未通过\n");
        break;
    default:
        break;
    }
    str = strjieshoubei + strzhengliu + strlengningshui + strdiding;

    QMessageBox::information(this, m_ptc->toUnicode(""),str, QMessageBox::Yes);
    m_pScreen->show();
    this->hide();
}

void QCheckFrom::CheckStateShow()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x02);
    m_Serialcmd.append(0x02);
    m_Serialdata.append((char)0x00);

    m_pSerialCheckopro->TransmitData(m_Serialcmd, m_Serialdata);
}
void QCheckFrom::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setStyleSheet("QWidget#QCheckFrom{image:url(:/images/bk/bk_check.png)}""QCheckFrom{background-color:transparent;}");

    ui->label->setForegroundRole(QPalette::BrightText);
    //bt

    //prb
    //ui->prb_checkdlg_process->setFocusPolicy(Qt::NoFocus);
    //ui->prb_checkdlg_process->setStyleSheet("QProgressBar{background-color:transparent;}");
}
