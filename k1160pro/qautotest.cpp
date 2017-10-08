#include <QMessageBox>
#include "qmainscreen.h"
#include "qautotest.h"
#include "qinputtool.h"
#include "ui_qautotest.h"

QAutoTest::QAutoTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QAutoTest),
    m_pTestPro(NULL),
    m_pPici(NULL),
    m_bpiciFlag(false),
    m_pSerialAuto(NULL),
    m_iIndex(1),
    pdataquery(NULL),
    strtable("method"),
    m_bRunFlag(false)
{
    ui->setupUi(this);
    m_ptc =  QTextCodec::codecForName("UTF-8");
    InitOCX();
    InitOCXData();
    InitComboxData();
    InitSings();

    QSettings set;
    QString emptyv = set.value("R0/emptyv", "0").toString();
    ui->ed_autotest_tiji->setText(emptyv);

    QString diding = set.value("R0/diding", "0").toString();
    ui->ed_autotest_nongdu->setText(diding);

    QString name = set.value("R0/name", "").toString();
    ui->ed_autotest_name->setText(name);

    QString pihao = set.value("R0/pihao", "001").toString();
    ui->ed_autotest_pihao->setText(pihao);

    int ceshileixing = set.value("R0/ceshileixing", 0).toInt();
    ui->cb_autotest_ceshileixing->setCurrentIndex(ceshileixing);

    QString yangpinliang = set.value("R0/yangpinliang", "0").toString();
    ui->ed_autotest_yangpinliang->setText(yangpinliang);

    int yangpinliangdanwei = set.value("R0/yangpinliangdanwei", 0).toInt();
    ui->cb_autotest_yangpinliang->setCurrentIndex(yangpinliangdanwei);

    int jieguoleixing = set.value("R0/jieguoleixing", 0).toInt();
    ui->cb_autotest_jieguoleixing->setCurrentIndex(jieguoleixing);

    QString note = set.value("R0/note", "").toString();
    ui->ed_autotest_beizhu->setText(note);

    if(NULL == m_pSerialAuto)
    {
        QMainScreen *pWidget = static_cast<QMainScreen *>(this->parent());
        m_pSerialAuto = pWidget->m_pSerialProtcol;
        connect(m_pSerialAuto->m_pReadThread, SIGNAL(emitReadData(QByteArray)),this, SLOT(AnalysisData(QByteArray)));
    }


    pdataquery = new QDatabasequery();
    pdataquery->SetTableName("./db/Method/method");
    linstvalues.clear();
    pdataquery->opendatabase();
    pdataquery->GetValues(strtable, linstvalues, 1);
    pdataquery->cloesdatabase();
    for(int i = 0; i < linstvalues.size(); i++)
    {
        ui->cb_autotest_fangfamingcheng->addItem(linstvalues.at(i));
    }
    int id = set.value("R0/mindex", 0).toInt();
    ui->cb_autotest_fangfamingcheng->setCurrentIndex(id);
}

QAutoTest::~QAutoTest()
{
    delete ui;
}


void QAutoTest::AnalysisData(QByteArray pData)
{
    //qDebug() << m_Buffer[i].toHex();
    unsigned char j = (int)pData.at(4);
    unsigned int jj = (int)j;
    j = (int)pData.at(5);
    jj = jj << 8;
    jj = jj | j;

    switch (jj) {
    case _SERIALCMD_MCU_START_:
    {
        qDebug("_SERIALCMD_MCU_START_");
    }
        break;
    case _SERIALCMD_MCU_NAOH_:
    {
    }
        break;
    case _SERIALCMD_MCU_STOP_:
    {
    }
        break;
    case _SERIALCMD_MCU_ASK_:

        break;
    case _SERIALCMD_MCU_ZHENGLIU:
    {
    }
        break;
    case _SERIALCMD_MCU_STATE_:
    {
        qDebug("0000 QAutoTestaProcessForm _SERIALCMD_MCU_STATE_");
        StateSensor(pData);
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


void QAutoTest::StateSensor(QByteArray pData)
{
    unsigned int ibool = 0;
    unsigned char iNum;
    QString strNum;
    QString str;

    qDebug() << __func__ << pData.size();

    ibool = (unsigned int )pData[18];


    if(1 == ibool)
    {
        m_pLbfeiyetong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_feiyetong_press.png);}");
    }
    else
    {
        m_pLbfeiyetong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_feiyetong_normal.png);}");
    }

    ibool = (unsigned int )pData[17];
    if(1 == ibool)
    {
        m_pLbdidingsuantong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_didingsuantong_press.png);}");
    }
    else
    {
        m_pLbdidingsuantong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_didingsuantong_normal.png);}");
    }

    ibool = (unsigned int )pData[15];
    if(1 == ibool)
    {
        m_pLbpengsuantong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_pengsuantong_press.png);}");
    }
    else
    {
        m_pLbpengsuantong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_pengsuantong_normal.png);}");
    }

    ibool = (unsigned int )pData[16];
    if(1 == ibool)
    {
        m_pLbjiantong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_jiantong_press.png);}");
    }
    else
    {
        m_pLbjiantong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_jiantong_normal.png);}");
    }

    ibool = (unsigned int )pData[14];
    if(1 == ibool)
    {
        m_pLbshuitong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_shuitong_press.png);}");
    }
    else
    {
        m_pLbshuitong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_shuitong_normal.png);}");
    }


    ibool = (unsigned int )pData[9];
    if(1 == ibool)
    {
        m_pLblengningshui->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_lengningshui_press.png);}");
    }
    else
    {
        m_pLblengningshui->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_lengningshui_normal.png);}");
    }

    ibool = (unsigned int )pData[12];
    if(1 == ibool)
    {
        m_pLbzhengqifashengqi->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_zhengqifashengqi_press.png);}");
    }
    else
    {
        m_pLbzhengqifashengqi->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_zhengqifashengqi_normal.png);}");

    }

    ibool = (unsigned int )pData[10];
    if(1 == ibool)
    {
        m_pLbzhengqifashengqiyewei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_zhengqifashengqiyewei_press.png);}");
    }
    else
    {
        m_pLbzhengqifashengqiyewei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_zhengqifashengqiyewei_normal.png);}");
    }

    ibool = (unsigned int )pData[6];
    if(1 == ibool)
    {
        m_pLbanquanmen->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_anquanmen_press.png);}");
    }
    else
    {
        m_pLbanquanmen->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_anquanmen_normal.png);}");
    }

    ibool = (unsigned int )pData[7];
    if(1 == ibool)
    {
        m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_xiaohuaguan_press.png);}");
    }
    else
    {
        m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_xiaohuaguan_normal.png);}");
    }

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

