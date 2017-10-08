#ifndef QSYSEVENTVIEW_H
#define QSYSEVENTVIEW_H

#include "hntableview.h"
#include "hngui-qt.h"

class QSysEventIdDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    QSysEventIdDelegate(QObject *parent = 0): QItemDelegate(parent) { }

    // QItemDelegate interface
protected:
    void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;

private:
    // QItemDelegate interface
protected:
    void drawDecoration(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QPixmap &pixmap) const;
    void drawFocus(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect) const;
    void drawCheck(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, Qt::CheckState state) const;
};

namespace Ui {
class HNSysEventView;
}

class HNSysEventView : public HNTableView
{
    Q_OBJECT

public:
    explicit HNSysEventView(QWidget *parent = 0);
    ~HNSysEventView();

private:
    Ui::HNSysEventView *ui;
    QSysEventIdDelegate* m_dg;
};

#endif // QSYSEVENTVIEW_H
