#include "qsettingdebugform.h"
#include "ui_qsettingdebugform.h"
#include "qmainscreen.h"

QSettingDebugForm::QSettingDebugForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSettingDebugForm),
    m_pSerialDebug(NULL),
    m_pStateDebugTimer(NULL)
{
    ui->setupUi(this);
    m_ptc =  QTextCodec::codecForName("UTF-8");
    InitOCX();
    InitSings();
    m_bjianshuibeng = false;
    m_bpengsuanbeng =false;
    m_bqingxibeng = false;
    m_bsuantongfa = false;
    m_bpaifeifa = false;
    m_bjianguanfa = false;
    m_bjiaobanji = false;
    m_byanseled = false;
    m_bzhengqisantongfa = false;
    m_bjianbeng = false;
    m_bdidingsantongfa = false;
    m_bzhaomingled = false;
    m_bjieshoubeioaifeibeng = false;
    m_bjieshoubeipaifeifa = false;
    m_blengningshuijinshuifa = false;

    if(NULL == m_pSerialDebug)
    {
        QMainScreen *pWidget = static_cast<QMainScreen *>(this->parent());
        m_pSerialDebug = pWidget->m_pSerialProtcol;
    }
     connect(m_pSerialDebug->m_pReadThread, SIGNAL(emitReadData(QByteArray)),this, SLOT(AnalysisData(QByteArray)));

     m_Serialcmd.clear();
     m_Serialdata.clear();
     m_Serialcmd.append(0x07);
     m_Serialcmd.append(0x01);
     m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);

     if(NULL == m_pStateDebugTimer)
     {
         m_pStateDebugTimer = new QTimer();
     }

     m_pStateDebugTimer->start(450);
     connect(m_pStateDebugTimer,SIGNAL(timeout()),this,SLOT(Stateshow()));
}

QSettingDebugForm::~QSettingDebugForm()
{
    delete ui;
}

void QSettingDebugForm::AnalysisData(QByteArray pData)
{
    unsigned char j = (int)pData.at(4);
    unsigned int jj = (int)j;
    j = (int)pData.at(5);
    jj = jj << 8;
    jj = jj | j;

    //qDebug() << "QSettingDebugForm cmd" << hex << jj;
    switch (jj) {
    case _SERIALCMD_MCU_DEBUG_COLORS_:
        {
            Setcolor(pData);
        }
        break;
    case _SERIALCMD_MCU_STATE_:
       {
        //break;
        //引发启动时0x8801崩溃
        //解除
           StateSensor(pData);
       }
    default:
        break;
    }
}

void QSettingDebugForm::StateSensor(QByteArray pData)
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