void QAutoTest::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("QWidget#QAutoTest{image:url(:/images/bk/bk_autotest.png)}""QAutoTest{background-color:transparent;}");
    //this->setStyleSheet("QWidget#QAutoTest{image:url(:/images/bk/keyboardg.png)}");
    //edit
    ui->ed_autotest_name->setMaxLength(26);

    int y = 54;
    int dy = 38;
    int ddy = 2;

    ui->label_methodid->hide();
    ui->label_methodname->hide();;

    //ui->ed_autotest_name->setFocusPolicy(Qt::NoFocus);
    ui->ed_autotest_name->setGeometry(145, y + dy * 0,291, 35);
    ui->ed_autotest_name->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");
    //ui->ed_autotest_name->setStyleSheet("QLineEdit{background-color:transparent;}""font-size:17px}");


    ui->ed_autotest_pihao->setGeometry(145, y + dy * 1, 291, 35);
    ui->ed_autotest_pihao->setMaxLength(26);
    //ui->ed_autotest_pihao->setFocusPolicy(Qt::NoFocus);
    ui->ed_autotest_pihao->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");
    //ui->ed_autotest_pihao->setStyleSheet("QLineEdit{background-color:transparent;}""font-size:17px}");

    ui->cb_autotest_ceshileixing->setGeometry(148, y + dy * 2 + ddy, 285, 31);
    ui->cb_autotest_ceshileixing->setStyleSheet("QComboBox{border:2px solid #D7D7D7;border-radius: 4px;}"
                                                "QComboBox QAbstractItemView::item{height:50px;}"
                                                "QComboBox::down-arrow{image:url(:/images/bt/arrowdownBo.png);}"
                                                "QComboBox::drop-down{border:0px;}");
    ui->cb_autotest_ceshileixing->setView(new QListView());

    ui->ed_autotest_yangpinliang->setGeometry(145, y + dy * 3, 188, 35);
    //ui->ed_autotest_yangpinliang->setFocusPolicy(Qt::NoFocus);
    ui->ed_autotest_yangpinliang->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line.png);font-size:17px}");

    ui->cb_autotest_yangpinliang->setGeometry(333, y + dy * 3 + ddy, 101, 31);
    ui->cb_autotest_yangpinliang->setStyleSheet("QComboBox{border:2px solid #D7D7D7;border-radius: 4px;}"
                                                "QComboBox QAbstractItemView::item{height:50px;}"
                                                "QComboBox::down-arrow{image:url(:/images/bt/arrowdownBo.png);}"
                                                "QComboBox::drop-down{border:0px;}");
    ui->cb_autotest_yangpinliang->setView(new QListView());

    ui->cb_autotest_jieguoleixing->setGeometry(148, y + dy * 4 + ddy, 285, 31);
    ui->cb_autotest_jieguoleixing->setStyleSheet("QComboBox{border:2px solid #D7D7D7;border-radius: 4px;}"
                                                 "QComboBox QAbstractItemView::item{height:50px;}"
                                                 "QComboBox::down-arrow{image:url(:/images/bt/arrowdownBo.png);}"
                                                 "QComboBox::drop-down{border:0px;}");
    ui->cb_autotest_jieguoleixing->setView(new QListView());



    ui->ed_autotest_tiji->setGeometry(145, y + dy * 5,291, 35);
    //ui->ed_autotest_tiji->setFocusPolicy(Qt::NoFocus);
    ui->ed_autotest_tiji->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");

    ui->ed_autotest_nongdu->setGeometry(145, y + dy * 6, 291, 35);
    //ui->ed_autotest_nongdu->setFocusPolicy(Qt::NoFocus);
    ui->ed_autotest_nongdu->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");

    ui->ed_autotest_beizhu->setMaxLength(26);
    ui->ed_autotest_beizhu->setGeometry(145, y + dy * 7, 291, 35);
    //ui->ed_autotest_beizhu->setFocusPolicy(Qt::NoFocus);
    ui->ed_autotest_beizhu->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");


    ui->lb_autotest_mingcheng->setGeometry(36, y + dy * 0, 100, 30);
    //ui->lb_autotest_mingcheng->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_mingcheng->setText(m_ptc->toUnicode("样品名称："));
    ui->lb_autotest_mingcheng->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_pihao->setGeometry(36, y + dy * 1, 120, 30);
    //ui->lb_autotest_pihao->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_pihao->setText(m_ptc->toUnicode("样品批号："));
    ui->lb_autotest_pihao->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_ceshileixing->setGeometry(36, y + dy * 2, 120, 30);
    //ui->lb_autotest_ceshileixing->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_ceshileixing->setText(m_ptc->toUnicode("测试类型："));
    ui->lb_autotest_ceshileixing->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_yangpinliang->setGeometry(36, y + dy * 3, 120, 30);
    //ui->lb_autotest_yangpinliang->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_yangpinliang->setText(m_ptc->toUnicode("样品量："));
    ui->lb_autotest_yangpinliang->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_jieguoleixing->setGeometry(36, y + dy * 4, 120, 30);
    //ui->lb_autotest_jieguoleixing->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_jieguoleixing->setText(m_ptc->toUnicode("结果类型："));
    ui->lb_autotest_jieguoleixing->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_tiji->setGeometry(36, y + dy * 5, 120, 30);
    //ui->lb_autotest_tiji->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_tiji->setText(m_ptc->toUnicode("空白体积："));
    ui->lb_autotest_tiji->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_nongdu->setGeometry(36, y + dy * 6, 120, 30);
    //ui->lb_autotest_nongdu->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_nongdu->setText(m_ptc->toUnicode("滴定酸浓度："));
    ui->lb_autotest_nongdu->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_mL->setGeometry(440, y + dy * 5, 20, 30);
    //ui->lb_autotest_mL->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_mL->setText(m_ptc->toUnicode("mL"));
    ui->lb_autotest_mL->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_mol->setGeometry(440, y + dy * 6, 60, 30);
    //ui->lb_autotest_ml0->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_mol->setText(m_ptc->toUnicode("mol/L"));
    ui->lb_autotest_mol->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_beizhu->setGeometry(36, y + dy * 7, 120, 30);
    //ui->lb_autotest_beizhu->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_beizhu->setText(m_ptc->toUnicode("备  注："));
    ui->lb_autotest_beizhu->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");



    //bt
    ui->pb_autotest_pici->setFlat(true);
    ui->pb_autotest_pici->setFocusPolicy(Qt::NoFocus);
    ui->pb_autotest_pici->setGeometry(442,53, 108,44);
    ui->pb_autotest_pici->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_pici_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_pici_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_pici_press.png);}");

    ui->pb_autotest_start->setFlat(true);
    ui->pb_autotest_start->setFocusPolicy(Qt::NoFocus);
    ui->pb_autotest_start->setGeometry(760,609, 145,49);
    ui->pb_autotest_start->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_start_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_start_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_start_press.png);}");

    //label
    ui->label_xuhao->setGeometry(600,222,111,36);
    //ui->label_xuhao->setFocusPolicy(Qt::NoFocus);
    ui->label_xuhao->setText(m_ptc->toUnicode("实验序号"));
    ui->label_xuhao->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_1->setGeometry(28,6,111,36);
    //ui->label_1->setFocusPolicy(Qt::NoFocus);
    ui->label_1->setText(m_ptc->toUnicode("实验数据"));
    ui->label_1->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_2->setGeometry(28,405,111,36);
    //ui->label_2->setFocusPolicy(Qt::NoFocus);
    ui->label_2->setText(m_ptc->toUnicode("实验方法"));
    ui->label_2->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_3->setGeometry(600,6,111,36);
    //ui->label_3->setFocusPolicy(Qt::NoFocus);
    ui->label_3->setText(m_ptc->toUnicode("状态"));
    ui->label_3->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");


    m_pLbxiaohuaguanpaifei = new QMLabel(this);
    //m_pLbxiaohuguan->setFocusPolicy(Qt::NoFocus);
    m_pLbxiaohuaguanpaifei->setGeometry( 447, 586, 62, 22);
    m_pLbxiaohuaguanpaifei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_yes.png);}");

    m_pLbjieshoubeipaifei = new QMLabel(this);
    //m_pLbjieshoubei->setFocusPolicy(Qt::NoFocus);
    m_pLbjieshoubeipaifei->setGeometry(447,614,62, 22);
    m_pLbjieshoubeipaifei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_no.png);}");


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

    ui->lb_autotest_fangfamingcheng->setGeometry(36, 455, 100, 30);
    //ui->lb_autotest_fangfamingcheng->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_fangfamingcheng->setText(m_ptc->toUnicode("方法名称："));
    ui->lb_autotest_fangfamingcheng->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->cb_autotest_fangfamingcheng->setGeometry(136, 455 + ddy, 287, 31);
    ui->cb_autotest_fangfamingcheng->setStyleSheet("QComboBox{border:2px solid #D7D7D7;border-radius: 4px;}"
                                                   "QComboBox QAbstractItemView::item{height:50px;}"
                                                   "QComboBox::down-arrow{image:url(:/images/bt/arrowdownBo.png);}"
                                                   "QComboBox::drop-down{border:0px;}");
    ui->cb_autotest_fangfamingcheng->setView(new QListView());

    ui->lb_autotest_danbaixishu->setGeometry(36, 499, 120, 30);
    //ui->lb_autotest_danbaixishu->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_danbaixishu->setText(m_ptc->toUnicode("蛋白系数："));
    ui->lb_autotest_danbaixishu->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->label_danbaixishu->setGeometry(126, 505, 111, 18);
    //ui->label_danbaixishu->setFocusPolicy(Qt::NoFocus);
    ui->label_danbaixishu->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");



    ui->lb_autotest_pengsuan->setGeometry(36, 527, 120, 30);
    //ui->lb_autotest_pengsuan->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_pengsuan->setText(m_ptc->toUnicode("硼酸："));
    ui->lb_autotest_pengsuan->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->label_pengsuan->setGeometry(126, 535, 111, 18);
    //ui->label_pengsuan->setFocusPolicy(Qt::NoFocus);
    ui->label_pengsuan->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_xishishui->setGeometry(36, 555, 120, 30);
    //ui->lb_autotest_xishishui->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_xishishui->setText(m_ptc->toUnicode("稀释水："));
    ui->lb_autotest_xishishui->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->label_xishishui->setGeometry(126, 561, 111, 18);
    //ui->label_xishishui->setFocusPolicy(Qt::NoFocus);
    ui->label_xishishui->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_jian->setGeometry(36, 583, 120, 30);
    //ui->lb_autotest_jian->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_jian->setText(m_ptc->toUnicode("碱："));
    ui->lb_autotest_jian->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->label_jian->setGeometry(126, 589, 111, 18);
    //ui->label_jian->setFocusPolicy(Qt::NoFocus);
    ui->label_jian->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");


    ui->lb_autotest_zhengliu->setGeometry(36, 611, 120, 30);
    //ui->lb_autotest_zhengliu->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_zhengliu->setText(m_ptc->toUnicode("蒸馏："));
    ui->lb_autotest_zhengliu->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->label_zhengliu->setGeometry(126, 617, 111, 18);
    //ui->label_zhengliu->setFocusPolicy(Qt::NoFocus);
    ui->label_zhengliu->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    /////
    ui->lb_autotest_didingfangshi->setGeometry(324, 499, 120, 30);
    //ui->lb_autotest_didingfangshi->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_didingfangshi->setText(m_ptc->toUnicode("滴定方式："));
    ui->lb_autotest_didingfangshi->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->label_didingfangshi->setGeometry(410, 505, 111, 18);
    //ui->label_didingfangshi->setFocusPolicy(Qt::NoFocus);
    ui->label_didingfangshi->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_jiajianfangshi->setGeometry(324, 527, 120, 30);
    //ui->lb_autotest_jiajianfangshi->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_jiajianfangshi->setText(m_ptc->toUnicode("加碱方式："));
    ui->lb_autotest_jiajianfangshi->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->label_jiajianfangshi->setGeometry(410, 533, 111, 18);
    //ui->label_jiajianfangshi->setFocusPolicy(Qt::NoFocus);
    ui->label_jiajianfangshi->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_zhengqiliuliang->setGeometry(324, 555, 120, 30);
    ui->lb_autotest_zhengqiliuliang->setText(m_ptc->toUnicode("蒸汽流量："));
    ui->lb_autotest_zhengqiliuliang->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->label_zhengqiliuliang->setGeometry(450, 560, 60, 18);
    ui->label_zhengqiliuliang->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_xiaohuaguanpaifei->setGeometry(324, 583, 120, 30);
    //ui->lb_autotest_xiaohuaguanpaifei->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_xiaohuaguanpaifei->setText(m_ptc->toUnicode("消化管排废："));
    ui->lb_autotest_xiaohuaguanpaifei->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_jieshoubeiqingxi->setGeometry(324, 610, 120, 30);
    ui->lb_autotest_jieshoubeiqingxi->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_jieshoubeiqingxi->setText(m_ptc->toUnicode("接收杯清洗："));
    ui->lb_autotest_jieshoubeiqingxi->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");


    ui->lb_autotest_ml1->setGeometry(292, 537, 20, 30);
    //ui->lb_autotest_ml1->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_ml1->setText(m_ptc->toUnicode("mL"));
    ui->lb_autotest_ml1->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_ml2->setGeometry(292, 558, 20, 30);
    //ui->lb_autotest_ml2->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_ml2->setText(m_ptc->toUnicode("mL"));
    ui->lb_autotest_ml2->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_ml3->setGeometry(292, 583, 20, 30);
    //ui->lb_autotest_ml3->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_ml3->setText(m_ptc->toUnicode("mL"));
    ui->lb_autotest_ml3->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_ml4->setGeometry(292, 611, 20, 30);
    //ui->lb_autotest_ml3->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_ml4->setText(m_ptc->toUnicode("mL"));
    ui->lb_autotest_ml4->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_autotest_baifnehao->setGeometry(480, 555, 20, 30);
    //ui->lb_autotest_baifnehao->setFocusPolicy(Qt::NoFocus);
    ui->lb_autotest_baifnehao->setText(m_ptc->toUnicode("%"));
    ui->lb_autotest_baifnehao->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    //combox




}

