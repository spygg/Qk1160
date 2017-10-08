#ifndef HNCREATEUSERDIALOG_H
#define HNCREATEUSERDIALOG_H

#include "hndialog.h"

namespace Ui {
class HNCreateUserDialog;
}

class HNCreateUserDialog : public HNDialog
{
    Q_OBJECT

public:
    explicit HNCreateUserDialog(QWidget *parent = 0);
    ~HNCreateUserDialog();

    void initAll();
    void userInfo(QString& name, QString& password, QString& confirm, QString& authority, QString& comment);
private:
    Ui::HNCreateUserDialog *ui;
};

#endif // HNCREATEUSERDIALOG_H
