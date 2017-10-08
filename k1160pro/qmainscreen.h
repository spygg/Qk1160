#ifndef QMAINSCREEN_H
#define QMAINSCREEN_H

#include <QWidget>
#include <QDateTime>
#include <QPalette>
#include <QTimer>
#include <QTextCodec>
#include "qmlabel.h"
#include "qautotest.h"
#include "qautotestaprocessform.h"
#include "qmanualtestform.h"
#include "qcleanform.h"
#include "qsettingmethodform.h"
#include "qsettingmachineform.h"
#include "qsettingcleanform.h"
#include "qsettingcalibrationform.h"
#include "qsettingnetform.h"
#include "qsettingdebugform.h"
#include "qsettinguserform.h"
#include "qsettingoriginsform.h"
#include "quserform.h"
#include "qhelpform.h"
#include "qcloudform.h"
//#include "qcheckfrom.h"
#include "Serial/qserialprotcol.h"
#include "NetSource/simplenetwork.h"
#include "NetSource/NetDataCode.h"
#include "NetSource/NetControl.h"
#include "hngui.h"
#include "hncloudform.h"
#include "hnsampledatawidget.h"
#include "hnupgradewidget.h"

namespace Ui {
class QMainScreen;
}

class QMainScreen : public QWidget
{
    Q_OBJECT

public:
    explicit QMainScreen(QWidget *parent = 0);
    ~QMainScreen();
    void setusername(QString strname, int index, int bk_index);
    QString GetUserName();
    void setUserLevel(int ilevel);
    int  getUserLevel();
    QSettingOriginsForm *m_pSettingOrigins;
    QSettingMethodForm *m_pMethod;
    QAutoTest   *m_pAutoTest;
    int         m_iUserlevel;
    bool        m_bwififlag;
    bool connecttoserver();

    void login();

private slots:
    void slotConnectSucc();
    void slotConnectFail();
    void slotEventFilter();
    void slotDownSucc();
    void NetConnected();
    void NetDisConnected();

    void TestDlg();
    void DataDlg();
    void SettingDlg();
    void HelpDlg();
    void UserDlg();
    void ServerDlg();
    void ShowTimer();
    //1
    void AutoTestDlg();
    void ManualTestDlg();
    void CleanDlg();
    //2
    void TitleTest();
    void Machine();
    void Clean();
    void Check();
    void Net();
    void Debug();
    void TitleUser();
    void Suyuan();
    //3
    void     TltileDataBase();
    //4
    void     TltilePic();
    void Upgrade();

    //5
    void     TltileUserManager();
    //6
    void     TltileCould();


    void StartSendFile();
    void StartSendFileDataDNO();
    void RefreshTreeView();
    void SearchFile();
    void RequestData();
    void writeFile(QByteArray parry, int index);
    void changescreen(int index);
    void changehead(int index);

    void stopManuTest();
private:
    void InitOCX();
    void InitSings();
    void showTest();
    void showData();
    void showSetting();
    void showHelp();
    void showUser();
    void showCloud();
private:
    Ui::QMainScreen *ui;
private:
    //

    HNMsgBox m_box;

    QAutoTestaProcessForm   *m_pAutoPro;
    QManualTestForm *m_pManualTest;
    QCleanForm *m_pclean;

    //


    HNSampleDataWidget *m_pDataBase;
    HNUpgradeWidget* m_pUpgrade;


    QSettingMachineForm *m_pMachine;
    QSettingCleanForm *m_pSettingclean;
    QSettingCalibrationForm *m_pCheck;
    QSettingNetForm *m_pNet;
    QSettingDebugForm *m_pDebug;
    QSettingUserForm *m_pSettingUser;


    //帮助页面
    QHelpForm   *m_pHelp;
    QUserForm   *m_pUser;
    HNCloudForm  *m_cloud;

    //页切换按钮
    //1
    QMLabel     *m_pLbAutoTest;
    QMLabel     *m_pLbManualTest;
    QMLabel     *m_pLbClean;
    //2
    QMLabel     *m_pLbTitleTest;
    QMLabel     *m_pLbMachine;
    QMLabel     *m_pLbTitleClean;
    QMLabel     *m_pLbCheck;
    QMLabel     *m_pLbNet;
    QMLabel     *m_pLbDebug;
    QMLabel     *m_pLbTitleUser;


    //3
    QMLabel     *m_pLbTltileDataBase;
    //4
    QMLabel     *m_pLbTltilePic;
    //5
    QMLabel     *m_pLbTltileUserManager;
    //6
    QMLabel     *m_pLbTltileCould;
    //
    QMLabel     *m_pLbUpgrade;

    QMLabel     *m_pLbTest;
    QMLabel     *m_pLbData;
    QMLabel     *m_pLbSetting;
    QMLabel     *m_pLbHelp;
    QMLabel     *m_pLbUser;
    QMLabel     *m_pLbServer;
    QMLabel     *m_pLbEmpty;
    QMLabel     *m_pLbSuyuan;
    QTimer       *m_pTimer;
    QString     m_strname;
    int         m_iindex;
    QTextCodec  *m_ptc;
    bool        m_bNetFlag;
    bool        m_bSettingFlag;
    bool        m_bDataFlag;
public:
    //QCheckFrom  *m_pCheckDlg;
    NetControl  *m_pNetControl;
    MachineSetting  m_machinesetting;
    QSerialProtcol *m_pSerialProtcol;
    QByteArray  m_Serialcmd;
    QByteArray  m_Serialdata;
};

#endif // QMAINSCREEN_H