void QAutoTest::InitOCXData()
{
    QRegExp rx("^-?(100|1?[0-9]?\\d(\\.\\d{1,6})?)$");
    QRegExpValidator *pReg = new QRegExpValidator(rx, this);
    ui->ed_autotest_yangpinliang->setValidator(pReg);
    ui->ed_autotest_tiji->setValidator(pReg);
    ui->ed_autotest_nongdu->setValidator(pReg);
    //ui->ed_autotest_pihao->setValidator(new QIntValidator(1, 1000,  this));
    ui->label_index->setGeometry(703, 268, 103, 131);
    ui->label_index->setStyleSheet("QLabel{background-color:transparent;font-size:100px}");
    ui->label_index->setText(m_ptc->toUnicode("1"));
}

void QAutoTest::InitComboxData()
{
    ui->cb_autotest_ceshileixing->addItem(m_ptc->toUnicode("空白"));
    ui->cb_autotest_ceshileixing->addItem(m_ptc->toUnicode("样品"));

    ui->cb_autotest_yangpinliang->addItem(m_ptc->toUnicode("mL"));
    ui->cb_autotest_yangpinliang->addItem(m_ptc->toUnicode("g"));

    ui->cb_autotest_jieguoleixing->addItem(m_ptc->toUnicode("mL"));
    ui->cb_autotest_jieguoleixing->addItem(m_ptc->toUnicode("% Nitrogen"));
    ui->cb_autotest_jieguoleixing->addItem(m_ptc->toUnicode("% Protein"));
    ui->cb_autotest_jieguoleixing->addItem(m_ptc->toUnicode("mg N/kg"));
    ui->cb_autotest_jieguoleixing->addItem(m_ptc->toUnicode("mg N/g"));
    ui->cb_autotest_jieguoleixing->addItem(m_ptc->toUnicode("mg NH3/kg"));
    ui->cb_autotest_jieguoleixing->addItem(m_ptc->toUnicode("mg N"));
    ui->cb_autotest_jieguoleixing->addItem(m_ptc->toUnicode("mg N/mL"));
    ui->cb_autotest_jieguoleixing->addItem(m_ptc->toUnicode("mg N/100mL"));
    ui->cb_autotest_jieguoleixing->addItem(m_ptc->toUnicode("% Recovery"));
    ui->cb_autotest_jieguoleixing->addItem(m_ptc->toUnicode("mg Protein"));
    ui->cb_autotest_jieguoleixing->addItem(m_ptc->toUnicode("mg N/100g"));
    ui->cb_autotest_jieguoleixing->addItem(m_ptc->toUnicode("g N/kg"));
}

