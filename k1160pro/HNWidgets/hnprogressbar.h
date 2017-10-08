/*
 * 原装QtProgressBar，在板子上paint的时候发生异常，所以重写。
 * 行为约束：图片的大小和Bar的宽度必须相等，不容易失真
 */
#ifndef HNPROGRESSBAR_H
#define HNPROGRESSBAR_H

#include <QWidget>
#include "hnwidget.h"

namespace Ui {
class HNProgressBar;
}

class HNProgressBar : public QWidget
{
    Q_OBJECT

public:
    explicit HNProgressBar(QWidget *parent = 0);
    ~HNProgressBar();

    void setPixMap(QString back, QString trunk);
public slots:
    void setValue(int value);
    void setRange(int min, int max);

private:
    Ui::HNProgressBar *ui;

private:
    QString m_back, m_trunk;
    int m_min, m_max, m_value;
};

#endif // HNPROGRESSBAR_H
