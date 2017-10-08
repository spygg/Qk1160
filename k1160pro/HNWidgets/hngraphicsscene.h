#ifndef HNGRAPHICSSCENE_H
#define HNGRAPHICSSCENE_H

#include <QGraphicsScene>
#include "hngraphicsitem.h"

class HNGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    HNGraphicsScene(QObject *parent = 0);
    HNGraphicsScene(const QRectF &sceneRect, QObject *parent = 0);
    HNGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = 0);
    virtual ~HNGraphicsScene() {}

    void render(QPainter *painter,
                const QRectF &target = QRectF(), const QRectF &source = QRectF(),
                Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio);
    HNGraphicsEllipseItem *addEllipse(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush());
    inline QGraphicsEllipseItem *addEllipse(qreal x, qreal y, qreal w, qreal h, const QPen &pen = QPen(), const QBrush &brush = QBrush())
    { return addEllipse(QRectF(x, y, w, h), pen, brush); }

    HNGraphicsPathItem *addPath(const QPainterPath &path, const QPen &pen = QPen(), const QBrush &brush = QBrush());
    HNGraphicsPixmapItem *addPixmap(const QPixmap &pixmap);
    HNGraphicsPolygonItem *addPolygon(const QPolygonF &polygon, const QPen &pen = QPen(), const QBrush &brush = QBrush());
    HNGraphicsTextItem *addText(const QString &text, const QFont &font = QFont());
    HNGraphicsSimpleTextItem *addSimpleText(const QString &text, const QFont &font = QFont());
    HNGraphicsProxyWidget *addWidget(QWidget *widget, Qt::WindowFlags wFlags = 0);
    HNGraphicsLineItem *addLine(const QLineF &line, const QPen &pen = QPen());
    inline HNGraphicsLineItem *addLine(qreal x1, qreal y1, qreal x2, qreal y2, const QPen &pen = QPen())
    { return addLine(QLineF(x1, y1, x2, y2), pen); }
    HNGraphicsRectItem *addRect(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush());
    inline HNGraphicsRectItem *addRect(qreal x, qreal y, qreal w, qreal h, const QPen &pen = QPen(), const QBrush &brush = QBrush())
    { return addRect(QRectF(x, y, w, h), pen, brush); }

signals:

public slots:


    // QGraphicsScene interface
protected:
    void drawItems(QPainter *painter, int numItems, QGraphicsItem *items[], const QStyleOptionGraphicsItem options[], QWidget *widget = 0);

private:
};

#endif // HNGRAPHICSSCENE_H
