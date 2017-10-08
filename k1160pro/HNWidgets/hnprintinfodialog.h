#ifndef HNPRINTINFODIALOG_H
#define HNPRINTINFODIALOG_H

#include <QDialog>

namespace Ui {
class HNPrintInfoDialog;
}

class HNPrintInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HNPrintInfoDialog(QWidget *parent = 0);
    ~HNPrintInfoDialog();

    void initAll();
    void printInfo(QString& title, QString& header, QString& footer);

private slots:

private:
    Ui::HNPrintInfoDialog *ui;
};

#endif // HNPRINTINFODIALOG_H
