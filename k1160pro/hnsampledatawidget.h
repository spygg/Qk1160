#ifndef HNSAMPLEDATAWIDGET_H
#define HNSAMPLEDATAWIDGET_H

#include <QWidget>
#include "hnreport.h"

namespace Ui {
class HNSampleDataWidget;
}

class HNSampleDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HNSampleDataWidget(QWidget *parent = 0);
    ~HNSampleDataWidget();

public slots:
    void initAll();
    void reopen();
    void refresh();

private slots:
    void on_btnPrint_clicked();

    void on_btnExport_clicked();

    void on_btnDelete_clicked();

private:
    void exportPdf();
    int  printInfoDlg();
    Ui::HNSampleDataWidget *ui;
    HNReport* r;
    QString title, header, footer;
    QString pdfname;

};

#endif // HNSAMPLEDATAWIDGET_H
