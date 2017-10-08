#ifndef QLISTGUI_H
#define QLISTGUI_H
#include <QtGui>
#include <QLineEdit>
#include <QComboBox>
#include <QItemDelegate>
#include <QTextCodec>

class ReadOnlyDelegate : public QItemDelegate
{
    Q_OBJECT
public:
   explicit ReadOnlyDelegate(QObject *parent = 0);
    ~ReadOnlyDelegate();
    QWidget *createEditor(QWidget*parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;
};


//利用QLineEdit委托和正则表达式对输入进行限制
class IDDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    IDDelegate(QObject *parent = 0);
    ~IDDelegate();
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const;
};


//利用QLineEdit委托和正则表达式对输入进行限制
class NameDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    NameDelegate(QObject *parent = 0);
    ~NameDelegate();
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class TestDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    TestDelegate(QObject *parent = 0);
    ~TestDelegate();
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QTextCodec  *m_ptc;

};



//代理类，把所有单元格中的字符居中显示
class ListModel : public QStandardItemModel
{
    Q_OBJECT
public:
    ListModel(QObject *parent=NULL);
    ListModel(int row, int column, QObject *parent);
    ~ListModel();
    QVariant data(const QModelIndex &index, int role);

};

#endif // QLISTGUI_H
