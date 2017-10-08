#include "hnprogressdialog.h"
#include "ui_hnprogressdialog.h"
#include "HNDefine.h"

HNProgressDialog::HNProgressDialog(QWidget *parent) :
    HNDialog(parent),
    ui(new Ui::HNProgressDialog)
{
    ui->setupUi(this);
    bar = ui->widgetBar;
    bar->setRange(0, 100);
    bar->setValue(0);

    connect(ui->btnCancel, SIGNAL(clicked()),
            this, SLOT(reject()));

    //setFixedWidth(260);

#ifdef __HNWIDGETS_K1160__
    setFixedSize(526, 283);
    bar->setFixedSize(481, 31);
    bar->move(20, 50);

    ui->btnCancel->setText("");
    ui->btnCancel->setFixedSize(104, 40);
    ui->btnCancel->iconTable().initNormal("://pictures_k1160/bt_back_normal.png",
                                      "://pictures_k1160/bt_back_press.png" );
    ui->btnCancel->iconTable().initOther("://pictures_k1160/bt_back_hover.png",
                                     "://pictures_k1160/bt_back_disable.png");

    ui->widgetBar->setPixMap("://pictures_k1160/bk_progress_background.png",
                             "://pictures_k1160/bk_progress_chunk.png");
#endif

}

HNProgressDialog::~HNProgressDialog()
{
    delete ui;
}

void HNProgressDialog::initAll()
{
    bar->setRange(0, 100);
    bar->setValue(0);
}

void HNProgressDialog::setRange(int min, int max)
{
    bar->setRange(min, max);
}

void HNProgressDialog::setContent(QString content)
{
    ui->label->setText(content);
}

void HNProgressDialog::setValue(int value)
{
    bar->setValue(value);
}

