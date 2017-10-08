#include "hnuserinfomodel.h"
#include "HNDefine.h"

HNUserInfoModel::HNUserInfoModel(QObject *parent, QSqlDatabase db) :
      HNTableModel(parent, db)
{
}
