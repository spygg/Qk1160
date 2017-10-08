#ifndef HNDIALOG_H
#define HNDIALOG_H

#include <QDialog>

namespace Ui {
class HNDialog;
}

class HNDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HNDialog(QWidget *parent = 0);
    ~HNDialog();

private:
    Ui::HNDialog *ui;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
};

#endif // HNDIALOG_H
