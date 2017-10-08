#include "qsettingcalibrationform.h"
#include "ui_qsettingcalibrationform.h"
#include "qmainscreen.h"
#include "DataDef.h"

QSettingCalibrationForm::QSettingCalibrationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSettingCalibrationForm),
    m_iIndex(0),
    m_pSerialSetCal(NULL),
    m_bstepFlag(true),
    m_iStep(0)
{
    ui->setupUi(this);
    m_ptc =  QTextCodec::codecForName("UTF-8");
    InitOCX();
    InitSings();
    m_bzhusaibeng = true;
    m_bpengsuanbeng = true;
    m_bjianbeng = true;
    m_bxishishui = true;
    m_byansejieshouye = true;
    m_byanse = true;

    if(NULL == m_pSerialSetCal)
    {
        QMainScreen *pWidget = static_cast<QMainScreen *>(this->parent());
        m_pSerialSetCal = pWidget->m_pSerialProtcol;
    }
}

QSettingCalibrationForm::~QSettingCalibrationForm()
{
    delete ui;
}


void QSettingCalibrationForm::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("QWidget#QSettingCalibrationForm{image:url(:/images/bk/bk_setting_method.png)}""QSettingCalibrationForm{background-color:transparent;}");


    ui->label_jiaozhun->setGeometry(28,7,111,36);
    ui->label_jiaozhun->setText(m_ptc->toUnicode("校准"));
    ui->label_jiaozhun->setStyleSheet("QLabel{background-color:transparent;font-size:19px;}");

    m_pLbzhusaibeng = new QMLabel(this);
    m_pLbzhusaibeng->setGeometry(50,75,39, 39);
    m_pLbzhusaibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");

    m_pLbpengsuanbeng = new QMLabel(this);
    m_pLbpengsuanbeng->setGeometry(50,157,39, 39);
    m_pLbpengsuanbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");

    m_pLbjianbeng = new QMLabel(this);
    m_pLbjianbeng->setGeometry(50,239,39, 39);
    m_pLbjianbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");

    m_pLbxishishuibeng = new QMLabel(this);
    m_pLbxishishuibeng->setGeometry(50,321,39, 39);
    m_pLbxishishuibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");

    m_pLbyansejieshouye = new QMLabel(this);
    m_pLbyansejieshouye->setGeometry(50,403,39, 39);
    m_pLbyansejieshouye->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");

    m_pLbyanse = new QMLabel(this);
    m_pLbyanse->setGeometry(50,485,39, 39);
    m_pLbyanse->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");

    //label
    ui->lb_settingCalibration_zhusai->setGeometry(115, 81, 220, 30);
    ui->lb_settingCalibration_zhusai->setText(m_ptc->toUnicode("柱塞泵校准"));
    ui->lb_settingCalibration_zhusai->setStyleSheet("QLabel{background-color:transparent;font-size:19px;}");

    ui->lb_settingCalibration_pengsuan->setGeometry(115, 163, 220, 30);
    ui->lb_settingCalibration_pengsuan->setText(m_ptc->toUnicode("硼酸泵校准"));
    ui->lb_settingCalibration_pengsuan->setStyleSheet("QLabel{background-color:transparent;font-size:19px;}");

    ui->lb_settingCalibration_jian->setGeometry(115, 245, 220, 30);
    ui->lb_settingCalibration_jian->setText(m_ptc->toUnicode("碱泵校准"));
    ui->lb_settingCalibration_jian->setStyleSheet("QLabel{background-color:transparent;font-size:19px;}");

    ui->lb_settingCalibration_xishishui->setGeometry(115, 327, 220, 30);
    ui->lb_settingCalibration_xishishui->setText(m_ptc->toUnicode("稀释水泵校准"));
    ui->lb_settingCalibration_xishishui->setStyleSheet("QLabel{background-color:transparent;font-size:19px;}");

    ui->lb_settingCalibration_yanseyewei->setGeometry(115, 409, 220, 30);
    ui->lb_settingCalibration_yanseyewei->setText(m_ptc->toUnicode("颜色及接收液液位校准"));
    ui->lb_settingCalibration_yanseyewei->setStyleSheet("QLabel{background-color:transparent;font-size:19px;}");

    ui->lb_settingCalibration_yanse->setGeometry(115, 491, 220, 30);
    ui->lb_settingCalibration_yanse->setText(m_ptc->toUnicode("颜色微调"));
    ui->lb_settingCalibration_yanse->setStyleSheet("QLabel{background-color:transparent;font-size:19px;}");

    ui->pb_next->setFlat(true);
    //ui->pb_next->setFocusPolicy(Qt::NoFocus);
    ui->pb_next->setGeometry(536,486,108,44);
    ui->pb_next->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_next_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_next_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_next_press.png);}");


    ui->pb_1->setFlat(true);
    //ui->pb_1->setFocusPolicy(Qt::NoFocus);
    ui->pb_1->setGeometry(526,406,50,46);
    ui->pb_1->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/btn_1normal.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_1normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_1press.png);}");
    ui->pb_1->hide();

    ui->pb_5->setFlat(true);
    //ui->pb_5->setFocusPolicy(Qt::NoFocus);
    ui->pb_5->setGeometry(626,406,50,46);
    ui->pb_5->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/btn_5normal.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_5normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_5press.png);}");
    ui->pb_5->hide();

    ui->pb_10->setFlat(true);
    //ui->pb_10->setFocusPolicy(Qt::NoFocus);
    ui->pb_10->setGeometry(726,406,50,46);
    ui->pb_10->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/btn_10normal.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_10normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_10press.png);}");
    ui->pb_10->hide();

    ui->pb_baipingheng->setFlat(true);
    //ui->pb_10->setFocusPolicy(Qt::NoFocus);
    ui->pb_baipingheng->setGeometry(600,240,108,44);
    ui->pb_baipingheng->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/btn_baipingheng_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_baipingheng_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_baipingheng_press.png);}");
    ui->pb_baipingheng->hide();

    ui->pb_jianhao->setFlat(true);
    //ui->pb_jianhao->setFocusPolicy(Qt::NoFocus);
    ui->pb_jianhao->setGeometry(546,311,29,29);
    ui->pb_jianhao->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:images/bt/btn_-normal.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_-normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_-press.png);}");
    ui->pb_jianhao->hide();

    ui->pb_jiahao->setFlat(true);
    //ui->pb_jiahao->setFocusPolicy(Qt::NoFocus);
    ui->pb_jiahao->setGeometry(754,311,29,29);
    ui->pb_jiahao->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:images/bt/btn_+noraml.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_+noraml.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_+press.png);}");
    ui->pb_jiahao->hide();

    int width = 35;

    ui->pb_back->setFlat(true);
    //ui->pb_back->setFocusPolicy(Qt::NoFocus);
    ui->pb_back->setGeometry(706,486,108,44);
    ui->pb_back->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_back_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_back_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_back_press.png);}");


    QRegExp rx("^-?(100|1?[0-9]?\\d(\\.\\d{1,6})?)$");
    QRegExpValidator *pReg = new QRegExpValidator(rx, this);
    ui->le_float->setValidator(pReg);
    ui->le_float->setGeometry(580,377,107, 35);
    ui->le_float->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_small.png);font-size:17px;}");
    ui->le_float->hide();

    ui->le_int50->setValidator(new QIntValidator(0, 50,  this));
    ui->le_int50->setGeometry(580,377,107, 35);
    ui->le_int50->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(://images/bt/ed_line_small.png);font-size:17px;}");
    ui->le_int50->hide();

    ui->le_int150->setValidator(new QIntValidator(0, 150,  this));
    ui->le_int150->setGeometry(580,377,107, 35);
    ui->le_int150->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_small.png);font-size:17px;}");
    ui->le_int150->hide();

    ui->lbML->setGeometry(700,373,80, 35);
    ui->lbML->setText("mL");
    ui->lbML->hide();


    ui->le_jiajianfa->setValidator(new QIntValidator(-30, 30,  this));
    ui->le_jiajianfa->setGeometry(595,311,142, 35);
    ui->le_jiajianfa->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(://images/bt/ed_line_jiajianfa.png);font-size:17px;}");
    ui->le_jiajianfa->hide();

    ui->label->setGeometry(450, 150, 399,205);
    ui->label->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bk/zhusaibeng01.png);}");

}

