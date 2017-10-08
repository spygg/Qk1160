#include "qmanualtestform.h"
#include "qmainscreen.h"
#include "ui_qmanualtestform.h"
#include <QMessageBox>
#define MAX_DIDING 2000
#include "HNDefine.h"

QManualTestForm::QManualTestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QManualTestForm),
    m_pSerialManual(NULL),
    pdataquery(NULL),
    strtable("method")
{
    ui->setupUi(this);
    m_ptc =  QTextCodec::codecForName("UTF-8");

    m_brunning = false;

    m_bjieshoubeiflag = true;
    m_bxiaohuaguanflag = true;

    m_blbcheckpengsuan = true;
    m_blbcheckxishishui = true;
    m_blbcheckdiding = true;
    m_blbcheckjian = true;
    m_blbcheckzhengliu = true;

    if(NULL == m_pSerialManual)
    {
        QMainScreen *pWidget = static_cast<QMainScreen *>(this->parent());
        m_pSerialManual = pWidget->m_pSerialProtcol;
   connect(m_pSerialManual->m_pReadThread, SIGNAL(emitReadData(QByteArray)),this, SLOT(AnalysisData(QByteArray)));
    }

    InitOCX();
    InitSings();
    pdataquery = new QDatabasequery();
    pdataquery->SetTableName("./db/Method/method");
    pdataquery->GetValues(strtable, linstvalues, 1);
    pdataquery->cloesdatabase();
}

QManualTestForm::~QManualTestForm()
{
    delete ui;
}


