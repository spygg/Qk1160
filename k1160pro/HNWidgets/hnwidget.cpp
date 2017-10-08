#include "hnwidget.h"
#include "ui_hnwidget.h"
#include <QStylePainter>
#include "HNDefine.h"

HNWidget::HNWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNWidget)
{
    ui->setupUi(this);
    m_type = HNCENTER;
}

HNWidget::~HNWidget()
{
    delete ui;
}

void HNWidget::setPixmap(QString pic)
{
    m_pic = pic;
}

void HNWidget::paintEvent(QPaintEvent *)
{
    QStylePainter p(this);
    if(m_pic.isEmpty())
        return;

    QImage image(m_pic);
    switch (m_type) {
    case HNCENTER:
        p.drawItemPixmap(rect(), Qt::AlignCenter, QIcon(m_pic).pixmap(rect().size(), QIcon::Normal, QIcon::On));
        break;
    case HNTILEDWIDTH:
        //会产生label的效果，左右按照rect长，但是不缩放形状
        p.drawItemPixmap(rect(), Qt::AlignLeft | Qt::AlignTop,
                         QPixmap::fromImage(image.copy(rect())
                                            .scaledToWidth(rect().width())
                                            ));
        break;
    case HNZOOMWIDTH:
        p.drawItemPixmap(rect(), Qt::AlignLeft | Qt::AlignTop,
                         QPixmap::fromImage(image
                                            .scaled(rect().width(), image.height(), Qt::IgnoreAspectRatio)
                                            ));
        break;
    default:
        break;
    }
}
