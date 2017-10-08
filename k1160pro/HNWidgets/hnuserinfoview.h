#ifndef HNUSERINFOVIEW_H
#define HNUSERINFOVIEW_H

#include "hntableview.h"
#include <QItemDelegate>

class HNUserInfoViewTextDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    HNUserInfoViewTextDelegate(QObject *parent = 0): QItemDelegate(parent) { }

    // QItemDelegate interface
protected:
    void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;
};

namespace Ui {
class HNUserInfoView;
}

class HNUserInfoView : public HNTableView
{
    Q_OBJECT

public:
    explicit HNUserInfoView(QWidget *parent = 0);
    ~HNUserInfoView();

private:
    Ui::HNUserInfoView *ui;
    HNUserInfoViewTextDelegate* m_dg;
};

#endif // HNUSERINFOVIEW_H
