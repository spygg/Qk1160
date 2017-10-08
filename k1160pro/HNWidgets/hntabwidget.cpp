#include "hntabwidget.h"
#include "ui_hntabwidget.h"
#include "hntabbar.h"
#include <QDebug>
#include <QPainter>
#include <QStylePainter>
#include <QStyleOptionTabWidgetFrameV2>
#include "HNDefine.h"

HNTabWidget::HNTabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::HNTabWidget)
{
    m_bar = new HNTabBar(this);
    setTabBar(m_bar);

    ui->setupUi(this);
}

HNTabWidget::~HNTabWidget()
{
    delete ui;
}

HNTabBar *HNTabWidget::cTabBar()
{
    return m_bar;
}

void HNTabWidget::setObjectName(const QString &name)
{
    m_bar->setObjectName(QString("%1_bar").arg(name));
    QTabWidget::setObjectName(name);
}
