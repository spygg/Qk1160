#include "hncloudtreeview.h"
#include "ui_hncloudtreeview.h"

HNCloudTreeView::HNCloudTreeView(QWidget *parent) :
    HNTreeView(parent),
    ui(new Ui::HNCloudTreeView)
{
    ui->setupUi(this);
    setHeaderHidden(true);
    setEditTriggers(NoEditTriggers);
}

HNCloudTreeView::~HNCloudTreeView()
{
    delete ui;
}
