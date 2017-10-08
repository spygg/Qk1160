#ifndef QPROGRESSWINDOW_H
#define QPROGRESSWINDOW_H

#include "hndialog.h"
#include "hnprogressbar.h"

namespace Ui {
class HNProgressDialog;
}

class HNProgressDialog : public HNDialog
{
    Q_OBJECT

public:
    explicit HNProgressDialog(QWidget *parent = 0);
    ~HNProgressDialog();

    void initAll();
    void setRange(int min, int max);
    void setContent(QString content);

public slots:
    void setValue(int value);

private:
    Ui::HNProgressDialog *ui;
    HNProgressBar* bar;
};

#endif // QPROGRESSWINDOW_H
