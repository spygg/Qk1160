#ifndef HNPUSHBUTTON_H
#define HNPUSHBUTTON_H

#include <QPushButton>
#include "HNDefine.h"

namespace Ui {
class HNPushButton;
}

class HNPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit HNPushButton(QWidget *parent = 0);
    ~HNPushButton();

    //HNPushButton [] = 不能正常运算 所以采用这种形式。
    TBtnIconTable& iconTable() { return m_pixmap; }

private:
    Ui::HNPushButton *ui;
    int state;
    TBtnIconTable m_pixmap;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

    // QWidget interface
protected:
    void enabledChange(bool);
};

#endif // HNPUSHBUTTON_H
