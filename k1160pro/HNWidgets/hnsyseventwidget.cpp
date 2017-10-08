#include "hnsyseventwidget.h"
#include "ui_hnsyseventwidget.h"
#include "HNDefine.h"

HNSysEventWidget::HNSysEventWidget(QWidget *parent) :
    HNSysEventView(parent),
    ui(new Ui::QSysEventWidget)
{
    ui->setupUi(this);
    m_db = newDatabaseConn();
    m_model = HNSingleEvent(this, m_db);
    setModel(m_model);
    setDatabaseName(m_db, DB_EVENT);
    m_model->setTable(TABLE_EVENT);
    m_model->setRelation(Event_Name, QSqlRelation(TABLE_EVTYPE, "id", "Type"));
    m_model->select();
    //setColumnHidden(Event_User, true);
    setColumnHidden(Event_Content, true);
    resizeColumnToContents(Event_ID);
    setColumnWidth(Event_Name, 400);
    resizeColumnToContents(Event_Time);
}

HNSysEventWidget::~HNSysEventWidget()
{
    delete ui;
}
