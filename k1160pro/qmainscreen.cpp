#include "qmainscreen.h"
#include "ui_qmainscreen.h"
#include "qinputtool.h"

QMainScreen::QMainScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMainScreen),
    m_pTimer(NULL),
    m_pAutoTest(NULL),
    m_pAutoPro(NULL),
    m_pManualTest(NULL),
    m_pclean(NULL),
    m_pDataBase(NULL),
    m_pMethod(NULL),
    m_pMachine(NULL),
    m_pSettingclean(NULL),
    m_pCheck(NULL),
    m_pNet(NULL),
    m_pDebug(NULL),
    m_pSettingUser(NULL),
    m_pHelp(NULL),
    m_pUser(NULL),
    m_cloud(NULL),
    m_pSettingOrigins(NULL),
    m_pSerialProtcol(NULL),
    m_bNetFlag(false),
    m_bSettingFlag(false),
    m_bDataFlag(false),
    m_iUserlevel(2),
    m_bwififlag(false)
{
    ui->setupUi(this);
    m_ptc =  QTextCodec::codecForName("UTF-8");
    if(NULL == m_pTimer)
    {
       m_pTimer = new QTimer();
    }

    if(NULL == m_pSerialProtcol)
    {
        m_pSerialProtcol = new QSerialProtcol(this);
    }

    //
    InitOCX();
    InitSings();

    m_pLbTest->setFocus();
    /*

    */
    m_pTimer->start(1000);


}

QMainScreen::~QMainScreen()
{
    delete ui;
}