void QSettingDebugForm::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("QWidget#QSettingDebugForm{image:url(:/images/bk/bk_setting_method.png)}""QSettingDebugForm{background-color:transparent;}");

    ui->label_debug->setGeometry(28,8,111,36);
    ui->label_debug->setText(m_ptc->toUnicode("调试"));
    ui->label_debug->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->ed_settingdebug_zheqi->setGeometry(226,256,107, 35);
    ui->ed_settingdebug_zheqi->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_small.png);font-size:17px}");
    ui->ed_settingdebug_zheqi->setHidden(true);

    ui->ed_settingdebug_lengning->setReadOnly(true);
    ui->ed_settingdebug_lengning->setGeometry(226,301,104, 35);
    ui->ed_settingdebug_lengning->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_small.png);font-size:17px}");
    ui->ed_settingdebug_lengning->setHidden(true);

    ui->ed_settingdebug_r->setGeometry(226,363,107, 35);
    ui->ed_settingdebug_r->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_small.png);font-size:17px}");
    ui->ed_settingdebug_r->setText("");

    ui->ed_settingdebug_g->setGeometry(226,405,104, 35);
    ui->ed_settingdebug_g->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_small.png);font-size:17px}");
    ui->ed_settingdebug_g->setText("");

    ui->ed_settingdebug_b->setGeometry(226,447,107, 35);
    ui->ed_settingdebug_b->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_small.png);font-size:17px}");
    ui->ed_settingdebug_b->setText("");

    ui->le_settingdebug_c->setGeometry(226,493,107, 35);
    ui->le_settingdebug_c->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_small.png);font-size:17px}");
    ui->le_settingdebug_c->setText("");

    //label
    ui->le_settingdebug_zhengqi->setGeometry(83, 257, 125, 30);
    ui->le_settingdebug_zhengqi->setText(m_ptc->toUnicode("蒸汽发生器温度:"));
    ui->le_settingdebug_zhengqi->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
    ui->le_settingdebug_zhengqi->setHidden(true);

    ui->le_settingdebug_lengning->setGeometry(83, 302, 120, 30);
    ui->le_settingdebug_lengning->setText(m_ptc->toUnicode("冷凝水温度:"));
    ui->le_settingdebug_lengning->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
    ui->le_settingdebug_lengning->setHidden(true);

    ui->lb_settingdebug_yanse->setGeometry(83, 361, 120, 30);
    ui->lb_settingdebug_yanse->setText(m_ptc->toUnicode("颜色传感器"));
    ui->lb_settingdebug_yanse->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->le_settingdebug_r->setGeometry(183, 361, 50, 30);
    ui->le_settingdebug_r->setText(m_ptc->toUnicode("R"));
    ui->le_settingdebug_r->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");


    ui->le_settingdebug_g->setGeometry(183, 403, 50, 30);
    ui->le_settingdebug_g->setText(m_ptc->toUnicode("G"));
    ui->le_settingdebug_g->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");


    ui->le_settingdebug_b->setGeometry(183, 449, 50, 30);
    ui->le_settingdebug_b->setText(m_ptc->toUnicode("B"));
    ui->le_settingdebug_b->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settingdebug_c->setGeometry(183, 495, 50, 30);
    ui->lb_settingdebug_c->setText(m_ptc->toUnicode("C"));
    ui->lb_settingdebug_c->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settingdebug_jiashuibeng->setGeometry(473, 61, 220, 30);
    ui->lb_settingdebug_jiashuibeng->setText(m_ptc->toUnicode("蒸汽发生器/稀释水加水泵"));
    ui->lb_settingdebug_jiashuibeng->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settingdebug_santongfa->setGeometry(473, 100, 220, 30);
    ui->lb_settingdebug_santongfa->setText(m_ptc->toUnicode("蒸汽发生器/稀释水三通阀"));
    ui->lb_settingdebug_santongfa->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settingdebug_qingxibeng->setGeometry(473, 139, 120, 30);
    ui->lb_settingdebug_qingxibeng->setText(m_ptc->toUnicode("接收杯清洗泵"));
    ui->lb_settingdebug_qingxibeng->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settingdebug_pengsuanbeng->setGeometry(696, 139, 120, 30);
    ui->lb_settingdebug_pengsuanbeng->setText(m_ptc->toUnicode("硼酸泵"));
    ui->lb_settingdebug_pengsuanbeng->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settingdebug_paifeifa->setGeometry(473, 178, 120, 30);
    ui->lb_settingdebug_paifeifa->setText(m_ptc->toUnicode("排废瓶排废阀"));
    ui->lb_settingdebug_paifeifa->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settingdebug_jianguanfa->setGeometry(696, 178, 120, 30);
    ui->lb_settingdebug_jianguanfa->setText(m_ptc->toUnicode("夹管阀"));
    ui->lb_settingdebug_jianguanfa->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settingdebug_jiaobanji->setGeometry(473, 217, 120, 30);
    ui->lb_settingdebug_jiaobanji->setText(m_ptc->toUnicode("搅拌电机"));
    ui->lb_settingdebug_jiaobanji->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settingdebug_yanseled->setGeometry(696, 217, 120, 30);
    ui->lb_settingdebug_yanseled->setText(m_ptc->toUnicode("颜色LED"));
    ui->lb_settingdebug_yanseled->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settingdebug_jieshoubeipaifeifa->setGeometry(473, 256, 120, 30);
    ui->lb_settingdebug_jieshoubeipaifeifa->setText(m_ptc->toUnicode("接收杯排废"));
    ui->lb_settingdebug_jieshoubeipaifeifa->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settingdebug_jianbeng->setGeometry(696, 256, 120, 30);
    ui->lb_settingdebug_jianbeng->setText(m_ptc->toUnicode("碱泵"));
    ui->lb_settingdebug_jianbeng->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settingdebug_leingningshuijinshuifa->setGeometry(473, 295, 120, 30);
    ui->lb_settingdebug_leingningshuijinshuifa->setText(m_ptc->toUnicode("冷凝水进水阀"));
    ui->lb_settingdebug_leingningshuijinshuifa->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settingdebug_zhengqisantongfa->setGeometry(696, 295, 120, 30);
    ui->lb_settingdebug_zhengqisantongfa->setText(m_ptc->toUnicode("蒸汽阀"));
    ui->lb_settingdebug_zhengqisantongfa->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settingdebug_jieshoubeipaifeibeng->setGeometry(473, 334, 120, 30);
    ui->lb_settingdebug_jieshoubeipaifeibeng->setText(m_ptc->toUnicode("蒸馏阀"));
    ui->lb_settingdebug_jieshoubeipaifeibeng->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settingdebug_didingsantongfa->setGeometry(473, 295, 120, 30);
    ui->lb_settingdebug_didingsantongfa->setText(m_ptc->toUnicode("滴定三通阀"));
    ui->lb_settingdebug_didingsantongfa->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
    ui->lb_settingdebug_didingsantongfa->hide();

    ui->lb_settingdebug_zhaomingled->setGeometry(696, 295, 120, 30);
    ui->lb_settingdebug_zhaomingled->setText(m_ptc->toUnicode("照明LED"));
    ui->lb_settingdebug_zhaomingled->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
    ui->lb_settingdebug_zhaomingled->hide();

    ui->lb_settingdebug_zhusaibeng->setGeometry(473, 472, 120, 30);
    ui->lb_settingdebug_zhusaibeng->setText(m_ptc->toUnicode("柱塞泵"));
    ui->lb_settingdebug_zhusaibeng->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");


    m_pLbpengsuantong = new QMLabel(this);
    //m_pLbpengsuantong->setFocusPolicy(Qt::NoFocus);
    m_pLbpengsuantong->setGeometry(96, 66,40, 40);
    m_pLbpengsuantong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_pengsuantong_normal.png);}");

    m_pLbshuitong = new QMLabel(this);
    //m_pLbshuitong->setFocusPolicy(Qt::NoFocus);
    m_pLbshuitong->setGeometry( 156,  66, 40, 40);
    m_pLbshuitong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_shuitong_normal.png);}");

    m_pLbjiantong = new QMLabel(this);
    //m_pLbjiantong->setFocusPolicy(Qt::NoFocus);
    m_pLbjiantong->setGeometry(214, 66,40, 40);
    m_pLbjiantong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_jiantong_normal.png);}");

    m_pLbdidingsuantong = new QMLabel(this);
    //m_pLbdidingsuantong->setFocusPolicy(Qt::NoFocus);
    m_pLbdidingsuantong->setGeometry( 273,  66, 40, 40);
    m_pLbdidingsuantong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_didingsuantong_normal.png);}");


    m_pLbzhengqifashengqiyewei = new QMLabel(this);
    m_pLbzhengqifashengqiyewei->setGeometry(96, 116,40, 40);
    m_pLbzhengqifashengqiyewei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_zhengqifashengqiyewei_normal.png);}");

    m_pLbanquanmen = new QMLabel(this);
    m_pLbanquanmen->setGeometry(156, 116,40, 40);
    m_pLbanquanmen->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_anquanmen_normal.png);}");

    m_pLbxiaohuaguan = new QMLabel(this);
    m_pLbxiaohuaguan->setGeometry(214, 116,40, 40);
    m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_xiaohuaguan_normal.png);}");

    m_pLbfeiyetong = new QMLabel(this);
    //m_pLbfeiyetong->setFocusPolicy(Qt::NoFocus);
    m_pLbfeiyetong->setGeometry(273, 116,40, 40);
    m_pLbfeiyetong->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_feiyetong_normal.png);}");

    m_pLbzhengqifashengqi = new QMLabel(this);
    //m_pLbzhengqifashengqi->setFocusPolicy(Qt::NoFocus);
    m_pLbzhengqifashengqi->setGeometry(96,166,40, 40);
    m_pLbzhengqifashengqi->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_zhengqifashengqi_normal.png);}");

    ui->label_wendu1->setGeometry(156,166,58, 40);
    //ui->label_wendu1->setFocusPolicy(Qt::NoFocus);
    ui->label_wendu1->setText(m_ptc->toUnicode("0℃"));
    ui->label_wendu1->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    m_pLblengningshui = new QMLabel(this);
    //m_pLblengningshui->setFocusPolicy(Qt::NoFocus);
    m_pLblengningshui->setGeometry(214,166,40, 40);
    m_pLblengningshui->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/lab_lengningshui_normal.png);}");

    ui->label_wendu2->setGeometry(273,166,58, 40);
    //ui->label_wendu2->setFocusPolicy(Qt::NoFocus);
    ui->label_wendu2->setText(m_ptc->toUnicode("0℃"));
    ui->label_wendu2->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    //label
    m_plbjiashuibeng = new QMLabel(this);
    m_plbjiashuibeng->setGeometry(696,64,78, 29);
    m_plbjiashuibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    m_plbsantongfa = new QMLabel(this);
    m_plbsantongfa->setGeometry(696,103,78, 29);
    m_plbsantongfa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    m_plbqingxibeng = new QMLabel(this);
    m_plbqingxibeng->setGeometry(608,142,78, 29);
    m_plbqingxibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    m_plbpengsuanbeng = new QMLabel(this);
    m_plbpengsuanbeng->setGeometry(782,142,78, 29);
    m_plbpengsuanbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    m_plbpaifeifa = new QMLabel(this);
    m_plbpaifeifa->setGeometry(608,181,78, 29);
    m_plbpaifeifa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    m_plbjiaguanfa = new QMLabel(this);
    m_plbjiaguanfa->setGeometry(782,181,78, 29);
    m_plbjiaguanfa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    m_plbjiaobanji = new QMLabel(this);
    m_plbjiaobanji->setGeometry(608,220,78, 29);
    m_plbjiaobanji->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    m_plbyanseled = new QMLabel(this);
    m_plbyanseled->setGeometry(782,220,78, 29);
    m_plbyanseled->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    m_plbjieshoubeipaifeifa = new QMLabel(this);
    m_plbjieshoubeipaifeifa->setGeometry(608,259,78, 29);
    m_plbjieshoubeipaifeifa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    m_plbjianbeng = new QMLabel(this);
    m_plbjianbeng->setGeometry(782,259,78, 29);
    m_plbjianbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    m_plblengningshuijinshuifa = new QMLabel(this);
    m_plblengningshuijinshuifa->setGeometry(608,298,78, 29);
    m_plblengningshuijinshuifa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    //蒸汽
    m_plbzhengqisantongfa = new QMLabel(this);
    m_plbzhengqisantongfa->setGeometry(782,298,78, 29);
    m_plbzhengqisantongfa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    //蒸馏
    m_plbjieshoubeipaifeibeng = new QMLabel(this);
    m_plbjieshoubeipaifeibeng->setGeometry(608,337,78, 29);
    m_plbjieshoubeipaifeibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    m_plbdidingsantongfa = new QMLabel(this);
    m_plbdidingsantongfa->setGeometry(608,298,78, 29);
    m_plbdidingsantongfa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
    m_plbdidingsantongfa->hide();

    m_plbzhaopmingled = new QMLabel(this);
    m_plbzhaopmingled->setGeometry(782,298,78, 29);
    m_plbzhaopmingled->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
    m_plbzhaopmingled->hide();

    ui->pb_zhusaibengup->setFlat(true);
    //ui->pb_zhusaibengup->setFocusPolicy(Qt::NoFocus);
    ui->pb_zhusaibengup->setGeometry(608,475,46,46);
    ui->pb_zhusaibengup->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/btn_upnormal.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_upnormal.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_uppress.png);}");

    ui->pb_zhusaibengdown->setFlat(true);
    //ui->pb_zhusaibengdown->setFocusPolicy(Qt::NoFocus);
    ui->pb_zhusaibengdown->setGeometry(678,475,46,46);
    ui->pb_zhusaibengdown->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/btn_downnormal.png)}""QPushButton:hover{background-image: url(:/images/bt/btn_downnormal.png);}""QPushButton:pressed{background-image: url(:/images/bt/btn_downpress.png);}");

}

