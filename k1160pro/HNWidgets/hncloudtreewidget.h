#ifndef QCLOUDTREEWIDGET_H
#define QCLOUDTREEWIDGET_H

#include "hncloudtreeview.h"
#include "hncloudmodel.h"
#include "hnmsgbox.h"
#include "hnprogressdialog.h"

namespace Ui {
class HNCloudTreeWidget;
}

class HNCloudTreeWidget : public HNCloudTreeView
{
    Q_OBJECT

public:
    explicit HNCloudTreeWidget(QWidget *parent = 0);
    ~HNCloudTreeWidget();

public slots:
    void slotConnect();
    void slotDisConnect();

private slots:
    void slotConnected();
    void currentRowChanged();
    void downFile();
    void delFile();
    void slotDownSuccess();

private:
    Ui::HNCloudTreeWidget *ui;
    HNClient* m_client;
    HNCloudModel* model;
    QString m_tmpfile, m_localfile;
    HNMsgBox* m_box;
    HNProgressDialog* m_progDown;
};

#endif // QCLOUDTREEWIDGET_H