void QManualTestForm::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("QWidget#QManualTestForm{image:url(:/images/bk/bk_manualtest1.png)}""QManualTestForm{background-color:transparent;}");

    int y = 57;
    int dy = 36;
    int ddy = 2;

    //edit
    ui->le_manualtest_pengsuan->setGeometry(157, y + dy * 0,291, 35);
    ui->le_manualtest_pengsuan->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");

    ui->le_manualtest_xishishui->setGeometry(157, y + dy * 1, 291, 35);
    ui->le_manualtest_xishishui->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");

    ui->le_manualtest_jian->setGeometry(157, y + dy * 2, 291, 35);
    ui->le_manualtest_jian->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");

    ui->le_manualtest_zhengliu->setGeometry(157, y + dy * 3, 188, 35);
    ui->le_manualtest_zhengliu->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line.png);font-size:17px}");

    ui->le_manualtest_diding->setGeometry(157, y + dy * 4,291, 35);
    ui->le_manualtest_diding->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");

    ui->lb_manualtest_ml->setGeometry(454, y + dy * 0, 100, 30);
    ui->lb_manualtest_ml->setText(m_ptc->toUnicode("mL"));
    ui->lb_manualtest_ml->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_manualtest_ml1->setGeometry(454, y + dy * 1, 100, 30);
    ui->lb_manualtest_ml1->setText(m_ptc->toUnicode("mL"));
    ui->lb_manualtest_ml1->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_manualtest_ml2->setGeometry(454, y + dy * 2, 100, 30);
    ui->lb_manualtest_ml2->setText(m_ptc->toUnicode("mL"));
    ui->lb_manualtest_ml2->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_manualtest_ml3->setGeometry(454, y + dy * 4, 100, 30);
    ui->lb_manualtest_ml3->setText(m_ptc->toUnicode("μL"));
    ui->lb_manualtest_ml3->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_manualtest_pengsuan->setGeometry(72, y + dy * 0, 100, 30);
    ui->lb_manualtest_pengsuan->setText(m_ptc->toUnicode("硼酸："));
    ui->lb_manualtest_pengsuan->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_manualtest_xishishui->setGeometry(72, y + dy * 1, 100, 30);
    ui->lb_manualtest_xishishui->setText(m_ptc->toUnicode("稀释水："));
    ui->lb_manualtest_xishishui->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_manualtest_jian->setGeometry(72, y + dy * 2, 100, 30);
    ui->lb_manualtest_jian->setText(m_ptc->toUnicode("碱："));
    ui->lb_manualtest_jian->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_manualtest_zhengliu->setGeometry(72, y + dy * 3, 100, 30);
    ui->lb_manualtest_zhengliu->setText(m_ptc->toUnicode("蒸馏："));
    ui->lb_manualtest_zhengliu->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->cb_mangual_zhengliu->setGeometry(344, y + dy * 3 + ddy, 101, 31);
    ui->cb_mangual_zhengliu->setStyleSheet("QComboBox{border:2px solid #D7D7D7;border-radius: 4px;}"
                                           "QComboBox QAbstractItemView::item{height:50px;}"
                                           "QComboBox::down-arrow{image:url(:/images/bt/arrowdownBo.png);}"
                                           "QComboBox::drop-down{border:0px;}");
    ui->cb_mangual_zhengliu->setView(new QListView());

    ui->lb_manualtest_diding->setGeometry(72, y + dy * 4, 100, 30);
    ui->lb_manualtest_diding->setText(m_ptc->toUnicode("滴定:"));
    ui->lb_manualtest_diding->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");



    y = 370;
    dy = 36;
    int ddx = 2;

    ui->lb_manualtest_fangfamingcheng->setGeometry(72, y + dy * 0, 100, 30);
    ui->lb_manualtest_fangfamingcheng->setText(m_ptc->toUnicode("方法名称："));
    ui->lb_manualtest_fangfamingcheng->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_manualtest_danbaixishu->setGeometry(72, y + dy * 1, 100, 30);
    ui->lb_manualtest_danbaixishu->setText(m_ptc->toUnicode("蛋白系数："));
    ui->lb_manualtest_danbaixishu->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_manualtest_didingfangshi->setGeometry(72, y + dy * 2, 100, 30);
    ui->lb_manualtest_didingfangshi->setText(m_ptc->toUnicode("滴定方式："));
    ui->lb_manualtest_didingfangshi->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_manualtest_jiajianfangshi->setGeometry(72, y + dy * 3, 100, 30);
    ui->lb_manualtest_jiajianfangshi->setText(m_ptc->toUnicode("加碱方式："));
    ui->lb_manualtest_jiajianfangshi->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_manualtest_liuliang->setGeometry(72, y + dy * 4, 100, 30);
    ui->lb_manualtest_liuliang->setText(m_ptc->toUnicode("蒸汽流量："));
    ui->lb_manualtest_liuliang->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_manualtest_baifen->setGeometry(454, y + dy * 4, 100, 30);
    ui->lb_manualtest_baifen->setText(m_ptc->toUnicode("%"));
    ui->lb_manualtest_baifen->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_manualtest_xiaohuaguan->setGeometry(72, y + dy * 5, 100, 30);
    ui->lb_manualtest_xiaohuaguan->setText(m_ptc->toUnicode("消化管排废："));
    ui->lb_manualtest_xiaohuaguan->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_manualtest_jieshoubei->setGeometry(268, y + dy * 5, 100, 30);
    ui->lb_manualtest_jieshoubei->setText(m_ptc->toUnicode("接收杯清洗："));
    ui->lb_manualtest_jieshoubei->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");


    m_pLbxiaohuaguanonoff = new QMLabel(this);
    m_pLbxiaohuaguanonoff->setGeometry(180,y + dy * 5 + ddy,78, 29);
    m_pLbxiaohuaguanonoff->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");

    m_pLbjieshoubeoonoff = new QMLabel(this);
    m_pLbjieshoubeoonoff->setGeometry(368,y + dy * 5 + ddy,78, 29);
    m_pLbjieshoubeoonoff->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");

    ui->le_manualtest_mingcheng->setGeometry(157, y + dy * 0, 291, 35);
    ui->le_manualtest_mingcheng->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");

    ui->le_manualtest_xishu->setGeometry(157, y + dy * 1,291, 35);
    ui->le_manualtest_xishu->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");

    //combox
    ui->cb_mangual_diding->setGeometry(157 + ddx, y + dy * 2 + ddy, 287, 31);
    ui->cb_mangual_diding->setStyleSheet("QComboBox{border:2px solid #D7D7D7;border-radius: 4px;}"
                                         "QComboBox QAbstractItemView::item{height:50px;}"
                                         "QComboBox::down-arrow{image:url(:/images/bt/arrowdownBo.png);}"
                                         "QComboBox::drop-down{border:0px;}");
    ui->cb_mangual_diding->setView(new QListView());

    ui->cb_mangual_jiajian->setGeometry(157 + ddx, y + dy * 3 + ddy, 287, 31);
    ui->cb_mangual_jiajian->setStyleSheet("QComboBox{border:2px solid #D7D7D7;border-radius: 4px;}"
                                          "QComboBox QAbstractItemView::item{height:50px;}"
                                          "QComboBox::down-arrow{image:url(:/images/bt/arrowdownBo.png);}"
                                          "QComboBox::drop-down{border:0px;}");
    ui->cb_mangual_jiajian->setView(new QListView());

    ui->le_manualtest_liuliang->setGeometry(157, y + dy * 4, 291, 35);
    ui->le_manualtest_liuliang->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");

    ui->le_enternumeber->setGeometry(629, 413, 223, 38);
    ui->le_enternumeber->setMargin(3);
    ui->le_enternumeber->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/ed_enterNumber.png);font-size:17px}");



    ui->cb_mangual_zhengliu->addItem(m_ptc->toUnicode("mL"));
    ui->cb_mangual_zhengliu->addItem(m_ptc->toUnicode("s"));



    ui->cb_mangual_diding->addItem(m_ptc->toUnicode("边蒸馏边滴定"));
    ui->cb_mangual_diding->addItem(m_ptc->toUnicode("先蒸馏后滴定"));


    ui->cb_mangual_jiajian->addItem(m_ptc->toUnicode("先加碱后蒸馏"));
    ui->cb_mangual_jiajian->addItem(m_ptc->toUnicode("先蒸馏后加碱"));

    //bt
    ui->pb_manualtest_clean->setFlat(true);
    //ui->pb_manualtest_clean->setFocusPolicy(Qt::NoFocus);
    ui->pb_manualtest_clean->setGeometry(431,249,108,44);
    ui->pb_manualtest_clean->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_clean_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_clean_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_clean_press.png);}");

    ui->pb_manualtest_save->setFlat(true);
    //ui->pb_manualtest_save->setFocusPolicy(Qt::NoFocus);
    ui->pb_manualtest_save->setGeometry(431, 605,108,44);
    ui->pb_manualtest_save->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_save_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_save_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_save_press.png);}");

    ui->pb_manualtest_1->setFlat(true);
   //ui->pb_manualtest_1->setFocusPolicy(Qt::NoFocus);
    ui->pb_manualtest_1->setGeometry(629,471,69,34);
    ui->pb_manualtest_1->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/btn_board1normal.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_board1normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_board1press.png);}");


    ui->pb_manualtest_4->setFlat(true);
    //ui->pb_manualtest_4->setFocusPolicy(Qt::NoFocus);
    ui->pb_manualtest_4->setGeometry(629,518,69,34);
    ui->pb_manualtest_4->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/btn_board4normal.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_board4normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_board4press.png);}");


    ui->pb_manualtest_7->setFlat(true);
    //ui->pb_manualtest_7->setFocusPolicy(Qt::NoFocus);
    ui->pb_manualtest_7->setGeometry(629,565,69,34);
    ui->pb_manualtest_7->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/btn_board7noraml.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_board7noraml.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_board7press.png);}");


    ui->pb_manualtest_c->setFlat(true);
    //ui->pb_manualtest_c->setFocusPolicy(Qt::NoFocus);
    ui->pb_manualtest_c->setGeometry(629,613,69,34);
    ui->pb_manualtest_c->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/btn_cnormal.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_cnormal.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_cpress.png);}");

    ui->pb_manualtest_2->setFlat(true);
    //ui->pb_manualtest_2->setFocusPolicy(Qt::NoFocus);
    ui->pb_manualtest_2->setGeometry(711,471,69,34);
    ui->pb_manualtest_2->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/btn_board2normal.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_board2normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_board2press.png);}");


    ui->pb_manualtest_5->setFlat(true);
    //ui->pb_manualtest_5->setFocusPolicy(Qt::NoFocus);
    ui->pb_manualtest_5->setGeometry(711,518,69,34);
    ui->pb_manualtest_5->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/btn_board5normal.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_board5normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_board5press.png);}");


    ui->pb_manualtest_8->setFlat(true);
    //ui->pb_manualtest_8->setFocusPolicy(Qt::NoFocus);
    ui->pb_manualtest_8->setGeometry(711,565,69,34);
    ui->pb_manualtest_8->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/btn_board8normal.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_board8normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_board8press.png);}");


    ui->pb_manualtest_0->setFlat(true);
    //ui->pb_manualtest_0->setFocusPolicy(Qt::NoFocus);
    ui->pb_manualtest_0->setGeometry(711,613,69,34);
    ui->pb_manualtest_0->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/btn_board0normal.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_board0normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_board0press.png);}");


    ui->pb_manualtest_3->setFlat(true);
    //ui->pb_manualtest_3->setFocusPolicy(Qt::NoFocus);
    ui->pb_manualtest_3->setGeometry(790,471,69,34);
    ui->pb_manualtest_3->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/btn_board3normal.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_board3normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_board3press.png);}");


    ui->pb_manualtest_6->setFlat(true);
    //ui->pb_manualtest_6->setFocusPolicy(Qt::NoFocus);
    ui->pb_manualtest_6->setGeometry(790,518,69,34);
    ui->pb_manualtest_6->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/btn_board6normal.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_board6normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_board6press.png);}");

    ui->pb_manualtest_9->setFlat(true);
    //ui->pb_manualtest_9->setFocusPolicy(Qt::NoFocus);
    ui->pb_manualtest_9->setGeometry(790,565,69,34);
    ui->pb_manualtest_9->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/btn_board9normal.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_board9normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_board9press.png);}");



    ui->pb_manualtest_ok->setFlat(true);
    //ui->pb_manualtest_ok->setFocusPolicy(Qt::NoFocus);
    ui->pb_manualtest_ok->setGeometry(790,613,69,34);
    ui->pb_manualtest_ok->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/btn_oknormal.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_oknormal.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_okpress.png);}");




    //lable

    ui->lb_manualtest_checkpengsuan->setGeometry(619, 269, 100, 30);
    ui->lb_manualtest_checkpengsuan->setText(m_ptc->toUnicode("硼酸："));
    ui->lb_manualtest_checkpengsuan->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_manualtest_checkxishishui->setGeometry(619, 315, 100, 30);
    ui->lb_manualtest_checkxishishui->setText(m_ptc->toUnicode("稀释水："));
    ui->lb_manualtest_checkxishishui->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_manualtest_checkzhengliu->setGeometry(619, 361, 100, 30);
    ui->lb_manualtest_checkzhengliu->setText(m_ptc->toUnicode("蒸馏："));
    ui->lb_manualtest_checkzhengliu->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_manualtest_checkjian->setGeometry(782, 269, 100, 30);
    ui->lb_manualtest_checkjian->setText(m_ptc->toUnicode("碱："));
    ui->lb_manualtest_checkjian->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_manualtest_checkdiding->setGeometry(782, 315, 100, 30);
    ui->lb_manualtest_checkdiding->setText(m_ptc->toUnicode("滴定："));
    ui->lb_manualtest_checkdiding->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->label->setGeometry(28,9,111,36);
    ui->label->setText(m_ptc->toUnicode("实验数据"));
    ui->label->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_2->setGeometry(28,315,111,36);
    ui->label_2->setText(m_ptc->toUnicode("方法"));
    ui->label_2->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_3->setGeometry(600,9,111,36);
    ui->label_3->setText(m_ptc->toUnicode("状态"));
    ui->label_3->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_4->setGeometry(600,220,111,36);
    ui->label_4->setText(m_ptc->toUnicode("操作"));
    ui->label_4->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    m_plbcheckpengsuan = new QMLabel(this);
    m_plbcheckpengsuan->setGeometry(689,269,39, 39);
    m_plbcheckpengsuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");


    m_plbcheckjian = new QMLabel(this);
    m_plbcheckjian->setGeometry(836,269,39, 39);
    m_plbcheckjian->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");


    m_plbcheckxishishui = new QMLabel(this);
    m_plbcheckxishishui->setGeometry(689,315,39, 39);
    m_plbcheckxishishui->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");


    m_plbcheckdiding = new QMLabel(this);
    m_plbcheckdiding->setGeometry(836,315,39, 39);
    m_plbcheckdiding->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");


    m_plbcheckzhengliu = new QMLabel(this);
    m_plbcheckzhengliu->setGeometry(689,361,39, 39);
    m_plbcheckzhengliu->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");


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
}

