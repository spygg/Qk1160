#include "hndialog.h"
#include "ui_hndialog.h"
#include "QPainter"
#include "QPainterPath"
#include "HNDefine.h"

HNDialog::HNDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HNDialog)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);//阻挡父亲窗口内其他控件，除非本dialog关闭 show的功能强大起来 可以使用输入法

#if 0
    setWindowFlags(Qt::FramelessWindowHint|windowFlags());
    setAttribute(Qt::WA_TranslucentBackground, true);
    QPalette plt = palette();
    plt.setColor(QPalette::Normal, QPalette::Shadow, QColor(255, 149, 12, 255));
    plt.setColor(QPalette::Normal, QPalette::Window, QColor(255, 255, 255, 255));
    setPalette(plt);
#endif


    setAttribute(Qt::WA_DeleteOnClose, false);
    setAttribute(Qt::WA_StyledBackground, true);
    setWindowFlags(windowFlags() | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    setWindowIcon(QIcon("://pictures/bk_logo.ico"));
}

HNDialog::~HNDialog()
{
    delete ui;
}

void HNDialog::paintEvent(QPaintEvent *e)
{
    QDialog::paintEvent(e);
    return;

    QPainter p(this);
    QPalette plt = palette();

    //半透明背景
    QPen pen;
    int border = 2;
    int radius = 4;
    pen.setWidth(border);
    pen.setColor(plt.color(QPalette::Normal, QPalette::Shadow));
    p.setPen(pen);
    p.setBrush(plt.brush(QPalette::Normal, QPalette::Window));
    p.drawRoundedRect(QRect(3, 3, rect().width()-border-3, rect().height()-border-3), radius, radius);
}
