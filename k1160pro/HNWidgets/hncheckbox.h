#ifndef HNCHECKBOX_H
#define HNCHECKBOX_H

#include <QCheckBox>
#include "HNDefine.h"

namespace Ui {
class HNCheckBox;
}

class HNCheckBox : public QCheckBox
{
    Q_OBJECT

public:
    explicit HNCheckBox(QWidget *parent = 0);
    ~HNCheckBox();
    void pixMap(QImage& m_icon, QImage& m_iconSel);
    void setPixmap(const QString& m_icon = QString(), const QString &m_iconSel = QString());

private:
    Ui::HNCheckBox *ui;
    TBtnIconTable m_icon;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);

    // QAbstractButton interface
protected:
    bool hitButton(const QPoint &pos) const;
};

#endif // HNCHECKBOX_H
