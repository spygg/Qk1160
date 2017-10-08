#include <QLayout>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include "qmainscreen.h"
#include "DataDef.h"
#include "qautotest.h"
#include "qautotestaprocessform.h"
#include "ui_qautotestaprocessform.h"
#include "qcalbase.h"
#include "HNDefine.h"

using namespace std;

typedef vector<int> vint;
typedef list <int>  lint;
typedef list <double> ldouble;
typedef list< pair<double,double> > lpair;

lpair position;
vint  velocity;
vint  times;
lint  press1;
lint  press2;
ldouble press3;

QAutoTestaProcessForm::QAutoTestaProcessForm(QWidget *parent) :
    QWidget(parent),
    m_pSerialAutopro(NULL),
    m_pProcessTimer(NULL),
    m_pStateTimer(NULL),
    m_pRGBTimer(NULL),
    m_pdataTimer(NULL),
    customPlot(NULL),
    m_bIsFirst(true),
    m_iprFlag(0),
    m_iIndex(0),
    m_bRunning(false),
    pWheelUp(NULL),
    pWheelDown(NULL),
    m_dIndex(0),
    strtable("data"),
    pdataquery(NULL),
    ui(new Ui::QAutoTestaProcessForm)
{
    ui->setupUi(this);
    m_ptc =  QTextCodec::codecForName("UTF-8");

    InitOCX();
    InitSings();

    InitDiagram();

    pdataquery = new QDatabasequery();
    pdataquery->SetTableName("./db/Data/SampleResult");
   //connect(m_pdataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    //m_pdataTimer->start(0); // Interval 0 means to refresh as fast as possible
    //customPlot->setBackground(QBrush(QColor(76,74,68)));

    // make left and bottom axes transfer their ranges to right and top axes:
 //   connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
 //   connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
}


QAutoTestaProcessForm::~QAutoTestaProcessForm()
{
    m_pSerialAutopro = NULL;
    m_pProcessTimer = NULL;
    m_pStateTimer = NULL;
    m_pRGBTimer = NULL;
    m_pdataTimer = NULL;
    delete ui;
}

void QAutoTestaProcessForm::InitData()
{
    m_Serialcmd.clear();
    m_Serialcmd.append(0x03);
    m_Serialcmd.append((char)0x00);
    QAutoTest *pAutoTest = static_cast<QAutoTest *>(this->parent());

    m_Serialdata.append(pAutoTest->m_pListTestMethod.at(0)->m_ipengsuan);
    m_Serialdata.append(pAutoTest->m_pListTestMethod.at(0)->m_ixishishui);
    m_Serialdata.append(pAutoTest->m_pListTestMethod.at(0)->m_ijian);
    m_Serialdata.append(pAutoTest->m_pListTestMethod.at(0)->m_izhengliu >> 8);
    m_Serialdata.append(pAutoTest->m_pListTestMethod.at(0)->m_izhengliu);
    m_Serialdata.append(pAutoTest->m_pListTestMethod.at(0)->m_imls);
    m_Serialdata.append(pAutoTest->m_pListTestMethod.at(0)->m_ididing);
    m_Serialdata.append(pAutoTest->m_pListTestMethod.at(0)->m_ijiajian);
    m_Serialdata.append(pAutoTest->m_pListTestMethod.at(0)->m_izhengqi);
    m_Serialdata.append(pAutoTest->m_pListTestMethod.at(0)->m_ixiaohuaguan);
    m_Serialdata.append(pAutoTest->m_pListTestMethod.at(0)->m_ijieshoubei);
    m_Serialdata.append(pAutoTest->m_pListTestMethod.at(0)->m_ilengningshui);
    m_pSerialAutopro->TransmitData(m_Serialcmd, m_Serialdata);

    //m_pProcessTimer->start(800);
    m_pRGBTimer->start(1000);
    //m_pStateTimer->start(600);
    m_bRunning = true;

    switch (pAutoTest->m_pListTestMethod.at(0)->m_ididing) {
    case 0:
        ui->pr_autotest_progressBar->setRange(0, 6);
        m_iprFlag = 0;
        break;
    case 1:
        ui->pr_autotest_progressBar->setRange(0, 5);
        m_iprFlag = 1;
        break;
    default:
        break;
    }

    ui->pr_autotest_progressBar->setValue(0);
    QString str;
    ui->label_name->setText(pAutoTest->m_pListTestData.at(pAutoTest->m_iIndex-1)->m_strName);
    ui->label_yangpinpihao->setText(pAutoTest->m_pListTestData.at(pAutoTest->m_iIndex-1)->m_strpihao);
    str = QString("%1").arg(pAutoTest->m_pListTestData.at(pAutoTest->m_iIndex-1)->m_fEmptyvolum);
    ui->label_kongbaitiji->setText(str);
    str = QString("%1").arg(pAutoTest->m_pListTestData.at(pAutoTest->m_iIndex-1)->m_fdiding);
    ui->label_nongdu->setText(str);
    str = QString("%1").arg(pAutoTest->m_pListTestData.at(pAutoTest->m_iIndex-1)->m_fSampleNumber);
    ui->label_yangpinliang->setText(str);
    str = QString::number(pAutoTest->m_pListTestMethod.at(0)->m_ipengsuan, 10);
    ui->label_pengsuan->setText(str);
    str = QString::number(pAutoTest->m_pListTestMethod.at(0)->m_ilengningshui, 10);
    ui->label_xishishui->setText(str);
    str = QString::number(pAutoTest->m_pListTestMethod.at(0)->m_ijian, 10);
    ui->label_jian->setText(str);
    str = QString::number(pAutoTest->m_pListTestMethod.at(0)->m_izhengliu, 10);
    ui->label_zhengliu->setText(str);

    if(pAutoTest->m_pListTestData.at(pAutoTest->m_iIndex-1)->m_enumSampleNumberType == _enum_Sampleg)

        ui->label_yangpinliangdanwei->setText("g");
    else if(pAutoTest->m_pListTestData.at(pAutoTest->m_iIndex-1)->m_enumSampleNumberType == _enum_Sampleml)
        ui->label_yangpinliangdanwei->setText("mL");

}


