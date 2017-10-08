#include "qsettingmethodform.h"
#include "ui_qsettingmethodform.h"
#include "DataDef.h"
#include "qmainscreen.h"
//#include "qdatabasequery.h"
#include <QMessageBox>

QSettingMethodForm::QSettingMethodForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSettingMethodForm),
    m_ItemModel(NULL),
    pdataquery(NULL),
    strtable("method"),
    m_strexpress(""),
    m_bfromview(false),
    m_RemFileSize(0),
    m_bSendFileFalg(false),
    m_bDataDNOFalg(true),
    m_iIndex(0),
    m_iLen(0)
{
    ui->setupUi(this);
    m_ptc =  QTextCodec::codecForName("UTF-8");
    QMainScreen *pWidget = static_cast<QMainScreen *>(this->parent());
    m_pNetControl = pWidget->m_pNetControl;
    InitOCX();
    InitSings();
    m_bjieshoubei = true;
    m_bxiaohuaguan = true;
    pdataquery = new QDatabasequery();
    pdataquery->SetTableName("./db/Method/method");
    pdataquery->opendatabase();
    pdataquery->GetValues(strtable, linstvalues, 1);
    pdataquery->cloesdatabase();
    settableview(linstvalues);
}

QSettingMethodForm::~QSettingMethodForm()
{
    delete ui;
}


