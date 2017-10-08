#ifndef HNPASSWORDDIALOG_H
#define HNPASSWORDDIALOG_H

#include "hndialog.h"

namespace Ui {
class HNPasswordDialog;
}

class HNPasswordDialog : public HNDialog
{
    Q_OBJECT

public:
    explicit HNPasswordDialog(QWidget *parent = 0);
    ~HNPasswordDialog();

    void setWifiName(QString name);
    QString wifiPwd();

signals:
    void connectClicked(QString password);
private slots:
    void connectClicked();
    void btnEnabled(QString);

private:
    Ui::HNPasswordDialog *ui;
};

#endif // HNPASSWORDDIALOG_H