void QAutoTestaProcessForm::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(0,0,916,667);
    this->setStyleSheet("QWidget#QAutoTestaProcessForm{image:url(:/images/bk/bk_autotestpr.png)}""QAutoTest{background-color:transparent;}");

    m_pLbpengsuantong = new QMLabel(this);
    //m_pLbpengsuantong->setFocusPolicy(Qt::NoFocus);
    m_pLbpengsuantong->setGeometry(626, 56,40, 40);
    m_pLbpengsuantong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_pengsuantong_normal.png);}");

    m_pLbshuitong = new QMLabel(this);
    //m_pLbshuitong->setFocusPolicy(Qt::NoFocus);
    m_pLbshuitong->setGeometry( 685,  56, 40, 40);
    m_pLbshuitong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_shuitong_normal.png);}");

    m_pLbjiantong = new QMLabel(this);
    //m_pLbjiantong->setFocusPolicy(Qt::NoFocus);
    m_pLbjiantong->setGeometry(744, 56,40, 40);
    m_pLbjiantong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_jiantong_normal.png);}");

    m_pLbdidingsuantong = new QMLabel(this);
    //m_pLbdidingsuantong->setFocusPolicy(Qt::NoFocus);
    m_pLbdidingsuantong->setGeometry( 803,  56, 40, 40);
    m_pLbdidingsuantong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_didingsuantong_normal.png);}");


    m_pLbzhengqifashengqiyewei = new QMLabel(this);
    m_pLbzhengqifashengqiyewei->setGeometry(626, 106,40, 40);
    m_pLbzhengqifashengqiyewei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_zhengqifashengqiyewei_normal.png);}");

    m_pLbanquanmen = new QMLabel(this);
    m_pLbanquanmen->setGeometry(685, 106,40, 40);
    m_pLbanquanmen->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_anquanmen_normal.png);}");

    m_pLbxiaohuaguan = new QMLabel(this);
    m_pLbxiaohuaguan->setGeometry(744, 106,40, 40);
    m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_xiaohuaguan_normal.png);}");

    m_pLbfeiyetong = new QMLabel(this);
    //m_pLbfeiyetong->setFocusPolicy(Qt::NoFocus);
    m_pLbfeiyetong->setGeometry(803, 106,40, 40);
    m_pLbfeiyetong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_feiyetong_normal.png);}");

    m_pLbzhengqifashengqi = new QMLabel(this);
    //m_pLbzhengqifashengqi->setFocusPolicy(Qt::NoFocus);
    m_pLbzhengqifashengqi->setGeometry(626,156,40, 40);
    m_pLbzhengqifashengqi->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_zhengqifashengqi_normal.png);}");

    ui->label_wendu1->setGeometry(685,156,58, 40);
    //ui->label_wendu1->setFocusPolicy(Qt::NoFocus);
    ui->label_wendu1->setText(m_ptc->toUnicode("0℃"));
    ui->label_wendu1->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    m_pLblengningshui = new QMLabel(this);
    //m_pLblengningshui->setFocusPolicy(Qt::NoFocus);
    m_pLblengningshui->setGeometry(744,156,40, 40);
    m_pLblengningshui->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_lengningshui_normal.png);}");

    ui->label_wendu2->setGeometry(803,156,58, 40);
    //ui->label_wendu2->setFocusPolicy(Qt::NoFocus);
    ui->label_wendu2->setText(m_ptc->toUnicode("0℃"));
    ui->label_wendu2->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->lb_autotestpt_mingcheng->setGeometry(33, 566, 100, 30);
    ui->lb_autotestpt_mingcheng->setText(m_ptc->toUnicode("样品名称："));
    ui->lb_autotestpt_mingcheng->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->label_name->setGeometry(126, 566, 100, 30);
    ui->label_name->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotestpt_bianhao->setGeometry(33, 594, 100, 30);
    ui->lb_autotestpt_bianhao->setText(m_ptc->toUnicode("样品编号："));
    ui->lb_autotestpt_bianhao->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->label_yangpinpihao->setGeometry(126, 594, 100, 30);
    ui->label_yangpinpihao->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");


    ui->lb_autotestpt_tiji->setGeometry(296, 622, 100, 30);
    ui->lb_autotestpt_tiji->setText(m_ptc->toUnicode("空白体积："));
    ui->lb_autotestpt_tiji->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->label_kongbaitiji->setGeometry(393, 622, 100, 30);
    ui->label_kongbaitiji->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotestpt_xishu->setGeometry(36, 589, 100, 30);
    ui->lb_autotestpt_xishu->setText(m_ptc->toUnicode("蛋白系数："));
    ui->lb_autotestpt_xishu->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
    ui->lb_autotestpt_xishu->hide();

    ui->label_danbaixishu->setGeometry(126, 589, 100, 30);
    ui->label_danbaixishu->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
    ui->label_danbaixishu->hide();

    ui->lb_autotestpt_nongdu->setGeometry(33, 622, 100, 30);
    ui->lb_autotestpt_nongdu->setText(m_ptc->toUnicode("滴定酸浓度："));
    ui->lb_autotestpt_nongdu->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->label_nongdu->setGeometry(133, 622, 100, 30);
    ui->label_nongdu->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotestpt_yangpinliang->setGeometry(296, 594, 100, 30);
    ui->lb_autotestpt_yangpinliang->setText(m_ptc->toUnicode("样品量："));
    ui->lb_autotestpt_yangpinliang->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->label_yangpinliang->setGeometry(393, 594, 100, 30);
    ui->label_yangpinliang->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->label_yangpinliangdanwei->setGeometry(518, 594, 100, 30);
    ui->label_yangpinliangdanwei->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotestpt_pengsuan->setGeometry(330, 531, 100, 30);
    ui->lb_autotestpt_pengsuan->setText(m_ptc->toUnicode("硼酸："));
    ui->lb_autotestpt_pengsuan->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
    ui->lb_autotestpt_pengsuan->hide();

    ui->label_pengsuan->setGeometry(420, 531, 100, 30);
    ui->label_pengsuan->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
    ui->label_pengsuan->hide();

    ui->lb_autotestpt_xishishui->setGeometry(330, 560, 100, 30);
    ui->lb_autotestpt_xishishui->setText(m_ptc->toUnicode("稀释水："));
    ui->lb_autotestpt_xishishui->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
    ui->lb_autotestpt_xishishui->hide();

    ui->label_xishishui->setGeometry(420, 560, 100, 30);
    ui->label_xishishui->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
    ui->label_xishishui->hide();

    ui->lb_autotestpt_jian->setGeometry(330, 589, 100, 30);
    ui->lb_autotestpt_jian->setText(m_ptc->toUnicode("碱："));
    ui->lb_autotestpt_jian->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
    ui->lb_autotestpt_jian->hide();

    ui->label_jian->setGeometry(420, 589, 100, 30);
    ui->label_jian->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
    ui->label_jian->hide();

    ui->lb_autotestpt_zhengliu->setGeometry(330, 618, 100, 30);
    ui->lb_autotestpt_zhengliu->setText(m_ptc->toUnicode("蒸馏："));
    ui->lb_autotestpt_zhengliu->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
    ui->lb_autotestpt_zhengliu->hide();

    ui->label_zhengliu->setGeometry(420, 618, 100, 30);
    ui->label_zhengliu->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
    ui->label_zhengliu->hide();
