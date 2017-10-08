#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>
#include "qcheckfrom.h"
#include "qmainscreen.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void SetUser();
    void setLevel(int ilevel);
    int  getLevel();
private slots:
    void on_pb_logindlg_login_clicked();
    void changescreen(int index);
    void on_le_logindlg_username_textChanged(const QString &arg1);

    void on_le_logindlg_username_textEdited(const QString &arg1);

    void on_cb_username_currentTextChanged(const QString &arg1);

private:
    void InitOCX();


    void mousePressEvent(QMouseEvent *e);

private:
    QString     m_strexpress;
    QStringList linstname;
    QStringList linstvalues;
    QStringList linstvaluestemp;
    QString     strtable;
    QDatabasequery *pdataquery;
    QMainScreen *m_pScreen;
    QCheckFrom  *m_pCheckDlg;
    QTextCodec  *m_ptc;
    Ui::MainWindow *ui;
    int m_ilevel;

};

#endif // MAINWINDOW_H
