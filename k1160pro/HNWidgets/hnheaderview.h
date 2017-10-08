#ifndef HNHEADERVIEW_H
#define HNHEADERVIEW_H

#include <QHeaderView>

class HNHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    explicit HNHeaderView(Qt::Orientation orientation = Qt::Horizontal, QWidget *parent = 0);

signals:

public slots:


    // QHeaderView interface
protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
    QSize sectionSizeFromContents(int logicalIndex) const;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);

private:
    Qt::Orientation ori;
};

#endif // HNHEADERVIEW_H
