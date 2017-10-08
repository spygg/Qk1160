#include "hntreewidget.h"
#include "ui_hntreewidget.h"

HNTreeWidget::HNTreeWidget(QWidget *parent) :
    HNTreeView(parent),
    ui(new Ui::HNTreeWidget)
{
    ui->setupUi(this);

    m_fs = new HNFileSystem(this);
    m_model = new HNTreeModel(this, m_fs);
    setModel(m_model);

    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    header()->setResizeMode(QHeaderView::ResizeToContents);

#ifdef __MIPS_LINUX__
    setFocusPolicy(Qt::NoFocus);
#endif

    QFont fnt(font());
    fnt.setPointSize(16);
    setFont(fnt);

#if 0
    //关于选中项的颜色，暂且按照默认，后来更改整体UI颜色和效果
    //可以实现橙色一行选中
    //肯定也能实现表头透明和Hanon效果。
    QFile styleFile("://HNWidgets.qss");
    styleFile.open(QIODevice::ReadOnly);
    QString styleString(styleFile.readAll());;
    setStyleSheet(styleString);
    styleFile.close();
#endif


    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(clicked(QModelIndex)));
    connect(this->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(currentRowChanged()));
}

HNTreeWidget::~HNTreeWidget()
{
    delete ui;
}

void HNTreeWidget::query(QString path)
{
    QString file;
    m_fs->parse(path, m_prot, file);
    m_model->query(path);
    for(int i = 0; i < FILE_MAX; i++)
        m_model->setHeaderData(i, Qt::Horizontal, "");
    for(int i = 1; i < FILE_MAX; i++)
        setColumnHidden(i, true);
}

void HNTreeWidget::removeRow()
{
    QModelIndex curIndex = currentIndex();
    QModelIndex parIndex = curIndex.parent();

    if(!curIndex.isValid())
        return;

    m_model->removeRow(curIndex.row(), parIndex);
}

void HNTreeWidget::currentRowChanged()
{
    QModelIndex curIndex = currentIndex();
    QModelIndex parIndex = curIndex.parent();

    if(!curIndex.isValid())
        return;

    //根据是否文件夹进行判断
    if(parIndex.isValid())
        return;

        QString path = m_model->index(curIndex.row(), FILE_FILEPATH, parIndex).data().toString();
        pline() << m_prot << path;
        query(QString("%1%2").arg(m_prot).arg(path));

        //expand(curIndex);
}

void HNTreeWidget::clicked(QModelIndex)
{
    QModelIndex curIndex = currentIndex();
    QModelIndex parIndex = curIndex.parent();

    if(!curIndex.isValid())
        return;

    //根据是否文件夹进行判断
    if(parIndex.isValid())
        return;

    QString type = m_model->index(curIndex.row(), FILE_TYPE, parIndex).data().toString();

    pline() << type;

    if(type == "dir")
    {
        if(isExpanded(curIndex))
            collapse(curIndex);
    else
            expand(curIndex);
    }
}