void QMainScreen::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setStyleSheet("QWidget#QMainScreen{image:url(:/images/bk/bk_mainscreen.png)}""QMainScreen{background-color:transparent;}");

    //bt
    QPalette pe;
    pe.setColor(QPalette::WindowText,QColor(255,255,255));
    ui->lab_mainscreenDlg_Time->setPalette(pe);
    ui->lab_mainscreenDlg_Time->setGeometry(857,28,158, 38);
    ui->lab_mainscreenDlg_Time->setText(m_ptc->toUnicode(""));
    ui->lab_mainscreenDlg_Time->setStyleSheet("QLabel{background-color:transparent;font-size:12px}");
    ui->lab_mainscreenDlg_Time->setForegroundRole(QPalette::BrightText);

    ui->label_wifi->setGeometry(800,5,32,32);
    //ui->label_wifi->setPalette(pe);
    if(HNEthManager::Instance((this))->currentWifi()[ESSID_STATUS] == "COMPLETED")
    {
        ui->label_wifi->setStyleSheet("QLabel{background-color:transparent;font-size:12px}""QLabel{background-image: url(:/images/bt/wifi_on.png);}");
    }
    else
        ui->label_wifi->setStyleSheet("QLabel{background-color:transparent;font-size:12px}""QLabel{background-image: url(:/images/bt/wifi_off.png);}");
    //ui->label_wifi->setStyleSheet("QLabel{background-color:transparent;font-size:16px}");
    //ui->label_wifi->setText(m_ptc->toUnicode("未连接"));

    ui->lb_userimage->setGeometry(850,8,28, 28);
    ui->lb_userimage->setStyleSheet("QLabel{background-color:transparent;font-size:12px}");

    ui->lb_userinfo->setPalette(pe);
    ui->lb_userinfo->setGeometry(891,8,158, 38);
    ui->lb_userinfo->setText(m_ptc->toUnicode(""));
    ui->lb_userinfo->setStyleSheet("QLabel{background-color:transparent;font-size:12px}");
    ui->lb_userinfo->setForegroundRole(QPalette::BrightText);

    //label
    m_pLbTest = new QMLabel(this);
    m_pLbTest->setGeometry(0, 61, 108, 102);
    m_pLbTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_test_normal.png);}""QMLabel:press{background-image: url(:/images/bt/lab_test_press.png);}");

    m_pLbData = new QMLabel(this);
    m_pLbData->setGeometry(0, 162, 108, 102);
    m_pLbData->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_data_normal.png);}");

    m_pLbSetting = new QMLabel(this);
    m_pLbSetting->setGeometry(0, 263, 108, 102);
    m_pLbSetting->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_setting_normal.png);}");

    m_pLbHelp = new QMLabel(this);
    m_pLbHelp->setGeometry(0, 364, 108, 102);
    m_pLbHelp->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_help_normal.png);}");

    m_pLbUser = new QMLabel(this);
    m_pLbUser->setGeometry(0, 465, 108, 102);
    m_pLbUser->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_user_normal.png);}");

    m_pLbServer = new QMLabel(this);
    m_pLbServer->setObjectName("m_pLbServer");
    m_pLbServer->setGeometry(0, 566, 108, 102);
    m_pLbServer->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_server_normal.png);}");

    m_pLbEmpty = new QMLabel(this);
    m_pLbEmpty->setGeometry(0, 667, 108, 102);
    m_pLbEmpty->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_empty_normal.png);}");

    //label
    //1
    m_pLbAutoTest = new QMLabel(this);
    m_pLbAutoTest->hide();
    m_pLbAutoTest->setGeometry(108, 64, 111, 36);
    m_pLbAutoTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_autotest_auto_press.png);}");

    m_pLbManualTest = new QMLabel(this);
    m_pLbManualTest->hide();
    m_pLbManualTest->setGeometry(223, 64, 111, 36);
    m_pLbManualTest->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_autotest_manual.png);}");

    m_pLbClean = new QMLabel(this);
    m_pLbClean->hide();
    m_pLbClean->setGeometry(338,64,111, 36);
    m_pLbClean->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_autotest_normal.png);}");

    //2
    m_pLbTitleTest = new QMLabel(this);
    m_pLbTitleTest->hide();
    m_pLbTitleTest->setGeometry(108, 64, 111, 36);
    m_pLbTitleTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_titletest.png);}");

    m_pLbMachine = new QMLabel(this);
    m_pLbMachine->hide();
    m_pLbMachine->setGeometry( 223, 64, 111, 36);
    m_pLbMachine->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_machine.png);}");

    m_pLbUpgrade = new QMLabel(this);
    m_pLbUpgrade->hide();
    m_pLbUpgrade->setGeometry( 223, 64, 111, 36);
    m_pLbUpgrade->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(./skin/default/lab_upgrade_normal.png);}");
    m_pLbUpgrade->hide();

    m_pLbTitleClean = new QMLabel(this);
    m_pLbTitleClean->hide();
    m_pLbTitleClean->setGeometry(338,64,111, 36);
    m_pLbTitleClean->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_clean.png);}");

    m_pLbCheck = new QMLabel(this);
    m_pLbCheck->hide();
    m_pLbCheck->setGeometry(453, 64, 111, 36);
    m_pLbCheck->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_check.png);}");

    m_pLbNet = new QMLabel(this);
    m_pLbNet->hide();
    m_pLbNet->setGeometry( 568, 64, 111, 36);
    m_pLbNet->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(://images/bt/lab_net.png);}");

    m_pLbDebug = new QMLabel(this);
    m_pLbDebug->hide();
    m_pLbDebug->setGeometry(683,64,111, 36);
    m_pLbDebug->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_debug.png);}");

    m_pLbTitleUser = new QMLabel(this);
    m_pLbTitleUser->hide();
    m_pLbTitleUser->setGeometry(798, 64, 111, 36);
    m_pLbTitleUser->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_titleuser.png);}");

    m_pLbSuyuan = new QMLabel(this);
    m_pLbSuyuan->hide();
    m_pLbSuyuan->setGeometry( 913, 64, 111, 36);
    m_pLbSuyuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_suyuan.png);}");

    //3
    m_pLbTltileDataBase = new QMLabel(this);
    m_pLbTltileDataBase->hide();
    m_pLbTltileDataBase->setGeometry(108, 64, 111, 36);
    m_pLbTltileDataBase->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_TitleDataBase.png);}");

    //4
    m_pLbTltilePic = new QMLabel(this);
    m_pLbTltilePic->hide();
    m_pLbTltilePic->setGeometry(108, 64, 111, 36);
    m_pLbTltilePic->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(./skin/default/lab_TitlePic_normal.png);}");

    //5
    m_pLbTltileUserManager = new QMLabel(this);
    m_pLbTltileUserManager->hide();
    m_pLbTltileUserManager->setGeometry(108, 64, 111, 36);
    m_pLbTltileUserManager->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_TitleUserManager.png);}");

    //6
    m_pLbTltileCould = new QMLabel(this);
    m_pLbTltileCould->hide();
    m_pLbTltileCould->setGeometry(108, 64, 111, 36);
    m_pLbTltileCould->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_TitleCloud.png);}");

    m_pAutoTest = new QAutoTest(this);
    m_pAutoTest->setWindowModality(Qt::WindowModal);
    m_pAutoTest->hide();
    m_pAutoPro = new QAutoTestaProcessForm(this);
    m_pAutoPro->setWindowModality(Qt::WindowModal);
    m_pAutoPro->hide();
    m_pManualTest = new QManualTestForm(this);
    m_pManualTest->setWindowModality(Qt::WindowModal);
    m_pManualTest->hide();
    m_pclean = new QCleanForm(this);
    m_pclean->setWindowModality(Qt::WindowModal);
    m_pclean->hide();
    m_pDataBase = new HNSampleDataWidget(this);
    m_pDataBase->setWindowModality(Qt::WindowModal);
    m_pDataBase->initAll();
    m_pDataBase->hide();

    m_pUpgrade = new HNUpgradeWidget(this);
    m_pUpgrade->setWindowFlags(Qt::FramelessWindowHint);
    m_pUpgrade->setAttribute(Qt::WA_StyledBackground);
    m_pUpgrade->setGeometry(108,100,916,667);
    m_pUpgrade->setStyleSheet("QWidget#HNUpgradeWidget{image:url(./skin/default/bk_upgrade.png)}""HNUpgradeWidget{background-color:transparent;}");
    m_pUpgrade->setWindowModality(Qt::WindowModal);
    m_pUpgrade->hide();

    m_pMethod = new QSettingMethodForm(this);
    m_pMethod->setWindowModality(Qt::WindowModal);
    m_pMethod->hide();
    m_pHelp = new QHelpForm(this);
    m_pHelp->setWindowModality(Qt::WindowModal);
    m_pHelp->hide();
    m_pUser = new QUserForm(this);
    m_pUser->setWindowModality(Qt::WindowModal);
    m_pUser->hide();
    m_cloud = new HNCloudForm(this);
    m_cloud->setWindowModality(Qt::WindowModal);
    m_cloud->hide();

    //m_pMethod = new QSettingMethodForm(this);
    //m_pMethod->hide();

    m_pMachine = new QSettingMachineForm(this);
    m_pMachine->hide();
    m_pSettingclean = new QSettingCleanForm(this);
    m_pSettingclean->hide();
    m_pCheck = new QSettingCalibrationForm(this);
    m_pCheck->hide();
    m_pNet = new QSettingNetForm(this);
    m_pNet->hide();
    m_pDebug = new QSettingDebugForm(this);
    m_pDebug->hide();
    m_pSettingUser = new QSettingUserForm(this);
    m_pSettingUser->hide();
    m_pSettingOrigins = new QSettingOriginsForm(this);
    m_pSettingOrigins->hide();

 //   m_pCheckDlg = new QCheckFrom(this);
 //   m_pCheckDlg->hide();

    //lab

}

