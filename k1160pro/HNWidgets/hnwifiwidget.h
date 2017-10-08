#ifndef HNWIFIWIDGET_H
#define HNWIFIWIDGET_H

#include "hnwifiview.h"
#include "hnwifimodel.h"
#include "hngui-qt.h"
#include "hnpassworddialog.h"

namespace Ui {
class HNWIFIWidget;
}

class HNWIFIWidget : public HNWIFIView
{
    Q_OBJECT

public:
    explicit HNWIFIWidget(QWidget *parent = 0);
    ~HNWIFIWidget();

private slots:
    void clickWIFI();

private:
    Ui::HNWIFIWidget *ui;
    HNWIFIModel* m_model;
    HNPasswordDialog* m_pass;
};

#endif // HNWIFIWIDGET_H