void QManualTestForm::InitSings()
{
    connect(m_pLbxiaohuaguanonoff, SIGNAL(clicked()), this, SLOT(xiaohuaguan()));
    connect(m_pLbjieshoubeoonoff, SIGNAL(clicked()), this, SLOT(jieshoubei()));
    connect(m_plbcheckpengsuan, SIGNAL(clicked()), this, SLOT(checkpengsuan()));
    connect(m_plbcheckjian, SIGNAL(clicked()), this, SLOT(checkjian()));
    connect(m_plbcheckxishishui, SIGNAL(clicked()), this, SLOT(checkxishishui()));
    connect(m_plbcheckdiding, SIGNAL(clicked()), this, SLOT(checkdiding()));
    connect(m_plbcheckzhengliu, SIGNAL(clicked()), this, SLOT(checkzhengliu()));

}

void QManualTestForm::AnalysisData(QByteArray pData)
{
    //qDebug("Manual ReadThread back.");
    unsigned char j = (int)pData.at(4);
    unsigned int jj = (int)j;
    j = (int)pData.at(5);
    jj = jj << 8;
    jj = jj | j;

    switch (jj) {
    case _SERIALCMD_MCU_STATE_:
       {
           StateSensor(pData);
       }
       break;
    default:
        break;
    }
}