void QMainScreen::InitSings()
{

    QObject::connect(m_pTimer,SIGNAL(timeout()),this,SLOT(ShowTimer()));

    connect(m_pLbTest, SIGNAL(clicked()), this, SLOT(TestDlg()));
    connect(m_pLbData, SIGNAL(clicked()), this, SLOT(DataDlg()));
    connect(m_pLbSetting, SIGNAL(clicked()), this, SLOT(SettingDlg()));
    connect(m_pLbHelp, SIGNAL(clicked()), this, SLOT(HelpDlg()));
    connect(m_pLbUser, SIGNAL(clicked()), this, SLOT(UserDlg()));
    connect(m_pLbServer, SIGNAL(clicked()), this, SLOT(ServerDlg()));

    connect(m_pLbAutoTest, SIGNAL(clicked()), this, SLOT(AutoTestDlg()));
    connect(m_pLbManualTest, SIGNAL(clicked()), this, SLOT(ManualTestDlg()));
    connect(m_pLbClean, SIGNAL(clicked()), this, SLOT(CleanDlg()));
    connect(m_pLbUpgrade, SIGNAL(clicked()), this, SLOT(Upgrade()));
    connect(m_pLbTltilePic, SIGNAL(clicked()), this, SLOT(TltilePic()));

    //2
    connect(m_pLbTitleTest, SIGNAL(clicked()), this, SLOT(TitleTest()));
    connect(m_pLbMachine, SIGNAL(clicked()), this, SLOT(Machine()));
    connect(m_pLbTitleClean, SIGNAL(clicked()), this, SLOT(Clean()));
    connect(m_pLbCheck, SIGNAL(clicked()), this, SLOT(Check()));
    connect(m_pLbNet, SIGNAL(clicked()), this, SLOT(Net()));
    connect(m_pLbDebug, SIGNAL(clicked()), this, SLOT(Debug()));
    connect(m_pLbTitleUser, SIGNAL(clicked()), this, SLOT(TitleUser()));
    connect(m_pLbSuyuan, SIGNAL(clicked()), this, SLOT(Suyuan()));

    connect(m_pUser, SIGNAL(emitHeadIndex(int)), this, SLOT(changehead(int)));
    connect(HNEthManager::Instance(this), SIGNAL(sigConnected()), this, SLOT(NetConnected()));
    connect(HNEthManager::Instance(this), SIGNAL(sigLanConnected()), this, SLOT(NetConnected()));
    connect(HNEthManager::Instance(this), SIGNAL(sigDisConnected()), this, SLOT(NetDisConnected()));
    connect(HNEthManager::Instance(this), SIGNAL(sigLanDisConnected()), this, SLOT(NetDisConnected()));

    //connect(m_pLbEmpty, SIGNAL(clicked()), this, SLOT(TimePicChange()));

    connect(m_cloud, SIGNAL(downSucc()), this, SLOT(slotDownSucc()));

    connect(m_pLbTest, SIGNAL(clicked()), this, SLOT(slotEventFilter()));
    connect(m_pLbData, SIGNAL(clicked()), this, SLOT(slotEventFilter()));
    connect(m_pLbSetting, SIGNAL(clicked()), this, SLOT(slotEventFilter()));
    connect(m_pLbHelp, SIGNAL(clicked()), this, SLOT(slotEventFilter()));
    connect(m_pLbUser, SIGNAL(clicked()), this, SLOT(slotEventFilter()));
    connect(m_pLbServer, SIGNAL(clicked()), this, SLOT(slotEventFilter()));

}


void QMainScreen::NetConnected()
{
    qDebug() << "0000001";
    //ui->label_wifi->setText(m_ptc->toUnicode("连接"));
    ui->label_wifi->setStyleSheet("QLabel{background-color:transparent;font-size:12px}""QLabel{background-image: url(:/images/bt/wifi_on.png);}");
    m_bwififlag = true;
    pline();
    return;
    m_bNetFlag = connecttoserver();
    if(true == m_bNetFlag)
    {
        login();
    }
}

void QMainScreen::NetDisConnected()
{
    qDebug() << "0000002";
    //ui->label_wifi->setText(m_ptc->toUnicode("未连接"));
    ui->label_wifi->setStyleSheet("QLabel{background-color:transparent;font-size:12px}""QLabel{background-image: url(:/images/bt/wifi_off.png);}");
    m_bwififlag = false;

}
void QMainScreen::TestDlg()
{
    m_pLbTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_test_press.png);}");
    m_pLbData->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_data_normal.png);}");
    m_pLbSetting->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_setting_normal.png);}");
    m_pLbHelp->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_help_normal.png);}");
    m_pLbUser->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_user_normal.png);}");
    m_pLbServer->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_server_normal.png);}");

    //1
    m_pLbTltileDataBase->hide();
    //2
    m_pLbAutoTest->show();
    m_pLbManualTest->show();
    m_pLbClean->show();

    //3
    m_pLbTitleTest->hide();
    m_pLbMachine->hide();
    m_pLbTitleClean->hide();
    m_pLbCheck->hide();
    m_pLbNet->hide();
    m_pLbDebug->hide();
    m_pLbTitleUser->hide();
    m_pLbSuyuan->hide();
    m_pLbUpgrade->hide();

    //4
    m_pLbTltilePic->hide();

    //5
    m_pLbTltileUserManager->hide();

    //6
    m_pLbTltileCould->hide();
    showTest();
}