void QAutoTest::InitSings()
{
    /*
    connect(m_pLbAutoTest, SIGNAL(clicked()), this, SLOT(AutoTestDlg()));
    connect(m_pLbManualTest, SIGNAL(clicked()), this, SLOT(ManualTestDlg()));
    connect(m_pLbClean, SIGNAL(clicked()), this, SLOT(CleanDlg()));
    */
}

void QAutoTest::SetState(bool bFlag)
{
    m_bRunFlag = bFlag;
}
QString QAutoTest::GetUserName()
{
    QMainScreen *p = (QMainScreen *) this->parent();
    QString str =  p->GetUserName();
    return str;
}

void QAutoTest::updatabase()
{
    linstvalues.clear();
    pdataquery->opendatabase();
    pdataquery->GetValues(strtable, linstvalues, 1);
    pdataquery->cloesdatabase();
    ui->cb_autotest_fangfamingcheng->clear();
    for(int i = 0; i < linstvalues.size(); i++)
    {
        ui->cb_autotest_fangfamingcheng->addItem(linstvalues.at(i));
    }
}

bool QAutoTest::GetState()
{
    return m_bRunFlag;
}


void QAutoTest::AutoTestDlg()
{
    m_pLbAutoTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_autotest_auto_press.png);}");
    m_pLbManualTest->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_autotest_manual.png);}");
    m_pLbClean->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_autotest_normal.png);}");
}

