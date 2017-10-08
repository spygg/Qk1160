#include "qsettingoriginsform.h"
#include "ui_qsettingoriginsform.h"
#include "DataDef.h"
#include <QMessageBox>
#include "HNDefine.h"

#define DB_SUYUAN "suyuan"
#define TABLE_SUYUAN "suyuan"

QSettingOriginsForm::QSettingOriginsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSettingOriginsForm),
    strtable("suyuan")
{
    ui->setupUi(this);
    //m_querymodel = new QSqlQueryModel(this);
    m_ptc =  QTextCodec::codecForName("UTF-8");
    connect(ui->pb_pgup, SIGNAL(clicked()),
            ui->tb_settingOrigins_list, SLOT(on_btnLeft_clicked()));
    connect(ui->pb_pgdn, SIGNAL(clicked()),
            ui->tb_settingOrigins_list, SLOT(on_btnRight_clicked()));

    ui->tb_settingOrigins_list->setDB(QString("%1/%2").arg(".").arg(DB_EVENT));
    ui->tb_settingOrigins_list->setTable(TABLE_EVENT);

    InitOCX();
    InitSings();
}

QSettingOriginsForm::~QSettingOriginsForm()
{
    delete ui;
}


void QSettingOriginsForm::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("QWidget#QSettingOriginsForm{image:url(:/images/bk/bk_clean.png)}""QSettingOriginsForm{background-color:transparent;}");


    ui->pb_pgup->setFlat(true);
    ui->pb_pgup->setFocusPolicy(Qt::NoFocus);
    ui->pb_pgup->setGeometry(248,578,108,44);
    ui->pb_pgup->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_pgup_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_pgup_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_pgup_press.png);}");

    ui->pb_pgdn->setFlat(true);
    ui->pb_pgdn->setFocusPolicy(Qt::NoFocus);
    ui->pb_pgdn->setGeometry(500,578,108,44);
    ui->pb_pgdn->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_pgdn_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_pgdn_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_pgdn_press.png);}");

    ui->lb_page->setGeometry(766, 525, 50, 24);
    ui->lb_page->setFocusPolicy(Qt::NoFocus);
    ui->lb_page->setText(m_ptc->toUnicode("00/00"));
    ui->lb_page->setStyleSheet("QMLabel{background-color:transparent;}");
    ui->lb_page->hide();

    //edit
    ui->le_page->setGeometry(821,525,62,28);
    ui->le_page->setFocusPolicy(Qt::NoFocus);
    ui->le_page->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/le_data_jump.png);}");
    ui->le_page->hide();

    ui->tb_settingOrigins_list->setAlternatingRowColors(true);
    ui->tb_settingOrigins_list->setFocusPolicy(Qt::NoFocus);
    ui->tb_settingOrigins_list->setGeometry(38, 41, 837, 540);

    /*
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("./db/suyuan.db");
    if(!m_db.open()) return;

    ui->tb_settingOrigins_list->setModel(m_querymodel);
    m_icurrentpage = 1;
    m_itotalcount = GetTotalCount(strtable);
    m_itotalpage = GetPageCount();
    */

    ui->tb_settingOrigins_list->setHeaderData(0,Qt::Horizontal, m_ptc->toUnicode("编号"));
    ui->tb_settingOrigins_list->setHeaderData(1,Qt::Horizontal, m_ptc->toUnicode("名称"));
    ui->tb_settingOrigins_list->setHeaderData(2,Qt::Horizontal, m_ptc->toUnicode("动作"));
    ui->tb_settingOrigins_list->setHeaderData(3,Qt::Horizontal, m_ptc->toUnicode("时间"));
    ui->tb_settingOrigins_list->setHeaderData(4,Qt::Horizontal, m_ptc->toUnicode("操作人"));

    //RecordQuery(0);
    //ui->tb_settingOrigins_list->setSelectionBehavior(QAbstractItemView::SelectRows);
    //UpdateStatus();

    ui->tb_settingOrigins_list->setResizeMode(QHeaderView::Stretch);
    ui->tb_settingOrigins_list->setResizeMode(3, QHeaderView::ResizeToContents);

    //ui->tb_settingOrigins_list->setColumnHidden(4);
    ui->tb_settingOrigins_list->setColumnHidden(5);

    ui->tb_settingOrigins_list->query();
    ui->tb_settingOrigins_list->setCurrentPage(1);

#ifdef _MIPS_LINUX_ENV_
    //ui->tb_settingOrigins_list->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->tb_settingOrigins_list->horizontalHeader()->setStretchLastSection(true);
#else
    //ui->tb_settingOrigins_list->horizontalHeader()->setStretchLastSection(true);
    //ui->tb_settingOrigins_list->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif
    /*
    m_ItemModel = new QStandardItemModel(this);
    m_ItemModel->setColumnCount(3);
    m_ItemModel->setRowCount(60);
    m_ItemModel->setHorizontalHeaderLabels(QStringList() << m_ptc->toUnicode("实验名称") << m_ptc->toUnicode("删除时间") << m_ptc->toUnicode("操作人员"));

    //ui->tb_settingOrigins_list->setAlternatingRowColors(true);
    ui->tb_settingOrigins_list->setGeometry(38, 41, 837, 476);
    ui->tb_settingOrigins_list->setStyleSheet("QTableView::item{background-color:rgb(255,255,255)}""QTableView::item{selection-background-color:rgb(232,232,232)}");
    ui->tb_settingOrigins_list->verticalHeader()->hide();
    //ui->tb_pici_param->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->tb_pici_param->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tb_settingOrigins_list->setFrameShape(QFrame::NoFrame);
    ui->tb_settingOrigins_list->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
    "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
    "QScrollBar::handle:hover{background:gray;}"
    "QScrollBar::sub-line{background:transparent;}"
    "QScrollBar::add-line{background:transparent;}");
    ui->tb_settingOrigins_list->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
    "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
    "QScrollBar::handle:hover{background:gray;}"
    "QScrollBar::sub-line{background:transparent;}"
    "QScrollBar::add-line{background:transparent;}");
    ui->tb_settingOrigins_list->setModel(m_ItemModel);

    ui->tb_settingOrigins_list->setSelectionBehavior(QAbstractItemView::SelectRows);
#ifdef _MIPS_LINUX_ENV_
    ui->tb_settingOrigins_list->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tb_settingOrigins_list->horizontalHeader()->setStretchLastSection(true);
#else
    ui->tb_settingOrigins_list->horizontalHeader()->setStretchLastSection(true);
    ui->tb_settingOrigins_list->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

    ReadOnlyDelegate *preadonlydelegate = new ReadOnlyDelegate(this);
    ui->tb_settingOrigins_list->setItemDelegateForColumn(0, preadonlydelegate);
    */
}