void QSettingMethodForm::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("QWidget#QSettingMethodForm{image:url(:/images/bk/bk_setting_method.png)}""QSettingMethodForm{background-color:transparent;}");

    ui->label_fangfa->setGeometry(28,8,111,36);
    ui->label_fangfa->setText(m_ptc->toUnicode("方法"));
    ui->label_fangfa->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    //bt
    ui->pb_settingmethod_pgup->setFlat(true);
    //ui->pb_settingmethod_pgup->setFocusPolicy(Qt::NoFocus);
    ui->pb_settingmethod_pgup->setGeometry(85,604,108,44);
    ui->pb_settingmethod_pgup->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_pgup_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_pgup_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_pgup_press.png);}");
    ui->pb_settingmethod_pgup->hide();

    ui->pb_settingmethod_pgdn->setFlat(true);
    //ui->pb_settingmethod_pgdn->setFocusPolicy(Qt::NoFocus);
    ui->pb_settingmethod_pgdn->setGeometry(212,604,108,44);
    ui->pb_settingmethod_pgdn->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_pgdn_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_pgdn_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_pgdn_press.png);}");
    ui->pb_settingmethod_pgdn->hide();

    ui->pb_settingmethod_delete->setFlat(true);
    //ui->pb_settingmethod_delete->setFocusPolicy(Qt::NoFocus);
    ui->pb_settingmethod_delete->setGeometry(172,604,108,44);
    ui->pb_settingmethod_delete->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_delete_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_delete_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_delete_press.png);}");

    ui->pb_settingmethod_add->setFlat(true);
    //ui->pb_settingmethod_add->setFocusPolicy(Qt::NoFocus);
    ui->pb_settingmethod_add->setGeometry(329+70,604,108,44);
    ui->pb_settingmethod_add->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_add_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_add_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_add_press.png);}");


    ui->pb_settingmethod_save->setFlat(true);
    //ui->pb_settingmethod_save->setFocusPolicy(Qt::NoFocus);
    ui->pb_settingmethod_save->setGeometry(486+140,604,108,44);
    ui->pb_settingmethod_save->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_save_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_save_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_save_press.png);}");

    ui->pb_settingmethod_colud->setFlat(true);
    //ui->pb_settingmethod_colud->setFocusPolicy(Qt::NoFocus);
    ui->pb_settingmethod_colud->setGeometry(643,604,108,44);
    ui->pb_settingmethod_colud->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_cloud_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_cloud_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_cloud_press.png);}");
    ui->pb_settingmethod_colud->setHidden(true);

    //edit
    ui->le_settingmethod_mingcheng->setGeometry(540,72,291, 35);
    ui->le_settingmethod_mingcheng->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);}");
    ui->le_settingmethod_mingcheng->setMaxLength(26);

    QValidator *v0=new QDoubleValidator(0, 9999, 2, this); // 0-100 only accept number
    ui->le_settingmethod_xishu->setGeometry(540,120,291, 35);
    ui->le_settingmethod_xishu->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);}");
    ui->le_settingmethod_xishu->setValidator(v0);
    //ui->le_settingmethod_xishu->setInputMask("0000.00");


    QValidator *v1=new QIntValidator(0, 150, this); // 0-100 only accept number

    ui->le_settingmethod_pengsuan->setGeometry(540,168,291, 35);
    ui->le_settingmethod_pengsuan->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);}");
    ui->le_settingmethod_pengsuan->setValidator(v1);

    ui->le_settingmethod_xishishui->setGeometry(540,216,291, 35);
    ui->le_settingmethod_xishishui->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);}");
    ui->le_settingmethod_xishishui->setValidator(v1);

    ui->le_settingmethod_jian->setGeometry(540,264,291, 35);
    ui->le_settingmethod_jian->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);}");
    ui->le_settingmethod_jian->setValidator(v1);

    ui->le_settingmethod_zhengliu->setGeometry(540,312, 188,35);
    ui->le_settingmethod_zhengliu->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line.png);}");

    QValidator *v3 =new QIntValidator(30, 100, this); // 0-100 only accept number
    ui->le_settingmethod_liuliang->setGeometry(540,456,291, 35);
    ui->le_settingmethod_liuliang->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);}");
    ui->le_settingmethod_liuliang->setValidator(v3);

    //combox
    ui->cb_settingmethod_diding->setGeometry(540, 360, 287, 31);
    ui->cb_settingmethod_diding->setStyleSheet("QComboBox{border:1px solid gray;}"
      "QComboBox QAbstractItemView::item{height:50px;}"
      "QComboBox::down-arrow{image:url(:/images/bt/arrowdownBo.png);}"
      "QComboBox::drop-down{border:0px;}");
    ui->cb_settingmethod_diding->setView(new QListView());


    ui->cb_settingmethod_diding->addItem(m_ptc->toUnicode("边蒸馏边滴定"));
    ui->cb_settingmethod_diding->addItem(m_ptc->toUnicode("先蒸馏后滴定"));

    ui->cb_setting_metoh_jiajian->setGeometry(540, 408, 287, 31);
    ui->cb_setting_metoh_jiajian->setStyleSheet("QComboBox{border:1px solid gray;}"
      "QComboBox QAbstractItemView::item{height:50px;}"
      "QComboBox::down-arrow{image:url(:/images/bt/arrowdownBo.png);}"
      "QComboBox::drop-down{border:0px;}");
    ui->cb_setting_metoh_jiajian->setView(new QListView());


    ui->cb_setting_metoh_jiajian->addItem(m_ptc->toUnicode("先加碱后蒸馏"));
    ui->cb_setting_metoh_jiajian->addItem(m_ptc->toUnicode("先蒸馏后加碱"));

    ui->cb_settingmethod_zhengliudanwei->setGeometry(728, 313, 102, 31);
    ui->cb_settingmethod_zhengliudanwei->setStyleSheet("QComboBox{border:1px solid gray;}"
      "QComboBox QAbstractItemView::item{height:50px;}"
      "QComboBox::down-arrow{image:url(:/images/bt/arrowdownBo.png);}"
      "QComboBox::drop-down{border:0px;}");
    ui->cb_settingmethod_zhengliudanwei->setView(new QListView());

    ui->cb_settingmethod_zhengliudanwei->addItem(m_ptc->toUnicode("mL"));
    ui->cb_settingmethod_zhengliudanwei->addItem(m_ptc->toUnicode("s"));
    ui->cb_settingmethod_zhengliudanwei->setCurrentIndex(0);

    //label
    ui->lb_settting_method_mingcheng->setGeometry(456, 73, 100, 30);
    ui->lb_settting_method_mingcheng->setText(m_ptc->toUnicode("方法名称："));
    ui->lb_settting_method_mingcheng->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settting_method_xishu->setGeometry(456, 121, 100, 30);
    ui->lb_settting_method_xishu->setText(m_ptc->toUnicode("蛋白系数："));
    ui->lb_settting_method_xishu->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settting_method_pengsuan->setGeometry(456, 169, 100, 30);
    ui->lb_settting_method_pengsuan->setText(m_ptc->toUnicode("硼酸："));
    ui->lb_settting_method_pengsuan->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settting_method_xishishui->setGeometry(456, 217, 100, 30);
    ui->lb_settting_method_xishishui->setText(m_ptc->toUnicode("稀释水："));
    ui->lb_settting_method_xishishui->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settting_method_jian->setGeometry(456, 265, 100, 30);
    ui->lb_settting_method_jian->setText(m_ptc->toUnicode("碱："));
    ui->lb_settting_method_jian->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settting_method_zhengliu->setGeometry(456, 313, 100, 30);
    ui->lb_settting_method_zhengliu->setText(m_ptc->toUnicode("蒸馏："));
    ui->lb_settting_method_zhengliu->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settting_method_diding->setGeometry(456, 361, 100, 30);
    ui->lb_settting_method_diding->setText(m_ptc->toUnicode("滴定方式："));
    ui->lb_settting_method_diding->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settting_method_jiajian->setGeometry(456, 409, 100, 30);
    ui->lb_settting_method_jiajian->setText(m_ptc->toUnicode("加碱方式："));
    ui->lb_settting_method_jiajian->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settting_method_liuliang->setGeometry(456, 457, 100, 30);
    ui->lb_settting_method_liuliang->setText(m_ptc->toUnicode("蒸汽流量："));
    ui->lb_settting_method_liuliang->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settting_method_xiaohuaguan->setGeometry(456, 503, 100, 30);
    ui->lb_settting_method_xiaohuaguan->setText(m_ptc->toUnicode("消化管排废："));
    ui->lb_settting_method_xiaohuaguan->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settting_method_jieshoubei->setGeometry(456, 546, 100, 30);
    ui->lb_settting_method_jieshoubei->setText(m_ptc->toUnicode("接收杯清洗："));
    ui->lb_settting_method_jieshoubei->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settting_method_ml->setGeometry(830, 168, 100, 30);
    ui->lb_settting_method_ml->setText(m_ptc->toUnicode("mL"));
    ui->lb_settting_method_ml->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settting_method_ml1->setGeometry(830, 216, 100, 30);
    ui->lb_settting_method_ml1->setText(m_ptc->toUnicode("mL"));
    ui->lb_settting_method_ml1->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settting_method_ml2->setGeometry(830, 264, 100, 30);
    ui->lb_settting_method_ml2->setText(m_ptc->toUnicode("mL"));
    ui->lb_settting_method_ml2->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settting_method_baifen->setGeometry(830, 456, 100, 30);
    ui->lb_settting_method_baifen->setText(m_ptc->toUnicode("%"));
    ui->lb_settting_method_baifen->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    m_pLbjieshoubei = new QMLabel(this);
    m_pLbjieshoubei->setGeometry(640,545,78, 29);
    m_pLbjieshoubei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    m_pLbxiaohuaguan = new QMLabel(this);
    m_pLbxiaohuaguan->setGeometry(640,502,78, 29);
    m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");

    m_ItemModel = new ListModel(this);
    m_ItemModel->setColumnCount(1);
    m_ItemModel->setRowCount(100);
    m_ItemModel->setHorizontalHeaderLabels(QStringList() /*<< m_ptc->toUnicode("序号") */<< m_ptc->toUnicode("方法名称"));


    ui->tb_method_param->setAlternatingRowColors(true);
    ui->tb_method_param->setGeometry(14, 68, 388, 491);
    ui->tb_method_param->setStyleSheet("QTableView::item{background-color:rgb(255,255,255)}""QTableView::item{selection-background-color:rgb(232,232,232)}");
    ui->tb_method_param->verticalHeader()->hide();
    //ui->tb_pici_param->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->tb_pici_param->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tb_method_param->setFrameShape(QFrame::NoFrame);
    ui->tb_method_param->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
    "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
    "QScrollBar::handle:hover{background:gray;}"
    "QScrollBar::sub-line{background:transparent;}"
    "QScrollBar::add-line{background:transparent;}");
    ui->tb_method_param->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
    "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
    "QScrollBar::handle:hover{background:gray;}"
    "QScrollBar::sub-line{background:transparent;}"
    "QScrollBar::add-line{background:transparent;}");
    ui->tb_method_param->setModel(m_ItemModel);

    ui->tb_method_param->setSelectionBehavior(QAbstractItemView::SelectRows);