/*
    ui->label_zhengliu->setGeometry(420, 618, 100, 30);
    ui->lb_autotestpt_ml1->setText(m_ptc->toUnicode("99*C"));
    ui->label_zhengliu->setStyleSheet("QLabel{background-color:transparent;font-size:28px}");

*/

    ui->lb_autotestpt_ml1->setGeometry(518, 622, 100, 30);
    ui->lb_autotestpt_ml1->setText(m_ptc->toUnicode("mL"));
    ui->lb_autotestpt_ml1->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotestpt_mol->setGeometry(241, 622, 100, 30);
    ui->lb_autotestpt_mol->setText(m_ptc->toUnicode("mol/L"));
    ui->lb_autotestpt_mol->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotestpt_ml2->setGeometry(521, 560, 100, 30);
    ui->lb_autotestpt_ml2->setText(m_ptc->toUnicode("mL"));
    ui->lb_autotestpt_ml2->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
    ui->lb_autotestpt_ml2->hide();

    ui->lb_autotestpt_ml3->setGeometry(521, 589, 100, 30);
    ui->lb_autotestpt_ml3->setText(m_ptc->toUnicode("mL"));
    ui->lb_autotestpt_ml3->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
    ui->lb_autotestpt_ml3->hide();

    ui->lb_autotestpt_ml4->setGeometry(521, 618, 100, 30);
    ui->lb_autotestpt_ml4->setText(m_ptc->toUnicode("mL"));
    ui->lb_autotestpt_ml4->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
    ui->lb_autotestpt_ml4->hide();

    ui->lb_autotestpt_didingtiji->setGeometry(63, 463, 260, 30);
    ui->lb_autotestpt_didingtiji->setText(m_ptc->toUnicode("滴定体积：0.0000ml"));
    ui->lb_autotestpt_didingtiji->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotestpt_jieguo->setGeometry(63, 417, 100, 30);
    ui->lb_autotestpt_jieguo->setText(m_ptc->toUnicode("结  果:"));
    ui->lb_autotestpt_jieguo->setStyleSheet("QLabel{background-color:transparent;font-size:18px}");

    ui->lb_autotestpt_jieguodanwei->setGeometry(171, 415, 300, 35);
    ui->lb_autotestpt_jieguodanwei->setText(m_ptc->toUnicode("0.0000"));
    ui->lb_autotestpt_jieguodanwei->setStyleSheet("QLabel{background-color:transparent;font-size:45px}");
    QPalette pa;
    pa.setColor(QPalette::WindowText, QColor(240, 130, 0));
    ui->lb_autotestpt_jieguodanwei->setPalette(pa);


    ui->lb_autotestpt_danweitype->setGeometry(351, 415, 300, 35);


    ui->lb_autotestpt_danweitype->setStyleSheet("QLabel{background-color:transparent;font-size:30px}");

    ui->lb_autotestpt_zhuangtai->setGeometry(63, 311, 300, 35);
    ui->lb_autotestpt_zhuangtai->setText(m_ptc->toUnicode(""));
    ui->lb_autotestpt_zhuangtai->setStyleSheet("QLabel{background-color:transparent;font-size:14px}");

    //label
    ui->label_shuju->setGeometry(28,9,111,36);
    ui->label_shuju->setText(m_ptc->toUnicode("实验数据"));
    ui->label_shuju->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_fangfa->setGeometry(28,518,111,36);
    ui->label_fangfa->setText(m_ptc->toUnicode("实验方法"));
    ui->label_fangfa->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_zhuangtai->setGeometry(600,9,111,36);
    ui->label_zhuangtai->setText(m_ptc->toUnicode("状态"));
    ui->label_zhuangtai->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_event->setGeometry(600,227,111,36);
    ui->label_event->setText(m_ptc->toUnicode("事件"));
    ui->label_event->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->textEdit_event->setGeometry(580,258,320, 131);
    ui->textEdit_event->setFocusPolicy(Qt::NoFocus);
    ui->textEdit_event->setStyleSheet("QTextEdit{background-color:transparent;font-size:17px}");

    ui->textEdit_Resualt->setGeometry(580,439,320, 131);
    ui->textEdit_Resualt->setFocusPolicy(Qt::NoFocus);
    ui->textEdit_Resualt->setStyleSheet("QTextEdit{background-color:transparent;font-size:17px}");

    ui->label_oldresualt->setGeometry(600,407,111,36);
    ui->label_oldresualt->setText(m_ptc->toUnicode("结果"));
    ui->label_oldresualt->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    //pr
    ui->pr_autotest_progressBar->setGeometry(60, 370, 450, 15);

    //bt
    ui->pb_autotestpt_back->setFlat(true);
    //ui->pb_autotestpt_back->setFocusPolicy(Qt::NoFocus);
    ui->pb_autotestpt_back->setGeometry(761,592,144,48);
    ui->pb_autotestpt_back->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_back_big_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_back_big_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_back_big_press.png);}");


    ui->pb_autotestpt_naoh->setFlat(true);
    //ui->pb_autotestpt_naoh->setFocusPolicy(Qt::NoFocus);
    ui->pb_autotestpt_naoh->setGeometry(579,592,144,48);
    ui->pb_autotestpt_naoh->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_naoh_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_naoh_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_naoh_press.png);}");

    ui->textEdit_Resualt->document()->setMaximumBlockCount(3);


}

void QAutoTestaProcessForm::InitSings()
{
/*
    QByteArray pData;
    pData.append(0X04);
    pData.append(0X01);
     float f;
     QString str;

     unsigned char j = (int)pData.at(0); //6
     unsigned int jj = (int)j;
     j = (int)pData.at(1);//7
     jj = jj << 8;
     jj = jj | j;
     f = (float)jj * (float)0.79;
     //str = QString(m_ptc->toUnicode("滴定体积：%1")).arg(f);
     //str = str + "ml";
     str = QString::number(f,'f', 4);
     str = m_ptc->toUnicode("滴定体积：") + str + "ml";
     ui->lb_autotestpt_didingtiji->setText(str);
*/
/*
    if(m_pdataTimer == NULL)
    {
        m_pdataTimer = new QTimer();
    }
*/
}

