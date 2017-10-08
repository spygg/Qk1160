#include "qtreemodel.h"

QTreeModel::QTreeModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    //rootItem=NULL;
    updateData();
}

QTreeModel::~QTreeModel()
{
    if(NULL != rootItem)
    {
        qDebug() << "this 3";
        delete rootItem;
        rootItem = NULL;
    }
}


void QTreeModel::updateData()
{
    // 废弃旧的模型数据
    /*
    if(rootItem)
    {
        delete rootItem;
        rootItem=NULL;
    }

    QList<QVariant> rootData;
    rootData<<"Tag"<<"Type";

    rootItem=new TreeItem(rootData);
    setupModelData(rootItem);
*/
    // 刷新模型
    reset();
}



QVariant QTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
/*
    // 添加图标
    if(role==Qt::DecorationRole&&index.column()==0)
            return QIcon("images/fold.png");

    // 显示节点数据值
    if(role==Qt::DisplayRole)
    {
        TreeItem *item=static_cast<TreeItem*>(index.internalPointer());
         return item->data(index.column());
    }
*/
    return QVariant();
}

Qt::ItemFlags QTreeModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    return Qt::ItemIsEnabled|Qt::ItemIsSelectable;
}

QVariant TagTreeModel::headerData(int section, Qt::Orientation orientation,int role) const
{
    if(orientation==Qt::Horizontal&&role==Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex QTreeModel::index(int row, int column,const QModelIndex &parent) const
{
    if(!hasIndex(row,column,parent))
        return QModelIndex();

    TreeItem *parentItem;
    if(!parent.isValid())
    {
        parentItem=rootItem;
    }else
    {
        parentItem=static_cast<TreeItem*>(parent.internalPointer());
    }

    TreeItem *childItem=parentItem->child(row);
    if(childItem)
        return createIndex(row,column,childItem); // 展开树形,为子节点建立索引
    else
        return QModelIndex();
}

QModelIndex QTreeModel::parent(const QModelIndex &index) const
{
    if(!index.isValid())
        return QModelIndex();

    TreeItem *childItem=static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem=childItem->parent();

    // 顶层节点,直接返回空索引
    if(parentItem==rootItem)
        return QModelIndex();

    // 为父结点建立索引
    return createIndex(parentItem->row(),0,parentItem);
}

int QTreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;

    if(!parent.isValid())
        parentItem=rootItem;
    else
        parentItem=static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount(); // 返回父结点下子结点数目
}

int QTreeModel::columnCount(const QModelIndex &parent ) const
{
    return rootItem->columnCount();
}

// 设置模型数据,构建包含10个根结点,每个根结点包含两个子节点的树形结构
void QTreeModel::setupModelData(TreeItem *parent)
{
    for(int i=0;i<10;i++)
    {
        QList<QVariant> datas;
        datas<<QString("设备-%1").arg(i+1)<<QString("类型-%1").arg(i+1);

        // 主结点下挂两个子节点
        TreeItem *primary=new TreeItem(datas,parent);
        parent->appendChild(primary);

        for(int j=0;j<2;j++)
        {
            QList<QVariant> ds;
            ds<<QString("子设备-%1").arg(j+1)<<QString("子类型-%1").arg(j+1);

            primary->appendChild(new TreeItem(ds,primary));
        }
    }
}
