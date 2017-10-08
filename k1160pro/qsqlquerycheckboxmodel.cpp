#include "qsqlquerycheckboxmodel.h"

QSqlQueryCheckBoxModel::QSqlQueryCheckBoxModel()
{
}

QSqlQueryCheckBoxModel::QSqlQueryCheckBoxModel(QObject *parent):QSqlQueryModel(parent){}


bool QSqlQueryCheckBoxModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
       return false;

    if (role == Qt::CheckStateRole && index.column() == 0)
      {
        check_state_map[index.row()] = (value == Qt::Checked ? Qt::Checked : Qt::Unchecked);
      }

     return true;
}



QVariant QSqlQueryCheckBoxModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role)
      {
            //case Qt::TextAlignmentRole:
            //              return Qt::AlignLeft | Qt::AlignVCenter;

            //case Qt::DisplayRole:
            //              return arr_row_list->at(index.row()).at(index.column());

            case Qt::CheckStateRole:
            {
                if(index.column() == 0)
                  {
                     if (check_state_map.contains(index.row()))
                         return check_state_map[index.row()] == Qt::Checked ? Qt::Checked : Qt::Unchecked;

                     return Qt::Unchecked;
                  }
             }
           default:
              return QVariant();
        }

        return QVariant();
}

Qt::ItemFlags QSqlQueryCheckBoxModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    if (index.column() == 0)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;

    return  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


QVariant QSqlQueryCheckBoxModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::CheckStateRole)
      {
          return Qt::Checked;
      }

     return QVariant();
}

/*
Qt::ItemFlags QSqlQueryCheckBoxModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    if(index.column()==0)
    {
        return  Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    else
    {
        return QAbstractItemModel::flags(index);
    }
}
*/