void QAutoTestaProcessForm::AnalysisData(QByteArray pData)
{
    int i = m_iIndex % 5;
    m_iIndex++;
    m_Buffer[i].clear();
    m_Buffer[i] = pData;

    //qDebug() << m_Buffer[i].toHex();
    unsigned char j = (int)m_Buffer[i].at(4);
    unsigned int jj = (int)j;
    j = (int)m_Buffer[i].at(5);
    jj = jj << 8;
    jj = jj | j;

    //qDebug() << QString("QAutoTestaProcessForm ReadThread back. %1").arg(jj);

    switch (jj) {
    case _SERIALCMD_MCU_START_:
        {
            qDebug("_SERIALCMD_MCU_START_");

            m_bRunning = true;
            QAutoTest *pAutoTest = static_cast<QAutoTest *>(this->parent());
            pAutoTest->SetState(m_bRunning);
        }
        break;
    case _SERIALCMD_MCU_NAOH_:
        {
           // qDebug("_SERIALCMD_MCU_NAOH_");
            QString str = m_ptc->toUnicode("执行加碱动作...");
            AutoScroll();
            ui->textEdit_event->insertPlainText(str + "\n");
        }
        break;
    case _SERIALCMD_MCU_STOP_:
        {
        //qDebug("_SERIALCMD_MCU_STOP_");
            //if(m_pProcessTimer->isActive())
            {
                m_pProcessTimer->stop();
                m_pRGBTimer->stop();
            }
            m_pStateTimer->stop();

            if(NULL != customPlot)
            {

            }
            m_bRunning = false;
            qDebug() << "m_bRunning = " << m_bRunning;
            QAutoTest *pAutoTest = static_cast<QAutoTest *>(this->parent());
            pAutoTest->SetState(m_bRunning);

            // 用户点击返回，同样保存数据
            CalNitrogen();
            SetToDataBase();


            this->close();
        }
        break;
    case _SERIALCMD_MCU_ASK_:
        StateProcess(m_Buffer[i]);
        break;
    case _SERIALCMD_MCU_ZHENGLIU:
        {
            StateRGB(m_Buffer[i]);
            //StateZhengliu(m_Buffer[i]);
        }
        break;
     case _SERIALCMD_MCU_STATE_:
        {
           //qDebug("QAutoTestaProcessForm _SERIALCMD_MCU_STATE_");
            StateSensor(m_Buffer[i]);
        }
        break;
        case _SERIALCMD_MCU_PAUSE_:
        {
/*
            qDebug() << "_SERIALCMD_MCU_PAUSE_";

            m_Serialcmd.clear();
            m_Serialdata.clear();
            m_Serialcmd.append(0x03);
            m_Serialcmd.append(0x07);
            m_pSerialAutopro->TransmitData(m_Serialcmd, m_Serialdata);


#ifdef      _MIPS_LINUX_ENV_
            QMessageBox::StandardButton rb  = QMessageBox::question(this, m_ptc->toUnicode("ERROR"), m_ptc->toUnicode("传感器异常,是否继续"), QMessageBox::Yes | QMessageBox::No);
            if(rb == QMessageBox::Yes)
            {
                m_Serialcmd.clear();
                m_Serialdata.clear();
                m_Serialcmd.append(0x03);
                m_Serialcmd.append(0x06);
                m_pSerialAutopro->TransmitData(m_Serialcmd, m_Serialdata);
            }

            if(rb == QMessageBox::No)
            {
                m_Serialcmd.clear();
                m_Serialdata.clear();
                m_Serialcmd.append(0x03);
                m_Serialcmd.append(0x02);
                m_pSerialAutopro->TransmitData(m_Serialcmd, m_Serialdata);
                on_pb_autotestpt_back_clicked();
            }
#endif
*/
        }
        break;
    default:
        break;
    }
}

void QAutoTestaProcessForm::StateProcess(QByteArray pData)
{
    //qDebug("StateProcess");
    int iProcess = 0;
    switch (pData[6]) {
    case _SERIALCMD_MCU_STATEPENGSUAN_:
        iProcess = 0;
        ui->lb_autotestpt_zhuangtai->setText(m_ptc->toUnicode("正在加硼酸..."));
        break;
    case _SERIALCMD_MCU_STATEXISHISHUI_:
        iProcess = 1;
        ui->lb_autotestpt_zhuangtai->setText(m_ptc->toUnicode("正在加稀释水..."));
        break;
    case _SERIALCMD_MCU_STATENAOH_:
        iProcess = 2;
        ui->lb_autotestpt_zhuangtai->setText(m_ptc->toUnicode("正在加碱..."));
        break;
    case _SERIALCMD_MCU_STATEZHENGLIU_:
        iProcess = 3;
        ui->lb_autotestpt_zhuangtai->setText(m_ptc->toUnicode("正在蒸馏..."));
        break;
    case _SERIALCMD_MCU_STATEDIDING_:
        iProcess = 4;
        ui->lb_autotestpt_zhuangtai->setText(m_ptc->toUnicode("正在滴定..."));
        break;
    case _SERIALCMD_MCU_STATEPAIFEI_:
        {
        if(0 == m_iprFlag)
        {
            iProcess = 5;
        }

        if(1 == m_iprFlag)
        {
            iProcess = 4;
        }
            ui->lb_autotestpt_zhuangtai->setText(m_ptc->toUnicode("正在排废..."));
            break;
        }
    case _SERIALCMD_MCU_STATEEND_:
    {
        if(0 == m_iprFlag)
        {
            iProcess = 6;
        }

        if(1 == m_iprFlag)
        {
            iProcess = 5;
        }
        ui->lb_autotestpt_zhuangtai->setText(m_ptc->toUnicode("实验结束"));
        m_pProcessTimer->stop();
        m_pRGBTimer->stop();
        m_bRunning = false;

        qDebug() << "m_bRunning = " << m_bRunning;
        QAutoTest *pAutoTest = static_cast<QAutoTest *>(this->parent());
        pAutoTest->SetState(m_bRunning);
        m_iIndex = 0;

        if(m_bback == true)
            break;

        CalNitrogen();
        SetToDataBase();

        QString result = ui->lb_autotestpt_jieguodanwei->text() + " " +
                ui->lb_autotestpt_danweitype->text();

        //static int index = 1;

        ui->textEdit_Resualt->append(result);
        break;
    }
    default:
        break;
    }
    ui->pr_autotest_progressBar->setValue(iProcess);
}

void QAutoTestaProcessForm::StateZhengliu(QByteArray pData)
{
 //   qDebug() << pData.toHex();
//    qDebug("_SERIALCMD_MCU_ZHENGLIU_FUN");
     float f;
     double d;
     QString str;
     QString str1;
     unsigned int j = 0;
     unsigned int jj = 0;

     j = (unsigned int)pData.at(6); //6
     jj = (unsigned int)j;
     j = (unsigned int)pData.at(7);//7
     jj = jj << 8;
     jj = jj | j;

     if(jj >= 65535)
     {
         return;
     }
    //str1 = "0.79";
     m_strV = QString::number(jj, 10);
     f = m_strV.toFloat();
     f = f / 1000;
     str = QString::number(f,'f', 4);
     str = m_ptc->toUnicode("滴定体积：") + str + "mL";
     ui->lb_autotestpt_didingtiji->setText(str);


}