#ifdef _MIPS_LINUX_ENV_
    ui->tb_method_param->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tb_method_param->horizontalHeader()->setStretchLastSection(true);
#else
    ui->tb_method_param->horizontalHeader()->setStretchLastSection(true);
    ui->tb_method_param->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

    //IDDelegate *pIDdelegate = new IDDelegate(this);
    ReadOnlyDelegate *preadonlydelegate = new ReadOnlyDelegate(this);
    //re *preadonlydelegate = new (this);
    ui->tb_method_param->setItemDelegateForColumn(0, preadonlydelegate);
}

void QSettingMethodForm::InitSings()
{
    connect(m_pLbjieshoubei, SIGNAL(clicked()), this, SLOT(jieshoubei()));
    connect(m_pLbxiaohuaguan, SIGNAL(clicked()), this, SLOT(xiaohuaguan()));
}


void QSettingMethodForm::jieshoubei()
{
    if(true == m_bjieshoubei)
     {
         m_pLbjieshoubei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
         m_bjieshoubei = false;
     }
     else
     {
          m_pLbjieshoubei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
          m_bjieshoubei = true;
     }
}


void QSettingMethodForm::xiaohuaguan()
{
   if(true == m_bxiaohuaguan)
    {
        m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
        m_bxiaohuaguan = false;
    }
    else
    {
         m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
         m_bxiaohuaguan = true;
    }
}

