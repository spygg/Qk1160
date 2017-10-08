#ifndef HNMANAGEETHENETWIDGET_H
#define HNMANAGEETHENETWIDGET_H

#include <QWidget>

namespace Ui {
class HNManageEthenetWidget;
}

class HNManageEthenetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HNManageEthenetWidget(QWidget *parent = 0);
    ~HNManageEthenetWidget();

    void initAll();

private slots:
    void netChanged();
    void wifiConnected();
    void wifiDisConnected();

    void on_btn_saveip_clicked();

    void on_chk_dhcp_stateChanged(int arg1);

private:
    Ui::HNManageEthenetWidget *ui;
};

#endif // HNMANAGEETHENETWIDGET_H
