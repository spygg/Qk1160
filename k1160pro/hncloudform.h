#ifndef HNCLOUDFORM_H
#define HNCLOUDFORM_H

#include <QWidget>
#include "hngui.h"
#include "hnlocaldbdialog.h"

class HNCloudForm : public QWidget
{
    Q_OBJECT
public:
    explicit HNCloudForm(QWidget *parent = 0);


    bool open() {
        return treeWidget->open();
    }


    void closehncfs() {
        treeWidget->closehncfs();
    }

    void queryRoot();

signals:
    void downSucc();

public slots:

private slots:
    void DeleteCloudItem();
    void UpDB();
    void DownDB();
    void status(int);
    void cancel();

private:
    void InitOCX();
    HNPushButton* btnBack;
    HNPushButton* btnSync;
    HNPushButton* btnRefresh;
    HNPushButton* btnDelete;
    QLabel* labelTitle;
    HNTreeWidget* treeWidget;
    HNLocalDBDialog* localDlg;
    HNProgressDialog* m_pdlg;
    HNFileSystem* m_fs;
    QString m_srcPath;
    QString m_cloudfile;
    QString m_localfile;

};

#endif // HNCLOUDFORM_H