void QMainScreen::DataDlg()
{
    if(true == m_pAutoTest->GetState())
    {
        return;
    }
    stopManuTest();

    m_pLbTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_test_normal.png);}");
    m_pLbData->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_data_press.png);}");
    m_pLbSetting->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_setting_normal.png);}");
    m_pLbHelp->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_help_normal.png);}");
    m_pLbUser->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_user_normal.png);}");
    m_pLbServer->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_server_normal.png);}");

    //1
    m_pLbTltileDataBase->show();
    //2
    m_pLbAutoTest->hide();
    m_pLbManualTest->hide();
    m_pLbClean->hide();

    //3
    m_pLbTitleTest->hide();
    m_pLbMachine->hide();
    m_pLbTitleClean->hide();
    m_pLbCheck->hide();
    m_pLbNet->hide();
    m_pLbDebug->hide();
    m_pLbTitleUser->hide();
    m_pLbSuyuan->hide();

    //4
    m_pLbTltilePic->hide();
    m_pLbUpgrade->hide();

    //5
    m_pLbTltileUserManager->hide();

    //6
    m_pLbTltileCould->hide();


    showData();

    m_pDataBase->refresh();
}

void QMainScreen::SettingDlg()
{
    if(true == m_pAutoTest->GetState())
    {
        return;
    }
    stopManuTest();

    m_pLbTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_test_normal.png);}");
    m_pLbData->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_data_normal.png);}");
    m_pLbSetting->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_setting_press.png);}");
    m_pLbHelp->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_help_normal.png);}");
    m_pLbUser->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_user_normal.png);}");
    m_pLbServer->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_server_normal.png);}");

    //1
    m_pLbTltileDataBase->hide();
    //2
    m_pLbAutoTest->hide();
    m_pLbManualTest->hide();
    m_pLbClean->hide();
    //3
    m_pLbTitleTest->show();
    m_pLbMachine->show();
    m_pLbTitleClean->show();
    m_pLbCheck->show();
    m_pLbNet->show();
    m_pLbDebug->show();
    m_pLbTitleUser->show();
    m_pLbSuyuan->show();
    //4
    m_pLbTltilePic->hide();
    m_pLbUpgrade->hide();
    //5
    m_pLbTltileUserManager->hide();
    //6
    m_pLbTltileCould->hide();
    showSetting();
}

void QMainScreen::HelpDlg()
{
    if(true == m_pAutoTest->GetState())
    {
        return;
    }
    stopManuTest();

    m_pLbTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_test_normal.png);}");
    m_pLbData->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_data_normal.png);}");
    m_pLbSetting->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_setting_normal.png);}");
    m_pLbHelp->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_help_press.png);}");
    m_pLbUser->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_user_normal.png);}");
    m_pLbServer->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_server_normal.png);}");

    //1
    m_pLbTltileDataBase->hide();

    //2
    m_pLbAutoTest->hide();
    m_pLbManualTest->hide();
    m_pLbClean->hide();

    //3
    m_pLbTitleTest->hide();
    m_pLbMachine->hide();
    m_pLbTitleClean->hide();
    m_pLbCheck->hide();
    m_pLbNet->hide();
    m_pLbDebug->hide();
    m_pLbTitleUser->hide();
    m_pLbSuyuan->hide();

    //4
    m_pLbTltilePic->show();
    //m_pLbUpgrade->show();

    //5
    m_pLbTltileUserManager->hide();

    //6
    m_pLbTltileCould->hide();
    showHelp();
}

void QMainScreen::UserDlg()
{
    if(true == m_pAutoTest->GetState())
    {
        return;
    }
    stopManuTest();

    m_pLbTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_test_normal.png);}");
    m_pLbData->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_data_normal.png);}");
    m_pLbSetting->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_setting_normal.png);}");
    m_pLbHelp->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_help_normal.png);}");
    m_pLbUser->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_user_press.png);}");
    m_pLbServer->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_server_normal.png);}");

    //1
    m_pLbTltileDataBase->hide();

    //2
    m_pLbAutoTest->hide();
    m_pLbManualTest->hide();
    m_pLbClean->hide();

    //3
    m_pLbTitleTest->hide();
    m_pLbMachine->hide();
    m_pLbTitleClean->hide();
    m_pLbCheck->hide();
    m_pLbNet->hide();
    m_pLbDebug->hide();
    m_pLbTitleUser->hide();
    m_pLbSuyuan->hide();

    //4
    m_pLbTltilePic->hide();
    m_pLbUpgrade->hide();

    //5
    m_pLbTltileUserManager->show();

    //6
    m_pLbTltileCould->hide();
    showUser();
}

