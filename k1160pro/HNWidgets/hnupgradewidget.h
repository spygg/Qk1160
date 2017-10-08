#ifndef HNUPGRADEWIDGET_H
#define HNUPGRADEWIDGET_H

#include <QWidget>
#include "hnclient.h"

class QBackupLocalThread : public QThread
{
public:
    explicit QBackupLocalThread(QObject *parent = 0) : QThread(parent){}

    // QThread interface
protected:
    void run();
};

class QUpgradeThread : public QThread
{
public:
    explicit QUpgradeThread(QObject *parent = 0) : QThread(parent){}
    // QThread interface
protected:
    void run();
};

namespace Ui {
class HNUpgradeWidget;
}

class HNUpgradeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HNUpgradeWidget(QWidget *parent = 0);
    ~HNUpgradeWidget();

    void initAll();

signals:
    void sigCancelUpgrade();

private slots:
    void setText(QString text);
    void setValue(int value);
    void download();
    void logined();
    void versionR();
    void downOK();
    void restart();

    void on_btnDown_clicked();

    void on_btnCancel_clicked();

    void on_btnCheck_clicked();

private:
    Ui::HNUpgradeWidget *ui;
    HNClient* m_cli;
    QTimer* timer;
    QBackupLocalThread* m_backupT;
    QUpgradeThread* m_upgradeT;
    QString m_newSoftwareID;
};

#endif // HNUPGRADEWIDGET_H
