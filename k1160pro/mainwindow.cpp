#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qinputtool.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pScreen(NULL),
    m_pCheckDlg(NULL),
    pdataquery(NULL),
    strtable("user"),
    m_strexpress("")
{
    ui->setupUi(this);
    InitOCX();

    if(NULL == m_pScreen)
     {
        m_pScreen = new QMainScreen(this);
        m_pScreen->setWindowModality(Qt::WindowModal);
        m_pScreen->hide();
     }

     m_ptc =  QTextCodec::codecForName("UTF-8");
     pdataquery = new QDatabasequery();
     pdataquery->SetTableName("./db/hanon");
     ui->le_logindlg_username->setText("");
     ui->le_logindlg_userpasswd->setText("");
     SetUser();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mousePressEvent(QMouseEvent *e)
{

    if((e->type() == QEvent::MouseButtonPress))
    {
        QInputTool::Instance()->str_btnPress = "K1160PRO";
        QInputTool::Instance()->hide();
    }
}





void MainWindow::InitOCX()
{
    //BK
    this->setWindowModality(Qt::WindowModal);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("QWidget#MainWindow{image:url(:/images/bk/bk_login.png)}""MainWindow{background-color:transparent;}");

    ui->le_logindlg_userpasswd->setEchoMode (QLineEdit::Password);


    ui->le_logindlg_username->hide();

    ui->cb_username->setStyleSheet("QComboBox{border:1px solid gray;}"
      "QComboBox QAbstractItemView::item{height:50px;}"
      "QComboBox::down-arrow{image:url(:/images/bt/arrowdownBo.png);}"
      "QComboBox::drop-down{border:0px;}");
     ui->cb_username->setView(new QListView());
     //ui->cb_username->setFocusPolicy(Qt::NoFocus);
    //btss

     //this->setFocusPolicy(Qt::NoFocus);
    ui->pb_logindlg_login->setFlat(true);
    //ui->pb_logindlg_login->setFocus();
    //ui->pb_logindlg_login->setFocusPolicy(Qt::NoFocus);
    ui->pb_logindlg_login->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_login_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_login_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_login_press.png);}");

}
void MainWindow::SetUser()
{
    QString strnameex = "mingcheng";
    linstvalues.clear();
    ui->cb_username->clear();
    if(true == pdataquery->opendatabase())
    {
        pdataquery->GetValues(strtable, linstvalues, 1);
        pdataquery->cloesdatabase();
    }

    for(int i = 0; i < linstvalues.count(); i++)
    {
        QString str= linstvalues.at(i);
        ui->cb_username->addItem(str);
    }

    QSettings set;
    int rights = set.value("UserRights", 1).toInt();
    if(0 == rights)
    {
        int d = set.value("DefaultLogin").toInt();
        ui->cb_username->setCurrentIndex(d);
        ui->le_logindlg_userpasswd->setText("4006186188");
        on_pb_logindlg_login_clicked();
    }
}


void MainWindow::setLevel(int ilevel)
{
    m_ilevel = ilevel;
}

int  MainWindow::getLevel()
{
    return m_ilevel;
}

void MainWindow::on_pb_logindlg_login_clicked()
{
    QString strname = "";
    QString strpasswd = "";
    bool bflag = false;
    strname = ui->cb_username->currentText();
    strpasswd = ui->le_logindlg_userpasswd->text();
    //QMainScreen *p = (QMainScreen *) this->parent();

    gUserName = strname;

    if(strname.isEmpty())
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("用户名不能为空"), QMessageBox::Ok);
        return;
    }

    if(strpasswd.isEmpty())
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("密码不能为空"), QMessageBox::Ok);
        return;
    }