void QAutoTest::ManualTestDlg()
{
    m_pLbAutoTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_autotest_auto_normal.png);}");
    m_pLbManualTest->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_autotest_manual_press.png);}");
    m_pLbClean->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_autotest_normal.png);}");
}

void QAutoTest::CleanDlg()
{
    m_pLbAutoTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_autotest_auto_normal.png);}");
    m_pLbManualTest->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_autotest_manual.png);}");
    m_pLbClean->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_autotest_clean_press.png);}");
}
void QAutoTest::UpData()
{
    QString str;

    pline() << m_iIndex << m_pListTestData.count();

    if(m_iIndex < m_pListTestData.count())
    {
        m_iIndex++;
    }
    else
    {
        m_iIndex = 1;
        m_bpiciFlag = false;

        while(m_pListTestData.count()>1)
            m_pListTestData.removeAt(1);
        //m_pListTestData.clear();
        ui->pb_autotest_pici->setEnabled(true);

        //ui->ed_autotest_name->clear();
        //ui->ed_autotest_name->clear();
        //ui->cb_autotest_ceshileixing->setCurrentIndex(_enumEmpty);
        //ui->ed_autotest_yangpinliang->clear();
        //ui->cb_autotest_yangpinliang->setCurrentIndex(_enum_Sampleml);
        //ui->cb_autotest_jieguoleixing->setCurrentIndex(_enum_Resualtml);
        //ui->ed_autotest_tiji->clear();
        //ui->ed_autotest_nongdu->clear();
        //return;
    }


    str = QString::number(m_iIndex);
    ui->label_index->setText(str);
    str = "";
    str = m_pListTestData.at(m_iIndex -1)->m_strName;
    ui->ed_autotest_name->setText(str);

    str = m_pListTestData.at(m_iIndex-1)->m_strpihao;
    ui->ed_autotest_pihao->setText(str);

    if(_enumEmpty == m_pListTestData.at(m_iIndex-1)->m_enumSampleType)
    {
        ui->cb_autotest_ceshileixing->setCurrentIndex(_enumEmpty);
    }
    else
    {
        ui->cb_autotest_ceshileixing->setCurrentIndex(_enumSample);
    }

    str = QString::number(m_pListTestData.at(m_iIndex-1)->m_fSampleNumber,'g', 6);
    ui->ed_autotest_yangpinliang->setText(str);

    if(_enum_Sampleml == m_pListTestData.at(m_iIndex-1)->m_enumSampleNumberType)
    {
        ui->cb_autotest_yangpinliang->setCurrentIndex(_enum_Sampleml);
    }
    else
    {
        ui->cb_autotest_yangpinliang->setCurrentIndex(_enum_Sampleg);
    }

    ui->cb_autotest_jieguoleixing->setCurrentIndex(m_pListTestData.at(m_iIndex-1)->m_enumResualtType);

    str = QString::number(m_pListTestData.at(m_iIndex-1)->m_fEmptyvolum,'g', 6);
    ui->ed_autotest_tiji->setText(str);

    str = QString::number(m_pListTestData.at(m_iIndex-1)->m_fdiding,'g', 6);
    ui->ed_autotest_nongdu->setText(str);
}