bool QManualTestForm::checkusername(QString strname)
{
    if(true == pdataquery->opendatabase())
    {
        //QString strname = "mingcheng";
        linstvalues.clear();
        pdataquery->GetValues(strtable, linstvalues, 1);
        pdataquery->cloesdatabase();
    }
    for(int i = 0; i < linstvalues.count(); i++)
    {
        if(strname == linstvalues.at(i))
        {
            return false;
        }
    }

    return true;
}

void QManualTestForm::StateSensor(QByteArray pData)
{
     unsigned int ibool = 0;
     unsigned int iNum = 0;
     QString strNum;
     QString str;
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


void QManualTestForm::xiaohuaguan()
{
    if(m_bxiaohuaguanflag)
    {
        m_pLbxiaohuaguanonoff->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    }
    else
    {
        m_pLbxiaohuaguanonoff->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
    }

    m_bxiaohuaguanflag = !m_bxiaohuaguanflag;
}

void QManualTestForm::jieshoubei()
{
    if(m_bjieshoubeiflag)
    {
        m_pLbjieshoubeoonoff->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    }
    else
    {
        m_pLbjieshoubeoonoff->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
    }

    m_bjieshoubeiflag = !m_bjieshoubeiflag;
}

void QManualTestForm::checknum(QString strNum)
{
    int i = strNum.toInt();
    if(i > MAX_DIDING)
    {
        QMessageBox::warning(this, m_ptc->toUnicode("最大值为2000"), m_ptc->toUnicode(""), QMessageBox::Ok);
        return;
    }
}

void QManualTestForm::checkpengsuan()
{
    if(true == m_blbcheckpengsuan)
     {
        m_plbcheckpengsuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_blbcheckpengsuan = false;

        m_plbcheckjian->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckjian = true;

        m_plbcheckxishishui->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckxishishui = true;

        m_plbcheckdiding->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckdiding = true;

        m_plbcheckzhengliu->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckzhengliu = true;


     }
     else
     {
        m_plbcheckpengsuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckpengsuan = true;
     }
}


void QManualTestForm::checkjian()
{
    if(true == m_blbcheckjian)
     {
        m_plbcheckpengsuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckpengsuan = true;

        m_plbcheckjian->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_blbcheckjian = false;

        m_plbcheckxishishui->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckxishishui = true;

        m_plbcheckdiding->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckdiding = true;

        m_plbcheckzhengliu->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckzhengliu = true;


     }
     else
     {
        m_plbcheckjian->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckjian = true;
     }
}

void QManualTestForm::checkxishishui()
{
    if(true == m_blbcheckxishishui)
     {
        m_plbcheckpengsuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckpengsuan = true;

        m_plbcheckjian->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckjian = true;

        m_plbcheckxishishui->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_blbcheckxishishui = false;

        m_plbcheckdiding->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckdiding = true;

        m_plbcheckzhengliu->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckzhengliu = true;
     }
     else
     {
        m_plbcheckxishishui->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckxishishui = true;
     }
}

void QManualTestForm::checkdiding()
{
    if(true == m_blbcheckdiding)
     {
        m_plbcheckpengsuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckpengsuan = true;

        m_plbcheckjian->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckjian = true;

        m_plbcheckxishishui->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckxishishui = true;

        m_plbcheckdiding->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_blbcheckdiding = false;

        m_plbcheckzhengliu->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckzhengliu = true;


     }
     else
     {
        m_plbcheckdiding->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckdiding = true;
     }
}

void QManualTestForm::checkzhengliu()
{
    if(true == m_blbcheckzhengliu)
     {
        m_plbcheckpengsuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckpengsuan = true;

        m_plbcheckjian->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckjian = true;

        m_plbcheckxishishui->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckxishishui = true;

        m_plbcheckdiding->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckdiding = true;

        m_plbcheckzhengliu->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_blbcheckzhengliu = false;


     }
     else
     {
        m_plbcheckzhengliu->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_blbcheckzhengliu = true;
     }
}


void QManualTestForm::on_pb_manualtest_1_clicked()
{
    if((true == m_blbcheckpengsuan) && (true == m_blbcheckjian) && (true == m_blbcheckxishishui) && (true == m_blbcheckdiding) && (true == m_blbcheckzhengliu))
    {
        return;
    }
    int j = 0;
    QString str = ui->le_enternumeber->text();
    j = str.toInt();
    if(false == m_blbcheckzhengliu)
    {
        int i = ui->cb_mangual_zhengliu->currentIndex(); // 0--ml 1--s

        if(0 == i)
        {
            j *= 10;
            j += 1;
            if(j > 430)
            {
                return;
            }
        }
        else
        {
            j *= 10;
            j += 1;
            if(j > 900)
            {
                return;
            }
        }
    }
    else
    {
        j *= 10;
        j += 1;
        if(j > MAX_DIDING)
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("最大值为2000"), QMessageBox::Ok);
            return;
        }
    }
    str = ui->le_enternumeber->text();
    int i = str.toInt();
    if(0 == i)
    {
        str = "";
    }
    str = str + "1";
    ui->le_enternumeber->setText(str);
}

