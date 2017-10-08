#include "qsettingnetform.h"
#include "ui_qsettingnetform.h"
#include "DataDef.h"
#include "qmainscreen.h"
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include "hnwifiwidget.h"

QSettingNetForm::QSettingNetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSettingNetForm),
    m_bDHCP(true)
{
    ui->setupUi(this);
    m_ptc =  QTextCodec::codecForName("UTF-8");
    InitOCX();
    InitSings();
}

QSettingNetForm::~QSettingNetForm()
{
    delete ui;
}


void QSettingNetForm::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("QWidget#QSettingNetForm{image:url(:/images/bk/bk_net.png)}""QSettingNetForm{background-color:transparent;}");

    QRegExp regExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    QRegExpValidator *pValidator = new QRegExpValidator(regExp, this);

    ui->label_netset->setGeometry(28,7,111,36);
    ui->label_netset->setText(m_ptc->toUnicode("网络设置"));
    ui->label_netset->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->ed_settingnet_ip->setGeometry(558,233,291, 35);
    ui->ed_settingnet_ip->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");
    ui->ed_settingnet_ip->setValidator(pValidator);
    ui->ed_settingnet_ip->setInputMask("000.000.000.000;");

    ui->ed_settingnet_mask->setGeometry(558,282,291, 35);
    ui->ed_settingnet_mask->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");
    ui->ed_settingnet_mask->setValidator(pValidator);
    ui->ed_settingnet_mask->setInputMask("000.000.000.000;");


    ui->ed_settingnet_getway->setGeometry(558,331,291, 35);
    ui->ed_settingnet_getway->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");
    ui->ed_settingnet_getway->setValidator(pValidator);
    ui->ed_settingnet_getway->setInputMask("000.000.000.000;");

    ui->ed_settingnet_dns->setGeometry(558,380,291,35);
    ui->ed_settingnet_dns->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");
    ui->ed_settingnet_dns->setValidator(pValidator);
    ui->ed_settingnet_dns->setInputMask("000.000.000.000;");

    ui->le_settingnet_ip->setGeometry(451, 235, 100, 30);
    ui->le_settingnet_ip->setText(m_ptc->toUnicode("IP地址:"));
    ui->le_settingnet_ip->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->le_settingnet_mask->setGeometry(451, 284, 100, 30);
    ui->le_settingnet_mask->setText(m_ptc->toUnicode("子网掩码:"));
    ui->le_settingnet_mask->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->le_settingnet_getway->setGeometry(451, 332, 100, 30);
    ui->le_settingnet_getway->setText(m_ptc->toUnicode("网关:"));
    ui->le_settingnet_getway->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->le_settingnet_dns->setGeometry(451, 382, 100, 30);
    ui->le_settingnet_dns->setText(m_ptc->toUnicode("DNS:"));
    ui->le_settingnet_dns->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    //bt
    ui->pb_zhixing->setFlat(true);
    //ui->pb_zhixing->setFocusPolicy(Qt::NoFocus);
    ui->pb_zhixing->setGeometry(730,600,144,48);
    ui->pb_zhixing->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_start_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_start_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_start_press.png);}");

    ui->m_pwifi->setGeometry(51, 233, 287, 177);

    m_pwifiManager = HNEthManager::Instance(this);
    QString ip, mask, gw, dns;
    HNEthManager::Instance()->getAddr(ip, mask, gw, dns);
    ui->ed_settingnet_ip->setText(ip);
    ui->ed_settingnet_mask->setText(mask);
    ui->ed_settingnet_getway->setText(gw);
    ui->ed_settingnet_dns->setText(dns);


    //label
    m_pDHCP = new QMLabel(this);
    m_pDHCP->setGeometry(558,420,39, 39);
    m_pDHCP->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");

    m_pDHCPText = new QMLabel(this);
    m_pDHCPText->setGeometry(602, 423, 100, 30);
    m_pDHCPText->setText(m_ptc->toUnicode("DHCP"));
    m_pDHCPText->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");
}

void QSettingNetForm::InitSings()
{
    connect(m_pDHCP, SIGNAL(clicked()), this, SLOT(dhcp()));
    connect(HNEthManager::Instance(), SIGNAL(sigConnected()), this, SLOT(NetChanged()));
    connect(HNEthManager::Instance(), SIGNAL(sigDisConnected()), this, SLOT(NetChanged()));
    connect(HNEthManager::Instance(), SIGNAL(sigLanConnected()), this, SLOT(NetChanged()));
    connect(HNEthManager::Instance(), SIGNAL(sigLanDisConnected()), this, SLOT(NetChanged()));
}