void QSettingCalibrationForm::InitSings()
{
    connect(m_pLbzhusaibeng, SIGNAL(clicked()), this, SLOT(zhusaibeng()));
    connect(m_pLbpengsuanbeng, SIGNAL(clicked()), this, SLOT(pengsuanbeng()));
    connect(m_pLbjianbeng, SIGNAL(clicked()), this, SLOT(jianbeng()));
    connect(m_pLbxishishuibeng, SIGNAL(clicked()), this, SLOT(xishishuibeng()));
    connect(m_pLbyansejieshouye, SIGNAL(clicked()), this, SLOT(yansejieshouye()));
    connect(m_pLbyanse, SIGNAL(clicked()), this, SLOT(yanse()));
}

void QSettingCalibrationForm::zhusaibengfun(int index)
{
    m_Serialcmd.clear();
    m_Serialdata.clear();

    switch (index) {
    case 0:
    {
        ui->label->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bk/zhusaibeng01.png);}");
        ui->le_int50->hide();
        ui->le_int150->hide();
        ui->lbML->hide();
        ui->le_float->hide();
        ui->pb_10->hide();
        ui->pb_5->hide();
        ui->pb_1->hide();
        ui->pb_jianhao->hide();
        ui->pb_jiahao->hide();
        ui->pb_baipingheng->hide();
        ui->le_jiajianfa->hide();
    }
        break;
    case 1:
    {
        ui->label->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bk/zhusaibeng02.png);}");
        m_Serialcmd.append(0x06);
        m_Serialcmd.append(0x01);
        m_Serialdata.append(0x01);
        m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
    }
        break;
    case 2:
    {
        ui->label->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bk/zhusaibeng03.png);}");
        ui->le_float->show();
        ui->lbML->show();
        m_Serialcmd.append(0x06);
        m_Serialcmd.append(0x01);
        m_Serialdata.append(0x02);
        m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
    }
        break;
    default:
        break;
    }

}

