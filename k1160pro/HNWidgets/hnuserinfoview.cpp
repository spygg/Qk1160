#include "hnuserinfoview.h"
#include "ui_hnuserinfoview.h"
#include "HNDefine.h"
#include "hngui-qt.h"


HNUserInfoView::HNUserInfoView(QWidget *parent) :
    HNTableView(parent),
    ui(new Ui::HNUserInfoView)
{
    ui->setupUi(this);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    horizontalHeader()->setHidden(false);
    verticalHeader()->setHidden(true);
    resizeColumnsToContents();
#ifdef __MIPS_LINUX__
    setFocusPolicy(Qt::NoFocus);
#endif

    horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    setShowGrid(true);

    m_dg = new HNUserInfoViewTextDelegate(this);
    setItemDelegateForColumn(Auth_Id, m_dg);
}

HNUserInfoView::~HNUserInfoView()
{
    delete ui;
}


void HNUserInfoViewTextDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
    QSettings set;
    QString id = set.value("DefaultLogin").toString();

    if(id == text)
        painter->drawImage(rect, QImage("://theme/basic/bk_sel.png"));
}
