#ifndef HNSUYUANFORM_H
#define HNSUYUANFORM_H

#include <QWidget>
#include "hnmptablewidget.h"

class HNSuyuanForm : public QWidget
{
    Q_OBJECT
public:
    explicit HNSuyuanForm(QWidget *parent = 0);

signals:

public slots:

private:
    HNMPTableWidget* m_table;
};

#endif // HNSUYUANFORM_H