void QAutoTestaProcessForm::StateRGB(QByteArray pData)
{
    //aa55000e83040000012c00b4cc33
    //qDebug() << pData.toHex();
    //qDebug("StateRGB");
    /*
    QString strData = QString(pData);


    char *pc1 = NULL;
    char *pc2 = NULL;

    unsigned int uih = 0;
    unsigned int uil = 0;


    strData = "aa55000e83040000012c00b4cc33";
    QString strH = strData.mid(16,2);
    pc1 = strH.toLatin1().data();
    uih1 = atoi(pc1);
    qDebug() << uih;

    QString strl = strData.mid(18, 2);
    pc2 = strl.toLatin1().data();
    uil = atoi(pc2);
    qDebug() << uil;

    double db = uih*256 + uil;

    if(db > 360)
    {
        qDebug() << db;
        return;
    }
    qDebug()<<"db" << db;
    AutoLine(db);
*/

     float f;
     double d;
     unsigned char c1;
     unsigned char c2;
     unsigned char c3;
     unsigned char c4;

     QString str;
     QString str1;
     unsigned int j = 0;
     unsigned int jj = 0;

     unsigned int i = 0;
     unsigned int ii = 0;

     unsigned char *pc = NULL;
    //pData.append("aa55000e83040000012c00b4cc33");
    //pc = (unsigned char *)pData.data();
    c1 = (unsigned char)pData.at(8);
   //qDebug() <<"0"<<c1;
    j  = c1 << 8;
    //qDebug() <<"1"<<j ;
    c2 = (unsigned char)pData.at(9);
    //qDebug() <<"2"<<c2;
    jj = j  + (unsigned int)c2;
    //qDebug() <<"3"<<jj;

    c3 = (unsigned char)pData.at(6);
   //qDebug() <<"0"<<c1;
    i  = c3 << 8;
    //qDebug() <<"1"<<j ;
    c4 = (unsigned char)pData.at(7);
    //qDebug() <<"2"<<c2;
    ii = i  + (unsigned int)c4;
    //qDebug() <<"3"<<jj;

    if(ii >= 65535)
    {
        return;
    }
   //str1 = "0.79";
    m_strV = QString::number(ii, 10);
    f = m_strV.toFloat();
    f = f / 1000;
    str = QString::number(f,'f', 4);
    m_didingV = str;
    str = m_ptc->toUnicode("滴定体积：") + str + "mL";
    ui->lb_autotestpt_didingtiji->setText(str);

    AutoLine(ii, jj);

    unsigned char cState = (unsigned char)pData.at(10);
    int istate = (unsigned int)cState;
    qDebug() <<"istate = "<<istate;
    if(0 == istate)
    {
#ifdef      _MIPS_LINUX_ENV_
            m_pRGBTimer->stop();
            double pause = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

            QMessageBox::StandardButton rb  = QMessageBox::question(this, m_ptc->toUnicode("ERROR"), m_ptc->toUnicode("传感器异常,是否继续"), QMessageBox::Yes | QMessageBox::No);
            if(rb == QMessageBox::Yes)
            {
                m_Serialcmd.clear();
                m_Serialdata.clear();
                m_Serialcmd.append(0x03);
                m_Serialcmd.append(0x06);
                m_pRGBTimer->start(1000);
                m_pausePointKey += QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0 - pause + 1;
                m_pSerialAutopro->TransmitData(m_Serialcmd, m_Serialdata);
            }

            if(rb == QMessageBox::No)
            {
                m_Serialcmd.clear();
                m_Serialdata.clear();
                m_Serialcmd.append(0x03);
                m_Serialcmd.append(0x02);
                m_pSerialAutopro->TransmitData(m_Serialcmd, m_Serialdata);
                //on_pb_autotestpt_back_clicked();
            }
#endif
    }

/*
     c1 =pc[8]; //8
     qDebug() <<"0"<<j;
     j = c1;
     qDebug() <<"1"<<j;
     jj = j;
     qDebug() <<"2"<<jj;
     c2 = pc[9];//9
     qDebug() <<"33"<<c2;
     j = c2;
     qDebug() <<"3"<<j;
     jj = jj << 8;
     qDebug() <<"4"<<jj;
     jj = jj | j;
     qDebug() <<"5"<<jj;
*/
/*
     qDebug() << pData.toHex();

     m_strV = QString::number(jj, 10);
     f = m_strV.toFloat();
     str = QString::number(f,'f', 4);
     qDebug() <<f;
     qDebug() <<str;

     if(jj >= 360)
     {
         qDebug() << pData.toHex();
         qDebug() <<"return";
         return;
     }
    //str1 = "0.79";

     AutoLine(f);
     */

    CalNitrogen();

}

void QAutoTestaProcessForm::StateSensor(QByteArray pData)
{
     unsigned int ibool = 0;
     unsigned char iNum;
     QString strNum;
     QString str;

     qDebug() << __func__ << pData.size();

     static QByteArray data = pData;

     for(int i = 6; i <= 18; i++)
     {
         if(i == 13 || i == 11 || i == 8)
             continue;

         if(pData[i] != data[i])
             break;

         if(i == 18)
             return;
     }

     if(pData[18] != data[18])
     {
         ibool = (unsigned int )pData[18];
         if(1 == ibool)
         {
             m_pLbfeiyetong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_feiyetong_press.png);}");
             AutoScroll();
             str= m_ptc->toUnicode("废液桶异常...");
             ui->textEdit_event->insertPlainText(str + "\n");
         }
         else
         {
             m_pLbfeiyetong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_feiyetong_normal.png);}");
         }
     }

     if(pData[17] != data[17])
     {
         ibool = (unsigned int )pData[17];
         if(1 == ibool)
         {
             m_pLbdidingsuantong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_didingsuantong_press.png);}");
             AutoScroll();
             str= m_ptc->toUnicode("滴定酸桶异常...");
             ui->textEdit_event->insertPlainText(str + "\n");
         }
         else
         {
             m_pLbdidingsuantong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_didingsuantong_normal.png);}");
         }
     }

     if(pData[15] != data[15])
     {
         ibool = (unsigned int )pData[15];
         if(1 == ibool)
         {
             m_pLbpengsuantong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_pengsuantong_press.png);}");
             AutoScroll();
             str= m_ptc->toUnicode("硼酸桶异常...");
             ui->textEdit_event->insertPlainText(str + "\n");
         }
         else
         {
             m_pLbpengsuantong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_pengsuantong_normal.png);}");
         }
     }

     if(pData[16] != data[16])
     {
         ibool = (unsigned int )pData[16];
         if(1 == ibool)
         {
             m_pLbjiantong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_jiantong_press.png);}");
             AutoScroll();
             str= m_ptc->toUnicode("碱桶异常...");
             ui->textEdit_event->insertPlainText(str + "\n");
         }
         else
         {
             m_pLbjiantong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_jiantong_normal.png);}");
         }
     }

     if(pData[14] != data[14])
     {
         ibool = (unsigned int )pData[14];
         if(1 == ibool)
         {
             m_pLbshuitong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_shuitong_press.png);}");
             AutoScroll();
             str= m_ptc->toUnicode("水桶异常...");
             ui->textEdit_event->insertPlainText(str + "\n");
         }
         else
         {
             m_pLbshuitong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_shuitong_normal.png);}");
         }
     }


     if(pData[9] != data[9])
     {
         ibool = (unsigned int )pData[9];
         if(1 == ibool)
         {
             m_pLblengningshui->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_lengningshui_press.png);}");
             AutoScroll();
             str= m_ptc->toUnicode("冷凝水异常...");
             ui->textEdit_event->insertPlainText(str + "\n");
         }
         else
         {
             m_pLblengningshui->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_lengningshui_normal.png);}");
         }
     }


     if(pData[12] != data[12])
     {
         ibool = (unsigned int )pData[12];
         if(1 == ibool)
         {
             m_pLbzhengqifashengqi->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_zhengqifashengqi_press.png);}");
             AutoScroll();
             str= m_ptc->toUnicode("蒸汽发生器异常...");
             ui->textEdit_event->insertPlainText(str + "\n");
         }
         else
         {
             m_pLbzhengqifashengqi->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_zhengqifashengqi_normal.png);}");

         }
     }

     if(pData[10] != data[10])
     {
         ibool = (unsigned int )pData[10];
         if(1 == ibool)
         {
             m_pLbzhengqifashengqiyewei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_zhengqifashengqiyewei_press.png);}");
             AutoScroll();
             str= m_ptc->toUnicode("蒸汽发生器液位异常...");
             ui->textEdit_event->insertPlainText(str + "\n");
         }
         else
         {
             m_pLbzhengqifashengqiyewei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_zhengqifashengqiyewei_normal.png);}");
         }
     }

     if(pData[6] != data[6])
     {
         ibool = (unsigned int )pData[6];
         if(1 == ibool)
         {
             m_pLbanquanmen->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_anquanmen_press.png);}");
             AutoScroll();
             str= m_ptc->toUnicode("安全门异常...");
             ui->textEdit_event->insertPlainText(str + "\n");
         }
         else
         {
             m_pLbanquanmen->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_anquanmen_normal.png);}");
         }
     }

     if(pData[7] != data[7])
     {
         ibool = (unsigned int )pData[7];
         if(1 == ibool)
         {
             m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_xiaohuaguan_press.png);}");
             AutoScroll();
             str= m_ptc->toUnicode("消化管异常...");
             ui->textEdit_event->insertPlainText(str + "\n");
         }
         else
         {
             m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_xiaohuaguan_normal.png);}");
         }
     }

     data = pData;

     iNum = pData[12];
     strNum = QString::number(iNum, 10);
     strNum = strNum + m_ptc->toUnicode("℃");
     ui->label_wendu1->setText(strNum);

     iNum = pData[10];
     strNum = QString::number(iNum, 10);
     strNum = strNum + m_ptc->toUnicode("℃");
     ui->label_wendu2->setText(strNum);
     /*
     QMessageBox::warning(this, m_ptc->toUnicode("ERROR"), m_ptc->toUnicode("传感器异常"), QMessageBox::Ok);
     m_Serialcmd.clear();
     m_Serialdata.clear();
     m_Serialcmd.append(0x03);
     m_Serialcmd.append(0x02);
     m_pSerialProtcol->TransmitData(m_Serialcmd, m_Serialdata);
     */
     //QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode(""), QMessageBox::Ok);
}

