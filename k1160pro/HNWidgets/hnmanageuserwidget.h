#ifndef HNMANAGEUSERWIDGET_H
#define HNMANAGEUSERWIDGET_H

#include <QWidget>

namespace Ui {
class HNManageUserWidget;
}

class HNManageUserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HNManageUserWidget(QWidget *parent = 0);
    ~HNManageUserWidget();

private slots:
    void on_btnNewUser_clicked();

    void on_btnDelUser_clicked();

private:
    Ui::HNManageUserWidget *ui;
};

#endif // HNMANAGEUSERWIDGET_H
