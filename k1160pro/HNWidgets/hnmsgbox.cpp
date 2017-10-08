#include "hnmsgbox.h"
#include "ui_hnmsgbox.h"

HNMsgBox::HNMsgBox(QWidget *parent) :
    HNDialog(parent),
    ui(new Ui::HNMsgBox)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose, true);
    connect(ui->btnYes, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->btnYesWarn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->btnNo, SIGNAL(clicked()), this, SLOT(reject()));
    delayShow = 100;

#ifdef __HNWIDGETS_K1160__
    ui->btnNo->setText("");
    ui->btnNo->setFixedSize(104, 40);
    ui->btnNo->iconTable().initNormal("://pictures_k1160/bt_back_normal.png",
                                      "://pictures_k1160/bt_back_press.png" );
    ui->btnNo->iconTable().initOther("://pictures_k1160/bt_back_hover.png",
                                     "://pictures_k1160/bt_back_disable.png");

    ui->btnYes->setText("");
    ui->btnYes->setFixedSize(104, 40);
    ui->btnYes->iconTable().initNormal("://pictures_k1160/bt_login_normal.png",
                                       "://pictures_k1160/bt_login_press.png" );
    ui->btnYes->iconTable().initOther("://pictures_k1160/bt_login_hover.png",
                                      "://pictures_k1160/bt_login_disable.png");

    ui->btnYesWarn->setText("");
    ui->btnYesWarn->setFixedSize(104, 40);
    ui->btnYesWarn->iconTable().initNormal("://pictures_k1160/bt_login_normal.png",
                                           "://pictures_k1160/bt_login_press.png" );
    ui->btnYesWarn->iconTable().initOther("://pictures_k1160/bt_login_hover.png",
                                          "://pictures_k1160/bt_login_disable.png");
#endif
}

HNMsgBox::~HNMsgBox()
{
    delete ui;
}



int HNMsgBox::warning(QWidget *parent, QString content )
{
    HNMsgBox* msgBox = new HNMsgBox(parent);
    return msgBox->_warning(content);
}

int HNMsgBox::question(QWidget *parent, QString content)
{
    HNMsgBox* msgBox = new HNMsgBox(parent);
    return msgBox->_tips(content);
}

int HNMsgBox::_warning(QString content)
{
    ui->lb_content->setText(content);
    ui->stwBtn->setCurrentIndex(1);
    return exec();
}

int HNMsgBox::_tips(QString content)
{
    ui->lb_content->setText(content);
    ui->stwBtn->setCurrentIndex(0);
    return exec();
}






void HNMsgBox::warning(QString content)
{
    setAttribute(Qt::WA_DeleteOnClose, false);
    ui->lb_content->setText(content);
    ui->stwBtn->setCurrentIndex(1);
    m_time = 0;
    //startTimer(1000);
    show();
    HNSleep(delayShow);
}

void HNMsgBox::question(QString content)
{
    setAttribute(Qt::WA_DeleteOnClose, false);
    ui->lb_content->setText(content);
    ui->stwBtn->setCurrentIndex(0);
    m_time = 0;
    //startTimer(1000);
    show();
    HNSleep(delayShow);
}

void HNMsgBox::information(QString content)
{
    setAttribute(Qt::WA_DeleteOnClose, false);
    ui->lb_content->setText(content);
    ui->stwBtn->setCurrentIndex(2);
    m_time = 0;
    //startTimer(1000);
    show();
    HNSleep(delayShow);
}

void HNMsgBox::timerEvent(QTimerEvent *e)
{
    return;
    if(m_time > 5)
    {
        killTimer(e->timerId());
        reject();
        return;
    }
    m_time ++ ;
}




