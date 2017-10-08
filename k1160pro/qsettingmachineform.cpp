
#include "time.h"
#include <QDateTime>
#include <QMessageBox>
#include <QListView>
#include "qsettingmachineform.h"
#include "ui_qsettingmachineform.h"
#include "qmainscreen.h"

QSettingMachineForm::QSettingMachineForm(QWidget *parent) :
    QWidget(parent),
    m_pSerial(NULL),
    ui(new Ui::QSettingMachineForm)
{
    ui->setupUi(this);
    m_ptc =  QTextCodec::codecForName("UTF-8");
    if(NULL == m_pSerial)
    {
        QMainScreen *pWidget = static_cast<QMainScreen *>(this->parent());
        m_pSerial = pWidget->m_pSerialProtcol;
    }
    m_bjiandan =false;
    m_bxiangxi = true;
    m_bzijian = true;
    m_blengningshui= true;
    m_bsuyuandingbiaoxishu = true;
    m_bsuyuanfangfaxishu = true;
    m_isuyuanfangfaxishu = 0;
    InitOCX();
    InitSings();
}

QSettingMachineForm::~QSettingMachineForm()
{
    delete ui;
}


void QSettingMachineForm::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("QWidget#QSettingMachineForm{image:url(:/images/bk/bk_setting_yiqi.png)}""QSettingMachineForm{background-color:transparent;}");

    //label
    ui->label_xishu1->setGeometry(28,8,111,36);
    ui->label_xishu1->setText(m_ptc->toUnicode("系数"));
    ui->label_xishu1->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_dayin->setGeometry(328,8,111,36);
    ui->label_dayin->setText(m_ptc->toUnicode("打印"));
    ui->label_dayin->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_zijian->setGeometry(628,8,111,36);
    ui->label_zijian->setText(m_ptc->toUnicode("自检"));
    ui->label_zijian->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_time->setGeometry(28,300,111,36);
    ui->label_time->setText(m_ptc->toUnicode("时间"));
    ui->label_time->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_3->setGeometry(328,300,111,36);
    ui->label_3->setText(m_ptc->toUnicode("冷凝水"));
    ui->label_3->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_xishu2->setGeometry(628,300,111,36);
    ui->label_xishu2->setText(m_ptc->toUnicode("系数"));
    ui->label_xishu2->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->lb_settingmachine_xishu->setGeometry(84, 123, 120, 30);
    ui->lb_settingmachine_xishu->setText(m_ptc->toUnicode("输入定标系数"));
    ui->lb_settingmachine_xishu->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->lb_settingmachine_jiandna->setGeometry(436, 89, 120, 30);
    ui->lb_settingmachine_jiandna->setText(m_ptc->toUnicode("简单打印"));
    ui->lb_settingmachine_jiandna->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");
    ui->lb_settingmachine_jiandna->hide();
    ui->lb_settingmachine_xiangxi->hide();
    ui->lb_settingmachine_xiangxi->setGeometry(436, 171, 120, 30);
    ui->lb_settingmachine_xiangxi->setText(m_ptc->toUnicode("详细打印"));
    ui->lb_settingmachine_xiangxi->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->lb_settingmachine_lengningshui->setGeometry(411, 395, 120, 30);
    ui->lb_settingmachine_lengningshui->setText(m_ptc->toUnicode("冷凝水检测"));
    ui->lb_settingmachine_lengningshui->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->lb_settingmachine_zijian->setGeometry(715, 120, 120, 30);
    ui->lb_settingmachine_zijian->setText(m_ptc->toUnicode("开机自检"));
    ui->lb_settingmachine_zijian->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->lb_settingmachine_fangfa->setGeometry(694, 395, 120, 30);
    ui->lb_settingmachine_fangfa->setText(m_ptc->toUnicode("方法系数选择"));
    ui->lb_settingmachine_fangfa->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    m_plbjiandan = new QMLabel(this);
    m_plbjiandan->setGeometry(384,85,39, 39);
    m_plbjiandan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
    m_bjiandan = false;
    m_plbjiandan->hide();

    QFile styleFile("://HNWidgets.qss");
    styleFile.open(QIODevice::ReadOnly);
    QString styleString(styleFile.readAll());;

    styleFile.close();

    ui->btnJiandan->setGeometry(384, 95, 150, 40);
    ui->btnJiandan->setText("简单打印");
    ui->btnJiandan->setStyleSheet(styleString);

    ui->btnComplex->setGeometry(384, 157, 150, 40);
    ui->btnComplex->setText("复杂打印");
    ui->btnComplex->setStyleSheet(styleString);

    QSettings set;
    int value = set.value("Machine/ReportType", 0).toInt();
    if(value ==0)
    {
        ui->btnJiandan->setChecked (true);
        m_bjiandan = true;
        m_bxiangxi = false;
    }
    else
    {
        ui->btnComplex->setChecked(true);
        m_bjiandan = false;
        m_bxiangxi = true;
    }

    m_plbxiangxi = new QMLabel(this);
    m_plbxiangxi->setGeometry(384,167,39, 39);
    m_plbxiangxi->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
    m_plbxiangxi->hide();

    m_plbzijian = new QMLabel(this);
    m_plbzijian->setGeometry(707,163,78, 29);

    value = set.value("Machine/SelfCheck", 1).toInt();
    if(value ==1)
    {
        m_plbzijian->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
    }
    else
        m_plbzijian->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    m_bzijian = value;

    m_plblengningshui = new QMLabel(this);
    m_plblengningshui->setGeometry(411,439,78, 29);

    value = set.value("Machine/LengningshuiCheck", 1).toInt();
    if(value ==1)

    m_plblengningshui->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");

    else
        m_plblengningshui->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    m_blengningshui = value;

    //bt
    ui->pb_setttingmatchine_save->setFlat(true);
    //ui->pb_setttingmatchine_save->setFocusPolicy(Qt::NoFocus);
    ui->pb_setttingmatchine_save->setGeometry(750,600,108,44);
    ui->pb_setttingmatchine_save->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_save_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_save_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_save_press.png);}");

    QDateTime dt = QDateTime::currentDateTime();
    ui->dateTimeEdit->setGeometry(44,439,183, 81);
    ui->dateTimeEdit->setDateTime(dt);
    ui->dateTimeEdit->hide();
    ui->dial_year->setRange(0, 10);
    ui->dial_month->setRange(1, 12);
    ui->dial_day->setRange(1, 31);
    ui->dial_hour->setRange(0, 23);
    ui->dial_muit->setRange(0, 59);
    ui->dial_second_2->setRange(0, 59);

    ui->label_year->setStyleSheet("QLabel{background-color:transparent;font-size:14px}");
    ui->label_year->setAlignment(Qt::AlignCenter);
    ui->label_mouth->setStyleSheet("QLabel{background-color:transparent;font-size:14px}");
    ui->label_mouth->setAlignment(Qt::AlignCenter);
    ui->label_day->setStyleSheet("QLabel{background-color:transparent;font-size:14px}");
    ui->label_day->setAlignment(Qt::AlignCenter);
    ui->label_hour->setStyleSheet("QLabel{background-color:transparent;font-size:14px}");
    ui->label_hour->setAlignment(Qt::AlignCenter);
    ui->label_muit->setStyleSheet("QLabel{background-color:transparent;font-size:14px}");
    ui->label_muit->setAlignment(Qt::AlignCenter);
    ui->label_second->setStyleSheet("QLabel{background-color:transparent;font-size:14px}");
    ui->label_second->setAlignment(Qt::AlignCenter);

    QRegExp rx("^-?(100|1?[0-9]?\\d(\\.\\d{1,6})?)$");
    QRegExpValidator *pReg = new QRegExpValidator(rx, this);

    //edit
    ui->le_settingmachine_xishu->setGeometry(44,177,187, 35);
    ui->le_settingmachine_xishu->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line.png);}");
    ui->le_settingmachine_xishu->setValidator(pReg);

    QString str = set.value("Machine/dingbiaoxishu").toString();
    ui->le_settingmachine_xishu->setText(str);


    ui->cb_setttingmatchine_fangfaxishu->setGeometry(667,439,187, 35);
    ui->cb_setttingmatchine_fangfaxishu->setStyleSheet("QComboBox{border:1px solid gray;}"
      "QComboBox QAbstractItemView::item{height:50px;}"
      "QComboBox::down-arrow{image:url(:/images/bt/arrowdownBo.png);}"
      "QComboBox::drop-down{border:0px;}");
    ui->cb_setttingmatchine_fangfaxishu->setView(new QListView());

    ui->cb_setttingmatchine_fangfaxishu->addItem(m_ptc->toUnicode("1.401"));
    ui->cb_setttingmatchine_fangfaxishu->addItem(m_ptc->toUnicode("1.400"));

    value = set.value("Machine/fangfaxishu", 0).toInt();
    ui->cb_setttingmatchine_fangfaxishu->setCurrentIndex(value);

    ui->le_settingmachine_fangfaxishu->hide();
    //ui->le_settingmachine_fangfaxishu->setGeometry(667,439,183, 31);
   // ui->le_settingmachine_fangfaxishu->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line.png);}");
}

