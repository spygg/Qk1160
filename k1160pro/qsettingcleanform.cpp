#include <QMessageBox>
#include "qsettingcleanform.h"
#include "ui_qsettingcleanform.h"
#include "qmainscreen.h"

QSettingCleanForm::QSettingCleanForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSettingCleanForm),
    m_pSerialSettingClean(NULL)
{
    ui->setupUi(this);
    m_ptc =  QTextCodec::codecForName("UTF-8");

    if(NULL == m_pSerialSettingClean)
    {
        QMainScreen *pWidget = static_cast<QMainScreen *>(this->parent());
        m_pSerialSettingClean = pWidget->m_pSerialProtcol;
    }

    InitOCX();
    InitSings();
    //PushData();
}

QSettingCleanForm::~QSettingCleanForm()
{
    delete ui;
}

void QSettingCleanForm::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("QWidget#QSettingCleanForm{image:url(:/images/bk/bk_setting_yiqi.png)}""QSettingCleanForm{background-color:transparent;}");

    //label

    ui->label->setGeometry(28,8,111,36);
    ui->label->setText(m_ptc->toUnicode("换酸清洗"));
    ui->label->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_2->setGeometry(328,8,111,36);
    ui->label_2->setText(m_ptc->toUnicode("清洗时间"));
    ui->label_2->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_3->setGeometry(628,8,111,36);
    ui->label_3->setText(m_ptc->toUnicode("清洗次数"));
    ui->label_3->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_4->setGeometry(28,300,111,36);
    ui->label_4->setText(m_ptc->toUnicode("清洗时间"));
    ui->label_4->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_5->setGeometry(328,300,111,36);
    ui->label_5->setText(m_ptc->toUnicode("清洗时间"));
    ui->label_5->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_6->setGeometry(628,300,111,36);
    ui->label_6->setText(m_ptc->toUnicode("清洗时间"));
    ui->label_6->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->lb_settingclean_zijian->setGeometry(40, 104, 220, 30);
    ui->lb_settingclean_zijian->setText(m_ptc->toUnicode("自检完成后自动换酸清洗"));
    ui->lb_settingclean_zijian->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->lb_settingclean_xiaohuaguan->setGeometry(384, 104, 220, 30);
    ui->lb_settingclean_xiaohuaguan->setText(m_ptc->toUnicode("消化管排废时间"));
    ui->lb_settingclean_xiaohuaguan->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->lb_settingclean_huansuan->setGeometry(690, 104, 220, 30);
    ui->lb_settingclean_huansuan->setText(m_ptc->toUnicode("换酸清洗次数"));
    ui->lb_settingclean_huansuan->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->lb_settingclean_jieshoubei->setGeometry(79, 394, 220, 30);
    ui->lb_settingclean_jieshoubei->setText(m_ptc->toUnicode("接收杯清洗时间"));
    ui->lb_settingclean_jieshoubei->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->lb_settingclean_jianguan->setGeometry(384, 394, 220, 30);
    ui->lb_settingclean_jianguan->setText(m_ptc->toUnicode("碱管路清洗时间"));
    ui->lb_settingclean_jianguan->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->lb_settingclean_pengsuanguan->setGeometry(672, 394, 220, 30);
    ui->lb_settingclean_pengsuanguan->setText(m_ptc->toUnicode("硼酸管路清洗时间"));
    ui->lb_settingclean_pengsuanguan->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    //edit
    ui->le_settingclean_xiaohuaguan->setGeometry(403,146,105, 45);
    ui->le_settingclean_xiaohuaguan->setText(m_ptc->toUnicode("2"));
    ui->le_settingclean_xiaohuaguan->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/le_setting_enter.png);font-size:17px}");

    ui->le_settingclean_huansuan->setGeometry(698,146,  105, 45);
    ui->le_settingclean_huansuan->setText(m_ptc->toUnicode("2"));
    ui->le_settingclean_huansuan->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/le_setting_enter.png);font-size:17px}");

    ui->le_settingclean_jieshoubei->setGeometry(93,449,105, 45);
    ui->le_settingclean_jieshoubei->setText(m_ptc->toUnicode("2"));
    ui->le_settingclean_jieshoubei->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/le_setting_enter.png);font-size:17px}");

    ui->le_settingclean_jianguan->setGeometry(403,449,105, 45);
    ui->le_settingclean_jianguan->setText(m_ptc->toUnicode("2"));
    ui->le_settingclean_jianguan->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/le_setting_enter.png);font-size:17px}");

    ui->le_settingclean_pengsuanguan->setGeometry(698,449,105, 45);
    ui->le_settingclean_pengsuanguan->setText(m_ptc->toUnicode("2"));
    ui->le_settingclean_pengsuanguan->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/le_setting_enter.png);font-size:17px}");

    //bt
    ui->pb_settingclean_save->setFlat(true);
    //ui->pb_settingclean_save->setFocusPolicy(Qt::NoFocus);
    ui->pb_settingclean_save->setGeometry(750,600,108,44);
    ui->pb_settingclean_save->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_save_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_save_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_save_press.png);}");

    m_plbzijian = new QMLabel(this);
    m_plbzijian->setGeometry(93,146,78, 29);
    m_plbzijian->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    ui->le_settingclean_xiaohuaguan->setValidator(new QIntValidator(1, 99,  this));
    ui->le_settingclean_huansuan->setValidator(new QIntValidator(1, 99,  this));
    ui->le_settingclean_jieshoubei->setValidator(new QIntValidator(1, 99,  this));
    ui->le_settingclean_jianguan->setValidator(new QIntValidator(1, 99,  this));
    ui->le_settingclean_pengsuanguan->setValidator(new QIntValidator(1, 99,  this));

    ui->label_s->setGeometry(510,152,111,36);
    //ui->label_s->setFocusPolicy(Qt::NoFocus);
    ui->label_s->setText(m_ptc->toUnicode("S"));
    ui->label_s->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_times->setGeometry(805,152,111,36);
    //ui->label_times->setFocusPolicy(Qt::NoFocus);
    ui->label_times->setText(m_ptc->toUnicode("次"));
    ui->label_times->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_s1->setGeometry(200,452,111,36);
    //ui->label_s1->setFocusPolicy(Qt::NoFocus);
    ui->label_s1->setText(m_ptc->toUnicode("S"));
    ui->label_s1->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_s2->setGeometry(510,452,111,36);
    //ui->label_s2->setFocusPolicy(Qt::NoFocus);
    ui->label_s2->setText(m_ptc->toUnicode("S"));
    ui->label_s2->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_s3->setGeometry(805,452,111,36);
    //ui->label_s3->setFocusPolicy(Qt::NoFocus);
    ui->label_s3->setText(m_ptc->toUnicode("S"));
    ui->label_s3->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    QSettings set;
    m_bzijian = set.value("Machine/zijianhouhuansuan", 1).toInt();
    if(m_bzijian)
        m_plbzijian->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
    else
        m_plbzijian->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    QString str = set.value("Machine/xiaohuaguanqingxishijian", 2).toString();
    ui->le_settingclean_xiaohuaguan->setText(str);

    str = set.value("Machine/huansuancishu", 2).toString();
    ui->le_settingclean_huansuan->setText(str);

    str = set.value("Machine/jieshoubeiqingxishijian", 2).toString();
    ui->le_settingclean_jieshoubei->setText(str);

    str = set.value("Machine/jianguanluqingxishijian", 2).toString();
    ui->le_settingclean_jianguan->setText(str);

    str = set.value("Machine/pengsuanguanluqingxishijian", 2).toString();
    ui->le_settingclean_pengsuanguan->setText(str);


}