void QAutoTestaProcessForm::SerialCal()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x03);
    m_Serialcmd.append(0x03);
    m_pSerialAutopro->TransmitData(m_Serialcmd, m_Serialdata);
/*
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x03);
    m_Serialcmd.append(0x04);
    m_pSerialAutopro->TransmitData(m_Serialcmd, m_Serialdata);
    */
}

void QAutoTestaProcessForm::RGBState()
{
    //qDebug() << "RGBState";
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x03);
    m_Serialcmd.append(0x04);
    m_pSerialAutopro->TransmitData(m_Serialcmd, m_Serialdata);
}

void QAutoTestaProcessForm::StateShow()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x08);
    m_Serialcmd.append(0x01);
    m_pSerialAutopro->TransmitData(m_Serialcmd, m_Serialdata);
}

void QAutoTestaProcessForm::CalNitrogen()
{
    float ffangfaxishu = 0.0;
    float fsuannongdu = 0.0;
    float fkongbaitiji = 0.0;
    float fyangpinliang = 0.0;
    float fdanbaixishu = 0.0;
    float ftiji = 0.0;
    float f = 0.0;
    QString str = "";

    QAutoTest *pAutoTest = static_cast<QAutoTest *>(this->parent());
    QMainScreen *pWidget = static_cast<QMainScreen *>(pAutoTest->parent());

    QSettings set;
    int value = set.value("Machine/fangfaxishu").toInt();
    if(value == 0)
        ffangfaxishu = 1.401;
    else
        ffangfaxishu = 1.400;

    //ffangfaxishu = pWidget->m_machinesetting.m_strffangfaxishu.toFloat();
    //qDebug() << "m_strffangfaxishu" << pWidget->m_machinesetting.m_strffangfaxishu;
    pline() << "计算蛋白含量 方法系数="  << ffangfaxishu;

    fsuannongdu = pAutoTest->m_pListTestData.at(0)->m_fdiding;
    fkongbaitiji = pAutoTest->m_pListTestData.at(0)->m_fEmptyvolum;
    fyangpinliang = pAutoTest->m_pListTestData.at(0)->m_fSampleNumber;
    fdanbaixishu = pAutoTest->m_pListTestMethod.at(0)->m_idanbaixishu;
    ftiji = m_strV.toFloat();
    ftiji = ftiji/1000;
    QCalBase acal;

    switch(pAutoTest->m_pListTestData.at(0)->m_enumResualtType)
    {
    case _enum_Resualtml:
    {
        f = acal.Calml(ftiji);
    }
        break;
    case _enum_Nitrongen:
    {
        qDebug() << ffangfaxishu << fsuannongdu << ftiji << fkongbaitiji << fyangpinliang;
        f = acal.CalNitrongen(ffangfaxishu, fsuannongdu, ftiji, fkongbaitiji, fyangpinliang);
        qDebug() << f;
    }
        break;
    case _enum_mgNkg:
    {
        f = acal.CalmgNKg(ffangfaxishu, fsuannongdu, ftiji, fkongbaitiji, fyangpinliang);
    }
        break;
    case _enum_mgNg:
    {
        f = acal.CalmgNg(ffangfaxishu, fsuannongdu, ftiji, fkongbaitiji, fyangpinliang);
    }
        break;
    case _enum_mgNH3kg:
    {  // f1 ????
        f = acal.CalmgNH3Kg(ffangfaxishu, fsuannongdu, ftiji, fkongbaitiji, fyangpinliang);
    }
        break;
    case _enum_mgN:
    {
        f = acal.CalmgN(ffangfaxishu, fsuannongdu, ftiji, fkongbaitiji);
    }
        break;
    case _enum_mgNml:
    {
        f = acal.CalmgNml(ffangfaxishu, fsuannongdu, ftiji, fkongbaitiji, fyangpinliang);
    }
        break;
    case _enum_mgN100ml:
    {
        f = acal.CalmgN100ml(ffangfaxishu, fsuannongdu, ftiji, fkongbaitiji, fyangpinliang);
    }
        break;
    case _enum_XRecovery:
    {
        f = acal.CalXrecovery(fsuannongdu, ftiji, fkongbaitiji);
    }
        break;
    case _enum_XPreotein:
    {
        //f6 ???
        f = acal.CalXProtein(ffangfaxishu, fsuannongdu, ftiji, fkongbaitiji, fyangpinliang, fdanbaixishu);
    }
        break;
    case _enum_mgPreotein:
    {   //????
        f = acal.CalmgProtein(ffangfaxishu, fsuannongdu, ftiji, fkongbaitiji, fdanbaixishu);
    }
        break;
    case _enum_mgN100g:
    {
        //????
        f = acal.CalmgN100g(ffangfaxishu, fsuannongdu, ftiji, fkongbaitiji, fyangpinliang);
    }
        break;
    case _enum_gNkg:
    {
        f = acal.CalgNKg(ffangfaxishu, fsuannongdu, ftiji, fkongbaitiji, fyangpinliang);
    }
        break;
    default:
        break;
    }
    pline() << f;
    if(f < 0)
        f = 0;
    str = QString::number(f,'f', 4);
    //str = str + "ml";
    qDebug() << str;
    ui->lb_autotestpt_jieguodanwei->setText(str);
    switch(pAutoTest->m_pListTestData.at(0)->m_enumResualtType)
    {
    case _enum_Resualtml:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("mL"));
        break;
    case _enum_Nitrongen:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("% Nitrogen"));
        break;
    case _enum_mgNkg:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("mg N/Kg"));
        break;
    case _enum_mgNg:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("mg N/g"));
        break;
    case _enum_mgNH3kg:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("mg NH3/Kg"));
        break;
    case _enum_mgN:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("mg N"));
        break;
    case _enum_mgNml:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("mg N/mL"));
        break;
    case _enum_mgN100ml:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("mg N/100mL"));
        break;
    case _enum_XRecovery:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("% Recovery"));
        break;
    case _enum_XPreotein:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("% Protein"));
        break;
    case _enum_mgPreotein:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("mg Protein"));
        break;
    case _enum_mgN100g:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("mg N/100g"));
        break;
    case _enum_gNkg:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("g N/Kg"));
        break;
    default:
        break;
    }
}

