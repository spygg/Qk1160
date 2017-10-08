#ifndef QEXCEPTIONVIEW_H
#define QEXCEPTIONVIEW_H

#include "hntableview.h"

namespace Ui {
class HNExceptionView;
}

class HNExceptionView : public HNTableView
{
    Q_OBJECT

public:
    explicit HNExceptionView(QWidget *parent = 0);
    ~HNExceptionView();

private:
    Ui::HNExceptionView *ui;
};

#endif // QEXCEPTIONVIEW_H