void QSettingMethodForm::on_pb_settingmethod_save_clicked()
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



    strmingcheng = ui->le_settingmethod_mingcheng->text();
    strxishu = ui->le_settingmethod_xishu->text();
    strpengsuan = ui->le_settingmethod_pengsuan->text();
    strxishishui = ui->le_settingmethod_xishishui->text();
    strjian = ui->le_settingmethod_jian->text();
    strzhengliu = ui->le_settingmethod_zhengliu->text();
    strliulang = ui->le_settingmethod_liuliang->text();

    if((strmingcheng.isEmpty()) || (strxishu.isEmpty()) || (strpengsuan.isEmpty()) || (strxishishui.isEmpty()) || (strjian.isEmpty()) || (strzhengliu.isEmpty()) || (strliulang.isEmpty()))
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("数据不能为空"), QMessageBox::Ok);
        return;
    }

    if(false == m_bfromview)
    {
        if(false == checkname(strmingcheng))
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("方法名重复"), QMessageBox::Ok);
            return;
        }
    }


    if(0 == ui->cb_settingmethod_diding->currentIndex())
    {
        strdidingfangshi = "0";
    }
    else
    {
        strdidingfangshi = "1";
    }

    if(0 == ui->cb_setting_metoh_jiajian->currentIndex())
    {
        strjiajianfangshi = "0";
    }
    else
    {
        strjiajianfangshi = "1";
    }

    if(0 == ui->cb_settingmethod_zhengliudanwei->currentIndex())
    {
        strzhengliudanwei = "0";
    }
    else
    {
        strzhengliudanwei = "1";
    }

    if(false == m_bjieshoubei)
    {
        strjieshoubei = "0";
    }
    else
    {
        strjieshoubei = "1";
    }

    if(false == m_bxiaohuaguan)
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

        if(false == m_bfromview)
        {
            pdataquery->insert(strtable, linstname, linstvalues);
            HNCreateSysEvent("新增方法记录");
        }
        else
        {
            QModelIndex index = ui->tb_method_param->currentIndex();
            QString strTemp = m_ItemModel->index(index.row(), 0).data().toString();
            QString strex = "mingcheng = '" + strTemp + "'";
            pdataquery->Updata(strtable, linstname, linstvalues, strex);
            HNCreateSysEvent("修改方法记录");
        }

        linstvalues.clear();
        pdataquery->GetValues(strtable, linstvalues, 1);
        pdataquery->cloesdatabase();
        settableview(linstvalues);

    }
    QMainScreen *pWidget = static_cast<QMainScreen *>(this->parent());
    pWidget->m_pAutoTest->updatabase();
    qDebug() << __func__ << __LINE__  << strxiaohuaguan;
    qDebug() << __func__ << __LINE__  << strjieshoubei;
    QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("保存成功"), QMessageBox::Ok);
}