void QSettingCalibrationForm::pengsuanfun(int index)
{
    switch (index) {
      case 0:
        {
            ui->label->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bk/pengsuan01.png);}");
            ui->lbML->hide();
            ui->le_int50->hide();
            ui->le_float->hide();
            ui->le_int150->hide();
            ui->pb_10->hide();
            ui->pb_5->hide();
            ui->pb_1->hide();
            ui->pb_jianhao->hide();
            ui->pb_jiahao->hide();
            ui->pb_baipingheng->hide();
            ui->le_jiajianfa->hide();
        }
        break;
      case 1:
        {
            ui->label->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bk/pengsuan02.png);}");
            ui->lbML->show();
            ui->le_int50->show();
            m_Serialcmd.append(0x06);
            m_Serialcmd.append(0x02);
            m_Serialdata.append(0x01);
            m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
        }
        break;
      default:
        break;
    }
}

void QSettingCalibrationForm::jianbengfun(int index)
{
    switch (index) {
    case 0:
        {
            ui->label->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bk/jianbeng01.png);}");
            ui->le_int50->hide();
            ui->le_float->hide();
            ui->lbML->hide();
            ui->le_int150->hide();
            ui->pb_10->hide();
            ui->pb_5->hide();
            ui->pb_1->hide();
            ui->pb_jianhao->hide();
            ui->pb_jiahao->hide();
            ui->pb_baipingheng->hide();
            ui->le_jiajianfa->hide();
        }
        break;
    case 1:
        {
            ui->label->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bk/jianbeng02.png);}");
            ui->lbML->show();
            ui->le_int50->show();
            m_Serialcmd.append(0x06);
            m_Serialcmd.append(0x03);
            m_Serialdata.append(0x01);
            m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
        }
        break;
    default:
        break;
    }
}


void QSettingCalibrationForm::xishishuifun(int index)
{
    switch (index) {
    case 0:
        {
            ui->label->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bk/xishishui01.png);}");
            ui->le_int50->hide();
            ui->le_float->hide();
            ui->le_int150->hide();
            ui->lbML->hide();
            ui->pb_10->hide();
            ui->pb_5->hide();
            ui->pb_1->hide();
            ui->pb_jianhao->hide();
            ui->pb_jiahao->hide();
            ui->pb_baipingheng->hide();
            ui->le_jiajianfa->hide();
        }
        break;
    case 1:
        {
            ui->label->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bk/xishishui02.png);}");
            ui->le_int50->show();
            ui->lbML->show();
            m_Serialcmd.append(0x06);
            m_Serialcmd.append(0x04);
            m_Serialdata.append(0x01);
            m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
        }
        break;
    default:
        break;
    }
}

