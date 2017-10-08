#include "hnsyseventmodel.h"

HNSysEventModel::HNSysEventModel(QObject *parent, QSqlDatabase db) :
    QSqlRelationalTableModel(parent, db)
{
}

HNSysEventModel *HNSingleEvent(QObject* p, QSqlDatabase& db)
{
    static HNSysEventModel* e = new HNSysEventModel(p, db);
    return e;
}