void QSettingMethodForm::on_pb_settingmethod_add_clicked()
{
    //ui->le_settingmethod_mingcheng->setEnabled(true);
    m_bfromview = false;
    cleandata();
}


void QSettingMethodForm::cleandata()
{

    ui->le_settingmethod_mingcheng->setText(m_ptc->toUnicode(""));
    ui->le_settingmethod_pengsuan->setText(m_ptc->toUnicode(""));
    ui->le_settingmethod_jian->setText(m_ptc->toUnicode(""));
    ui->le_settingmethod_liuliang->setText(m_ptc->toUnicode(""));
    ui->le_settingmethod_xishishui->setText(m_ptc->toUnicode(""));
    ui->le_settingmethod_xishu->setText(m_ptc->toUnicode(""));
    ui->le_settingmethod_zhengliu->setText(m_ptc->toUnicode(""));
    ui->cb_settingmethod_diding->setCurrentIndex(0);
    ui->cb_settingmethod_zhengliudanwei->setCurrentIndex(0);
    ui->cb_setting_metoh_jiajian->setCurrentIndex(0);

    m_pLbjieshoubei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
    m_bjieshoubei = false;

    m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
    m_bxiaohuaguan = false;
}

void QSettingMethodForm::settableview(QStringList &strdata)
{
    int index = 0;
    int i = 0;
    //pline() << strdata;
    if(strdata.isEmpty())
    {
        //return;
    }
    //pline();

    index = strdata.size();
    //m_ItemModel->clear();

    //m_ItemModel->setColumnCount(1);
    //m_ItemModel->setRowCount(100);
    //m_ItemModel->setHorizontalHeaderLabels(QStringList() /*<< m_ptc->toUnicode("序号") */<< m_ptc->toUnicode("方法名称"));

    while (i != index){
        QModelIndex mindex = m_ItemModel->index(i, 0,QModelIndex());
        m_ItemModel->setData(mindex, strdata.at(i));
        i++;
    }
    for(int ii = index; ii < 100; ii++)
    {
        QModelIndex mindex = m_ItemModel->index(i, 0,QModelIndex());
        m_ItemModel->setData(mindex, "");
    }
    //ui->tb_method_param->setModel(m_ItemModel);
}