void QMainScreen::ServerDlg()
{
    if(true == m_pAutoTest->GetState())
    {
        return;
    }

    stopManuTest();

    if(0 != getUserLevel())
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("用户权限不足"), QMessageBox::Ok);
        return;
    }


    if(HNEthManager::Instance((this))->currentWifi()[ESSID_STATUS] != "COMPLETED")
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("wifi未连接"), QMessageBox::Ok);
        return;
    }


    if(false == m_pNetControl->m_bUserLogin)
    {
        //QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("用户未登入，请检查wifi链接"), QMessageBox::Ok);
        //return;
    }

    m_pLbTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_test_normal.png);}");
    m_pLbData->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_data_normal.png);}");
    m_pLbSetting->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_setting_normal.png);}");
    m_pLbHelp->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_help_normal.png);}");
    m_pLbUser->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_user_normal.png);}");
    m_pLbServer->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_server_press.png);}");

    //1
    m_pLbTltileDataBase->hide();

    //2
    m_pLbAutoTest->hide();
    m_pLbManualTest->hide();
    m_pLbClean->hide();

    //3
    m_pLbTitleTest->hide();
    m_pLbMachine->hide();
    m_pLbTitleClean->hide();
    m_pLbCheck->hide();
    m_pLbNet->hide();
    m_pLbDebug->hide();
    m_pLbTitleUser->hide();
    m_pLbSuyuan->hide();

    //4
    m_pLbTltilePic->hide();
    m_pLbUpgrade->hide();

    //5
    m_pLbTltileUserManager->hide();

    //6
    m_pLbTltileCould->show();

    showCloud();
}


void QMainScreen::AutoTestDlg()
{
    if(true == m_pAutoTest->GetState())
    {
        return;
    }

    stopManuTest();

    m_pLbAutoTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_autotest_auto_press.png);}");
    m_pLbManualTest->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_autotest_manual.png);}");
    m_pLbClean->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_autotest_normal.png);}");

    //dlg
    m_pAutoTest->show();
    m_pManualTest->hide();
    m_pclean->hide();
}

void QMainScreen::ManualTestDlg()
{
    if(true == m_pAutoTest->GetState())
    {
        return;
    }
    m_pLbAutoTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_autotest_auto_normal.png);}");
    m_pLbManualTest->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_autotest_manual_press.png);}");
    m_pLbClean->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_autotest_normal.png);}");

    //dlg
    m_pAutoTest->hide();
    m_pManualTest->show();
    m_pclean->hide();
}

void QMainScreen::CleanDlg()
{
    if(true == m_pAutoTest->GetState())
    {
        return;
    }

    stopManuTest();

    m_pLbAutoTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_autotest_auto_normal.png);}");
    m_pLbManualTest->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_autotest_manual.png);}");
    m_pLbClean->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_autotest_clean_press.png);}");

    //dlg
    m_pAutoTest->hide();
    m_pManualTest->hide();
    m_pclean->show();
}

//2
void QMainScreen::TitleTest()
{

    m_pLbTitleTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_titletest_press.png);}");
    m_pLbMachine->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_machine.png);}");
    m_pLbTitleClean->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_clean.png);}");
    m_pLbCheck->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_check.png);}");
    m_pLbNet->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(://images/bt/lab_net.png);}");
    m_pLbDebug->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_debug.png);}");
    m_pLbTitleUser->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_titleuser.png);}");
    m_pLbSuyuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_suyuan.png);}");

    m_pMethod->show();
    m_pMachine->hide();
    m_pSettingclean->hide();
    m_pCheck->hide();
    m_pNet->hide();
    m_pDebug->hide();
    m_pSettingUser->hide();
    m_pSettingOrigins->hide();

}

void QMainScreen::Machine()
{
    m_pLbTitleTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_titletest.png);}");
    m_pLbMachine->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_machine_press.png);}");
    m_pLbTitleClean->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_clean.png);}");
    m_pLbCheck->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_check.png);}");
    m_pLbNet->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(://images/bt/lab_net.png);}");
    m_pLbDebug->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_debug.png);}");
    m_pLbTitleUser->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_titleuser.png);}");
    m_pLbSuyuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_suyuan.png);}");

    m_pMethod->hide();
    m_pMachine->show();
    m_pSettingclean->hide();
    m_pCheck->hide();
    m_pNet->hide();
    m_pDebug->hide();
    m_pSettingUser->hide();
    m_pSettingOrigins->hide();
}

void QMainScreen::Clean()
{
    m_pLbTitleTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_titletest.png);}");
    m_pLbMachine->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_machine.png);}");
    m_pLbTitleClean->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_cleanpress.png);}");
    m_pLbCheck->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_check.png);}");
    m_pLbNet->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(://images/bt/lab_net.png);}");
    m_pLbDebug->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_debug.png);}");
    m_pLbTitleUser->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_titleuser.png);}");
    m_pLbSuyuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_suyuan.png);}");

    m_pMethod->hide();
    m_pMachine->hide();
    m_pSettingclean->show();
    m_pCheck->hide();
    m_pNet->hide();
    m_pDebug->hide();
    m_pSettingUser->hide();
    m_pSettingOrigins->hide();
}
void QMainScreen::Check()
{
    if(0 != getUserLevel() && 1 != getUserLevel())
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("用户权限不足"), QMessageBox::Ok);
        return;
    }
    m_pLbTitleTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_titletest.png);}");
    m_pLbMachine->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_machine.png);}");
    m_pLbTitleClean->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_clean.png);}");
    m_pLbCheck->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_check_press.png);}");
    m_pLbNet->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(://images/bt/lab_net.png);}");
    m_pLbDebug->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_debug.png);}");
    m_pLbTitleUser->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_titleuser.png);}");
    m_pLbSuyuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_suyuan.png);}");

    m_pMethod->hide();
    m_pMachine->hide();
    m_pSettingclean->hide();
    m_pCheck->show();
    m_pNet->hide();
    m_pDebug->hide();
    m_pSettingUser->hide();
    m_pSettingOrigins->hide();
}