void QAutoTest::UpTestData(int index)
{


    //ui->ed_autotest_name->setFocus();
    // ui->label_1->setFocus();
    this->setFocus();
    QString str;
    m_bpiciFlag = true;
    if(m_pListTestData.isEmpty())
    {
        m_bpiciFlag = false;
        return;
    }
    ui->pb_autotest_pici->setEnabled(false);


    str = m_pListTestData.at(0)->m_strName;
    ui->ed_autotest_name->setText(str);

    str = m_pListTestData.at(0)->m_strpihao;
    ui->ed_autotest_pihao->setText(str);

    if(_enumEmpty == m_pListTestData.at(0)->m_enumSampleType)
    {
        ui->cb_autotest_ceshileixing->setCurrentIndex(_enumEmpty);

        ui->ed_autotest_yangpinliang->setText("0");

        ui->cb_autotest_yangpinliang->setCurrentIndex(m_pListTestData.at(0)->m_enumSampleNumberType);

        ui->cb_autotest_jieguoleixing->setCurrentIndex(m_pListTestData.at(0)->m_enumResualtType);
    }
    else
    {
        ui->cb_autotest_ceshileixing->setCurrentIndex(_enumSample);

        str = QString::number(m_pListTestData.at(0)->m_fSampleNumber,'g', 6);
        ui->ed_autotest_yangpinliang->setText(str);

        if(_enum_Sampleml == m_pListTestData.at(0)->m_enumSampleNumberType)
        {
            ui->cb_autotest_yangpinliang->setCurrentIndex(_enum_Sampleml);
        }
        else
        {
            ui->cb_autotest_yangpinliang->setCurrentIndex(_enum_Sampleg);
        }

        ui->cb_autotest_jieguoleixing->setCurrentIndex(m_pListTestData.at(0)->m_enumResualtType);
    }


    str = QString::number(m_pListTestData.at(0)->m_fEmptyvolum,'g', 6);
    ui->ed_autotest_tiji->setText(str);

    str = QString::number(m_pListTestData.at(0)->m_fdiding,'g', 6);
    ui->ed_autotest_nongdu->setText(str);

}
#include "qpropertyanimation.h"

void QAutoTest::on_pb_autotest_pici_clicked()
{
    if(!m_pPici)
        m_pPici = new QPiciFrom(this);
    //m_pPici->setWindowModality(Qt::WindowModal);
    //m_pPici->m_pListPiciTestData->clear();
    m_pPici->show();
}

