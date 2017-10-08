#ifndef HNSYSEVENTMODEL_H
#define HNSYSEVENTMODEL_H

#include "hntablemodel.h"
#include "hngui-qt.h"

class HNSysEventModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit HNSysEventModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());

signals:

public slots:
};

HNSysEventModel *HNSingleEvent(QObject *p, QSqlDatabase& db);

#endif // HNSYSEVENTMODEL_H
