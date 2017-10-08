#ifndef HNTREEVIEW_H
#define HNTREEVIEW_H

#include <QTreeView>

namespace Ui {
class HNTreeView;
}

class HNTreeView : public QTreeView
{
    Q_OBJECT

public:
    explicit HNTreeView(QWidget *parent = 0);
    ~HNTreeView();

private:
    Ui::HNTreeView *ui;

    // HNTreeView interface
protected:
    void drawRow(QPainter *painter, const QStyleOptionViewItem &options, const QModelIndex &index) const;
    void drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const;
};

#endif // HNTREEVIEW_H
