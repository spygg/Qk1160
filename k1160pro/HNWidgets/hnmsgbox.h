#ifndef HNMSGBOX_H
#define HNMSGBOX_H

#include "hndialog.h"

namespace Ui {
class HNMsgBox;
}

class HNMsgBox : public HNDialog
{
    Q_OBJECT

public:
    explicit HNMsgBox(QWidget *parent = 0);
    ~HNMsgBox();

    void warning(QString content);
    void question(QString content);
    void information(QString content);

    //警告，不可选择
    static int warning(QWidget* parent = 0, QString content = "");
    //提醒，供用户选择
    static int question(QWidget* parent = 0, QString content = "");

protected:
    int _warning(QString content);
    int _tips(QString content);

private:
    Ui::HNMsgBox *ui;
    quint32 m_time;
    int delayShow;

    // QObject interface
protected:
    void timerEvent(QTimerEvent *);
};

#endif // HNMSGBOX_H