void QSettingOriginsForm::InitSings()
{

}


int QSettingOriginsForm::GetTotalCount(QString &strTable)
{
    if(NULL != m_querymodel)
    {
        QString sql = QString("select * from ") + strTable;
        m_querymodel->setQuery(sql);
    }
    return m_querymodel->rowCount();
}


int QSettingOriginsForm::GetPageCount()
{
    return (m_itotalcount % m_epagecount == 0) ? (m_itotalcount / m_epagecount) : (m_itotalcount / m_epagecount + 1);
}

void QSettingOriginsForm::SetPageCount()
{
    QString szCurrentText = QString("%1/%2").arg(QString::number(m_icurrentpage)).arg(QString::number(m_itotalpage));
    ui->lb_page->setText(szCurrentText);
}

void QSettingOriginsForm::RecordQuery(int ilimit)
{
    if(NULL != m_querymodel)
    {
        //QString sql = QString("select * from ") + strtable + QString(" limit ") + ilimit + QString(" , ") + m_epagecount;
       QString sql = QString("select * from %1 limit %2,%3").arg(strtable).arg(QString::number(ilimit)).arg(QString::number(m_epagecount));
       m_querymodel->setQuery(sql);
    }
}


void QSettingOriginsForm::UpdateStatus()
{
    ui->tb_settingOrigins_list->query();
    ui->tb_settingOrigins_list->setCurrentPage(1);

    return;
    //QString szCurrentText = QString("%1/%2").arg(QString::number(m_icurrentpage)).arg(QString::number(m_itotalpage));
    //ui->lb_clean_page->setText(szCurrentText);
    SetPageCount();
    if(1 == m_icurrentpage)
    {
        ui->pb_pgup->setEnabled(false);
        ui->pb_pgdn->setEnabled(true);
    }
    else if(m_icurrentpage == m_itotalpage)
    {
        ui->pb_pgup->setEnabled(true);
        ui->pb_pgdn->setEnabled(false);
    }
    else
    {
        ui->pb_pgup->setEnabled(true);
        ui->pb_pgdn->setEnabled(true);
    }

}

void QSettingOriginsForm::on_pb_pgdn_clicked()
{
    return;

    int limitIndex = m_icurrentpage * m_epagecount;
         m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName("./db/suyuan.db");
        if(!m_db.open()) return;
        RecordQuery(limitIndex);
        m_icurrentpage += 1;
        m_db.close();
        UpdateStatus();
}

void QSettingOriginsForm::on_pb_pgup_clicked()
{
    return;

    int limitIndex = (m_icurrentpage - 2) * m_epagecount;
     m_db = QSqlDatabase::addDatabase("QSQLITE");
     m_db.setDatabaseName("./db/suyuan.db");
    if(!m_db.open()) return;
    RecordQuery(limitIndex);
    m_icurrentpage -= 1;
    m_db.close();
    UpdateStatus();
}

void QSettingOriginsForm::on_le_page_textEdited(const QString &arg1)
{
    //得到输入字符串
    QString szText = arg1;
    //数字正则表达式
    QRegExp regExp("-?[0-9]*");
    //判断是否为数字
    if(!regExp.exactMatch(szText))
     {
        QMessageBox::information(this, tr("提示"), tr("请输入数字"));
        return;
     }
      //是否为空
      if(szText.isEmpty())
      {
         QMessageBox::information(this, tr("提示"), tr("请输入跳转页面"));
         return;
      }
      //得到页数
      int pageIndex = szText.toInt();
      //判断是否有指定页
      if(pageIndex > m_itotalpage || pageIndex < 1)
      {
        QMessageBox::information(this, tr("提示"), tr("没有指定的页面，请重新输入"));
           return;
      }
      //得到查询起始行号
      int limitIndex = (pageIndex-1) * m_epagecount;
      m_db = QSqlDatabase::addDatabase("QSQLITE");
      m_db.setDatabaseName("./db/suyuan.db");
     if(!m_db.open()) return;
      //记录查询
      RecordQuery(limitIndex);
      m_db.close();
      //设置当前页
      m_icurrentpage = pageIndex;
      //刷新状态
      UpdateStatus();
}

#include <QSqlField>
#include "qdatabasequery.h"

void HNCreateSysEvent(QString content, QString status)
{

    QDatabasequery query;
    query.SetTableName("./db/SysEvent");
    query.opendatabase();

    QStringList lname, lvalue;
    lname << "Event" << "Status" << "Time" << "User" << "Content";
    lvalue << content << status << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
              << gUserName << "";
    QString table = "Event";
    query.insert(table, lname, lvalue);

    query.cloesdatabase();

}