void QManualTestForm::on_pb_manualtest_2_clicked()
{
    if((true == m_blbcheckpengsuan) && (true == m_blbcheckjian) && (true == m_blbcheckxishishui) && (true == m_blbcheckdiding) && (true == m_blbcheckzhengliu))
    {
        return;
    }
    int j = 0;
    QString str = ui->le_enternumeber->text();
    j = str.toInt();
    if(false == m_blbcheckzhengliu)
    {
        int i = ui->cb_mangual_zhengliu->currentIndex(); // 0--ml 1--s

        if(0 == i)
        {
            j *= 10;
            j += 2;
            if(j > 430)
            {
                return;
            }
        }
        else
        {
            j *= 10;
            j += 2;
            if(j > 900)
            {
                return;
            }
        }
    }
    else
    {
        j *= 10;
        j += 2;
        if(j > MAX_DIDING)
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("最大值为2000"), QMessageBox::Ok);
            return;
        }
    }

    str = ui->le_enternumeber->text();
    int i = str.toInt();
    if(0 == i)
    {
        str = "";
    }
    str = str + "2";
    ui->le_enternumeber->setText(str);
}

void QManualTestForm::on_pb_manualtest_3_clicked()
{
    if((true == m_blbcheckpengsuan) && (true == m_blbcheckjian) && (true == m_blbcheckxishishui) && (true == m_blbcheckdiding) && (true == m_blbcheckzhengliu))
    {
        return;
    }
    int j = 0;
    QString str = ui->le_enternumeber->text();
    j = str.toInt();
    if(false == m_blbcheckzhengliu)
    {
        int i = ui->cb_mangual_zhengliu->currentIndex(); // 0--ml 1--s

        if(0 == i)
        {
            j *= 10;
            j += 3;
            if(j > 430)
            {
                return;
            }
        }
        else
        {
            j *= 10;
            j += 3;
            if(j > 900)
            {
                return;
            }
        }
    }
    else
    {
        j *= 10;
        j += 3;
        if(j > MAX_DIDING)
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("最大值为2000"), QMessageBox::Ok);
            return;
        }
    }
    str = ui->le_enternumeber->text();
    int i = str.toInt();
    if(0 == i)
    {
        str = "";
    }
    str = str + "3";
    ui->le_enternumeber->setText(str);
}

