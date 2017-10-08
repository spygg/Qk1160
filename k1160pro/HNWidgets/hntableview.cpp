#include "hntableview.h"
#include "ui_hntableview.h"
#include <QFile>
#include <QScrollBar>
#include <QSqlRelationalDelegate>

HNTableView::HNTableView(QWidget *parent) :
    QTableView(parent),
    ui(new Ui::HNTableView)
{
    ui->setupUi(this);

    m_header = new HNHeaderView(Qt::Horizontal, this);
    m_vheader = new HNHeaderView(Qt::Vertical, this);

    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    //如果没有这个中介，release版本无故会崩溃。
    setItemDelegate(new QSqlRelationalDelegate(this));
#ifdef __MIPS_LINUX__
    setFocusPolicy(Qt::NoFocus);
#endif

#if 0
    QFile styleFile("://HNWidgets.qss");
    styleFile.open(QIODevice::ReadOnly);
    QString styleString(styleFile.readAll());;
    horizontalScrollBar()->setStyleSheet(styleString);
    styleFile.close();
#endif

}

HNTableView::~HNTableView()
{
    delete ui;
}

void HNTableView::setHNHeader()
{
    setHorizontalHeader(m_header);
}

void HNTableView::setHNVHeader()
{
    setVerticalHeader(m_vheader);
}

void HNTableView::setObjectName(const QString &name)
{
    QTableView::setObjectName(name);
    horizontalHeader()->setObjectName(QString("%1_Header").arg(name));
    verticalHeader()->setObjectName(QString("%1_VHeader").arg(name));
    m_header->setObjectName(QString("%1_HNHeader").arg(name));
    m_vheader->setObjectName(QString("%1_HNVHeader").arg(name));
}
