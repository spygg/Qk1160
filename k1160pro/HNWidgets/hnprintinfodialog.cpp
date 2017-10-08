#include "hnprintinfodialog.h"
#include "ui_hnprintinfodialog.h"
#include "HNDefine.h"

HNPrintInfoDialog::HNPrintInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HNPrintInfoDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, false);
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->btnPrint, SIGNAL(clicked()), this, SLOT(accept()));
}

HNPrintInfoDialog::~HNPrintInfoDialog()
{
    delete ui;
}

void HNPrintInfoDialog::initAll()
{
    //BK
    //this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_StyledBackground);
    this->setWindowModality(Qt::WindowModal);
    setAttribute(Qt::WA_StyledBackground, true);
    setWindowFlags(windowFlags() | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    setWindowIcon(QIcon("://pictures/bk_logo.ico"));

    this->setGeometry(156, 240, 805, 325);
    //moveCenter(this);
    this->setStyleSheet("QWidget#QPrinterForm{image:url(:/images/bk/bk_printer.png)}""QPrinterForm{background-color:transparent;}");

    //edit
    ui->leTitle->setGeometry(30,24,750, 43);
    ui->leTitle->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/bt_le_sobig.png);font-size:17px}");
    ui->leTitle->setAlignment(Qt::AlignCenter);
    ui->leHeader->setGeometry(30, 79, 750, 43);
    ui->leHeader->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/bt_le_sobig.png);font-size:17px}");
    ui->leHeader->setAlignment(Qt::AlignCenter);

    ui->leFooter->setGeometry(30, 134, 750, 43);
    ui->leFooter->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/bt_le_sobig.png);font-size:17px}");
    ui->leFooter->setAlignment(Qt::AlignCenter);

    //bt
    ui->btnCancel->setFlat(true);
    //ui->pushButton_back->setFocusPolicy(Qt::NoFocus);
    ui->btnCancel->setGeometry(505,250,144,48);
    ui->btnCancel->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_back_big_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_back_big_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_back_big_press.png);}");
    ui->btnCancel->setText("");
    ui->btnPrint->setFlat(true);
    //ui->pushButton_start->setFocusPolicy(Qt::NoFocus);
    ui->btnPrint->setGeometry(652,250,144,48);
    ui->btnPrint->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_start_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_start_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_start_press.png);}");
    ui->btnPrint->setText("");
}

void HNPrintInfoDialog::printInfo(QString &title, QString &header, QString &footer)
{
    if(!ui->leTitle->text().isEmpty())
        title = ui->leTitle->text();
    if(!ui->leHeader->text().isEmpty())
        header = ui->leHeader->text();
    if(!ui->leFooter->text().isEmpty())
        footer = ui->leFooter->text();
}
