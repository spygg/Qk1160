#ifndef HNRADIOBUTTON_H
#define HNRADIOBUTTON_H

#include <QRadioButton>
#include "HNDefine.h"

namespace Ui {
class HNRadioButton;
}

class HNRadioButton : public QRadioButton
{
    Q_OBJECT

public:
    explicit HNRadioButton(QWidget *parent = 0);
    ~HNRadioButton();

    void pixMap(QImage& m_icon, QImage& m_iconSel);
    void setPixmap(const QString& m_icon = QString(), const QString &m_iconSel = QString());
private:
    Ui::HNRadioButton *ui;
    TBtnIconTable m_icon;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);

    // QAbstractButton interface
protected:
    bool hitButton(const QPoint &pos) const;
};

#endif // HNRADIOBUTTON_H
