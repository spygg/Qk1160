#ifndef QSQLQUERYCHECKBOXMODEL_H
#define QSQLQUERYCHECKBOXMODEL_H

#include <QSqlQueryModel>
#include <QMap>

class QSqlQueryCheckBoxModel : public QSqlQueryModel
{
public:
    QSqlQueryCheckBoxModel();
    explicit QSqlQueryCheckBoxModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    //Qt::ItemFlags flags(const QModelIndex &index) const;
private:
    QMap<int, Qt::CheckState> check_state_map;
};

#endif // QSQLQUERYCHECKBOXMODEL_H