void QSettingNetForm::NetChanged()
{

    QString netName;
    if("Wired Lan" == HNEthManager::Instance()->currentNetName())
    {
        netName = tr("Current:Wired Lan");
        ui->m_pwifi->setEnabled(false);
    }
    else
    {
        netName = tr("Current:%1").arg(HNEthManager::Instance()->currentNetName());
        ui->m_pwifi->setEnabled(true);
        /*
        QMainScreen *pWidget = static_cast<QMainScreen *>(this->parent());
        if(true == pWidget->connecttoserver())
        {
            qDebug() << "connecttoserver true";
            pWidget->login();
        }
    */
    }
    ui->le_wifiname->setText(netName);
}

void QSettingNetForm::dhcp()
{
    if(true == m_bDHCP)
     {
        m_pDHCP->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_bDHCP = false;
        ui->ed_settingnet_ip->setEnabled(m_bDHCP);
        ui->ed_settingnet_dns->setEnabled(m_bDHCP);
        ui->ed_settingnet_getway->setEnabled(m_bDHCP);
        ui->ed_settingnet_mask->setEnabled(m_bDHCP);
        m_pwifiManager->setDHCP(true);
     }
     else
     {
        m_pDHCP->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bDHCP = true;
        ui->ed_settingnet_ip->setEnabled(m_bDHCP);
        ui->ed_settingnet_dns->setEnabled(m_bDHCP);
        ui->ed_settingnet_getway->setEnabled(m_bDHCP);
        ui->ed_settingnet_mask->setEnabled(m_bDHCP);
        m_pwifiManager->setDHCP(false);
     }
}

void QSettingNetForm::on_pb_zhixing_clicked()
{
    QString strip = "";
    QString strmask = "";
    QString strgw = "";
    QString strdns = "";

    strip = ui->ed_settingnet_ip->text();
    strmask = ui->ed_settingnet_mask->text();
    strgw = ui->ed_settingnet_getway->text();
    strdns = ui->ed_settingnet_dns->text();

    m_pwifiManager->setAddr(strip, strmask, strgw, strdns);
    m_pwifiManager->ipconfig();

    HNMsgBox::warning(this, "网络刷新成功");

    /*
    strip = m_ptc->toUnicode("192.168.77.152") + " ";
    strmask = m_ptc->toUnicode("netmask ") + m_ptc->toUnicode("255.255.255.0") + " up ";
    strgw = m_ptc->toUnicode("route add default gw ") + m_ptc->toUnicode("192.168.77.100") + " ";
    strdns = m_ptc->toUnicode("nameserver ") + m_ptc->toUnicode("192.168.77.100") + " ";
    */
/*
    ui->ed_settingnet_ip->setText(m_ptc->toUnicode("192.168.77.152"));
    ui->ed_settingnet_mask->setText(m_ptc->toUnicode("255.255.255.0"));
    ui->ed_settingnet_getway->setText(m_ptc->toUnicode("192.168.77.100"));
    ui->ed_settingnet_dns->setText(m_ptc->toUnicode("192.168.77.100"));
*/
    /*
    strip = ui->ed_settingnet_ip->text() + " ";
    strmask = "netmask " + ui->ed_settingnet_mask->text() + " up ";
    strgw = "route add default gw " + ui->ed_settingnet_getway->text() + " ";
    strdns = "nameserver " + ui->ed_settingnet_dns->text() + " ";

#ifdef _MIPS_LINUX_ENV_
    QFile inifile("/etc/init.d/rcS");
#else
    QFile inifile("/etc/network/rcSS");
#endif

    if (!inifile.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        return;
    }

    QTextStream instream(&inifile);
    QString str = "";
    while(!instream.atEnd())
    {
        QString line = instream.readLine();
        QStringList list = line.split(" ");
        if(list.size() > 1)
        {
            if("eth0" == list.at(1))
            {
                inifile.seek(0);
                str = inifile.readAll();
                if(true == str.contains("eth0", Qt::CaseInsensitive))
                {
                  //str.replace(QString("/sbin/ifconfig eth0 192.168.56.131 up"), QString("/sbin/ifconfig eth0 192.168.56.111 up"));
                  str.replace(line, QString("/sbin/ifconfig eth0 ") + strip + strmask + strgw + strdns);
                }
            }
        }

    }
    inifile.flush();
    inifile.close();


#ifdef _MIPS_LINUX_ENV_
   QFile::remove("/etc/init.d/rcS");
#else
   QFile::remove("/etc/network/rcSS");
#endif

    if(!inifile.open(QIODevice::WriteOnly)){

        }
    inifile.write(str.toUtf8());
    inifile.close();
    */
}