void QSettingMachineForm::InitSings()
{
    connect(m_plbjiandan, SIGNAL(clicked()), this, SLOT(jiandan()));
    connect(m_plbxiangxi, SIGNAL(clicked()), this, SLOT(xiangxi()));
    connect(m_plbzijian, SIGNAL(clicked()), this, SLOT(zijian()));
    connect(m_plblengningshui, SIGNAL(clicked()), this, SLOT(lengningshui()));
}

void QSettingMachineForm::jiandan()
{
    if(true == m_bjiandan)
     {
        m_plbjiandan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_bjiandan = false;

        m_plbxiangxi->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bxiangxi = true;
     }
     else
     {
        m_plbjiandan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjiandan = true;
     }
}


void QSettingMachineForm::xiangxi()
{
    if(true == m_bxiangxi)
     {
        m_plbxiangxi->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_bxiangxi = false;
        m_plbjiandan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bjiandan = true;
     }
     else
     {
        m_plbxiangxi->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bxiangxi = true;
     }
}


void QSettingMachineForm::zijian()
{
    if(true == m_bzijian)
     {
         m_plbzijian->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
         m_bzijian = false;
     }
     else
     {
          m_plbzijian->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
          m_bzijian = true;
     }

    QSettings set;
    set.setValue("Machine/SelfCheck", m_bzijian ? 1 : 0);
    set.sync();
}