void QSettingDebugForm::InitSings()
{
    connect(m_plbjiashuibeng, SIGNAL(clicked()), this, SLOT(jianshuibeng()));
    connect(m_plbsantongfa, SIGNAL(clicked()), this, SLOT(suantongfa()));
    connect(m_plbqingxibeng, SIGNAL(clicked()), this, SLOT(qingxibeng()));
    connect(m_plbpengsuanbeng, SIGNAL(clicked()), this, SLOT(pengsuanbeng()));
    connect(m_plbpaifeifa, SIGNAL(clicked()), this, SLOT(paifeifa()));
    connect(m_plbjiaguanfa, SIGNAL(clicked()), this, SLOT(jianguanfa()));
    connect(m_plbjiaobanji, SIGNAL(clicked()), this, SLOT(jiaobanji()));
    connect(m_plbyanseled, SIGNAL(clicked()), this, SLOT(yanseled()));
    connect(m_plbzhengqisantongfa, SIGNAL(clicked()), this, SLOT(zhengqisantongfa()));
    connect(m_plbjianbeng, SIGNAL(clicked()), this, SLOT(jianbeng()));
    connect(m_plbdidingsantongfa, SIGNAL(clicked()), this, SLOT(didingsantongfa()));
    connect(m_plbzhaopmingled, SIGNAL(clicked()), this, SLOT(zhaomingled()));
    connect(m_plbjieshoubeipaifeibeng, SIGNAL(clicked()), this, SLOT(jieshoubeioaifeibeng()));
    connect(m_plbjieshoubeipaifeifa, SIGNAL(clicked()), this, SLOT(jieshoubeipaifeifa()));
    connect(m_plblengningshuijinshuifa, SIGNAL(clicked()), this, SLOT(lengningshuijinshuifa()));
}