void QMainScreen::Net()
{
    m_pLbTitleTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_titletest.png);}");
    m_pLbMachine->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_machine.png);}");
    m_pLbTitleClean->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_clean.png);}");
    m_pLbCheck->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_check.png);}");
    m_pLbNet->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(://images/bt/lab_net_press.png);}");
    m_pLbDebug->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_debug.png);}");
    m_pLbTitleUser->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_titleuser.png);}");
    m_pLbSuyuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_suyuan.png);}");

    m_pMethod->hide();
    m_pMachine->hide();
    m_pSettingclean->hide();
    m_pCheck->hide();
    m_pNet->show();
    m_pDebug->hide();
    m_pSettingUser->hide();
    m_pSettingOrigins->hide();
}

void QMainScreen::Debug()
{
    if(0 != getUserLevel() && 1 != getUserLevel())
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("用户权限不足"), QMessageBox::Ok);
        return;
    }
    m_pLbTitleTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_titletest.png);}");
    m_pLbMachine->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_machine.png);}");
    m_pLbTitleClean->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_clean.png);}");
    m_pLbCheck->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_check.png);}");
    m_pLbNet->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(://images/bt/lab_net.png);}");
    m_pLbDebug->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_debug_press.png);}");
    m_pLbTitleUser->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_titleuser.png);}");
    m_pLbSuyuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_suyuan.png);}");

    m_pMethod->hide();
    m_pMachine->hide();
    m_pSettingclean->hide();
    m_pCheck->hide();
    m_pNet->hide();
    m_pDebug->show();
    m_pSettingUser->hide();
    m_pSettingOrigins->hide();
}
void QMainScreen::TitleUser()
{
    if(0 != getUserLevel() && 1 != getUserLevel())
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("用户权限不足"), QMessageBox::Ok);
        return;
    }
    m_pLbTitleTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_titletest.png);}");
    m_pLbMachine->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_machine.png);}");
    m_pLbTitleClean->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_clean.png);}");
    m_pLbCheck->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_check.png);}");
    m_pLbNet->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(://images/bt/lab_net.png);}");
    m_pLbDebug->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_debug.png);}");
    m_pLbTitleUser->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_titleuser_press.png);}");
    m_pLbSuyuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_suyuan.png);}");

    m_pMethod->hide();
    m_pMachine->hide();
    m_pSettingclean->hide();
    m_pCheck->hide();
    m_pNet->hide();
    m_pDebug->hide();
    m_pSettingUser->show();
    m_pSettingOrigins->hide();
}

void QMainScreen::Suyuan()
{
    if(0 != getUserLevel())
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("用户权限不足"), QMessageBox::Ok);
        return;
    }

    m_pLbTitleTest->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_titletest.png);}");
    m_pLbMachine->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_machine.png);}");
    m_pLbTitleClean->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_clean.png);}");
    m_pLbCheck->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_check.png);}");
    m_pLbNet->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(://images/bt/lab_net.png);}");
    m_pLbDebug->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_debug.png);}");
    m_pLbTitleUser->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(:/images/bt/lab_titleuser.png);}");
    m_pLbSuyuan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_suyuan_press.png);}");

    m_pMethod->hide();
    m_pMachine->hide();
    m_pSettingclean->hide();
    m_pCheck->hide();
    m_pNet->hide();
    m_pDebug->hide();
    m_pSettingUser->hide();
    m_pSettingOrigins->show();

    HNMsgBox box;
    box.information("正在刷新...");
    m_pSettingOrigins->UpdateStatus();
    box.close();
}


//3
void QMainScreen::TltileDataBase()
{

}

//4
void QMainScreen::TltilePic()
{
    m_pLbTltilePic->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(./skin/default/lab_TitlePic_press.png);}");
    m_pLbUpgrade->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(./skin/default/lab_upgrade_normal.png);}");
    m_pHelp->show();
    m_pUpgrade->hide();
}

void QMainScreen::Upgrade()
{
    if(0 != getUserLevel())
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("用户权限不足"), QMessageBox::Ok);
        return;
    }

    m_pLbTltilePic->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(./skin/default/lab_TitlePic_normal.png);}");
    m_pLbUpgrade->setStyleSheet("QMLabel{background-color:transparent;}""QMLabel{background-image: url(./skin/default/lab_upgrade_press.png);}");
    m_pHelp->hide();
    m_pUpgrade->show();
}

//5
void QMainScreen::TltileUserManager()
{

}

//6
void QMainScreen::TltileCould()
{

}


void QMainScreen::showTest()
{
    //dlg
    m_pAutoTest->show();
    m_pManualTest->hide();
    m_pclean->hide();
    m_pDataBase->hide();
    m_pMethod->hide();

    m_pHelp->hide();
    m_pUser->hide();
    m_cloud->hide();
    m_pUpgrade->hide();

    m_pMethod->hide();
    m_pMachine->hide();
    m_pSettingclean->hide();
    m_pCheck->hide();
    m_pNet->hide();
    m_pDebug->hide();
    m_pSettingUser->hide();
    m_pSettingOrigins->hide();
    AutoTestDlg();
}

