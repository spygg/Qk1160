#ifndef HNUSERINFOMODEL_H
#define HNUSERINFOMODEL_H

#include "hntablemodel.h"

class HNUserInfoModel : public HNTableModel
{
    Q_OBJECT
public:
    explicit HNUserInfoModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());

signals:

public slots:

};

#endif // HNUSERINFOMODEL_H
