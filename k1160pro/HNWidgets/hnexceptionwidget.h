#ifndef QEXCEPTIONWIDGET_H
#define QEXCEPTIONWIDGET_H

#include "hnexceptionview.h"
#include "hnexceptionmodel.h"

namespace Ui {
class QExceptionWidget;
}

class HNExceptionWidget : public HNExceptionView
{
    Q_OBJECT

public:
    explicit HNExceptionWidget(QWidget *parent = 0);
    ~HNExceptionWidget();

private:
    Ui::QExceptionWidget *ui;
    HNExceptionModel* m_model;
    QSqlDatabase m_db;
};

#endif // QEXCEPTIONWIDGET_H
