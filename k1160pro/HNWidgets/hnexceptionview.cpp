#include "hnexceptionview.h"
#include "ui_hnexceptionview.h"

HNExceptionView::HNExceptionView(QWidget *parent) :
    HNTableView(parent),
    ui(new Ui::HNExceptionView)
{
    ui->setupUi(this);
}

HNExceptionView::~HNExceptionView()
{
    delete ui;
}
