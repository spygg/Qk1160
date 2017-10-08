#ifndef HNGRAPHICSITEM_H
#define HNGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QGraphicsProxyWidget>

class HNGraphicsItem : public QGraphicsItem
{
public:
    explicit HNGraphicsItem(HNGraphicsItem *parent = 0);

};

class HNGraphicsTextItem : public QGraphicsTextItem
{
public:
    explicit HNGraphicsTextItem(HNGraphicsItem *parent = 0);


    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


class HNGraphicsSimpleTextItem : public QGraphicsSimpleTextItem
{
public:
    explicit HNGraphicsSimpleTextItem(HNGraphicsItem *parent = 0);

};


class HNGraphicsPixmapItem : public QGraphicsPixmapItem
{
public:
    explicit HNGraphicsPixmapItem(HNGraphicsItem *parent = 0);

};

class HNGraphicsRectItem : public QGraphicsRectItem
{
public:
    explicit HNGraphicsRectItem(HNGraphicsItem *parent = 0);


    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


class HNGraphicsLineItem : public QGraphicsLineItem
{
public:
    explicit HNGraphicsLineItem(HNGraphicsItem *parent = 0);


    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};




class HNGraphicsPathItem : public QGraphicsPathItem
{
public:
    explicit HNGraphicsPathItem(HNGraphicsItem *parent = 0);

};


class HNGraphicsEllipseItem : public QGraphicsEllipseItem
{
public:
    explicit HNGraphicsEllipseItem(HNGraphicsItem *parent = 0);

};


class HNGraphicsPolygonItem : public QGraphicsPolygonItem
{
public:
    explicit HNGraphicsPolygonItem(HNGraphicsItem *parent = 0);

};

class HNGraphicsItemGroup : public QGraphicsItemGroup
{
public:
    explicit HNGraphicsItemGroup(HNGraphicsItem *parent = 0);

};

class HNGraphicsProxyWidget : public QGraphicsProxyWidget
{
public:
    explicit HNGraphicsProxyWidget(HNGraphicsItem *parent = 0);

};


#endif // HNGRAPHICSITEM_H
