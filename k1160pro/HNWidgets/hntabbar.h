#ifndef HNTABBAR_H
#define HNTABBAR_H

#include <QTabBar>
#include <QList>
#include "HNDefine.h"

class HNTabBar : public QTabBar
{
    Q_OBJECT

public:
    explicit HNTabBar(QWidget *parent = 0);

    void tabPixmap(int index, QImage &icon, QImage &iconSel);
    void setTabPixmap(int index, const QString& icon = QString(), const QString &iconSel = QString());

protected:
    void paintEvent(QPaintEvent *);
    inline bool verticalTabs();

public slots:

private:
    QList<TBtnIconTable> iconList;
};

#endif // HNTABBAR_H
