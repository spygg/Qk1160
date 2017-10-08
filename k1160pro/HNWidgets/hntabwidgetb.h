#ifndef HNTABWIDGETB_H
#define HNTABWIDGETB_H

#include <QTabWidget>

namespace Ui {
class HNTabWidgetB;
}

class HNTabWidgetB : public QTabWidget
{
    Q_OBJECT

public:
    explicit HNTabWidgetB(QWidget *parent = 0);
    ~HNTabWidgetB();

    QTabBar* tabBar() { return QTabWidget::tabBar(); }

private:
    Ui::HNTabWidgetB *ui;
};

#endif // HNTABWIDGETB_H
