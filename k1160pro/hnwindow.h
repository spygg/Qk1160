#ifndef HNWINDOW_H
#define HNWINDOW_H

#include <QStackedWidget>

namespace Ui {
class HNWindow;
}

class HNWindow : public QStackedWidget
{
    Q_OBJECT

public:
    explicit HNWindow(QWidget *parent = 0);
    ~HNWindow();

private:
    Ui::HNWindow *ui;
};

#endif // HNWINDOW_H
