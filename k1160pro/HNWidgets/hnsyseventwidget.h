#ifndef QSYSEVENTWIDGET_H
#define QSYSEVENTWIDGET_H

#include "hnsyseventview.h"
#include "hnsyseventmodel.h"

namespace Ui {
class QSysEventWidget;
}

class HNSysEventWidget : public HNSysEventView
{
    Q_OBJECT

public:
    explicit HNSysEventWidget(QWidget *parent = 0);
    ~HNSysEventWidget();

private:
    Ui::QSysEventWidget *ui;
    QSqlDatabase m_db;
    HNSysEventModel* m_model;
};

#endif // QSYSEVENTWIDGET_H
