#include "hnwifiview.h"
#include "ui_hnwifiview.h"

#include "HNDefine.h"

HNWIFIView::HNWIFIView(QWidget *parent) :
    HNTableView(parent),
    ui(new Ui::HNWIFIView)
{
    ui->setupUi(this);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    horizontalHeader()->setHidden(true);
    verticalHeader()->setHidden(true);
    resizeColumnsToContents();
    horizontalHeader()->setStretchLastSection(true);
    setShowGrid(true);

#ifdef __MIPS_LINUX__
    setFocusPolicy(Qt::NoFocus);
#endif
    dg = new HNWIFIViewTextDelegate(this);
    setItemDelegateForColumn(ESSID_STATUS, dg);

    QFile styleFile("://HNWidgets.qss");
    styleFile.open(QIODevice::ReadOnly);
    QString styleString(styleFile.readAll());;
    verticalHeader()->setStyleSheet(styleString);
    styleFile.close();
}

HNWIFIView::~HNWIFIView()
{
    delete ui;
}

void HNWIFIViewTextDelegate::drawCheck(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, Qt::CheckState state) const
{
#if 0
    if (!rect.isValid())
        return;
    QStyleOptionViewItem opt(option);
    opt.rect = rect;
    opt.state = opt.state & ~QStyle::State_HasFocus;
    switch (state) {
    case Qt::Unchecked:
        opt.state |= QStyle::State_Off;
        break;
    case Qt::PartiallyChecked:
        opt.state |= QStyle::State_NoChange;
        break;
    case Qt::Checked:
            opt.state |= QStyle::State_On;
        break;
    }
    QApplication::style()->drawPrimitive(QStyle::PE_IndicatorViewItemCheck, &opt, painter);
#else
    QItemDelegate::drawCheck(painter, option, rect, state);
#endif
}

void HNWIFIViewTextDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
    if("COMPLETED" == text)
        painter->drawImage(rect, QImage("://pictures/bk_sel.png"));
}