void QManualTestForm::on_pb_manualtest_4_clicked()
{
    if((true == m_blbcheckpengsuan) && (true == m_blbcheckjian) && (true == m_blbcheckxishishui) && (true == m_blbcheckdiding) && (true == m_blbcheckzhengliu))
    {
        return;
    }
    int j = 0;
    QString str = ui->le_enternumeber->text();
    j = str.toInt();
    if(false == m_blbcheckzhengliu)
    {
        int i = ui->cb_mangual_zhengliu->currentIndex(); // 0--ml 1--s

        if(0 == i)
        {
            j *= 10;
            j += 4;
            if(j > 430)
            {
                return;
            }
        }
        else
        {
            j *= 10;
            j += 4;
            if(j > 900)
            {
                return;
            }
        }
    }
    else
    {
        j *= 10;
        j += 4;
        if(j > MAX_DIDING)
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("最大值为2000"), QMessageBox::Ok);
            return;
        }
    }
    str = ui->le_enternumeber->text();
    int i = str.toInt();
    if(0 == i)
    {
        str = "";
    }
    str = str + "4";
    ui->le_enternumeber->setText(str);
}

void QManualTestForm::on_pb_manualtest_5_clicked()
{
    if((true == m_blbcheckpengsuan) && (true == m_blbcheckjian) && (true == m_blbcheckxishishui) && (true == m_blbcheckdiding) && (true == m_blbcheckzhengliu))
    {
        return;
    }
    int j = 0;
    QString str = ui->le_enternumeber->text();
    j = str.toInt();
    if(false == m_blbcheckzhengliu)
    {
        int i = ui->cb_mangual_zhengliu->currentIndex(); // 0--ml 1--s

        if(0 == i)
        {
            j *= 10;
            j += 5;
            if(j > 430)
            {
                return;
            }
        }
        else
        {
            j *= 10;
            j += 5;
            if(j > 900)
            {
                return;
            }
        }
    }
    else
    {
        j *= 10;
        j += 5;
        if(j > MAX_DIDING)
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("最大值为2000"), QMessageBox::Ok);
            return;
        }
    }
    str = ui->le_enternumeber->text();
    int i = str.toInt();
    if(0 == i)
    {
        str = "";
    }
    str = str + "5";
    ui->le_enternumeber->setText(str);
}

void QManualTestForm::on_pb_manualtest_6_clicked()
{
    if((true == m_blbcheckpengsuan) && (true == m_blbcheckjian) && (true == m_blbcheckxishishui) && (true == m_blbcheckdiding) && (true == m_blbcheckzhengliu))
    {
        return;
    }
    int j = 0;
    QString str = ui->le_enternumeber->text();
    j = str.toInt();
    if(false == m_blbcheckzhengliu)
    {
        int i = ui->cb_mangual_zhengliu->currentIndex(); // 0--ml 1--s

        if(0 == i)
        {
            j *= 10;
            j += 6;
            if(j > 430)
            {
                return;
            }
        }
        else
        {
            j *= 10;
            j += 6;
            if(j > 900)
            {
                return;
            }
        }
    }
    else
    {
        j *= 10;
        j += 6;
        if(j > MAX_DIDING)
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("最大值为2000"), QMessageBox::Ok);
            return;
        }
    }
    str = ui->le_enternumeber->text();
    int i = str.toInt();
    if(0 == i)
    {
        str = "";
    }
    str = str + "6";
    ui->le_enternumeber->setText(str);
}

void QManualTestForm::on_pb_manualtest_7_clicked()
{
    if((true == m_blbcheckpengsuan) && (true == m_blbcheckjian) && (true == m_blbcheckxishishui) && (true == m_blbcheckdiding) && (true == m_blbcheckzhengliu))
    {
        return;
    }
    int j = 0;
    QString str = ui->le_enternumeber->text();
    j = str.toInt();
    if(false == m_blbcheckzhengliu)
    {
        int i = ui->cb_mangual_zhengliu->currentIndex(); // 0--ml 1--s

        if(0 == i)
        {
            j *= 10;
            j += 7;
            if(j > 430)
            {
                return;
            }
        }
        else
        {
            j *= 10;
            j += 7;
            if(j > 900)
            {
                return;
            }
        }
    }
    else
    {
        j *= 10;
        j += 7;
        if(j > MAX_DIDING)
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("最大值为2000"), QMessageBox::Ok);
            return;
        }
    }
    str = ui->le_enternumeber->text();
    int i = str.toInt();
    if(0 == i)
    {
        str = "";
    }
    str = str + "7";
    ui->le_enternumeber->setText(str);
}

void QManualTestForm::on_pb_manualtest_8_clicked()
{
    if((true == m_blbcheckpengsuan) && (true == m_blbcheckjian) && (true == m_blbcheckxishishui) && (true == m_blbcheckdiding) && (true == m_blbcheckzhengliu))
    {
        return;
    }
    int j = 0;
    QString str = ui->le_enternumeber->text();
    j = str.toInt();
    if(false == m_blbcheckzhengliu)
    {
        int i = ui->cb_mangual_zhengliu->currentIndex(); // 0--ml 1--s

        if(0 == i)
        {
            j *= 10;
            j += 8;
            if(j > 430)
            {
                return;
            }
        }
        else
        {
            j *= 10;
            j += 8;
            if(j > 900)
            {
                return;
            }
        }
    }
    else
    {
        j *= 10;
        j += 8;
        if(j > MAX_DIDING)
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("最大值为2000"), QMessageBox::Ok);
            return;
        }
    }
    str = ui->le_enternumeber->text();
    int i = str.toInt();
    if(0 == i)
    {
        str = "";
    }
    str = str + "8";
    ui->le_enternumeber->setText(str);
}

