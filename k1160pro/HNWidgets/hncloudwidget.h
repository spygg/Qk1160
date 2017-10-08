#ifndef QCLOUDFORM_H
#define QCLOUDFORM_H

#include <QWidget>
#include "hnclient.h"
#include "hnprogressdialog.h"

namespace Ui {
class HNCloudWidget;
}

class HNCloudWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HNCloudWidget(QWidget *parent = 0);
    ~HNCloudWidget();

    void chageLanguage();

signals:
public slots:
    void slotConnect();
    void slotDisConnect();

private:
    Ui::HNCloudWidget *ui;
};

#endif // QCLOUDFORM_H
