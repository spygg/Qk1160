#ifndef QCLOUDFORM_H
#define QCLOUDFORM_H

#include <QWidget>
#include <QTextCodec>
#include <QStandardItemModel>
#include <QIcon>
#include "NetSource/simplenetwork.h"
#include "NetSource/NetDataCode.h"
#include "NetSource/NetControl.h"

namespace Ui {
class QCloudForm;
}

class QCloudForm : public QWidget
{
    Q_OBJECT

public:
    explicit QCloudForm(QWidget *parent = 0);
    ~QCloudForm();
    void RefreshTreeView();
    void RequestData();
    void writeFile(QByteArray parry, int isize);
private slots:
    void on_pb_dir_clicked();

    void on_treeView_pressed(const QModelIndex &index);

    void on_pb_downfile_clicked();

private:
    void InitOCX();
    void InitSings();
    void SearchDir();

private:
    int m_iFileIndex;
    QStandardItemModel  *m_pQStandardItemModel;
    QVector<DirList *> m_VectorDirList;
    QVector<FileList *> m_VectorFileList;
    QVector<DownFileList *> m_VectorDownFileList;

    NetControl  *m_pNetControl;
    QIcon       *m_iconfolder;
    QIcon       *m_iconfile;
    QStandardItemModel *   m_model;
    Ui::QCloudForm *ui;
    QTextCodec  *m_ptc;
    QByteArray  m_FileData;
    int     m_iFileNo;
    int     m_isize;
    bool    m_bfileFlag;
};

#endif // QCLOUDFORM_H
