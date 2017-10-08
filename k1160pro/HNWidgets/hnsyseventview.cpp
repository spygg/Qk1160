#include "hnsyseventview.h"
#include "ui_hnsyseventview.h"
#include "HNDefine.h"

HNSysEventView::HNSysEventView(QWidget *parent) :
    HNTableView(parent),
    ui(new Ui::HNSysEventView)
{
    ui->setupUi(this);
    setSelectionMode(QAbstractItemView::NoSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    horizontalHeader()->setHidden(true);
    verticalHeader()->setHidden(true);
    //horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    horizontalHeader()->setMinimumSectionSize(0);
#ifdef __MIPS_LINUX__
    setFocusPolicy(Qt::NoFocus);
#endif
    setShowGrid(false);
    m_dg = new QSysEventIdDelegate(this);
    setItemDelegateForColumn(Event_ID, m_dg);
}

HNSysEventView::~HNSysEventView()
{
    delete ui;
}


void QSysEventIdDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
    painter->drawText(rect, Qt::AlignRight|Qt::AlignVCenter, QString("%1、").arg(text));
}

void QSysEventIdDelegate::drawDecoration(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QPixmap &pixmap) const
{

}

void QSysEventIdDelegate::drawFocus(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect) const
{

}

void QSysEventIdDelegate::drawCheck(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, Qt::CheckState state) const
{

}