void QSettingMethodForm::on_pb_settingmethod_delete_clicked()
{
    QMessageBox::StandardButton rb  = QMessageBox::question(this, m_ptc->toUnicode(""), m_ptc->toUnicode("是否删除数据"), QMessageBox::Yes | QMessageBox::No);
    if(rb == QMessageBox::Yes)
    {
        if(true == pdataquery->opendatabase())
        {
            QString strname = "mingcheng";
            pdataquery->del(strtable,strname, m_strexpress);

            linstvalues.clear();
            pdataquery->GetValues(strtable, linstvalues, 1);
            pdataquery->cloesdatabase();
            settableview(linstvalues);
            HNCreateSysEvent("删除方法记录");
        }

        //ui->le_settingmethod_mingcheng->setEnabled(true);
        m_bfromview =false;
        cleandata();
        QMainScreen *pWidget = static_cast<QMainScreen *>(this->parent());
        pWidget->m_pAutoTest->updatabase();
    }

    if(rb == QMessageBox::No)
    {
        return;
    }


}

void QSettingMethodForm::on_tb_method_param_doubleClicked(const QModelIndex &index)
{

}

void QSettingMethodForm::on_tb_method_param_clicked(const QModelIndex &index)
{
    m_strexpress = index.data().toString();

    int irow = index.row();
    QString strname = "mingcheng";
    linstvalues.clear();
    QString str = index.data().toString();
    if(true == pdataquery->opendatabase())
    {
        pdataquery->GetoneValues(strtable, linstvalues, strname, str, 13);
        pdataquery->cloesdatabase();
    }

    ui->le_settingmethod_mingcheng->setText(linstvalues.at(1));
    ui->le_settingmethod_xishu->setText(linstvalues.at(2));
    ui->le_settingmethod_pengsuan->setText(linstvalues.at(3));
    ui->le_settingmethod_xishishui->setText(linstvalues.at(4));
    ui->le_settingmethod_jian->setText(linstvalues.at(5));
    ui->le_settingmethod_zhengliu->setText(linstvalues.at(6));
    ui->cb_settingmethod_zhengliudanwei->setCurrentIndex(linstvalues.at(7).toInt());
    ui->cb_settingmethod_diding->setCurrentIndex(linstvalues.at(8).toInt());
    ui->cb_setting_metoh_jiajian->setCurrentIndex(linstvalues.at(9).toInt());
    ui->le_settingmethod_liuliang->setText(linstvalues.at(10));


    qDebug() << __func__ << __LINE__ << linstvalues.at(12).toInt();
    qDebug() << __func__<< __LINE__ << linstvalues.at(11).toInt();
    if(0 == linstvalues.at(12).toInt())
    {
        m_pLbjieshoubei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
        m_bjieshoubei =false;
    }
    else
    {
        m_pLbjieshoubei->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
        m_bjieshoubei = true;
    }

    if(0 == linstvalues.at(11).toInt())
    {
        m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_no.png);}");
        m_bxiaohuaguan = false;
    }
    else
    {
        m_pLbxiaohuaguan->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_yes.png);}");
        m_bxiaohuaguan = true;
    }

   // ui->le_settingmethod_mingcheng->setEnabled(false);
    m_bfromview = true;
}

bool QSettingMethodForm::checkname(QString strName)
{
    int iRow = m_ItemModel->rowCount();
    for(int i = 0; i < iRow; i++)
    {
         QString strTemp = m_ItemModel->index(i,0).data().toString();
         if(strTemp == strName)
         {
             return false;
         }
    }

    return true;
}

void QSettingMethodForm::SendFileInfo()
{
    QByteArray by;
    int iFileSize = 0;
    m_strFileList.append("./db/Method/method.db");
    //m_strFileList= QFileDialog::getOpenFileNames( 0, "Select File(s)", QDir::homePath());
    QString strName = m_strFileList.at(0);

    int index = strName.lastIndexOf('\/');
    strName = strName.mid(index+1);
    QDateTime dt = QDateTime::currentDateTime();

    QString strTime =  dt.toString("yyyy-MM-dd hh:mm:ss");
    strName = "hanon_" + strTime + "_.db";
    QFile File(m_strFileList.at(0));
    iFileSize = File.size();
    by.clear();
    QString strData = "";
    strData = QString(NETCOMMANDDATASENDFILEINFO).arg("001").arg(strName).arg("TRUE").arg(iFileSize);
    by.append(strData);
    m_pNetControl->PackAndSendData(by,COMMANDSENDFILEINFO);
}