void QSettingCalibrationForm::yansefun(int index)
{
    switch (index) {
    case 0:
        {
            ui->label->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bk/yanse01.png);}");
            ui->le_int50->hide();
            ui->lbML->show();
            ui->le_float->hide();
            ui->le_int150->show();
            ui->pb_10->hide();
            ui->pb_5->hide();
            ui->pb_1->hide();
            ui->pb_jianhao->hide();
            ui->pb_jiahao->hide();
            ui->pb_baipingheng->hide();
            ui->le_jiajianfa->hide();
        }
        break;
    case 1:
        {
            ui->label->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bk/yanse02.png);}");
            ui->lbML->hide();
            ui->le_int150->hide();
            m_Serialcmd.append(0x06);
            m_Serialcmd.append(0x05);
            m_Serialdata.append(0x01);
            QString str = ui->le_int150->text();
            m_Serialdata.append(str.toInt());
            m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
        }
        break;
    case 2:
        {
            ui->label->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bk/yanse03.png);}");
            m_Serialcmd.append(0x06);
            m_Serialcmd.append(0x05);
            m_Serialdata.append(0x02);
            ui->pb_10->show();
            ui->pb_5->show();
            ui->pb_1->show();
            m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
        }
        break;
    case 3:
        {
            ui->label->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bk/yanse04.png);}");
            m_Serialcmd.append(0x06);
            m_Serialcmd.append(0x05);
            m_Serialdata.append(0x03);
            m_Serialdata.append((char)0x00);
            ui->pb_10->hide();
            ui->pb_5->hide();
            ui->pb_1->hide();
            m_bstepFlag = true;
            m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
        }
        break;
    case 4:
        {
            ui->label->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bk/yanse05.png);}");
            m_Serialcmd.append(0x06);
            m_Serialcmd.append(0x05);
            m_Serialdata.append(0x04);
            ui->pb_10->show();
            ui->pb_5->show();
            ui->pb_1->show();
            m_bstepFlag = false;
            m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
        }
        break;
    case 5:
        {
            ui->label->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bk/yanse06.png);}");
            m_Serialcmd.append(0x06);
            m_Serialcmd.append(0x05);
            m_Serialdata.append(0x05);
            m_Serialdata.append((char)0x00);
            ui->pb_10->hide();
            ui->pb_5->hide();
            ui->pb_1->hide();
            m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
        }
        break;
    default:
        break;
    }
}

void QSettingCalibrationForm::yansejiaozhun(int index)
{
    ui->le_int50->hide();
    ui->le_float->hide();
    ui->le_int150->hide();
    ui->lbML->hide();
    ui->pb_10->hide();
    ui->pb_5->hide();
    ui->pb_1->hide();

    ui->pb_baipingheng->show();
    ui->pb_jianhao->show();
    ui->pb_jiahao->show();
    ui->le_jiajianfa->show();
}

void QSettingCalibrationForm::zhusaibeng()
{
    if(true == m_bzhusaibeng)
     {
        m_pLbzhusaibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_bzhusaibeng = false;
        m_pLbyanse->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_byanse = true;
        m_pLbyansejieshouye->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_byansejieshouye = true;
        m_pLbxishishuibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bxishishui = true;
        m_pLbjianbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjianbeng = true;
        m_pLbpengsuanbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bpengsuanbeng = true;
        m_iIndex = 0;
        zhusaibengfun(m_iIndex);
        ui->label->show();
     }
     else
     {
        m_pLbzhusaibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bzhusaibeng = true;
     }
}

