#include "hntablemodel.h"

HNTableModel::HNTableModel(QObject *parent, QSqlDatabase db):
    QSqlRelationalTableModel(parent, db)
{
}

void HNTableModel::query(QString filter)
{
    setFilter(filter);
    select();
}

QVariant HNTableModel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
    case Qt::TextAlignmentRole:
    case Qt::DisplayRole:
    case Qt::CheckStateRole:
    default:
        break;
    }

    return QSqlRelationalTableModel::data(index, role);
}


bool HNTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return QSqlRelationalTableModel::setData(index, value, role);
}

Qt::ItemFlags HNTableModel::flags(const QModelIndex &index) const
{
    return QSqlRelationalTableModel::flags(index);
}
