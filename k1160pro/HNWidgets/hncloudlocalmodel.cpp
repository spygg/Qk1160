#include "hncloudlocalmodel.h"
#include "HNDefine.h"
#include <QDir>
#include <QFileInfo>

HNCloudLocalModel::HNCloudLocalModel(QObject *parent) :
    HNStandardItemModel(parent)
{
    setColumnCount(DIR_MAX);
    queryRootDirs();
    m_client = HNClientInstance(this);
    connect(m_client, SIGNAL(signalUploadSucc()), this, SLOT(slotUploadSuccess()));
    connect(m_client, SIGNAL(signalCancelUpload()), this, SLOT(slotUploadSuccess()));
}

void HNCloudLocalModel::queryRootDirs()
{
    removeRows(0, rowCount());
    int row = 0;
    insertRows(row, 1);
    setData(index(row, DIR_NAME), tr("Method"));
    setData(index(row, DIR_CODE), "001");
    setData(index(row, DIR_PATH), DB_METHOD_PATH);
    row++;
    insertRows(row, 1);
    setData(index(row, DIR_NAME), tr("Data"));
    setData(index(row, DIR_CODE), "002");
    setData(index(row, DIR_PATH), DB_DATA_PATH);
    submit();
    emit sigQueryRootDirSuccess();
}

void HNCloudLocalModel::uploadFile(QString code, QString path, QString filename, int len)
{
    m_path = path;
    m_filename = filename;
    QString localname = path + "/" + filename;
    m_client->sendUploadFile(code, filename, localname);
}

void HNCloudLocalModel::queryFiles(QString code)
{
    QString path;
    if(code == "001")
        path = (QString("%1/Method").arg(DB_PATH));
    else if (code == "002")
        path = (QString("%1/Data").arg(DB_PATH));

    //判断路径是否存在
    QDir plot_dir(path);
    if(!plot_dir.exists())
        return;
    plot_dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList list = plot_dir.entryInfoList();

    int file_count = list.count();
    if(file_count <= 0)
        return;

    QStringList string_list;
    for(int i=0; i<file_count; i++)
    {
        QFileInfo file_info = list.at(i);
        QString suffix = file_info.suffix();
        if(QString::compare(suffix, QString("db"), Qt::CaseInsensitive) == 0)
        {
            QString path = file_info.fileName();
            string_list.append(path);
        }
    }

    QStandardItem* dir = findDirByCode(code);
    if(NULL == dir)
        return;
    dir->removeRows(0, dir->rowCount());
    dir->setColumnCount(FILE_MAX);
    dir->setRowCount(0);
    int row = 0;
    QString string_file;
    foreach (string_file, string_list) {
        dir->insertRows(row, 1);
        setData(index(row, FILE_NAME, dir->index()), string_file);
        setData(dir->index().child(row, FILE_ID), 0);
        setData(dir->index().child(row, FILE_SIZE), 0);
        setData(dir->index().child(row, FILE_DATE), 0);
        row++;
    }
    submit();
}

QStandardItem *HNCloudLocalModel::findDirByCode(QString code)
{
    for(int i = 0; i < rowCount(); i++)
    {
        if(data(index(i, 1)).toString() == code)
            return item(i, 0);
    }
    return NULL;
}

void HNCloudLocalModel::slotUploadSuccess()
{
    QString localfile = QString("%1/%2").arg(m_path).arg(m_filename);
    QFile::remove(localfile);
}