void QMainScreen::showData()
{
    //dlg
    if(true == m_pAutoTest->GetState())
    {
        return;
    }
    m_pUpgrade->hide();
    m_pAutoTest->hide();
    m_pManualTest->hide();
    m_pclean->hide();
    m_pDataBase->show();
    m_pMethod->hide();
    m_pHelp->hide();
    m_pUser->hide();
    m_cloud->hide();
    m_pMethod->hide();
    m_pMachine->hide();
    m_pSettingclean->hide();
    m_pCheck->hide();
    m_pNet->hide();
    m_pDebug->hide();
    m_pSettingUser->hide();
    m_pSettingOrigins->hide();
    m_bSettingFlag = false;
    m_bDataFlag = true;
}

void QMainScreen::showSetting()
{
    //dlg
    if(true == m_pAutoTest->GetState())
    {
        return;
    }
    m_pAutoTest->hide();
    m_pManualTest->hide();
    m_pclean->hide();
    m_pDataBase->hide();
    m_pMethod->show();
    m_pHelp->hide();
    m_pUpgrade->hide();
    m_pUser->hide();
    m_cloud->hide();
    m_pMethod->hide();
    m_pMachine->hide();
    m_pSettingclean->hide();
    m_pCheck->hide();
    m_pNet->hide();
    m_pDebug->hide();
    m_pSettingUser->hide();
    m_pSettingOrigins->hide();
    m_bSettingFlag = true;
    m_bDataFlag = false;
    TitleTest();
}
void QMainScreen::showHelp()
{
    //dlg
    if(true == m_pAutoTest->GetState())
    {
        return;
    }
    m_pAutoTest->hide();
    m_pManualTest->hide();
    m_pclean->hide();
    m_pDataBase->hide();
    m_pMethod->hide();
    m_pHelp->show();
    //m_pLbUpgrade->show();;
    m_pUser->hide();
    m_cloud->hide();
    m_pMethod->hide();
    m_pMachine->hide();
    m_pSettingclean->hide();
    m_pCheck->hide();
    m_pNet->hide();
    m_pDebug->hide();
    m_pSettingUser->hide();
    m_pSettingOrigins->hide();
    TltilePic();
}

void QMainScreen::showUser()
{
    //dlg
    if(true == m_pAutoTest->GetState())
    {
        return;
    }
    m_pUpgrade->hide();
    m_pAutoTest->hide();
    m_pManualTest->hide();
    m_pclean->hide();
    m_pDataBase->hide();
    m_pMethod->hide();
    m_pHelp->hide();
    m_pUser->show();
    m_cloud->hide();
    m_pMethod->hide();
    m_pMachine->hide();
    m_pSettingclean->hide();
    m_pCheck->hide();
    m_pNet->hide();
    m_pDebug->hide();
    m_pSettingUser->hide();
    m_pSettingOrigins->hide();
}

void QMainScreen::setUserLevel(int ilevel)
{
    m_iUserlevel = ilevel;
}

int  QMainScreen::getUserLevel()
{
    return m_iUserlevel;
}

void QMainScreen::showCloud()
{
    //dlg
    if(true == m_pAutoTest->GetState())
    {
        return;
    }


    m_pUpgrade->hide();
    m_pAutoTest->hide();
    m_pManualTest->hide();
    m_pclean->hide();
    m_pDataBase->hide();
    m_pMethod->hide();
    m_pHelp->hide();
    m_pUser->hide();
    m_cloud->show();
    m_pMethod->hide();
    m_pMachine->hide();
    m_pSettingclean->hide();
    m_pCheck->hide();
    m_pNet->hide();
    m_pDebug->hide();
    m_pSettingUser->hide();
    m_pSettingOrigins->hide();
}

 void QMainScreen::setusername(QString strname, int index, int bk_index)
 {
      m_strname = strname;
      m_iindex = index;
      //strname += "   已登入";
      ui->lb_userinfo->setText(strname);
      changehead(index);

      changescreen(bk_index);
 }

 QString QMainScreen::GetUserName()
 {
     QString str;
     str = ui->lb_userinfo->text();
    return m_strname;
     //return ui->lb_userinfo->text();
 }

void QMainScreen::ShowTimer()
{
    QDateTime time = QDateTime::currentDateTime();
    QString strTime = time.toString("yyyy-MM-dd hh:mm:ss ");

    QMap<int, QString> map;
    map.insert(1, "星期一");
    map.insert(2, "星期二");
    map.insert(3, "星期三");
    map.insert(4, "星期四");
    map.insert(5, "星期五");
    map.insert(6, "星期六");
    map.insert(7, "星期日");

    strTime.append(map.value(time.date().dayOfWeek()));

    ui->lab_mainscreenDlg_Time->setText(strTime);
}

bool QMainScreen::connecttoserver()
{
    QString str = "124.133.1.54";
//    QString str = "222.175.114.244";
   //QString str = "192.168.1.100";
    //QString str = "192.168.77.157";
    qint32 iPort = 7079;
    bool bflag = false;
    qDebug() << "m_pNetControl";
    if(NULL != m_pNetControl)
    {
        m_pNetControl->SetAddrOfHost(str);
        m_pNetControl->SetPortOfHost(iPort);
       bflag = m_pNetControl->ConnectToServer();
    }
    return bflag;
}

