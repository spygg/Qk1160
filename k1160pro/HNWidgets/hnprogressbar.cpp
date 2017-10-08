#include "hnprogressbar.h"
#include "ui_hnprogressbar.h"
#include "QStylePainter"
#include "HNDefine.h"
#include "QHBoxLayout"
#include "QSpacerItem"

HNProgressBar::HNProgressBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNProgressBar)
{
    ui->setupUi(this);
    m_value = m_min = 0;
    m_max = 100;
    m_back = "://pictures/bk_progress_background.png";
    m_trunk = "://pictures/bk_progress_chunk.png";
    ui->widthTrunk->setPixmap(m_trunk);
    ui->widgetBack->setPixmap(m_back);
    ui->widthTrunk->setType(HNWidget::HNTILEDWIDTH);
    ui->widgetBack->setType(HNWidget::HNZOOMWIDTH);
}

HNProgressBar::~HNProgressBar()
{
    delete ui;
}

void HNProgressBar::setPixMap(QString back, QString trunk)
{
    m_back = back;
    m_trunk = trunk;
    ui->widthTrunk->setPixmap(m_trunk);
    ui->widgetBack->setPixmap(m_back);
}

void HNProgressBar::setValue(int value)
{
    m_value = value;
    int w = ui->widgetBack->width() * m_value / (m_max-m_min);
    int h = ui->widgetBack->height();
    ui->widthTrunk->setFixedSize(w, h);
    pline() << width() << ui->widgetBack->width() << w << h;
}

void HNProgressBar::setRange(int min, int max)
{
    m_min = min;
    m_max = max;
}

