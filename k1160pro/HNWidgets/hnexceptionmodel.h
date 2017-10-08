#ifndef QEXCEPTIONMODEL_H
#define QEXCEPTIONMODEL_H

#include "hntablemodel.h"

class HNExceptionModel : public HNTableModel
{
    Q_OBJECT
public:
    explicit HNExceptionModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());
signals:

public slots:

};

#endif // QEXCEPTIONMODEL_H
