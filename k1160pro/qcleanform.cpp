#include "qcleanform.h"
#include "ui_qcleanform.h"
#include "qmainscreen.h"


QCleanForm::QCleanForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QCleanForm),
    m_pSerialClean(NULL),
    m_bFlag(true)
{
    ui->setupUi(this);
    m_ptc =  QTextCodec::codecForName("UTF-8");

    m_bjieshoubei = true;
    m_bhuansuan = true;
    m_bpengsuan = true;
    m_bxiaohuaguan = true;
    m_bjianguan = true;
    m_byiqi = true;

    if(NULL == m_pSerialClean)
    {
        QMainScreen *pWidget = static_cast<QMainScreen *>(this->parent());
        m_pSerialClean = pWidget->m_pSerialProtcol;
    }
    InitOCX();
    InitSings();
}

QCleanForm::~QCleanForm()
{
    delete ui;
}


void QCleanForm::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("QWidget#QCleanForm{image:url(:/images/bk/bk_clean.png)}""QCleanForm{background-color:transparent;}");

    //label
    m_pLbjieshoubei = new QMLabel(this);
    m_pLbjieshoubei->setGeometry(104,75,39, 39);
    m_pLbjieshoubei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");

    m_pLbhuansuan = new QMLabel(this);
    m_pLbhuansuan->setGeometry(104,157,39, 39);
    m_pLbhuansuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");

    m_pLbpengsuan = new QMLabel(this);
    m_pLbpengsuan->setGeometry(104,239,39, 39);
    m_pLbpengsuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");

    m_pLbxiaohuaguan = new QMLabel(this);
    m_pLbxiaohuaguan->setGeometry(503,75,39, 39);
    m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");

    m_pLbjianguan = new QMLabel(this);
    m_pLbjianguan->setGeometry(503,157,39, 39);
    m_pLbjianguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");

    m_pLbyiqi = new QMLabel(this);
    m_pLbyiqi->setGeometry(503,239,39, 39);
    m_pLbyiqi->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");

    ui->lb_clean_jieshoubei->setGeometry(172, 85, 150, 30);
    ui->lb_clean_jieshoubei->setText(m_ptc->toUnicode("接收杯清洗"));
    ui->lb_clean_jieshoubei->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_clean_huansuan->setGeometry(172, 167, 150, 30);
    ui->lb_clean_huansuan->setText(m_ptc->toUnicode("换酸清洗"));
    ui->lb_clean_huansuan->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_clean_pengsuan->setGeometry(172, 249, 150, 30);
    ui->lb_clean_pengsuan->setText(m_ptc->toUnicode("消化管排废"));
    ui->lb_clean_pengsuan->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_clean_xiaohuaguan->setGeometry(570, 85, 150, 30);
    ui->lb_clean_xiaohuaguan->setText(m_ptc->toUnicode("硼酸管清洗"));
    ui->lb_clean_xiaohuaguan->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_clean_jianguan->setGeometry(570, 167, 150, 30);
    ui->lb_clean_jianguan->setText(m_ptc->toUnicode("碱管路清洗"));
    ui->lb_clean_jianguan->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_clean_yiqi->setGeometry(570, 249, 150, 30);
    ui->lb_clean_yiqi->setText(m_ptc->toUnicode("仪器自动清洗"));
    ui->lb_clean_yiqi->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->pb_clean_start->setFlat(true);
    //ui->pb_clean_start->setFocusPolicy(Qt::NoFocus);
    ui->pb_clean_start->setGeometry(700,600, 145,49);
    ui->pb_clean_start->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_start_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_start_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_start_press.png);}");

}

void QCleanForm::InitSings()
{
    connect(m_pLbjieshoubei, SIGNAL(clicked()), this, SLOT(jieshoubei()));
    connect(m_pLbhuansuan, SIGNAL(clicked()), this, SLOT(huansuan()));
    connect(m_pLbpengsuan, SIGNAL(clicked()), this, SLOT(pengsuan()));
    connect(m_pLbxiaohuaguan, SIGNAL(clicked()), this, SLOT(xiaohuaguan()));
    connect(m_pLbjianguan, SIGNAL(clicked()), this, SLOT(jianguan()));
    connect(m_pLbyiqi, SIGNAL(clicked()), this, SLOT(yiqi()));

    connect(m_pSerialClean->m_pReadThread, SIGNAL(emitReadData(QByteArray)),
                    this, SLOT(AnalysisData(QByteArray)));
}

void QCleanForm::AnalysisData(QByteArray pData)
{
    unsigned char j = (int)pData.at(4);
    unsigned int jj = (int)j;
    j = (int)pData.at(5);
    jj = jj << 8;
    jj = jj | j;

    //qDebug() << QString("QCleanForm ReadThread back. %1").arg(jj);

    switch (jj) {
    case _SERIALCMD_MCU_CLEAN_STOP_:
        {
            qDebug("_SERIALCMD_MCU_CLEAN_STOP_");
            m_bFlag = true;
        }
        break;
    case _SERIALCMD_MCU_CLEAN_JIESHOUBEI_:
        {
            qDebug("_SERIALCMD_MCU_CLEAN_JIESHOUBEI_");
        }
        break;
    case _SERIALCMD_MCU_CLEAN_XIAOHUA_:
        {
            qDebug("_SERIALCMD_MCU_CLEAN_XIAOHUA_");
        }
        break;
    case _SERIALCMD_MCU_CLEAN_HUANSUAN_:
        {
            qDebug("_SERIALCMD_MCU_CLEAN_HUANSUAN_");
        }
        break;
    case _SERIALCMD_MCU_CLEAN_JIANGUAN_:
        {
            qDebug("_SERIALCMD_MCU_CLEAN_JIANGUAN_");
        }
        break;
    case _SERIALCMD_MCU_CLEAN_PENGSUAN_:
        {
            qDebug("_SERIALCMD_MCU_CLEAN_PENGSUAN_");
        }
        break;
    case _SERIALCMD_MCU_CLEAN_AUTO_:
        {
            qDebug("_SERIALCMD_MCU_CLEAN_AUTO_");
        }
        break;
    default:
        break;
    }

}