void QSettingCalibrationForm::pengsuanbeng()
{
    if(true == m_bpengsuanbeng)
     {
        m_pLbpengsuanbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_bpengsuanbeng = false;
        m_pLbyanse->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_byanse = true;
        m_pLbyansejieshouye->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_byansejieshouye = true;
        m_pLbxishishuibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bxishishui = true;
        m_pLbjianbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjianbeng = true;
        m_pLbzhusaibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bzhusaibeng = true;
        m_iIndex = 0;
        pengsuanfun(m_iIndex);
        ui->label->show();
     }
     else
     {
        m_pLbpengsuanbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bpengsuanbeng = true;
     }
}

void QSettingCalibrationForm::jianbeng()
{
    if(true == m_bjianbeng)
     {
        m_pLbjianbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_bjianbeng = false;
        m_pLbyanse->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_byanse = true;
        m_pLbyansejieshouye->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_byansejieshouye = true;
        m_pLbxishishuibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bxishishui = true;
        m_pLbpengsuanbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bpengsuanbeng = true;
        m_pLbzhusaibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bzhusaibeng = true;
        m_iIndex = 0;
        jianbengfun(m_iIndex);
        ui->label->show();
     }
     else
     {
        m_pLbjianbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjianbeng = true;
     }
}

void QSettingCalibrationForm::xishishuibeng()
{
    if(true == m_bxishishui)
     {
        m_pLbxishishuibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_bxishishui = false;
        m_pLbyanse->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_byanse = true;
        m_pLbyansejieshouye->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_byansejieshouye = true;
        m_pLbjianbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjianbeng = true;
        m_pLbpengsuanbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bpengsuanbeng = true;
        m_pLbzhusaibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bzhusaibeng = true;
        m_iIndex = 0;
        ui->label->show();
        xishishuifun(m_iIndex);
     }
     else
     {
        m_pLbxishishuibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bxishishui = true;
     }
}

void QSettingCalibrationForm::yansejieshouye()
{
    if(true == m_byansejieshouye)
     {
        m_pLbyansejieshouye->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_byansejieshouye = false;

        m_pLbyanse->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_byanse = true;
        m_pLbxishishuibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bxishishui = true;
        m_pLbjianbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjianbeng = true;
        m_pLbpengsuanbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bpengsuanbeng = true;
        m_pLbzhusaibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bzhusaibeng = true;
        m_iIndex = 0;

        yansefun(m_iIndex);
        ui->label->show();
     }
     else
     {
        m_pLbyansejieshouye->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_byansejieshouye = true;
     }
}

void QSettingCalibrationForm::yanse()
{
    if(true == m_byanse)
     {
        m_pLbyanse->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_byanse = false;
        m_pLbyansejieshouye->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_byansejieshouye = true;
        m_pLbxishishuibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bxishishui = true;
        m_pLbjianbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjianbeng = true;
        m_pLbpengsuanbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bpengsuanbeng = true;
        m_pLbzhusaibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bzhusaibeng = true;
        m_iIndex = 0;
        ui->label->hide();
        ui->le_jiajianfa->setText("0");
        yansejiaozhun(0);

     }
     else
     {
        m_pLbyanse->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_byanse = true;
     }
}

void QSettingCalibrationForm::on_pb_next_clicked()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    if(false == m_bzhusaibeng)
    {
        m_iIndex++;
        if(3 == m_iIndex)
        {            
            QSettings set;
            set.setValue("Machine/zhusaibeng", ui->le_float->text());
            set.sync();

            m_Serialcmd.append(0x06);
            m_Serialcmd.append(0x01);
            m_Serialdata.append(0x03);

            m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
            m_iIndex = 0;
        }
        zhusaibengfun(m_iIndex);
    }

    if(false == m_bpengsuanbeng)
    {
        m_iIndex++;
        if(2 == m_iIndex)
        {
            m_Serialcmd.append(0x06);
            m_Serialcmd.append(0x02);
            m_Serialdata.append(0x02);
            QString str = ui->le_int50->text();
            m_Serialdata.append(str.toInt());
            m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
            m_iIndex = 0;
        }
        pengsuanfun(m_iIndex);
    }

    if(false == m_bjianbeng)
    {
        m_iIndex++;
        if(2 == m_iIndex)
        {
            m_Serialcmd.append(0x06);
            m_Serialcmd.append(0x03);
            m_Serialdata.append(0x02);
            QString str = ui->le_int50->text();
            m_Serialdata.append(str.toInt());
            m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
            m_iIndex = 0;
        }
        jianbengfun(m_iIndex);
    }

    if(false == m_bxishishui)
    {
        m_iIndex++;
        if(2 == m_iIndex)
        {
            m_Serialcmd.append(0x06);
            m_Serialcmd.append(0x04);
            m_Serialdata.append(0x02);
            QString str = ui->le_int50->text();
            m_Serialdata.append(str.toInt());
            m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
            m_iIndex = 0;
        }
        xishishuifun(m_iIndex);
    }

    if(false == m_byansejieshouye)
    {
        m_iIndex++;
        if(6 == m_iIndex)
        {
            m_Serialcmd.append(0x06);
            m_Serialcmd.append(0x05);
            m_Serialdata.append(0x06);
            m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
            m_iIndex = 0;
        }
        yansefun(m_iIndex);
    }

    if(false == m_byanse)
    {
        QString str = ui->le_jiajianfa->text();
        int i = str.toInt();
        i = i + 100;
        m_Serialcmd.append(0x06);
        m_Serialcmd.append(0x06);
        m_Serialdata.append(i);
        m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);

    }
}

