#ifndef QMLABEL_H
#define QMLABEL_H

#include <QWidget>
#include <QLabel>

class QMLabel: public QLabel
{
    Q_OBJECT

public:
    explicit QMLabel(QWidget *parent = 0);
    ~QMLabel();
protected:
    virtual void mousePressEvent(QMouseEvent  *event);
signals:
    void clicked();
};

#endif // QMLABEL_H
