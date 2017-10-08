
#include "hncloudwidget.h"
#include "ui_hncloudwidget.h"
#include "HNDefine.h"
#include "hnprogressdialog.h"
#include "hnmsgbox.h"

HNCloudWidget::HNCloudWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNCloudWidget)
{
    ui->setupUi(this);

    connect(ui->pushButton_upload, SIGNAL(clicked()), ui->treeLocal, SLOT(uploadFile()));
    connect(ui->pushButton_del, SIGNAL(clicked()), ui->treeCloud, SLOT(delFile()));
    connect(ui->pushButton_down, SIGNAL(clicked()), ui->treeCloud, SLOT(downFile()));
    connect(ui->btn_print, SIGNAL(clicked()), ui->treeLocal, SLOT(printFile()));
}

HNCloudWidget::~HNCloudWidget()
{
    delete ui;
}

void HNCloudWidget::chageLanguage()
{
    ui->retranslateUi(this);
}

void HNCloudWidget::slotConnect()
{
    ui->treeCloud->slotConnect();
}

void HNCloudWidget::slotDisConnect()
{
    ui->treeCloud->slotDisConnect();
}