void QSettingDebugForm::jiashuibeng()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x07);
    m_Serialcmd.append(0x02);
    if(false == m_bjianshuibeng)
    {
        m_Serialdata.append((char)0x00);
    }
    else
    {
        m_Serialdata.append((char)0x01);
    }
    m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);
}

void QSettingDebugForm::xishihuisantongfa()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x07);
    m_Serialcmd.append(0x03);
    if(false == m_bsuantongfa)
    {
        m_Serialdata.append((char)0x00);
    }
    else
    {
        m_Serialdata.append((char)0x01);
    }
    m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);
}

void QSettingDebugForm::qingxibengfun()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x07);
    m_Serialcmd.append(0x04);
    if(false == m_bqingxibeng)
    {
        m_Serialdata.append((char)0x00);
    }
    else
    {
        m_Serialdata.append((char)0x01);
    }
    m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);
}

void QSettingDebugForm::pengsuanbengfun()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x07);
    m_Serialcmd.append(0x05);
    if(false == m_bpengsuanbeng)
    {
        m_Serialdata.append((char)0x00);
    }
    else
    {
        m_Serialdata.append((char)0x01);
    }
    m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);
}

void QSettingDebugForm::paifeifafun()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x07);
    m_Serialcmd.append(0x06);
    if(false == m_bpaifeifa)
    {
        m_Serialdata.append((char)0x00);
    }
    else
    {
        m_Serialdata.append((char)0x01);
    }
    m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);
}


