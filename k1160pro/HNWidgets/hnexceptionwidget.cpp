#include "hnexceptionwidget.h"
#include "ui_hnexceptionwidget.h"
#include "HNDefine.h"
#include "hngui-qt.h"

HNExceptionWidget::HNExceptionWidget(QWidget *parent) :
    HNExceptionView(parent),
    ui(new Ui::QExceptionWidget)
{
    ui->setupUi(this);
    m_db = newDatabaseConn();
    m_model = new HNExceptionModel(this, m_db);
    setModel(m_model);
    setItemDelegate(new QSqlRelationalDelegate(this));

    setDatabaseName(m_db, DB_EVENT);
    m_model->setTable(TABLE_EVENT);
    m_model->setRelation(Event_Name, QSqlRelation(TABLE_EVTYPE, "id", "Type"));
}

HNExceptionWidget::~HNExceptionWidget()
{
    delete ui;
}
