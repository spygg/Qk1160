#ifndef HNTABLEWIDGET_H
#define HNTABLEWIDGET_H

#include "hntableview.h"
#include "hntablemodel.h"

namespace Ui {
class HNTableWidget;
}

class HNTableWidget : public HNTableView
{
    Q_OBJECT

public:
    explicit HNTableWidget(QWidget *parent = 0);
    ~HNTableWidget();

    void setDB(QString db = "");
    void setTable(QString table);
    void query(QString excp = "");
    //在TableWidget中，删除的行肯定是选中的行，设定
    void removeRow(int row);
    void removeRows(int column, QList<QStringList> ids);

    void selectedRows(int column, QMap<int, QStringList>& ids);
private:
    Ui::HNTableWidget *ui;
    HNTableModel* m_model;
    QSqlDatabase m_db;
};

#endif // HNTABLEWIDGET_H