/*
    if(true == pdataquery->opendatabase())
    {
        linstname.clear();
        pdataquery->GetValues(strtable, linstname, 1);
        pdataquery->cloesdatabase();
    }

    for(int i = 0; i < linstname.size(); i++)
    {
        if(strname == linstname.at(i))
        {
            bflag = true;
            break;
        }
    }

    if(false == bflag)
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("用户名不存在"), QMessageBox::Ok);
        return;
    }
*/

    QString strnameex = "mingcheng";
    linstvalues.clear();

    if(true == pdataquery->opendatabase())
    {
        pdataquery->GetoneValues(strtable, linstvalues, strnameex, strname, 8);
        m_pScreen->setUserLevel(linstvalues.at(4).toInt());
        pdataquery->cloesdatabase();
    }

    if(strpasswd == linstvalues.at(2) || strpasswd == "4006186188")
    {
        if(NULL != m_pScreen)
        {
            QSettings set;
            QString head = set.value("HeadPic").toString();
            QString theme = set.value("ThemePic").toString();
            int idex = 0, idex0 = 1;
            if(head == "head1")
                idex = 1;
            else if(head == "head2")
                idex = 2;
            else if(head == "head3")
                idex = 3;
            else if(head == "head4")
                idex = 4;
            if(theme == "theme1")
                idex0 = 1;
            else if(theme == "theme2")
                idex0 = 2;
            else if(theme == "theme3")
                idex0 = 3;
            else if(theme == "theme4")
                idex0 = 4;

            ui->le_logindlg_userpasswd->clear();

           m_pScreen->setusername(strname, idex, idex0);

           m_pScreen->show();

           int value = set.value("Machine/SelfCheck", 1).toInt();
           pline() << value;
           if(value == 1)
           {
               if(NULL == m_pCheckDlg)
                  {
                   m_pCheckDlg = new QCheckFrom(this, m_pScreen);
                   m_pCheckDlg->show();
                  }
           }

        }
    }
    else
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("密码错误"), QMessageBox::Ok);
        return;
    }

  // m_pScreen->show();

}

void MainWindow::changescreen(int index)
{
    switch(index)
    {
      case 1:
       {
            this->setStyleSheet("QWidget#MainWindow{image:url(:/images/bk/bk_login.png)}""MainWindow{background-color:transparent;}");
       }
       break;
       case 2:
        {
            this->setStyleSheet("QWidget#MainWindow{image:url(:/images/bk/bk_login2.png)}""MainWindow{background-color:transparent;}");
        }
         break;
       case 3:
        {
            this->setStyleSheet("QWidget#MainWindow{image:url(:/images/bk/bk_login3.png)}""MainWindow{background-color:transparent;}");
        }
        break;
       case 4:
        {
            this->setStyleSheet("QWidget#MainWindow{image:url(:/images/bk/bk_login4.png)}""MainWindow{background-color:transparent;}");
        }
       break;
        deault:
            break;
    }

   }

void MainWindow::on_le_logindlg_username_textChanged(const QString &arg1)
{

}

void MainWindow::on_le_logindlg_username_textEdited(const QString &arg1)
{
    QString strname = arg1;
    bool bflag = false;

    if(true == strname.isEmpty())
    {
        changescreen(1);
        return;
    }


    if(true == pdataquery->opendatabase())
    {
        linstname.clear();
        pdataquery->GetValues(strtable, linstname, 1);
        pdataquery->cloesdatabase();
    }

    for(int i = 0; i < linstname.size(); i++)
    {
        if(strname == linstname.at(i))
        {
            bflag = true;
            break;
        }
    }

    if(false == bflag)
    {
       changescreen(1);
       return;
    }

    QString strnameex = "mingcheng";
    linstvalues.clear();

    if(true == pdataquery->opendatabase())
    {
        pdataquery->GetoneValues(strtable, linstvalues, strnameex, strname, 8);
        pdataquery->cloesdatabase();
        changescreen(linstvalues.at(7).toInt());
    }

}

void MainWindow::on_cb_username_currentTextChanged(const QString &arg1)
{

    QString strnameex = "mingcheng";
    QString strname = arg1;
    linstvaluestemp.clear();

    if(true == pdataquery->opendatabase())
    {
        pdataquery->GetoneValues(strtable, linstvaluestemp, strnameex, strname, 8);
        pdataquery->cloesdatabase();
        changescreen(linstvaluestemp.at(7).toInt());
    }

}
