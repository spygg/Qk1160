#include "quserform.h"
#include "ui_quserform.h"
#include "qmainwindow.h"
#include "qmainscreen.h"
#include "mainwindow.h"
#include <QMessageBox>

QUserForm::QUserForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QUserForm),
    pdataquery(NULL),
    strtable("user"),
    m_strexpress("")
{
    ui->setupUi(this);
    m_ptc =  QTextCodec::codecForName("UTF-8");
    InitOCX();
    InitSings();

    linstname.clear();
    linstvalues.clear();
    pdataquery = new QDatabasequery();
    pdataquery->SetTableName("./db/hanon");

    m_bhead1 = true;
    m_bhead2 = true;
    m_bhead3 = true;
    m_bhead4 = true;
    m_btheme1 = true;
    m_btheme2 = true;
    m_btheme3 = true;
    m_btheme4 = true;
}

QUserForm::~QUserForm()
{
    delete ui;
}


void QUserForm::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("QWidget#QUserForm{image:url(:/images/bk/bk_user.png)}""QUserForm{background-color:transparent;}");

    m_plbhead1 = new QMLabel(this);
    m_plbhead1->setGeometry(516,94,86, 86);
    m_plbhead1->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head1_normal.png);}");

    m_plbhead2 = new QMLabel(this);
    m_plbhead2->setGeometry(606,94,86, 86);
    m_plbhead2->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head2_normal.png);}");

    m_plbhead3 = new QMLabel(this);
    m_plbhead3->setGeometry(696,94,86, 86);
    m_plbhead3->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head3_normal.png);}");

    m_plbhead4 = new QMLabel(this);
    m_plbhead4->setGeometry(786,94,86, 86);
    m_plbhead4->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head4_normal.png);}");

    QSettings set;
    QString head = set.value("HeadPic").toString();
    if(head == "head1")
    {
        emit emitHeadIndex(1);
        m_plbhead1->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head1_press.png);}");
    }
    else if(head == "head2")
    {
        emit emitHeadIndex(2);
        m_plbhead2->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head2_press.png);}");
    }
    else if(head == "head3")
    {
        emit emitHeadIndex(3);
        m_plbhead3->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head3_press.png);}");
}
    else if(head == "head4")
    {
        emit emitHeadIndex(4);
        m_plbhead4->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head4_press.png);}");
}
    m_plbtheme1 = new QMLabel(this);
    m_plbtheme1->setGeometry(67,407,79, 59);
    m_plbtheme1->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme1_normal.png);}");

    m_plbtheme2 = new QMLabel(this);
    m_plbtheme2->setGeometry(158,407,79, 59);
    m_plbtheme2->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme2_normal.png);}");

    m_plbtheme3 = new QMLabel(this);
    m_plbtheme3->setGeometry(249,407,79, 59);
    m_plbtheme3->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme3_normal.png);}");

    m_plbtheme4 = new QMLabel(this);
    m_plbtheme4->setGeometry(340,407,79, 59);
    m_plbtheme4->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme4_normal.png);}");

    QString theme = set.value("ThemePic").toString();
    if(theme == "theme1")
    {
        emit emitScreenIndex(1);
        m_plbtheme1->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme1_press.png);}");
    }
    else if(theme == "theme2")
    {
        emit emitScreenIndex(2);
        m_plbtheme2->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme2_press.png);}");
    }
    else if(theme == "theme3")
        {
            emit emitScreenIndex(3);
        m_plbtheme3->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme3_press.png);}");
    }
    else if(theme == "theme4")
        {
            emit emitScreenIndex(4);
        m_plbtheme4->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme4_press.png);}");
    }


    //bt
    ui->pb_user_logout->setFlat(true);
    //ui->pb_user_logout->setFocusPolicy(Qt::NoFocus);
    ui->pb_user_logout->setGeometry(579,592,144,48);
    ui->pb_user_logout->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_logout_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_logout_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_logout_press.png);}");

    ui->pb_logout_save->setFlat(true);
    //ui->pb_logout_save->setFocusPolicy(Qt::NoFocus);
    ui->pb_logout_save->setGeometry(761,592,144,48);
    ui->pb_logout_save->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_savebig_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_savebig_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_savebig_press.png);}");

    ui->ed_user_oldpasswd->setGeometry(142,75,291, 35);
    ui->ed_user_oldpasswd->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");
    ui->ed_user_oldpasswd->setEchoMode (QLineEdit::Password);

    ui->ed_user_newpasswd->setGeometry(142,121,291, 35);
    ui->ed_user_newpasswd->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");
    ui->ed_user_newpasswd->setEchoMode (QLineEdit::Password);

    ui->ed_user_comfirepasswd->setGeometry(142,167,291, 35);
    ui->ed_user_comfirepasswd->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");
    ui->ed_user_comfirepasswd->setEchoMode (QLineEdit::Password);

    ui->lb_user_oldpasswd->setGeometry(48, 76, 150, 30);
    ui->lb_user_oldpasswd->setText(m_ptc->toUnicode("原始密码:"));
    ui->lb_user_oldpasswd->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_user_newpasswd->setGeometry(48, 122, 150, 30);
    ui->lb_user_newpasswd->setText(m_ptc->toUnicode("新密码:"));
    ui->lb_user_newpasswd->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_user_comfirepasswd->setGeometry(48, 168, 150, 30);
    ui->lb_user_comfirepasswd->setText(m_ptc->toUnicode("确认密码:"));
    ui->lb_user_comfirepasswd->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->label_mima->setGeometry(28,8,111,36);
    ui->label_mima->setText(m_ptc->toUnicode("密码"));
    ui->label_mima->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_touxiang->setGeometry(500,8,111,36);
    ui->label_touxiang->setText(m_ptc->toUnicode("头像"));
    ui->label_touxiang->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->label_zhuti->setGeometry(28,302,111,36);
    ui->label_zhuti->setText(m_ptc->toUnicode("主题"));
    ui->label_zhuti->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");


}