void QSettingMethodForm::on_pb_settingmethod_colud_clicked()
{

     QMainScreen *pWidget = static_cast<QMainScreen *>(this->parent());
     if(true == pWidget->m_bwififlag)
     {

         if(false == m_pNetControl->m_bUserLogin)
         {
             QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("用户未登入，请检查wifi链接"), QMessageBox::Ok);
             return;
         }
        //SendFileInfo();
     }
     else
     {
         QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("wifi未连接"), QMessageBox::Ok);
     }
}

void QSettingMethodForm::StartSendFile()
{
    QByteArray byTemp;
    QByteArray by;
    QString strNum = "";
    int TRANS_BYTES = 1024;
    int iAddress = 0;
    int iLen = 0;
    if(m_File.isOpen())
        m_File.close();

    int i = 0;
    QString strName = m_strFileList.at(0);
    m_File.setFileName(strName);

    for(int i = 0; i < 4; i++)
    {
        by.append(m_pNetControl->m_CommandFileID.at(i));
    }

    if(true == m_File.open(QIODevice::ReadOnly))
    {
        m_bSendFileFalg = true;
        m_RemFileSize = m_File.size() - m_RemFileSize;
       //while(m_RemFileSize > 0)
        {
            if(true == m_bDataDNOFalg)
            {
                m_bDataDNOFalg = false;
                by.clear();
                byTemp.clear();
                by.append(m_pNetControl->m_CommandFileID);
                by.append(m_pNetControl->GetDNOAndAddress(m_iIndex));
                by.append(m_pNetControl->GetDNOAndAddress(m_iLen));
                m_File.seek(m_File.size() - m_RemFileSize);
                byTemp = m_File.read(TRANS_BYTES);
                iLen = byTemp.size();
                by.append(m_pNetControl->GetDataLen(iLen));
                by.append(byTemp);
                m_iLen += iLen;
                m_RemFileSize -= TRANS_BYTES;
                m_iIndex++;
               m_pNetControl->PackAndSendData(by,COMMANDSENDFILEDATA);
            }
        }
        //m_bSendFileFalg = false;
    }
}


void QSettingMethodForm::updatedatabase()
{
    linstvalues.clear();
    pdataquery->opendatabase();
    pdataquery->GetValues(strtable, linstvalues, 1);
    pdataquery->cloesdatabase();
    settableview(linstvalues);
}

void QSettingMethodForm::Senddata()
{
    QByteArray by;
    QByteArray byTemp;
    int TRANS_BYTES = 1024;
    int iLen = 0;

    if(true == m_bDataDNOFalg)
    {
        m_bDataDNOFalg = false;
        by.clear();
        byTemp.clear();
        by.append(m_pNetControl->m_CommandFileID);
        by.append(m_pNetControl->GetDNOAndAddress(m_iIndex));
        by.append(m_pNetControl->GetDNOAndAddress(m_iLen));
        m_File.seek(m_File.size() - m_RemFileSize);
        byTemp = m_File.read(TRANS_BYTES);
        iLen = byTemp.size();
        by.append(m_pNetControl->GetDataLen(iLen));
        by.append(byTemp);
        m_iLen += iLen;
        m_RemFileSize -= TRANS_BYTES;
        m_iIndex++;
       m_pNetControl->PackAndSendData(by,COMMANDSENDFILEDATA);
    }
}

void QSettingMethodForm::on_cb_settingmethod_zhengliudanwei_currentIndexChanged(int index)
{
    static QValidator *v2 =new QIntValidator(0, 1800, this); // 0-100 only accept number
    static QValidator *v3 =new QIntValidator(0, 450, this); // 0-100 only accept number
    if(0 == index)
        ui->le_settingmethod_zhengliu->setValidator(v3);
    else if(1 == index)
        ui->le_settingmethod_zhengliu->setValidator(v2);
    //qDebug() << index;
}