void QMainScreen::login()
{
    QString strName = "101101201503000101";
    QString strPassword = "C4CA4238A0B923820DCC509A6F75849B";
    QString strData = "";

    QByteArray by;
    by.clear();

    strData = QString(NETCOMMANDDATALOGIN).arg(strName).arg(strPassword);
    by.append(strData);
    m_pNetControl->m_bUserLogin = false;
    m_pNetControl->PackAndSendData(by,COMMANDLOGIN);
}

void QMainScreen::slotConnectSucc()
{
    m_box.close();
    //HNMsgBox::warning(this, "连接成功");
}

void QMainScreen::slotConnectFail()
{
    m_box.close();
    //HNMsgBox::warning(this, "连接失败");
}

void QMainScreen::slotEventFilter()
{
    //pline() << sender()->objectName() << m_pLbServer->objectName();

    if(true == m_pAutoTest->GetState())
    {
        return;
    }

    if(HNEthManager::Instance((this))->currentWifi()[ESSID_STATUS] != "COMPLETED")
    {
        return;
    }

    if(sender()->objectName() != m_pLbServer->objectName())
    {
        //如果关闭速度很慢，那么底层代码需要修改
        m_cloud->closehncfs();
    }
    else
    {
        m_box.information("正在连接服务器......");
        bool ret = m_cloud->open();
        if(ret)
            m_cloud->queryRoot();
        else
        {
            return;
        }
    }
    if(!m_box.isHidden())
        m_box.accept();
}

void QMainScreen::slotDownSucc()
{
    HNMsgBox box;
    box.information("下载完成，正在更新");
    m_pMethod->updatedatabase();
    m_pAutoTest->updatabase();
    m_pDataBase->reopen();
    box.accept();
}

void QMainScreen::StartSendFile()
{
    qDebug() << "StartSendFile";
    if(true == m_bSettingFlag)
    {
        if(NULL != m_pMethod)
        {
            m_pMethod->StartSendFile();
        }
    }

    if(true == m_bDataFlag)
    {
         qDebug() << "m_bDataFlag";
        if(NULL != m_pDataBase)
        {
             qDebug() << "m_pDataBase";
            //m_pDataBase->StartSendFile();
        }
    }

}

void QMainScreen::StartSendFileDataDNO()
{
    if(true == m_bSettingFlag)
    {
        if(NULL != m_pMethod)
        {
            m_pMethod->m_bDataDNOFalg = true;
            m_pMethod->Senddata();
        }
    }

    if(true == m_bDataFlag)
    {
        if(NULL != m_pDataBase)
        {
            //m_pDataBase->m_bDataDNOFalg = true;
            //m_pDataBase->Senddata();
        }
    }
}

void QMainScreen::RefreshTreeView()
{
    qDebug() << "RefreshTreeView";
    if(true == m_bSettingFlag)
    {

    }

    if(true == m_bDataFlag)
    {

    }

    if(NULL != m_cloud)
    {
        qDebug() << "RefreshTreeView m_cloud";
        //m_cloud->RefreshTreeView();
    }
}

void QMainScreen::SearchFile()
{
    if(true == m_bSettingFlag)
    {
        if(NULL != m_pMethod)
        {
            m_pMethod->m_bSendFileFalg = false;
            m_pMethod->m_bDataDNOFalg = true;
            m_pMethod->m_iIndex = 0;
            m_pMethod->m_iLen = 0;
        }
    }

    if(true == m_bDataFlag)
    {
        if(NULL != m_pDataBase)
        {
            //m_pDataBase->m_bSendFileFalg = false;
            //m_pDataBase->m_bDataDNOFalg = true;
            //m_pDataBase->m_iIndex = 0;
            //m_pDataBase->m_iLen = 0;
        }
    }
}

void QMainScreen::RequestData()
{
    if(NULL != m_cloud)
    {
        //m_cloud->RequestData();
    }
}
void QMainScreen::writeFile(QByteArray parry, int index)
{
    if(NULL != m_cloud)
    {
        //m_cloud->writeFile(parry, index);
    }
}


void QMainScreen::changescreen(int index)
{
    switch(index)
    {
      case 1:
       {
        this->setStyleSheet("QWidget#QMainScreen{image:url(:/images/bk/bk_mainscreen.png)}""QMainScreen{background-color:transparent;}");

       }
       break;
       case 2:
        {
           this->setStyleSheet("QWidget#QMainScreen{image:url(:/images/bk/bk_mainscreen2.png)}""QMainScreen{background-color:transparent;}");
        }
         break;
       case 3:
        {
           this->setStyleSheet("QWidget#QMainScreen{image:url(:/images/bk/bk_mainscreen3.png)}""QMainScreen{background-color:transparent;}");
        }
        break;
       case 4:
        {
           this->setStyleSheet("QWidget#QMainScreen{image:url(:/images/bk/bk_mainscreen4.png)}""QMainScreen{background-color:transparent;}");
        }
       break;
        deault:
            break;
    }

}

void QMainScreen::changehead(int index)
{
    switch (index) {
    case 1:
        ui->lb_userimage->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/heads1.png);}");
        break;
    case 2:
        ui->lb_userimage->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/heads2.png);}");
        break;
    case 3:
        ui->lb_userimage->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/heads3.png);}");
        break;
    case 4:
        ui->lb_userimage->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/heads4.png);}");
        break;
    default:
        break;
    }

}

void QMainScreen::stopManuTest()
{
    if(false == m_pManualTest->m_brunning)
        return;

    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x04);
    m_Serialcmd.append(0x06);
    m_pSerialProtcol->TransmitData(m_Serialcmd, m_Serialdata);
    m_pManualTest->m_brunning = false;
}