void QUserForm::InitSings()
{
    QMainScreen *p = (QMainScreen *) this->parent();

    QMainWindow *pm = (QMainWindow *)p->parent();

    connect(this, SIGNAL(emitScreenIndex(int)), p, SLOT(changescreen(int)));

    connect(this, SIGNAL(emitScreenIndex(int)), pm, SLOT(changescreen(int)));

    connect(this, SIGNAL(emitHeadIndex(int)), p, SLOT(changehead(int)));

    connect(m_plbhead1, SIGNAL(clicked()), this, SLOT(head1()));
    connect(m_plbhead2, SIGNAL(clicked()), this, SLOT(head2()));
    connect(m_plbhead3, SIGNAL(clicked()), this, SLOT(head3()));
    connect(m_plbhead4, SIGNAL(clicked()), this, SLOT(head4()));

    connect(m_plbtheme1, SIGNAL(clicked()), this, SLOT(theme1()));
    connect(m_plbtheme2, SIGNAL(clicked()), this, SLOT(theme2()));
    connect(m_plbtheme3, SIGNAL(clicked()), this, SLOT(theme3()));
    connect(m_plbtheme4, SIGNAL(clicked()), this, SLOT(theme4()));
}

void QUserForm::head1()
{
    if(true == m_bhead1)
     {
         m_plbhead1->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head1_press.png);}");
         m_bhead1 = false;
         m_plbhead2->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head2_normal.png);}");
         m_bhead2 = true;
         m_plbhead3->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head3_normal.png);}");
         m_bhead3 = true;
         m_plbhead4->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head4_normal.png);}");
         m_bhead4 = true;

         emit emitHeadIndex(1);
         QSettings set;
         set.setValue("HeadPic", "head1");
         set.sync();
     }
     else
     {
          m_plbhead1->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head1_normal.png);}");
          m_bhead1 = true;
     }
}

void QUserForm::head2()
{
    if(true == m_bhead2)
     {
         m_plbhead2->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head2_press.png);}");
         m_bhead2 = false;
         m_plbhead1->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head1_normal.png);}");
         m_bhead1 = true;
         m_plbhead3->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head3_normal.png);}");
         m_bhead3 = true;
         m_plbhead4->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head4_normal.png);}");
         m_bhead4 = true;
         emit emitHeadIndex(2);
         QSettings set;
         set.setValue("HeadPic", "head2");
         set.sync();
     }
     else
     {
          m_plbhead2->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head2_normal.png);}");
          m_bhead2 = true;
     }
}

