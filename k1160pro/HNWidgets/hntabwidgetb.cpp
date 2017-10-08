#include "hntabwidgetb.h"
#include "ui_hntabwidgetb.h"

HNTabWidgetB::HNTabWidgetB(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::HNTabWidgetB)
{
    ui->setupUi(this);
}

HNTabWidgetB::~HNTabWidgetB()
{
    delete ui;
}
