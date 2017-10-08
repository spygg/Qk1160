#ifndef QTREEMODEL_H
#define QTREEMODEL_H

#include <QAbstractItemModel>

class QTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit QTreeModel(QObject *parent = 0);
    ~QTreeModel();

    QVariant data(const QModelIndex &index, int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const;

    QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const;

    QModelIndex parent(const QModelIndex &index) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    // 构建模型数据
    //void setupModelData(TreeItem *parent);

    // 更新模型数据
    void updateData();

private:
        //TreeItem *rootItem; // 最顶层顶根节点(一个无效的QModelIndex)
signals:

public slots:

};

#endif // QTREEMODEL_H
