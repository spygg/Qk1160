#include "hnmanageuserwidget.h"
#include "ui_hnmanageuserwidget.h"

HNManageUserWidget::HNManageUserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNManageUserWidget)
{
    ui->setupUi(this);
    ui->tbvUserInfo->addMap(ui->lbName, Auth_Name, "text");
    ui->tbvUserInfo->addMap(ui->lbPwd, Auth_Passwd, "text");
    ui->tbvUserInfo->addMap(ui->lbAuth, Auth_Authrity, "text");
    ui->tbvUserInfo->addMap(ui->lbCreater, Auth_Creater, "text");
    ui->tbvUserInfo->addMap(ui->lbCreateTime, Auth_CreateTime, "text");
    ui->tbvUserInfo->addMap(ui->lbComment, Auth_Comment, "text");
    connect(ui->tbvUserInfo->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),
            ui->tbvUserInfo, SLOT(updateMap()));
    ui->tbvUserInfo->refresh();


}

HNManageUserWidget::~HNManageUserWidget()
{
    delete ui;
}

void HNManageUserWidget::on_btnNewUser_clicked()
{

}

void HNManageUserWidget::on_btnDelUser_clicked()
{

}