void QAutoTestaProcessForm::AutoScroll()
{
    QTextCursor cursor = ui->textEdit_event->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit_event->setTextCursor(cursor);
}

void QAutoTestaProcessForm::InitSerial()
{
    if(NULL == m_pSerialAutopro)
    {

        if(NULL == m_pProcessTimer)
        {
           m_pProcessTimer = new QTimer();
        }

        if(NULL == m_pRGBTimer)
        {
           m_pRGBTimer = new QTimer();
        }

        if(NULL == m_pStateTimer)
        {
            m_pStateTimer = new QTimer();

        }

        //
        QAutoTest *pWidget = static_cast<QAutoTest *>(this->parent());
        m_pSerialAutopro = pWidget->m_pSerialAuto;
        connect(m_pSerialAutopro->m_pReadThread, SIGNAL(emitReadData(QByteArray)),this, SLOT(AnalysisData(QByteArray)));

        connect(m_pProcessTimer,SIGNAL(timeout()),this,SLOT(SerialCal()));
        connect(m_pRGBTimer,SIGNAL(timeout()),this,SLOT(SerialCal()));
        connect(m_pRGBTimer,SIGNAL(timeout()),this,SLOT(RGBState()));
        connect(m_pStateTimer,SIGNAL(timeout()),this,SLOT(StateShow()));
    }

    m_bback = false;
    m_initPointKey = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    m_lastPointKey = m_initPointKey;
    m_pausePointKey = 0;
}


void QAutoTestaProcessForm::on_pb_autotestpt_back_clicked()
{
   //m_pdataTimer->stop();
    qDebug() << "m_bRunning = " << m_bRunning;

    if(true == m_bRunning)
    {
        int rb  = QMessageBox::question(this, m_ptc->toUnicode(""), m_ptc->toUnicode("数据未保存，是否退出？"), QMessageBox::Yes | QMessageBox::No);
        pline() << rb;
        if(rb == QMessageBox::Yes)
        {
            m_dIndex = 0;
            m_bIsFirst = true;
            m_Serialcmd.clear();
            m_Serialdata.clear();
            m_Serialcmd.append(0x03);
            m_Serialcmd.append(0x02);
            m_pSerialAutopro->TransmitData(m_Serialcmd, m_Serialdata);
            m_bback = true;

            //debug
            //CalNitrogen();
            //SetToDataBase();

        }

        if(rb == QMessageBox::No)
        {
            return;
        }

    }
    else
    {
        m_dIndex = 0;
        m_bIsFirst = true;
        m_bRunning = false;
        QAutoTest *pAutoTest = static_cast<QAutoTest *>(this->parent());
        pAutoTest->SetState(m_bRunning);
        m_Serialcmd.clear();
        m_Serialdata.clear();
        this->close();
    }
    QAutoTest *pAutoTest = static_cast<QAutoTest *>(this->parent());
    if(true == pAutoTest->m_bpiciFlag)
    {
       pAutoTest->UpData();
    }

    this->close();
    pAutoTest->setFocus();
}

void QAutoTestaProcessForm::on_pb_autotestpt_naoh_clicked()
{

    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x03);
    m_Serialcmd.append(0x01);
    m_pSerialAutopro->TransmitData(m_Serialcmd, m_Serialdata);
/*
    for(int i =0; i < 360; i++)
    {
        sleep(1);
        realtimeData(i, i/2);
    }
*/
}

void QAutoTestaProcessForm::SetTextdata()
{
    QAutoTest *pAutoTest = static_cast<QAutoTest *>(this->parent());
    ui->lb_autotestpt_jieguodanwei->setText(m_ptc->toUnicode("0.0000"));
    ui->textEdit_event->clear();
    switch(pAutoTest->m_pListTestData.at(pAutoTest->m_iIndex-1)->m_enumResualtType)
    {
    case _enum_Resualtml:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("mL"));
        break;
    case _enum_Nitrongen:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("% Nitrogen"));
        break;
    case _enum_mgNkg:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("mg N/Kg"));
        break;
    case _enum_mgNg:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("mg N/g"));
        break;
    case _enum_mgNH3kg:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("mg NH3/Kg"));
        break;
    case _enum_mgN:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("mg N"));
        break;
    case _enum_mgNml:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("mg N/mL"));
        break;
    case _enum_mgN100ml:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("mg N/100mL"));
        break;
    case _enum_XRecovery:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("% Recovery"));
        break;
    case _enum_XPreotein:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("% Protein"));
        break;
    case _enum_mgPreotein:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("mg Protein"));
        break;
    case _enum_mgN100g:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("mg N/100g"));
        break;
    case _enum_gNkg:
        ui->lb_autotestpt_danweitype->setText(m_ptc->toUnicode("g N/Kg"));
        break;
    default:
        break;
    }
}

/*
void QAutoTestaProcessForm:: realtimeDataSlot(double v0, double v1)
{
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  double key = 0;
#else
  double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
#endif

  static double lastPointKey = 0;
  if (key-lastPointKey > 0.01) // at most add point every 10 ms
  {
    double value0 = random() %360;
    double value1 = random() %360;
    //qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
    //double value1 = qCos(key); //qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;
    // add data to lines:
    if(m_bIsFirst == true)
    {
        m_bIsFirst = false;
        customPlot->graph(0)->addData(key, 360);
    }
    customPlot->graph(0)->addData(key, value0);
    customPlot->graph(0)->rescaleValueAxis();

    customPlot->graph(1)->addData(key, value1);
    customPlot->graph(1)->rescaleValueAxis();
    //customPlot->axisRect()->setupFullAxesBox();

    lastPointKey = key;
  }

  // make key axis range scroll with the data (at a constant range size of 8):
  customPlot->xAxis->setRange(key+1, 8, Qt::AlignRight);
  customPlot->replot();
}
*/

void QAutoTestaProcessForm:: realtimeData(double v0, double v1)
{
  m_dIndex++;
  customPlot->graph(0)->addData(m_dIndex, v0);
  customPlot->graph(1)->addData(m_dIndex, v1);
  if(m_dIndex > 60)
  {
    customPlot->xAxis->setRange(0, m_dIndex+20, Qt::AlignLeft);
  }
  customPlot->replot();
}

