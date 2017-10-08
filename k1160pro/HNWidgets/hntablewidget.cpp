#include "hntablewidget.h"
#include "ui_hntablewidget.h"
#include "HNDefine.h"
#include "hngui-qt.h"

HNTableWidget::HNTableWidget(QWidget *parent) :
    HNTableView(parent),
    ui(new Ui::HNTableWidget)
{
    ui->setupUi(this);
    m_db = newDatabaseConn();
    m_model = new HNTableModel(this, m_db);
    setModel(m_model);
    //如果没有这个函数，程序存在启动崩溃的情况。
    setItemDelegate(new QSqlRelationalDelegate(this));

    QFile styleFile("://HNWidgets.qss");
    styleFile.open(QIODevice::ReadOnly);
    QString styleString(styleFile.readAll());;
    horizontalScrollBar()->setStyleSheet(styleString);
    verticalScrollBar()->setStyleSheet(styleString);
    styleFile.close();

}

HNTableWidget::~HNTableWidget()
{
    delete ui;
}

void HNTableWidget::setDB(QString db)
{
    if(db.isEmpty())
    {
        closeDatabase(m_db);
        return;
    }

    setDatabaseName(m_db, db);
}

void HNTableWidget::setTable(QString table)
{
    m_model->setTable(table);
}

void HNTableWidget::query(QString excp)
{
    m_model->query(excp);
}

void HNTableWidget::removeRow(int row)
{
    m_model->removeRow(row);
    m_model->submit();
}

void HNTableWidget::removeRows(int column, QList<QStringList> ids)
{
    int rowCount = m_model->rowCount();
    int i = 0;
    while(i < rowCount)
    {
        QModelIndex idx = m_model->index(i, column);

        //经过删除，真实的rowCount后的index无效
        if(!idx.isValid())
            break;

        QString modelColValue = m_model->data(idx).toString();

        //在ids中找到列值相等的，针对row进行删除，i不变；
        QListIterator<QStringList> itor(ids);
        while(itor.hasNext())
        {
            QString colValue = itor.next().at(column);

            if(colValue == modelColValue)
            {
                removeRow(i); i--;
                break;
            }
        }
        i++;
    }
}

void HNTableWidget::selectedRows(int column , QMap<int, QStringList> &ids)
{
    QModelIndexList l = selectionModel()->selectedRows(column);
    QModelIndex idx;
    foreach (idx, l) {
        QStringList l;
        for(int i = 0; i < m_model->columnCount(); i++)
            l << m_model->index(idx.row(), i).data().toString();
        ids.insert(idx.row(), l);
    }
}