void QUserForm::head3()
{
    if(true == m_bhead3)
     {
         m_plbhead3->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head3_press.png);}");
         m_bhead3 = false;
         m_plbhead1->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head1_normal.png);}");
         m_bhead1 = true;
         m_plbhead2->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head2_normal.png);}");
         m_bhead2 = true;
         m_plbhead4->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head4_normal.png);}");
         m_bhead4 = true;
         emit emitHeadIndex(3);
         QSettings set;
         set.setValue("HeadPic", "head3");
         set.sync();
     }
     else
     {
          m_plbhead3->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head3_normal.png);}");
          m_bhead3 = true;
     }
}

void QUserForm::head4()
{
    if(true == m_bhead4)
     {
         m_plbhead4->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head4_press.png);}");
         m_bhead4 = false;
         m_plbhead1->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head1_normal.png);}");
         m_bhead1 = true;
         m_plbhead2->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head2_normal.png);}");
         m_bhead2 = true;
         m_plbhead3->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head3_normal.png);}");
         m_bhead3 = true;
         emit emitHeadIndex(4);
         QSettings set;
         set.setValue("HeadPic", "head4");
         set.sync();
     }
     else
     {
          m_plbhead4->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_head4_normal.png);}");
          m_bhead4 = true;
     }
}

void QUserForm::theme1()
{
    if(true == m_btheme1)
     {
         m_plbtheme1->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme1_press.png);}");
         m_btheme1 = false;
         m_plbtheme2->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme2_normal.png);}");
         m_btheme2 = true;
         m_plbtheme3->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme3_normal.png);}");
         m_btheme3 = true;
         m_plbtheme4->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme4_normal.png);}");
         m_btheme4 = true;
         emit emitScreenIndex(1);
         QSettings set;
         set.setValue("ThemePic", "theme1");
         set.sync();

     }
     else
     {
          m_plbtheme1->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme1_normal.png);}");
          m_btheme1 = true;
     }
}

void QUserForm::theme2()
{
    if(true == m_btheme2)
     {
         m_plbtheme2->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme2_press.png);}");
         m_btheme2 = false;
         m_plbtheme1->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme1_normal.png);}");
         m_btheme1 = true;
         m_plbtheme3->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme3_normal.png);}");
         m_btheme3 = true;
         m_plbtheme4->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme4_normal.png);}");
         m_btheme4 = true;
         emit emitScreenIndex(2);
         QSettings set;
         set.setValue("ThemePic", "theme2");
         set.sync();

     }
     else
     {
          m_plbtheme2->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme2_normal.png);}");
          m_btheme2 = true;
     }
}

void QUserForm::theme3()
{
    if(true == m_btheme3)
     {
         m_plbtheme3->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme3_press.png);}");
         m_btheme3 = false;
         m_plbtheme1->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme1_normal.png);}");
         m_btheme1 = true;
         m_plbtheme2->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme2_normal.png);}");
         m_btheme2 = true;
         m_plbtheme4->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme4_normal.png);}");
         m_btheme4 = true;
         emit emitScreenIndex(3);
         QSettings set;
         set.setValue("ThemePic", "theme3");
         set.sync();
     }
     else
     {
          m_plbtheme3->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme3_normal.png);}");
          m_btheme3 = true;
     }
}

void QUserForm::theme4()
{
    if(true == m_btheme4)
     {
         m_plbtheme4->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme4_press.png);}");
         m_btheme4 = false;
         m_plbtheme1->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme1_normal.png);}");
         m_btheme1 = true;
         m_plbtheme2->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme2_normal.png);}");
         m_btheme2 = true;
         m_plbtheme3->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme3_normal.png);}");
         m_btheme3 = true;
         emit emitScreenIndex(4);
         QSettings set;
         set.setValue("ThemePic", "theme4");
         set.sync();
     }
     else
     {
          m_plbtheme4->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_theme4_normal.png);}");
          m_btheme4 = true;
     }
}