void QSettingMachineForm::lengningshui()
{
    if(true == m_blengningshui)
     {
         m_plblengningshui->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
         m_blengningshui = false;
     }
     else
     {
          m_plblengningshui->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
          m_blengningshui = true;
     }

    QSettings set;
    set.setValue("Machine/LengningshuiCheck", m_blengningshui?1:0);
    set.sync();
}


void QSettingMachineForm::on_pb_setttingmatchine_save_clicked()
{
    setxishu();

    QSettings set;
    set.setValue("Machine/dingbiaoxishu", ui->le_settingmachine_xishu->text());
    set.setValue("Machine/fangfaxishu", ui->cb_setttingmatchine_fangfaxishu->currentIndex());
    set.setValue("Machine/ReportType", ui->btnJiandan->isChecked()?0:1);
    set.setValue("Machine/SelfCheck", m_bzijian?1:0);
    set.setValue("Machine/LengningshuiCheck", m_blengningshui?1:0);

    set.sync();

    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialdata.append((quint8)m_blengningshui);
    m_Serialcmd.append(0x0a);
    m_Serialcmd.append(0x01);
    m_pSerial->TransmitData(m_Serialcmd, m_Serialdata);

    QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("保存成功"), QMessageBox::Ok);

}

void QSettingMachineForm::on_dial_year_rangeChanged(int min, int max)
{

}

