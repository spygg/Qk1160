#include <QMouseEvent>
#include "qmlabel.h"

QMLabel::QMLabel(QWidget *parent):
    QLabel(parent)
{
}

QMLabel::~QMLabel()
{

}

void QMLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
    QLabel::mousePressEvent(event);
}