void QCleanForm::jieshoubei()
{
    if(true == m_bjieshoubei)
     {
        m_pLbjieshoubei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_bjieshoubei = false;

        m_pLbjianguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjianguan = true;

        m_pLbyiqi->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_byiqi = true;

        m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bxiaohuaguan = true;

        m_pLbpengsuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bpengsuan = true;

        m_pLbhuansuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bhuansuan = true;

     }
     else
     {
        m_pLbjieshoubei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjieshoubei = true;
     }

}

void QCleanForm::huansuan()
{
    if(true == m_bhuansuan)
     {
        m_pLbhuansuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_bhuansuan = false;

        m_pLbjianguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjianguan = true;

        m_pLbyiqi->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_byiqi = true;

        m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bxiaohuaguan = true;

        m_pLbpengsuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bpengsuan = true;

        m_pLbjieshoubei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjieshoubei = true;
     }
     else
     {
        m_pLbhuansuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bhuansuan = true;
     }

}

void QCleanForm::pengsuan()
{
    if(true == m_bpengsuan)
     {
        m_pLbpengsuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_bpengsuan = false;

        m_pLbjianguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjianguan = true;

        m_pLbyiqi->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_byiqi = true;

        m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bxiaohuaguan = true;

        m_pLbhuansuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bhuansuan = true;

        m_pLbjieshoubei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjieshoubei = true;
     }
     else
     {
        m_pLbpengsuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bpengsuan = true;
     }
}

void QCleanForm::xiaohuaguan()
{
    if(true == m_bxiaohuaguan)
     {
        m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_bxiaohuaguan = false;

        m_pLbjianguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjianguan = true;

        m_pLbyiqi->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_byiqi = true;

        m_pLbpengsuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bpengsuan = true;

        m_pLbhuansuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bhuansuan = true;

        m_pLbjieshoubei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjieshoubei = true;
     }
     else
     {
        m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bxiaohuaguan = true;
     }
}

void QCleanForm::jianguan()
{
    if(true == m_bjianguan)
     {
        m_pLbjianguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_bjianguan = false;

        m_pLbyiqi->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_byiqi = true;

        m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bxiaohuaguan = true;

        m_pLbpengsuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bpengsuan = true;

        m_pLbhuansuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bhuansuan = true;

        m_pLbjieshoubei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjieshoubei = true;

     }
     else
     {
        m_pLbjianguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjianguan = true;
     }
}

void QCleanForm::yiqi()
{
    if(true == m_byiqi)
     {
        m_pLbyiqi->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_byiqi = false;

        m_pLbjianguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjianguan = true;

        m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bxiaohuaguan = true;

        m_pLbpengsuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bpengsuan = true;

        m_pLbhuansuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bhuansuan = true;

        m_pLbjieshoubei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjieshoubei = true;
     }
     else
     {
        m_pLbyiqi->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_byiqi = true;
     }
}


void QCleanForm::on_pb_clean_start_clicked()
{
    /*
    if(false == m_bFlag)
        return;
    */
    if(false == m_byiqi)
    {
        m_Serialcmd.clear();
        m_Serialdata.clear();
        m_Serialcmd.append(0x05);
        m_Serialcmd.append(0x06);
        m_pSerialClean->TransmitData(m_Serialcmd, m_Serialdata);
    }

    if(false == m_bjianguan)
    {
        m_Serialcmd.clear();
        m_Serialdata.clear();
        m_Serialcmd.append(0x05);
        m_Serialcmd.append(0x04);
        m_pSerialClean->TransmitData(m_Serialcmd, m_Serialdata);
    }

    if(false == m_bxiaohuaguan)
    {
        m_Serialcmd.clear();
        m_Serialdata.clear();
        m_Serialcmd.append(0x05);
        m_Serialcmd.append(0x05);
        m_pSerialClean->TransmitData(m_Serialcmd, m_Serialdata);
    }

    if(false == m_bpengsuan)
    {
        m_Serialcmd.clear();
        m_Serialdata.clear();
        m_Serialcmd.append(0x05);
        m_Serialcmd.append(0x02);
        m_pSerialClean->TransmitData(m_Serialcmd, m_Serialdata);
    }

    if(false == m_bhuansuan)
    {
        m_Serialcmd.clear();
        m_Serialdata.clear();
        m_Serialcmd.append(0x05);
        m_Serialcmd.append(0x03);
        m_pSerialClean->TransmitData(m_Serialcmd, m_Serialdata);
    }

    if(false == m_bjieshoubei)
    {
        m_Serialcmd.clear();
        m_Serialdata.clear();
        m_Serialcmd.append(0x05);
        m_Serialcmd.append(0x01);
        m_pSerialClean->TransmitData(m_Serialcmd, m_Serialdata);
    }
    m_bFlag = false;
}