void QSettingMachineForm::setxishu()
{
    if(false == m_bsuyuandingbiaoxishu)
    {
        linstname.clear();
        linstvalues.clear();

        linstname.append("mingcheng");
        linstname.append("dongzuo");
        linstname.append("shijian");

        linstvalues.append(m_ptc->toUnicode("修改定标系数"));
        linstvalues.append(m_ptc->toUnicode("成功"));

        QDateTime dt = QDateTime::currentDateTime();
        QString strData =  dt.toString("yyyy-MM-dd hh:mm:ss ddd");
        linstvalues.append(strData);

        pdataquery = new QDatabasequery();
        pdataquery->SetTableName("./db/suyuan");

        QString str = "suyuan";
        if(true == pdataquery->opendatabase())
        {
            pdataquery->insert(str, linstname, linstvalues);
            pdataquery->cloesdatabase();
        }
    }

    if(false == m_bsuyuanfangfaxishu)
    {
        linstname.clear();
        linstvalues.clear();

        linstname.append("mingcheng");
        linstname.append("dongzuo");
        linstname.append("shijian");

        linstvalues.append(m_ptc->toUnicode("修改方法系数"));
        linstvalues.append(m_ptc->toUnicode("成功"));

        QDateTime dt = QDateTime::currentDateTime();
        QString strDate =  dt.toString("yyyy-MM-dd hh:mm:ss ddd");
        linstvalues.append(strDate);

        pdataquery = new QDatabasequery();
        pdataquery->SetTableName("./db/suyuan");

        QString str = "suyuan";
        if(true == pdataquery->opendatabase())
        {
            pdataquery->insert(str, linstname, linstvalues);
            pdataquery->cloesdatabase();
        }
    }

    m_bsuyuandingbiaoxishu = true;
    m_bsuyuanfangfaxishu = true;


    //linstvalues.append(m_stronelinedata);


/*
    QMainScreen *p = (QMainScreen *) this->parent();
    //QString strname =  p->GetUserName();
    p->m_pSettingOrigins->RecordQuery(0);
    p->m_pSettingOrigins->UpdateStatus();
    //linstvalues.append(strname);
*/
}

void QSettingMachineForm::on_dial_year_valueChanged(int value)
{
    int iYear = 2015 + value;
    QString strYear = QString::number(iYear);
    ui->label_year->setText(strYear);
}

void QSettingMachineForm::on_dial_month_valueChanged(int value)
{
    QString strmouth = QString::number(value);
    ui->label_mouth->setText(strmouth);
}

void QSettingMachineForm::on_dial_day_valueChanged(int value)
{
    QString strday = QString::number(value);
    ui->label_day->setText(strday);
}

void QSettingMachineForm::on_dial_hour_valueChanged(int value)
{
    QString strhour = QString::number(value);
    ui->label_hour->setText(strhour);
}

void QSettingMachineForm::on_dial_muit_valueChanged(int value)
{
    QString strmuit = QString::number(value);
    ui->label_muit->setText(strmuit);

    QString strtime =  QString("date -s \"%1-%2-%3 %4:%5:%6\"")
            .arg(ui->label_year->text().toInt(), 4, 10, QLatin1Char('0'))
            .arg(ui->label_mouth->text().toInt(), 2, 10, QLatin1Char('0'))
            .arg(ui->label_day->text().toInt(), 2, 10, QLatin1Char('0'))
            .arg(ui->label_hour->text().toInt(), 2, 10, QLatin1Char('0'))
            .arg(ui->label_muit->text().toInt(), 2, 10, QLatin1Char('0'))
            .arg(ui->label_second->text().toInt(), 2, 10, QLatin1Char('0'));

    system(strtime.toAscii());
    //ignore
    //time_t tt = (time_t)dt.toTime_t();
    //只有超级权限的用户才可以使用成功
    //int r = stime(&tt);
    //同步到硬件时钟
    system("hwclock -w");
}

void QSettingMachineForm::on_dial_second_2_valueChanged(int value)
{
    QString strsecond = QString::number(value);
    ui->label_second->setText(strsecond);
}

void QSettingMachineForm::on_cb_setttingmatchine_fangfaxishu_currentIndexChanged(int index)
{

    if(m_isuyuanfangfaxishu != index)
    {
        m_bsuyuanfangfaxishu = false;
        m_isuyuanfangfaxishu = index;
    }

    QSettings set;
    set.setValue("Machine/fangfaxishu", index);
    set.sync();

}

void QSettingMachineForm::on_le_settingmachine_xishu_textChanged(const QString &arg1)
{
    m_bsuyuandingbiaoxishu = false;
    if(arg1 == "")
    {
        m_bsuyuandingbiaoxishu = true;
    }
}

void QSettingMachineForm::on_btnComplex_clicked()
{
    QSettings set;
    set.setValue("Machine/ReportType", 1);
    set.sync();
}

void QSettingMachineForm::on_btnJiandan_clicked()
{
    QSettings set;
    set.setValue("Machine/ReportType", 0);
    set.sync();
}