void QManualTestForm::on_pb_manualtest_9_clicked()
{
    if((true == m_blbcheckpengsuan) && (true == m_blbcheckjian) && (true == m_blbcheckxishishui) && (true == m_blbcheckdiding) && (true == m_blbcheckzhengliu))
    {
        return;
    }
    int j = 0;
    QString str = ui->le_enternumeber->text();
    j = str.toInt();
    if(false == m_blbcheckzhengliu)
    {
        int i = ui->cb_mangual_zhengliu->currentIndex(); // 0--ml 1--s

        if(0 == i)
        {
            j *= 10;
            j += 9;
            if(j > 430)
            {
                return;
            }
        }
        else
        {
            j *= 10;
            j += 9;
            if(j > 900)
            {
                return;
            }
        }
    }
    else
    {
        j *= 10;
        j += 9;
        if(j > MAX_DIDING)
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("最大值为2000"), QMessageBox::Ok);
            return;
        }
    }
    str = ui->le_enternumeber->text();
    int i = str.toInt();
    if(0 == i)
    {
        str = "";
    }
    str = str + "9";
    ui->le_enternumeber->setText(str);
}

void QManualTestForm::on_pb_manualtest_0_clicked()
{
    if((true == m_blbcheckpengsuan) && (true == m_blbcheckjian) && (true == m_blbcheckxishishui) && (true == m_blbcheckdiding) && (true == m_blbcheckzhengliu))
    {
        return;
    }
    int j = 0;
    QString str = ui->le_enternumeber->text();
    j = str.toInt();
    if(false == m_blbcheckzhengliu)
    {
        int i = ui->cb_mangual_zhengliu->currentIndex(); // 0--ml 1--s

        if(0 == i)
        {
            j *= 10;
            j += 0;
            if(j > 430)
            {
                return;
            }
        }
        else
        {
            j *= 10;
            j += 0;
            if(j > 900)
            {
                return;
            }
        }
    }
    else
    {
        j *= 10;
        j += 0;
        if(j > MAX_DIDING)
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("最大值为2000"), QMessageBox::Ok);
            return;
        }
    }
    str = ui->le_enternumeber->text();
    int i = str.toInt();
    if(0 == i)
    {
        str = "0";
    }
    else
    {
        str = str + "0";
    }

    ui->le_enternumeber->setText(str);
}

void QManualTestForm::on_pb_manualtest_c_clicked()
{
    if((true == m_blbcheckpengsuan) && (true == m_blbcheckjian) && (true == m_blbcheckxishishui) && (true == m_blbcheckdiding) && (true == m_blbcheckzhengliu))
    {
        return;
    }
    QString str = "0";
    ui->le_enternumeber->setText(str);
}

void QManualTestForm::on_pb_manualtest_ok_clicked()
{
    if((true == m_blbcheckpengsuan) && (true == m_blbcheckjian) && (true == m_blbcheckxishishui) && (true == m_blbcheckdiding) && (true == m_blbcheckzhengliu))
    {
        return;
    }
    QString str = "";
    str = ui->le_enternumeber->text();

    m_Serialcmd.clear();
    m_Serialdata.clear();

    quint16 i = 0;
    i  = str.toInt();

    if(false == m_blbcheckpengsuan)
    {
        m_Serialcmd.append(0x04);
        m_Serialcmd.append(0x01);
        str = ui->le_manualtest_pengsuan->text();
        int j = 0;
        j = str.toInt();
        m_Serialdata.append(i);
        j = i + j;
        str = str.number(j);
        ui->le_manualtest_pengsuan->setText(str);
    }

    if(false == m_blbcheckjian)
    {
        m_Serialcmd.append(0x04);
        m_Serialcmd.append(0x03);
        str = ui->le_manualtest_jian->text();
        int j = 0;
        j = str.toInt();
        m_Serialdata.append(i);
        j = i + j;
        str = str.number(j);
        ui->le_manualtest_jian->setText(str);
    }

    if(false == m_blbcheckxishishui)
    {
        m_Serialcmd.append(0x04);
        m_Serialcmd.append(0x02);
        str = ui->le_manualtest_xishishui->text();
        int j = 0;
        j = str.toInt();
        m_Serialdata.append(i);
        j = i + j;
        str = str.number(j);
        ui->le_manualtest_xishishui->setText(str);
    }

    if(false == m_blbcheckdiding)
    {
        m_Serialcmd.append(0x04);
        m_Serialcmd.append(0x05);
        str = ui->le_manualtest_diding->text();
        int j = 0;
        j = str.toInt();
        m_Serialdata << i;
        j = i + j;
        str = str.number(j);
        ui->le_manualtest_diding->setText(str);
    }

    if(false == m_blbcheckzhengliu)
    {
        m_Serialcmd.append(0x04);
        m_Serialcmd.append(0x04);
        str = ui->le_manualtest_zhengliu->text();
        int j = 0;
        j = str.toInt();
        if(i > 255)
        {
            m_Serialdata.append(i >> 8);
            m_Serialdata.append(i & 0x00FF);
        }
        else
        {
            m_Serialdata.append(char(0x00));
            m_Serialdata.append(i);
        }
        int zhengliudanwei = ui->cb_mangual_zhengliu->currentIndex();
        m_Serialdata.append(quint8(zhengliudanwei));
        j = i + j;
        str = str.number(j);
        ui->le_manualtest_zhengliu->setText(str);
    }
    m_pSerialManual->TransmitData(m_Serialcmd, m_Serialdata);
    m_brunning = true;
}

