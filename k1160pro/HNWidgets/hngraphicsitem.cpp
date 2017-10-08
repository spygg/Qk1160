#include "hngraphicsitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "HNDefine.h"

HNGraphicsItem::HNGraphicsItem(HNGraphicsItem *parent) : QGraphicsItem(parent) {}


HNGraphicsTextItem::HNGraphicsTextItem(HNGraphicsItem *parent) : QGraphicsTextItem(parent) {}


HNGraphicsRectItem::HNGraphicsRectItem(HNGraphicsItem *parent) : QGraphicsRectItem(parent) {}


HNGraphicsSimpleTextItem::HNGraphicsSimpleTextItem(HNGraphicsItem *parent) : QGraphicsSimpleTextItem(parent) {}


HNGraphicsLineItem::HNGraphicsLineItem(HNGraphicsItem *parent) : QGraphicsLineItem(parent) {}


HNGraphicsPixmapItem::HNGraphicsPixmapItem(HNGraphicsItem *parent) : QGraphicsPixmapItem(parent) {}


HNGraphicsPathItem::HNGraphicsPathItem(HNGraphicsItem *parent) : QGraphicsPathItem(parent) {}


HNGraphicsEllipseItem::HNGraphicsEllipseItem(HNGraphicsItem *parent) : QGraphicsEllipseItem(parent) {}


HNGraphicsPolygonItem::HNGraphicsPolygonItem(HNGraphicsItem *parent) : QGraphicsPolygonItem(parent) {}


HNGraphicsItemGroup::HNGraphicsItemGroup(HNGraphicsItem *parent) : QGraphicsItemGroup(parent) {}


HNGraphicsProxyWidget::HNGraphicsProxyWidget(HNGraphicsItem *parent) : QGraphicsProxyWidget(parent) {}


void HNGraphicsTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QFont oldFont(painter->font());

    painter->setFont(font());
    //painter->fillRect(option->rect, Qt::SolidPattern);
    painter->drawText(option->rect, Qt::AlignCenter, toPlainText());

    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus))
        ;

    if(0 && toPlainText().contains("K1160"))
    {
        pline() << font().pointSize() << font().pixelSize();
        pline() << pos() << option->rect << option->exposedRect << toPlainText();
        pline() << option->matrix << option->matrix.mapRect(option->rect);
    }
    painter->setFont(oldFont);
}


void HNGraphicsLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen oldPen(painter->pen());

    qreal xratio = option->rect.width() / option->exposedRect.width();
    qreal yratio = option->rect.height() / option->exposedRect.height();

    QPen pn = pen();
    pn.setWidth(pn.width()*xratio);
    painter->setPen(pn);

    QLineF l = QLineF(option->rect.left(), option->rect.top(),
                          option->rect.right(), option->rect.bottom());

    painter->drawLine(l);

    if(0)
    {
        pline() << line() << l << option->rect << option->exposedRect;
        pline() << option->matrix << option->matrix.mapRect(option->rect);
    }

    painter->setPen(oldPen);
}


void HNGraphicsRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen oldPen(painter->pen());
    QBrush oldBrush(painter->brush());

    qreal xratio = option->rect.width() / option->exposedRect.width();
    qreal yratio = option->rect.height() / option->exposedRect.height();

    QPen pn = pen();
    pn.setWidth(pn.width()*xratio);
    painter->setPen(pn);

    QRectF r = QRectF(option->rect.left(), option->rect.top(),
                          option->rect.width(), option->rect.height());

    painter->setBrush(brush());
    painter->drawRect(r);

    if(0)
    {
        pline() << option->matrix << option->matrix.mapRect(option->rect) << r;
    }

    painter->setPen(oldPen);
    painter->setBrush(oldBrush);
}
