#include "qlistgui.h"




ReadOnlyDelegate::ReadOnlyDelegate(QObject *parent): QItemDelegate(parent)
{

}


ReadOnlyDelegate::~ReadOnlyDelegate()
{

}


QWidget *ReadOnlyDelegate::createEditor(QWidget*parent, const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    return NULL;
}



IDDelegate::IDDelegate(QObject *parent): QItemDelegate(parent)
{

}
IDDelegate::~IDDelegate()
{

}


QWidget *IDDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    QRegExp regExp("^-?(100|1?[0-9]?\\d(\\.\\d{1,6})?)$");
    editor->setValidator(new QRegExpValidator(regExp, parent));
    return editor;
}

void IDDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(text);
}


void IDDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
    const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString text = lineEdit->text();
    model->setData(index, text, Qt::EditRole);
}
void IDDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}


TestDelegate::TestDelegate(QObject *parent): QItemDelegate(parent)
{
     m_ptc =  QTextCodec::codecForName("UTF-8");
}

TestDelegate::~TestDelegate()
{

}

QWidget *TestDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->addItem(m_ptc->toUnicode("空白"));
    editor->addItem(m_ptc->toUnicode("样品"));
    return editor;
}
void TestDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    int tindex = comboBox->findText(text);
    comboBox->setCurrentIndex(tindex);
}
void TestDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
    const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString text = comboBox->currentText();
    model->setData(index, text, Qt::EditRole);
}
void TestDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}


 ListModel::ListModel(QObject *parent) : QStandardItemModel(parent)
 {

 }

 ListModel::~ListModel()
 {

 }


 ListModel::ListModel(int row, int column, QObject *parent=NULL)
    : QStandardItemModel(row, column, parent)
 {

 }



QVariant ListModel::data(const QModelIndex &index, int role = Qt::DisplayRole)
{
    if( Qt::TextAlignmentRole == role )
        return Qt::AlignCenter;
    return QStandardItemModel::data(index, role);
}


NameDelegate::NameDelegate(QObject *parent)
{

}

NameDelegate::~NameDelegate()
{

}

QWidget *NameDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    //QRegExp regExp("^-?(100|1?[0-9]?\\d(\\.\\d{1,6})?)$");
    //editor->setValidator(new QRegExpValidator(regExp, parent));
    editor->setMaxLength(26);
    return editor;
}

void NameDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(text);
}


void NameDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
    const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString text = lineEdit->text();
    model->setData(index, text, Qt::EditRole);
}
void NameDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