void QSettingCalibrationForm::on_pb_back_clicked()
{
    if(false == m_bzhusaibeng)
    {
        m_iIndex = 0;
        zhusaibengfun(m_iIndex);
    }

    if(false == m_bpengsuanbeng)
    {
        m_iIndex = 0;
        pengsuanfun(m_iIndex);
    }

    if(false == m_bjianbeng)
    {
        m_iIndex = 0;
        jianbengfun(m_iIndex);
    }

    if(false == m_bxishishui)
    {
        m_iIndex = 0;
        xishishuifun(m_iIndex);
    }

    if(false == m_byansejieshouye)
    {
        m_iIndex = 0;
        yansefun(m_iIndex);
    }
    if(false == m_byanse)
    {
        m_iStep = 0;
        ui->le_jiajianfa->setText("0");
    }
}

void QSettingCalibrationForm::on_pb_1_clicked()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    if(true == m_bstepFlag)
    {
        m_Serialcmd.append(0x06);
        m_Serialcmd.append(0x05);
        m_Serialdata.append(0x03);
        m_Serialdata.append(0x01);
        m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
    }
    else
    {
        m_Serialcmd.append(0x06);
        m_Serialcmd.append(0x05);
        m_Serialdata.append(0x05);
        m_Serialdata.append(0x01);
        m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
    }
}

void QSettingCalibrationForm::on_pb_5_clicked()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    if(true == m_bstepFlag)
    {
        m_Serialcmd.append(0x06);
        m_Serialcmd.append(0x05);
        m_Serialdata.append(0x03);
        m_Serialdata.append(0x05);
        m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
    }
    else
    {
        m_Serialcmd.append(0x06);
        m_Serialcmd.append(0x05);
        m_Serialdata.append(0x05);
        m_Serialdata.append(0x05);
        m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
    }
}

void QSettingCalibrationForm::on_pb_10_clicked()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    if(true == m_bstepFlag)
    {
        m_Serialcmd.append(0x06);
        m_Serialcmd.append(0x05);
        m_Serialdata.append(0x03);
        m_Serialdata.append(0x10);
        m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
    }
    else
    {
        m_Serialcmd.append(0x06);
        m_Serialcmd.append(0x05);
        m_Serialdata.append(0x05);
        m_Serialdata.append(0x10);
        m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
    }
}

void QSettingCalibrationForm::on_pb_jianhao_clicked()
{
    if(-30 == m_iStep)
        return;

    QString str = "";
    --m_iStep;
    str = QString::number(m_iStep);
    ui->le_jiajianfa->setText(str);

}

void QSettingCalibrationForm::on_pb_jiahao_clicked()
{
    if(30 == m_iStep)
        return;

    QString str = "";
    ++m_iStep;
    str = QString::number(m_iStep);
    ui->le_jiajianfa->setText(str);
}

void QSettingCalibrationForm::on_pb_baipingheng_clicked()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x06);
    m_Serialcmd.append(0x08);
    m_Serialdata.append((char)0x00);
    m_pSerialSetCal->TransmitData(m_Serialcmd, m_Serialdata);
}