void QSettingDebugForm::jiaguanfafun()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x07);
    m_Serialcmd.append(0x07);
    if(false == m_bjianguanfa)
    {
        m_Serialdata.append((char)0x00);
    }
    else
    {
        m_Serialdata.append((char)0x01);
    }
    m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);
}

void QSettingDebugForm::jiaobandianjifun()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x07);
    m_Serialcmd.append(0x08);
    if(false == m_bjiaobanji)
    {
        m_Serialdata.append((char)0x00);
    }
    else
    {
        m_Serialdata.append((char)0x01);
    }
    m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);
}

void QSettingDebugForm::yanseledfun()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x07);
    m_Serialcmd.append(0x09);
    if(false == m_byanseled)
    {
        m_Serialdata.append((char)0x00);
    }
    else
    {
        m_Serialdata.append((char)0x01);
    }
    m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);
}

void QSettingDebugForm::zhengqisantongfafun()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x07);
    m_Serialcmd.append(0x0A);
    if(false == m_bzhengqisantongfa)
    {
        m_Serialdata.append((char)0x00);
    }
    else
    {
        m_Serialdata.append((char)0x01);
    }
    m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);
}

void   QSettingDebugForm::jianfafun()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x07);
    m_Serialcmd.append(0x0B);
    if(false == m_bjianbeng)
    {
        m_Serialdata.append((char)0x00);
    }
    else
    {
        m_Serialdata.append((char)0x01);
    }
    m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);
}

