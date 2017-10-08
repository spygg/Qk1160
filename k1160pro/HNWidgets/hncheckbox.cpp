#include "hncheckbox.h"
#include "ui_hncheckbox.h"
#include <QStylePainter>
#include "HNDefine.h"

HNCheckBox::HNCheckBox(QWidget *parent) :
    QCheckBox(parent),
    ui(new Ui::HNCheckBox)
{
    ui->setupUi(this);
}

HNCheckBox::~HNCheckBox()
{
    delete ui;
}

void HNCheckBox::pixMap(QImage &icon, QImage &iconSel)
{
    icon = QImage(this->m_icon[BTN_NORMAL]);
    iconSel = QImage(this->m_icon[BTN_PRESS]);
}

void HNCheckBox::setPixmap(const QString &icon, const QString &iconSel)
{
    this->m_icon[BTN_NORMAL] = icon;
    this->m_icon[BTN_PRESS] = iconSel;
}


void HNCheckBox::paintEvent(QPaintEvent *)
{
    QStylePainter p(this);

    QString icon = isChecked() ? m_icon[BTN_PRESS] : m_icon[BTN_NORMAL];

    if(icon.isEmpty())
        return;

    p.drawItemPixmap(rect(), Qt::AlignCenter, QIcon(icon).pixmap(rect().size(), QIcon::Normal, QIcon::On));
    QStyleOptionButton opt;
    initStyleOption(&opt);
    p.drawItemText(rect(), Qt::AlignCenter, opt.palette, true, text());
}

bool HNCheckBox::hitButton(const QPoint &pos) const
{
    return true;
}
