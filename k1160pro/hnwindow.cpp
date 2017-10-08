#include "hnwindow.h"
#include "ui_hnwindow.h"

HNWindow::HNWindow(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::HNWindow)
{
    ui->setupUi(this);
}

HNWindow::~HNWindow()
{
    delete ui;
}