void QSettingCleanForm::InitSings()
{
    connect(m_plbzijian, SIGNAL(clicked()), this, SLOT(zijian()));
}

void QSettingCleanForm::PushData()
{
    QString str;
    m_Serialcmd.clear();
    m_Serialdata.clear();
    MachineSetting ms;

    m_Serialdata.append((quint8)m_bzijian);


    str = ui->le_settingclean_xiaohuaguan->text();
    if(str.isEmpty())
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("数据不能为空"), QMessageBox::Ok);
        return;
    }
    m_Serialdata.append((quint8)str.toInt());
    str = ui->le_settingclean_huansuan->text();
    if(str.isEmpty())
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("数据不能为空"), QMessageBox::Ok);
        return;
    }
    m_Serialdata.append((quint8)str.toInt());
    str = ui->le_settingclean_jieshoubei->text();
    if(str.isEmpty())
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("数据不能为空"), QMessageBox::Ok);
        return;
    }
    m_Serialdata.append((quint8)str.toInt());
    str = ui->le_settingclean_jianguan->text();
    if(str.isEmpty())
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("数据不能为空"), QMessageBox::Ok);
        return;
    }
    m_Serialdata.append((quint8)str.toInt());
    str = ui->le_settingclean_pengsuanguan->text();
    if(str.isEmpty())
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("数据不能为空"), QMessageBox::Ok);
        return;
    }
    m_Serialdata.append((quint8)str.toInt());
    m_Serialcmd.append(0x09);
    m_Serialcmd.append(0x01);
    m_pSerialSettingClean->TransmitData(m_Serialcmd, m_Serialdata);

}


void QSettingCleanForm::zijian()
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
    set.setValue("Machine/zijianhouhuansuan", m_bzijian?1:0);
    set.sync();
}

void QSettingCleanForm::on_pb_settingclean_save_clicked()
{

    PushData();
    QSettings set;
    set.setValue("Machine/zijianhouhuansuan", m_bzijian?1:0);
    set.setValue("Machine/xiaohuaguanqingxishijian", ui->le_settingclean_xiaohuaguan->text());
    set.setValue("Machine/huansuancishu", ui->le_settingclean_huansuan->text());
    set.setValue("Machine/jieshoubeiqingxishijian", ui->le_settingclean_jieshoubei->text());
    set.setValue("Machine/jianguanluqingxishijian", ui->le_settingclean_jianguan->text());
    set.setValue("Machine/pengsuanguanluqingxishijian", ui->le_settingclean_pengsuanguan->text());
    set.sync();
    QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("保存成功"), QMessageBox::Ok);
}
