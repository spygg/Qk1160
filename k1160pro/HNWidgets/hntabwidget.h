#ifndef HNTABWIDGET_H
#define HNTABWIDGET_H

#include <QTabWidget>
#include "hntabbar.h"

namespace Ui {
class HNTabWidget;
}

class HNTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit HNTabWidget(QWidget *parent = 0);
    ~HNTabWidget();

    HNTabBar* cTabBar();
    void setObjectName(const QString &name);
    void setToolTipDuration(int index){;}

private:
    Ui::HNTabWidget *ui;

    HNTabBar* m_bar;
};

#endif // HNTABWIDGET_H
