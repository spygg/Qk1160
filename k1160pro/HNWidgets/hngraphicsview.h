#ifndef HNGRAPHICSVIEW_H
#define HNGRAPHICSVIEW_H

#include <QGraphicsView>


class HNGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit HNGraphicsView(QWidget *parent = 0);

signals:

public slots:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);

    // QGraphicsView interface
protected:
    void drawItems(QPainter *painter, int numItems, QGraphicsItem *items[], const QStyleOptionGraphicsItem options[]);
};

#endif // HNGRAPHICSVIEW_H