void QUserForm::on_pb_logout_save_clicked()
{
    QString stroldpasswd = "";
    QString strnewpasswd = "";
    QString strnewpasswdcf = "";
    QString strname = "";

    linstvalues.clear();
    linstname.clear();
    stroldpasswd = ui->ed_user_oldpasswd->text();
    strnewpasswd = ui->ed_user_newpasswd->text();
    strnewpasswdcf = ui->ed_user_comfirepasswd->text();

    if(stroldpasswd.isEmpty() && strnewpasswd.isEmpty() && strnewpasswdcf.isEmpty())
    {
        return;
    }

    if(stroldpasswd.isEmpty() || strnewpasswd.isEmpty() || strnewpasswdcf.isEmpty())
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("密码不能为空"), QMessageBox::Ok);
        return;
    }

    if(strnewpasswd != strnewpasswdcf)
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("新密码不一致"), QMessageBox::Ok);
        return;
    }

    strname = "mingcheng";
    QMainScreen *p = (QMainScreen *) this->parent();
    QString str =  p->GetUserName();

    if(true == pdataquery->opendatabase())
    {
        pdataquery->GetoneValues(strtable, linstvalues, strname, str, 8);
        pdataquery->cloesdatabase();
    }

    //QString strID = linstvalues.at(0);
    QString strName = linstvalues.at(1);
    QString strpasswd = linstvalues.at(2);
    QString strTime = linstvalues.at(3);
    QString strlevel = linstvalues.at(4);
    QString strnote = linstvalues.at(5);
    QString strimage = linstvalues.at(6);
    QString strbkimage = linstvalues.at(7);

    if((true == m_bhead1) && (true == m_bhead2) && (true == m_bhead3) && (true == m_bhead4))
    {
        strimage = "0";
    }

    if(false == m_bhead1)
    {
        strimage = "0";
    }


    if(false == m_bhead2)
    {
        strimage = "1";
    }


    if(false == m_bhead3)
    {
        strimage = "2";
    }


    if(false == m_bhead4)
    {
        strimage = "3";
    }

    if((true == m_btheme1) && (true == m_btheme2) && (true == m_btheme3) && (true == m_btheme4))
    {
        strbkimage = "1";
    }

    if(false == m_btheme1)
    {
        strbkimage = "1";
    }


    if(false == m_btheme2)
    {
        strbkimage = "2";
    }


    if(false == m_btheme3)
    {
        strbkimage = "3";
    }


    if(false == m_btheme4)
    {
        strbkimage = "4";
    }

    if(stroldpasswd != linstvalues.at(2))
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("旧密码错误"), QMessageBox::Ok);
        return;
    }

    //strpasswd = strnewpasswd;

    linstname.clear();
    //linstname.append(m_ptc->toUnicode("id"));
    linstname.append(m_ptc->toUnicode("mingcheng"));
    linstname.append(m_ptc->toUnicode("mima"));
    linstname.append(m_ptc->toUnicode("time"));
    linstname.append(m_ptc->toUnicode("level"));
    linstname.append(m_ptc->toUnicode("note"));
    linstname.append(m_ptc->toUnicode("image"));
    linstname.append(m_ptc->toUnicode("backimage"));

    linstvalues.clear();
    //linstvalues.append(strID);
    linstvalues.append(strName);
    linstvalues.append(strnewpasswd);
    linstvalues.append(strTime);
    linstvalues.append(strlevel);
    linstvalues.append(strnote);
    linstvalues.append(strimage);
    linstvalues.append(strbkimage);

    ui->ed_user_comfirepasswd->clear();
    ui->ed_user_newpasswd->clear();
    ui->ed_user_oldpasswd->clear();
    QString strex = "mingcheng='" + strName + "' and mima = '" + strpasswd + "'";

    pdataquery->opendatabase();
    pdataquery->Updata(strtable, linstname, linstvalues, strex);
    pdataquery->cloesdatabase();

    QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("保存成功"), QMessageBox::Ok);
}

void QUserForm::on_pb_user_logout_clicked()
{
    if( HNMsgBox::Rejected == HNMsgBox::question(this, "确认注销用户，登出系统？"))
        return;

    QMainScreen *p = (QMainScreen *) this->parent();

    MainWindow *pm = (MainWindow *)p->parent();
    pm->SetUser();
    p->hide();
    pm->show();
}
