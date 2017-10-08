#include "hnlistview.h"
#include "ui_hnlistview.h"

HNListView::HNListView(QWidget *parent) :
    QListView(parent),
    ui(new Ui::HNListView)
{
    ui->setupUi(this);
}

HNListView::~HNListView()
{
    delete ui;
}