void QSettingDebugForm::didingsantongfun()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x07);
    m_Serialcmd.append(0x0C);
    if(false == m_bdidingsantongfa)
    {
        m_Serialdata.append((char)0x00);
    }
    else
    {
        m_Serialdata.append((char)0x01);
    }
    m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);
}

void QSettingDebugForm::zhaomingledfun()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x07);
    m_Serialcmd.append(0x0D);
    if(false == m_bzhaomingled)
    {
        m_Serialdata.append((char)0x00);
    }
    else
    {
        m_Serialdata.append((char)0x01);
    }
    m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);
}

//蒸馏
void QSettingDebugForm::paifeibengfun()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x07);
    m_Serialcmd.append(0x0E);
    if(false == m_bjieshoubeioaifeibeng)
    {
        m_Serialdata.append((char)0x00);
    }
    else
    {
        m_Serialdata.append((char)0x01);
    }
    m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);
}

void QSettingDebugForm::paifeifafunA()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x07);
    m_Serialcmd.append(0x0F);
    if(false == m_bjieshoubeipaifeifa)
    {
        m_Serialdata.append((char)0x00);
    }
    else
    {
        m_Serialdata.append((char)0x01);
    }
    m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);
}

void QSettingDebugForm::jinshuifafun()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x07);
    m_Serialcmd.append(0x10);
    if(false == m_blengningshuijinshuifa)
    {
        m_Serialdata.append((char)0x00);
    }
    else
    {
        m_Serialdata.append((char)0x01);
    }
    m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);
}

void QSettingDebugForm::Setcolor(QByteArray pData)
{
    QString str = "";
    unsigned char j = (int)pData.at(6);
    unsigned int jj = (int)j;
    j = (int)pData.at(7);
    jj = jj << 8;
    jj = jj | j;
    str = QString::number(jj);
    ui->ed_settingdebug_r->setText(str);

    j = (int)pData.at(8);
    jj = (int)j;
    j = (int)pData.at(9);
    jj = jj << 8;
    jj = jj | j;
    str = QString::number(jj);
    ui->ed_settingdebug_g->setText(str);

    j = (int)pData.at(10);
    jj = (int)j;
    j = (int)pData.at(11);
    jj = jj << 8;
    jj = jj | j;
    str = QString::number(jj);
    ui->ed_settingdebug_b->setText(str);

    j = (int)pData.at(12);
    jj = (int)j;
    j = (int)pData.at(13);
    jj = jj << 8;
    jj = jj | j;
    str = QString::number(jj);
    ui->le_settingdebug_c->setText(str);
}

void QSettingDebugForm::Stateshow()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x08);
    m_Serialcmd.append(0x01);
    m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);

    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x07);
    m_Serialcmd.append(0x01);
    bool ret = m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);
    //qDebug() << "QSettingDebugForm state show" << ret ;
}

void QSettingDebugForm::jianshuibeng()
{
    if(true == m_bjianshuibeng)
     {
         m_plbjiashuibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
         m_bjianshuibeng = false;

     }
     else
     {
          m_plbjiashuibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
          m_bjianshuibeng = true;
     }
    jiashuibeng();
}


void QSettingDebugForm::suantongfa()
{
    if(true == m_bsuantongfa)
     {
         m_plbsantongfa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
         m_bsuantongfa = false;
     }
     else
     {
          m_plbsantongfa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
          m_bsuantongfa = true;
     }
    xishihuisantongfa();
}


void QSettingDebugForm::qingxibeng()
{
    if(true == m_bqingxibeng)
     {
         m_plbqingxibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
         m_bqingxibeng = false;
     }
     else
     {
          m_plbqingxibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
          m_bqingxibeng = true;
     }
    qingxibengfun();
}


void QSettingDebugForm::pengsuanbeng()
{
    if(true == m_bpengsuanbeng)
     {
         m_plbpengsuanbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
         m_bpengsuanbeng = false;
     }
     else
     {
          m_plbpengsuanbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
          m_bpengsuanbeng = true;
     }
    pengsuanbengfun();
}