void QAutoTest::on_pb_autotest_start_clicked()
{

    QString strname = "";
    QString strpihao = "";
    int iTestType = 0;
    QString strSampleNumber = "";
    int iSampleType = 0;
    int iResualtType = 0;
    QString strtiji = "";
    QString strnongdu = "";
    QString strNote = "";

    strname = ui->ed_autotest_name->text();
    strpihao = ui->ed_autotest_pihao->text();
    iTestType = ui->cb_autotest_ceshileixing->currentIndex();
    strSampleNumber = ui->ed_autotest_yangpinliang->text();
    iSampleType = ui->cb_autotest_yangpinliang->currentIndex();
    iResualtType = ui->cb_autotest_jieguoleixing->currentIndex();
    strtiji = ui->ed_autotest_tiji->text();
    strnongdu = ui->ed_autotest_nongdu->text();
    //strNote = ui->ed_autotest_nongdu->text();

    if((ui->cb_autotest_ceshileixing->currentIndex() == 1))
    {
        if(strSampleNumber.toFloat() == 0)
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""),
                                 m_ptc->toUnicode("样品量不能为0"), QMessageBox::Ok);
            return;
        }
    }

    if( (strname.isEmpty()) || (strpihao.isEmpty()) || (strSampleNumber.isEmpty()) || (strtiji.isEmpty()) || (strnongdu.isEmpty()))
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("数据不完整"), QMessageBox::Ok);
        return;
    }

    if(false == m_bpiciFlag)
    {


        m_pListTestData.clear();
        m_pListTestData.append(new TestData());
        m_pListTestData.at(0)->m_strName = strname;
        m_pListTestData.at(0)->m_strpihao = strpihao;

        if(0 == iTestType)
        {
            m_pListTestData.at(0)->m_enumSampleType = _enumEmpty;
        }
        else
        {
            m_pListTestData.at(0)->m_enumSampleType = _enumSample;
        }
        if(0 == iSampleType)
        {
            m_pListTestData.at(0)->m_enumSampleNumberType = _enum_Sampleml;
        }
        else
        {
            m_pListTestData.at(0)->m_enumSampleNumberType = _enum_Sampleg;
        }

        m_pListTestData.at(0)->m_enumResualtType = (RESUALTTYPE)iResualtType;

        m_pListTestData.at(0)->m_fSampleNumber = strSampleNumber.toFloat();
        m_pListTestData.at(0)->m_fEmptyvolum = strtiji.toFloat();
        if(ui->cb_autotest_ceshileixing->currentIndex() == 0)
            m_pListTestData.at(0)->m_fEmptyvolum = 0;
        m_pListTestData.at(0)->m_fdiding = strnongdu.toFloat();
        m_pListTestData.at(0)->m_strNote = strNote;

        ui->label_index->setText(m_ptc->toUnicode("1"));

    }
    else
    {
        //设置index的数据
        QByteArray ba = QString::number(m_iIndex).toAscii();
        ui->label_index->setText(m_ptc->toUnicode(ba));
    }
    /*
    m_pListTestMethod.clear();
    m_pListTestMethod.append(new TestMethod());
    m_pListTestMethod.at(0)->m_ipengsuan = 21;
    m_pListTestMethod.at(0)->m_ixishishui = 21;
    m_pListTestMethod.at(0)->m_ijian = 21;
    m_pListTestMethod.at(0)->m_izhengliu = 20;
    m_pListTestMethod.at(0)->m_imls = 1;
    m_pListTestMethod.at(0)->m_ididing = 1;
    m_pListTestMethod.at(0)->m_ijiajian = 1;
    m_pListTestMethod.at(0)->m_izhengqi = 100;
    m_pListTestMethod.at(0)->m_ixiaohuaguan = 0;
    m_pListTestMethod.at(0)->m_ijieshoubei = 0;
    m_pListTestMethod.at(0)->m_ilengningshui = 0;
*/

    m_pListTestMethod.clear();
    m_pListTestMethod.append(new TestMethod());
    m_pListTestMethod.at(0)->m_id = strlist.at(0).toInt();
    m_pListTestMethod.at(0)->m_name = strlist.at(1).toInt();
    m_pListTestMethod.at(0)->m_pici = strlist.at(2).toInt();
    m_pListTestMethod.at(0)->m_ipengsuan = strlist.at(3).toInt();
    m_pListTestMethod.at(0)->m_ixishishui = strlist.at(4).toInt();
    m_pListTestMethod.at(0)->m_ijian = strlist.at(5).toInt();
    m_pListTestMethod.at(0)->m_izhengliu = strlist.at(6).toInt();
    m_pListTestMethod.at(0)->m_imls = strlist.at(7).toInt();
    m_pListTestMethod.at(0)->m_ididing = strlist.at(8).toInt();
    m_pListTestMethod.at(0)->m_ijiajian = strlist.at(9).toInt();
    m_pListTestMethod.at(0)->m_izhengqi = strlist.at(10).toInt();
    m_pListTestMethod.at(0)->m_ixiaohuaguan = strlist.at(11).toInt();
    m_pListTestMethod.at(0)->m_ijieshoubei = strlist.at(12).toInt();
    m_pListTestMethod.at(0)->m_ilengningshui = 0;

    if(NULL == m_pTestPro)
    {
        qDebug("m_pTestPro");
        //        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("111111111111111111111111"), QMessageBox::Ok);
        m_pTestPro = new QAutoTestaProcessForm(this);
    }

    m_pTestPro->InitDiagram();
    m_pTestPro->SetTextdata();
    m_pTestPro->InitSerial();
    m_pTestPro->InitData();
    m_pTestPro->show();

    QSettings set;
    set.setValue("R0/name", m_pListTestData.at(m_iIndex-1)->m_strName);
    set.setValue("R0/pihao", m_pListTestData.at(m_iIndex-1)->m_strpihao);
    set.setValue("R0/ceshileixing", m_pListTestData.at(m_iIndex-1)->m_enumSampleType);
    set.setValue("R0/yangpinliang", m_pListTestData.at(m_iIndex-1)->m_fSampleNumber);
    set.setValue("R0/yangpinliangdanwei", m_pListTestData.at(m_iIndex-1)->m_enumSampleNumberType);
    set.setValue("R0/jieguoleixing", m_pListTestData.at(m_iIndex-1)->m_enumResualtType);
    set.setValue("R0/emptyv", m_pListTestData.at(m_iIndex-1)->m_fEmptyvolum);
    set.setValue("R0/diding", m_pListTestData.at(m_iIndex-1)->m_fdiding);
    set.setValue("R0/mid", m_pListTestMethod.at(0)->m_id);
    set.setValue("R0/mindex", ui->cb_autotest_fangfamingcheng->currentIndex());
    set.setValue("R0/note", m_pListTestData.at(m_iIndex-1)->m_strNote);
    set.sync();
}

void QAutoTest::on_cb_autotest_ceshileixing_currentIndexChanged(int index)
{
    if(index == 0)
    {
        if(ui->cb_autotest_jieguoleixing->currentIndex() > 0)
        {
            ui->cb_autotest_ceshileixing->setCurrentIndex(1);
            QMessageBox::warning(this, m_ptc->toUnicode(""),
                                 m_ptc->toUnicode("空白类型只允许ml结果单位"), QMessageBox::Ok);
        }
    }
}

