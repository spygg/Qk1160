#ifndef QREPORTVIEWDIALOG_H
#define QREPORTVIEWDIALOG_H

#include "hndialog.h"
#include "hngui-qt.h"
#include "hntablemodel.h"

namespace Ui {
class QReportViewDialog;
}

class HNPrintPreviewDialog : public HNDialog
{
    Q_OBJECT

public:
    explicit HNPrintPreviewDialog(QWidget *parent = 0);
    ~HNPrintPreviewDialog();

    //SerialNo;
    QString newReport(QString library, QString method);
    void endReport(QString serialNo, QString Exception,
                      QString stopReason, QByteArray& plot);
    void initAll(QString name);
    void printToPdf();
    void print();
    QSqlDatabase m_db;

    void setTitle(QString title);
    void addText(QString text);
    void addTable(QTableView* table);

public:
    static void htmltopdf(QString pdf, QString html);
    static void printpdf(QString pdf);

private:
    Ui::QReportViewDialog *ui;
};

#endif // QREPORTVIEWDIALOG_H
