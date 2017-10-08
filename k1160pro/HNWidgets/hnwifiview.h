#ifndef HNWIFIVIEW_H
#define HNWIFIVIEW_H

#include "hntableview.h"
#include <QItemDelegate>
#include <QStylePainter>

class HNWIFIViewTextDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    HNWIFIViewTextDelegate(QObject *parent = 0): QItemDelegate(parent), parent(parent) { }

private:
    QObject* parent;

    // QItemDelegate interface
protected:
    void drawCheck(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, Qt::CheckState state) const;

    // QItemDelegate interface
protected:
    void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;
};

namespace Ui {
class HNWIFIView;
}

class HNWIFIView : public HNTableView
{
    Q_OBJECT

public:
    explicit HNWIFIView(QWidget *parent = 0);
    ~HNWIFIView();

private:
    Ui::HNWIFIView *ui;
    HNWIFIViewTextDelegate* dg;
};

#endif // HNWIFIVIEW_H
