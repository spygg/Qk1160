#ifndef HNLISTVIEW_H
#define HNLISTVIEW_H

#include <QListView>

namespace Ui {
class HNListView;
}

class HNListView : public QListView
{
    Q_OBJECT

public:
    explicit HNListView(QWidget *parent = 0);
    ~HNListView();

private:
    Ui::HNListView *ui;
};

#endif // HNLISTVIEW_H