void QManualTestForm::on_pb_manualtest_clean_clicked()
{
    ui->le_manualtest_pengsuan->clear();
    ui->le_manualtest_jian->clear();
    ui->le_manualtest_xishishui->clear();
    ui->le_manualtest_diding->clear();
    ui->le_manualtest_zhengliu->clear();
}

void QManualTestForm::on_pb_manualtest_save_clicked()
{
    QString strmingcheng = "";
    QString strxishu = "";
    QString strpengsuan = "";
    QString strxishishui = "";
    QString strjian = "";
    QString strzhengliu = "";
    QString strliulang = "";
    QString strzhengliudanwei = "";
    QString strdidingfangshi = "";
    QString strjiajianfangshi = "";
    QString strxiaohuaguan = "";
    QString strjieshoubei = "";



    strmingcheng = ui->le_manualtest_mingcheng->text();
    strxishu = ui->le_manualtest_xishu->text();
    strpengsuan = ui->le_manualtest_pengsuan->text();
    strxishishui = ui->le_manualtest_xishishui->text();
    strjian = ui->le_manualtest_jian->text();
    strzhengliu = ui->le_manualtest_zhengliu->text();
    strliulang = ui->le_manualtest_liuliang->text();

    if((strmingcheng.isEmpty()) || (strxishu.isEmpty()) || (strpengsuan.isEmpty()) || (strxishishui.isEmpty()) || (strjian.isEmpty()) || (strzhengliu.isEmpty()) || (strliulang.isEmpty()))
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("数据不能为空"), QMessageBox::Ok);
        return;
    }

    if(false == checkusername(strmingcheng))
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("方法名重复"), QMessageBox::Ok);
        return;
    }


    if(0 == ui->cb_mangual_diding->currentIndex())
    {
        strdidingfangshi = "0";
    }
    else
    {
        strdidingfangshi = "1";
    }

    if(0 == ui->cb_mangual_jiajian->currentIndex())
    {
        strjiajianfangshi = "0";
    }
    else
    {
        strjiajianfangshi = "1";
    }

    if(0 == ui->cb_mangual_zhengliu->currentIndex())
    {
        strzhengliudanwei = "0";
    }
    else
    {
        strzhengliudanwei = "1";
    }

    if(false == m_bjieshoubeiflag)
    {
        strjieshoubei = "0";
    }
    else
    {
        strjieshoubei = "1";
    }

    if(false == m_bxiaohuaguanflag)
    {
        strxiaohuaguan = "0";
    }
    else
    {
        strxiaohuaguan = "1";
    }

    if(true == pdataquery->opendatabase())
    {

        if(linstvalues.size() >= 99)
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("数据超出范围"), QMessageBox::Ok);
            return;
        }
    }

    linstname.clear();
    linstvalues.clear();
    //linstname << m_ptc->toUnicode("id") << m_ptc->toUnicode("mingcheng") << m_ptc->toUnicode("xishu") <<
    //linstname.append(m_ptc->toUnicode("id"));
    linstname.append(m_ptc->toUnicode("mingcheng"));
    linstname.append(m_ptc->toUnicode("xishu"));
    linstname.append(m_ptc->toUnicode("pengsuan"));
    linstname.append(m_ptc->toUnicode("xishishui"));
    linstname.append(m_ptc->toUnicode("jian"));
    linstname.append(m_ptc->toUnicode("zhengliu"));
    linstname.append(m_ptc->toUnicode("zhengliudanwei"));
    linstname.append(m_ptc->toUnicode("diding"));
    linstname.append(m_ptc->toUnicode("jiajian"));
    linstname.append(m_ptc->toUnicode("zhengqiliuliang"));
    linstname.append(m_ptc->toUnicode("xiaohuaguan"));
    linstname.append(m_ptc->toUnicode("jieshoubei"));

    //linstvalues.append(m_ptc->toUnicode("1"));
    linstvalues.append(strmingcheng);
    linstvalues.append(strxishu);
    linstvalues.append(strpengsuan);
    linstvalues.append(strxishishui);
    linstvalues.append(strjian);
    linstvalues.append(strzhengliu);
    linstvalues.append(strzhengliudanwei);
    linstvalues.append(strdidingfangshi);
    linstvalues.append(strjiajianfangshi);
    linstvalues.append(strliulang);
    linstvalues.append(strxiaohuaguan);
    linstvalues.append(strjieshoubei);

    {
        pdataquery->insert(strtable, linstname, linstvalues);
    }
    QMainScreen *pWidget = static_cast<QMainScreen *>(this->parent());
    pWidget->m_pMethod->updatedatabase();
    pWidget->m_pAutoTest->updatabase();
/*
    linstvalues.clear();
    pdataquery->GetValues(strtable, linstvalues, 1);
    pdataquery->cloesdatabase();
 */

    HNMsgBox::warning(this, "保存成功");
}
