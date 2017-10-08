#include "hnradiobutton.h"
#include "ui_hnradiobutton.h"
#include <QStylePainter>

HNRadioButton::HNRadioButton(QWidget *parent) :
    QRadioButton(parent),
    ui(new Ui::HNRadioButton)
{
    ui->setupUi(this);
}

HNRadioButton::~HNRadioButton()
{
    delete ui;
}

void HNRadioButton::pixMap(QImage &icon, QImage &iconSel)
{
    icon = QImage(this->m_icon[BTN_NORMAL]);
    iconSel = QImage(this->m_icon[BTN_PRESS]);
}

void HNRadioButton::setPixmap(const QString &icon, const QString &iconSel)
{
    this->m_icon[BTN_NORMAL] = icon;
    this->m_icon[BTN_PRESS] = iconSel;
}

void HNRadioButton::paintEvent(QPaintEvent *)
{
    QStylePainter p(this);
    QString icon = isChecked() ? m_icon[BTN_PRESS] : m_icon[BTN_NORMAL];

    if(icon.isEmpty())
        return;

    p.drawItemPixmap(rect(), Qt::AlignCenter, QIcon(icon).pixmap(rect().size(), QIcon::Normal, QIcon::On));
    //以下方法会导致图片失真
    //QImage image(icon);
    //p.drawItemPixmap(rect(), Qt::AlignCenter, QPixmap::fromImage(image.scaled(rect().size(), Qt::IgnoreAspectRatio)));

    QStyleOptionButton opt;
    initStyleOption(&opt);
    p.drawItemText(rect(), Qt::AlignCenter, opt.palette, true, text());
}


bool HNRadioButton::hitButton(const QPoint &pos) const
{
    return true;
}
