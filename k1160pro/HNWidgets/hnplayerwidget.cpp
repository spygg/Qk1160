#include "hnplayerwidget.h"
#include "ui_hnplayerwidget.h"
#include "hnlinux.h"
#include "HNDefine.h"

HNPlayerWidget::HNPlayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMPlayerUI)
{
    ui->setupUi(this);

    m_bplayed = 0;
    app = new HNPlayerModel(this);
    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(posChanged()));
}

HNPlayerWidget::~HNPlayerWidget()
{
    delete ui;
}

void HNPlayerWidget::on_toolButton_mute_clicked()
{
    static bool m = false;
    m = ~m;
    app->mute(m);
}

void HNPlayerWidget::posChanged()
{
    int curPercent = app->percent();
    ui->horizontalSlider_seek->setValue(curPercent);
    pline() << curPercent;
    if(curPercent==1)
    {
        //double timeLength = app->timeLength();
    }
    static int i = 0;
    if( i < 1 ) i++, update();
    if(curPercent >= 99) app->stop();
}

void HNPlayerWidget::on_btn_play_clicked()
{
    if(0 == m_bplayed)
    {
        m_bplayed = 1;
        app->play(QString("%1/%2").arg(AV_PATH).arg("Tank.flv"), this->winId());
        QPoint point(ui->widget_show->rect().left(), ui->widget_show->rect().top());
        app->setRect(ui->widget_show->mapToGlobal(point).x(), ui->widget_show->mapToGlobal(point).y(),
                ui->widget_show->rect().width(), ui->widget_show->rect().height());
        ui->sliderVol->setRange(0, 100);
        ui->sliderVol->setValue(100);
        ui->horizontalSlider_seek->setRange(0, 100);
        ui->horizontalSlider_seek->setValue(0);
        timer->start(1000);
    }
    else if( 1 == m_bplayed )
    {
        m_bplayed = 2;
        timer->stop();
        app->pause();
    }
    else if( 2 == m_bplayed )
    {
        m_bplayed = 1;
        timer->start(1000);
        app->pause();
    }
}

void HNPlayerWidget::on_btn_stop_clicked()
{
    m_bplayed = 0;
    ui->horizontalSlider_seek->setValue(0);
    timer->stop();
    app->stop();
}

void HNPlayerWidget::on_sliderVol_valueChanged(int value)
{
    app->setVolume(value);
}