void QAutoTestaProcessForm::InitDiagram()
{
    if(NULL != customPlot)
    {
        customPlot->clearGraphs();
        customPlot->close();
        delete customPlot;
        customPlot = NULL;
    }

/*
    if(NULL != pWheelUp)
    {
        delete pWheelUp;
        pWheelUp = NULL;
    }

    pWheelUp = new QEvent(QEvent::Wheel);

    if(NULL != pWheelDown)
    {
        delete pWheelDown;
        pWheelDown = NULL;
    }

    pWheelDown = new QEvent(QEvent::Wheel);
*/
    if(NULL == customPlot)
    {
       customPlot = new QCustomPlot(this);
       customPlot->setInteractions(QCP::iRangeZoom);
       customPlot->setGeometry(10, 45, 530, 320);
/*
       customPlot->addGraph(); // blue line
       customPlot->graph(0)->setPen(QPen(QColor(240, 130, 0)));
       //customPlot->graph(0)->setBrush(QBrush(QColor(240, 130, 0)));
       customPlot->graph(0)->setAntialiasedFill(false);

       customPlot->addGraph(); // blue line
       customPlot->graph(1)->setPen(QPen(QColor(255,255, 255)));
       //customPlot->graph(0)->setBrush(QBrush(QColor(240, 130, 0)));
       customPlot->graph(1)->setAntialiasedFill(false);
*/
       customPlot->xAxis->setTickStep(2);
       customPlot->xAxis->setRange(0,60);
       customPlot->xAxis->setLabel(m_ptc->toUnicode("时间"));

       customPlot->yAxis->setRange(0, 360);
       customPlot->yAxis->setBasePen(QPen(Qt::blue));
       customPlot->yAxis->setLabel(m_ptc->toUnicode("颜色"));

       customPlot->yAxis2->setVisible(true);
       customPlot->yAxis2->setRange(0, 30);
       customPlot->yAxis2->setBasePen(QPen(Qt::red));
       customPlot->yAxis2->setLabel(m_ptc->toUnicode("体积"));

       customPlot->addGraph(customPlot->xAxis, customPlot->yAxis); // blue line

       customPlot->graph(0)->setPen(QPen(Qt::blue));
       customPlot->graph(0)->setAntialiasedFill(false);


       customPlot->addGraph(customPlot->xAxis, customPlot->yAxis2); // red line
       customPlot->graph(1)->setPen(QPen(Qt::red));
       customPlot->graph(1)->setAntialiasedFill(false);
       //customPlot->graph(1)->setChannelFillGraph(customPlot->graph(1));
/*
       customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
       customPlot->xAxis->setDateTimeFormat("mm:ss");
       customPlot->xAxis->setAutoTickStep(false);
       customPlot->xAxis->setTickStep(2);
*/



       //customPlot->axisRect()->setupFullAxesBox();
       //customPlot->setBackgroundScaled(true);
       //customPlot->setBackgroundScaledMode(Qt::KeepAspectRatio);
    }

    m_dIndex = 0;
}
void QAutoTestaProcessForm::AutoLine(double dLineV, double dlineColor)
{
/*
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  double key = 0;
#else
  double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
#endif

  static double lastPointKey = 0;
  if (key-lastPointKey > 0.01) // at most add point every 10 ms
  {
    double value0 = dLineV;
    double value1 = dlineColor;
    customPlot->graph(0)->addData(key, value0);
    customPlot->graph(1)->addData(key, value1);
    lastPointKey = key;
  }

  // make key axis range scroll with the data (at a constant range size of 8):
  customPlot->xAxis->setRange(key+1, 8, Qt::AlignRight);
  customPlot->replot();
  */
    qDebug() << "dLineV = " << dLineV;
    dLineV = dLineV / 1000;
    qDebug() << "dLineV1 = " << dLineV;
    m_dIndex++;
    int key = m_lastPointKey - m_initPointKey - m_pausePointKey;
    pline() << m_lastPointKey << m_initPointKey;
    pline() << m_pausePointKey << key;
    customPlot->graph(0)->addData(key, dlineColor);
    customPlot->graph(1)->addData(key, dLineV);
    if(key > 60)
    {
      //customPlot->xAxis->setTickStep(5);
      customPlot->xAxis->setRange(0, key+20, Qt::AlignLeft);
    }
    customPlot->replot();
    m_lastPointKey = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
}

bool QAutoTestaProcessForm::GetState()
{
    return m_bRunning;
}


void QAutoTestaProcessForm::SetToDataBase()
{
    if(true == pdataquery->opendatabase())
    {

        linstname.clear();
        linstvalues.clear();
        linstname.append(m_ptc->toUnicode("Name"));
        linstname.append(m_ptc->toUnicode("Index0"));
        linstname.append(m_ptc->toUnicode("Dos"));
        linstname.append(m_ptc->toUnicode("ML"));
        linstname.append(m_ptc->toUnicode("Result"));
        linstname.append(m_ptc->toUnicode("RML"));
        linstname.append(m_ptc->toUnicode("Tester"));
        linstname.append(m_ptc->toUnicode("Time"));

        linstname.append(m_ptc->toUnicode("M_ID"));
        linstname.append(m_ptc->toUnicode("EmptyV"));
        linstname.append(m_ptc->toUnicode("DidingC"));
        linstname.append(m_ptc->toUnicode("Zhushi"));
        linstname.append(m_ptc->toUnicode("DidingV"));

        QAutoTest *pAutoTest = static_cast<QAutoTest *>(this->parent());
        qint64 id = pAutoTest->m_pListTestMethod.at(0)->m_id;
        float emtv = pAutoTest->m_pListTestData.at(0)->m_fEmptyvolum;
        float didingc = pAutoTest->m_pListTestData.at(0)->m_fdiding;
        QString beizhu = pAutoTest->m_pListTestData.at(0)->m_strNote;


       // linstvalues.append(m_ptc->toUnicode("1"));
        QString strYangpinName = ui->label_name->text();
        linstvalues.append(strYangpinName);
        QString strPihao    = ui->label_yangpinpihao->text();
        linstvalues.append(strPihao);
        QString stryangpinliang = ui->label_yangpinliang->text();
        linstvalues.append(stryangpinliang);
        QString stryangpinliangdanwei = ui->label_yangpinliangdanwei->text();
        linstvalues.append(stryangpinliangdanwei);
        QString strResualt = ui->lb_autotestpt_jieguodanwei->text();
        linstvalues.append(strResualt);
        QString strDanweiType = ui->lb_autotestpt_danweitype->text();
        linstvalues.append(strDanweiType);
        QAutoTest *p = (QAutoTest *) this->parent();
        QString strname =  p->GetUserName();
        linstvalues.append(strname);
        QDateTime dt = QDateTime::currentDateTime();
        QString strDate =  dt.toString("yyyy-MM-dd hh:mm:ss");
        linstvalues.append(strDate);
        QString strMethod =  QString::number(id);
        linstvalues.append(strMethod);
        QString strEmptyv =  QString::number(emtv);
        linstvalues.append(strEmptyv);
        QString stringDiding =  QString::number(didingc);
        linstvalues.append(stringDiding);

        if(m_bback)
            beizhu += "实验未完成";

        linstvalues.append(beizhu);

        linstvalues.append(m_didingV);


        pdataquery->insert(strtable, linstname, linstvalues);

        pdataquery->cloesdatabase();

        //HNCreateSysEvent("插入样品结果");
    }
}