void QAutoTest::on_cb_autotest_jieguoleixing_currentIndexChanged(int index)
{
    switch(index)
    {
    case _enum_Nitrongen:
    case _enum_mgNkg:
    case _enum_mgNg:
    case _enum_mgNH3kg:
    case _enum_XRecovery:
    case _enum_XPreotein:
    case _enum_mgN100g:
    case _enum_gNkg:
    {
        if(ui->cb_autotest_yangpinliang->currentIndex() == 0)
        {
            ui->cb_autotest_jieguoleixing->setCurrentIndex(0);
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("算法与样品量单位不匹配请重新选择"), QMessageBox::Ok);
            return;
        }

        if(ui->cb_autotest_ceshileixing->currentIndex() == 0)
        {
            ui->cb_autotest_jieguoleixing->setCurrentIndex(0);
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("算法与测试类型不匹配请重新选择"), QMessageBox::Ok);
            return;
        }
        break;
    }
    case _enum_mgNml:
    case _enum_mgN100ml:
    {
        if(ui->cb_autotest_yangpinliang->currentIndex() == 1)
        {
            ui->cb_autotest_jieguoleixing->setCurrentIndex(0);
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("算法与样品量单位不匹配请重新选择"), QMessageBox::Ok);
            return;
        }

        if(ui->cb_autotest_ceshileixing->currentIndex() == 0)
        {
            ui->cb_autotest_jieguoleixing->setCurrentIndex(0);
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("算法与测试类型不匹配请重新选择"), QMessageBox::Ok);
            return;
        }

        break;
    }
    case _enum_mgN:
    case _enum_mgPreotein:
    {
        if(ui->cb_autotest_ceshileixing->currentIndex() == 0)
        {
            ui->cb_autotest_jieguoleixing->setCurrentIndex(0);
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("算法与测试类型不匹配请重新选择"), QMessageBox::Ok);
            return;
        }
        break;
    }
    default:
        break;
    }
}

void QAutoTest::on_cb_autotest_yangpinliang_currentIndexChanged(int index)
{
    int i_index = ui->cb_autotest_jieguoleixing->currentIndex();
    if(index == 0)
    {
        switch(i_index)
        {
        case _enum_Nitrongen:
        case _enum_mgNkg:
        case _enum_mgNg:
        case _enum_mgNH3kg:
        case _enum_XRecovery:
        case _enum_XPreotein:
        case _enum_mgN100g:
        case _enum_gNkg:
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("算法与样品量单位不匹配请重新选择"), QMessageBox::Ok);
            ui->cb_autotest_yangpinliang->setCurrentIndex(1);
            break;
        }
        case _enum_mgNml:
        case _enum_mgN100ml:
        {
            break;
        }
        default:
            break;
        }
    }

    if(index == 1)
    {
        switch(i_index)
        {
        case _enum_Nitrongen:
        case _enum_mgNkg:
        case _enum_mgNg:
        case _enum_mgNH3kg:
        case _enum_XRecovery:
        case _enum_XPreotein:
        case _enum_mgN100g:
        case _enum_gNkg:
        {
            break;
        }
        case _enum_mgNml:
        case _enum_mgN100ml:
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("算法与样品量单位不匹配请重新选择"), QMessageBox::Ok);
            ui->cb_autotest_yangpinliang->setCurrentIndex(0);
            break;
        }
        default:
            break;
        }
    }
}

void QAutoTest::on_cb_autotest_fangfamingcheng_currentIndexChanged(const QString &arg1)
{

    QString strname = "mingcheng";

    strlist.clear();
    QString str = arg1;
    if(true == pdataquery->opendatabase())
    {
        pdataquery->GetoneValues(strtable, strlist, strname, str, 13);
        pdataquery->cloesdatabase();
    }


    ui->label_methodid->setText(strlist.at(0));
    ui->label_methodname->setText(strlist.at(1));
    ui->label_danbaixishu->setText(strlist.at(2));
    ui->label_pengsuan->setText(strlist.at(3));
    ui->label_xishishui->setText(strlist.at(4));
    ui->label_jian->setText(strlist.at(5));
    ui->label_zhengliu->setText(strlist.at(6));
    if(0 == strlist.at(7).toInt())
    {
        ui->lb_autotest_ml4->setText("mL");
    }
    else
    {
        ui->lb_autotest_ml4->setText("s");
    }

    if(0 == strlist.at(8).toInt())
    {
        ui->label_didingfangshi->setText(m_ptc->toUnicode("边蒸馏边滴定"));
    }
    else
    {
        ui->label_didingfangshi->setText(m_ptc->toUnicode("先蒸馏后滴定"));
    }

    if(0 == strlist.at(9).toInt())
    {
        ui->label_jiajianfangshi->setText(m_ptc->toUnicode("先加碱后蒸馏"));
    }
    else
    {
        ui->label_jiajianfangshi->setText(m_ptc->toUnicode("先蒸馏后加碱"));
    }

    //ui->cb_settingmethod_zhengliudanwei->setCurrentIndex();

    ui->label_zhengqiliuliang->setText(strlist.at(10));

    if(0 == strlist.at(11).toInt())
    {

        m_pLbxiaohuaguanpaifei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_no.png);}");

    }
    else
    {
        m_pLbxiaohuaguanpaifei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_yes.png);}");

    }

    if(0 == strlist.at(12).toInt())
    {
        m_pLbjieshoubeipaifei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_no.png);}");
    }
    else
    {
        m_pLbjieshoubeipaifei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_yes.png);}");
    }

}