void QSettingDebugForm::paifeifa()
{
    if(true == m_bpaifeifa)
     {
         m_plbpaifeifa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
         m_bpaifeifa = false;
     }
     else
     {
          m_plbpaifeifa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
          m_bpaifeifa = true;
     }
    paifeifafun();
}

void QSettingDebugForm::jianguanfa()
{
    if(true == m_bjianguanfa)
     {
         m_plbjiaguanfa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
         m_bjianguanfa = false;
     }
     else
     {
          m_plbjiaguanfa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
          m_bjianguanfa = true;
     }
    jiaguanfafun();
}

void QSettingDebugForm::jiaobanji()
{
    if(true == m_bjiaobanji)
     {
         m_plbjiaobanji->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
         m_bjiaobanji = false;
     }
     else
     {
          m_plbjiaobanji->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
          m_bjiaobanji = true;
     }
    jiaobandianjifun();
}


void QSettingDebugForm::yanseled()
{
    if(true == m_byanseled)
     {
         m_plbyanseled->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
         m_byanseled = false;
     }
     else
     {
          m_plbyanseled->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
          m_byanseled = true;
     }

    yanseledfun();
}


void QSettingDebugForm::zhengqisantongfa()
{
    if(true == m_bzhengqisantongfa)
     {
         m_plbzhengqisantongfa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
         m_bzhengqisantongfa = false;
     }
     else
     {
          m_plbzhengqisantongfa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
          m_bzhengqisantongfa = true;
     }
    zhengqisantongfafun();
}


void QSettingDebugForm::jianbeng()
{
    if(true == m_bjianbeng)
     {
         m_plbjianbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
         m_bjianbeng = false;
     }
     else
     {
          m_plbjianbeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
          m_bjianbeng = true;
     }
    jianfafun();
}


void QSettingDebugForm::didingsantongfa()
{
    if(true == m_bdidingsantongfa)
     {
         m_plbdidingsantongfa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
         m_bdidingsantongfa = false;
     }
     else
     {
          m_plbdidingsantongfa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
          m_bdidingsantongfa = true;
     }

    didingsantongfun();
}


void QSettingDebugForm::zhaomingled()
{
    if(true == m_bzhaomingled)
     {
         m_plbzhaopmingled->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
         m_bzhaomingled = false;
     }
     else
     {
          m_plbzhaopmingled->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
          m_bzhaomingled = true;
     }
    zhaomingledfun();
}


void QSettingDebugForm::jieshoubeioaifeibeng()
{
    if(true == m_bjieshoubeioaifeibeng)
     {
         m_plbjieshoubeipaifeibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
         m_bjieshoubeioaifeibeng = false;
     }
     else
     {
          m_plbjieshoubeipaifeibeng->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
          m_bjieshoubeioaifeibeng = true;
     }
    paifeibengfun();
}


void QSettingDebugForm::jieshoubeipaifeifa()
{
    if(true == m_bjieshoubeipaifeifa)
     {
         m_plbjieshoubeipaifeifa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
         m_bjieshoubeipaifeifa = false;
     }
     else
     {
          m_plbjieshoubeipaifeifa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
          m_bjieshoubeipaifeifa = true;
     }
    paifeifafunA();
}


void QSettingDebugForm::lengningshuijinshuifa()
{
    if(true == m_blengningshuijinshuifa)
     {
         m_plblengningshuijinshuifa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
         m_blengningshuijinshuifa = false;
     }
     else
     {
          m_plblengningshuijinshuifa->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
          m_blengningshuijinshuifa = true;
     }
    jinshuifafun();
}




void QSettingDebugForm::on_pb_zhusaibengup_clicked()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x07);
    m_Serialcmd.append(0x11);
    m_Serialdata.append((char)0x00);
    m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);
}

void QSettingDebugForm::on_pb_zhusaibengdown_clicked()
{
    m_Serialcmd.clear();
    m_Serialdata.clear();
    m_Serialcmd.append(0x07);
    m_Serialcmd.append(0x11);
    m_Serialdata.append((char)0x01);
    m_pSerialDebug->TransmitData(m_Serialcmd, m_Serialdata);
}
