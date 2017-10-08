#include "hncloudmodel.h"
#include "HNDefine.h"
#include "qdir.h"
#include "qfileinfo.h"
#include "hnmsgbox.h"

HNCloudModel::HNCloudModel(QObject *parent) :
    HNStandardItemModel(parent)
{
    setColumnCount(FILE_MAX);
    m_client = HNClientInstance(this);
    connect(m_client, SIGNAL(signalListDirOK()), this, SLOT(queryRootDirsResult()));
    connect(m_client, SIGNAL(signalListFileOK()), this, SLOT(queryFilesResult()));
    connect(m_client, SIGNAL(signalLoginSucc()), this, SLOT(queryRootDirs()));
    connect(m_client, SIGNAL(signalDownSucc()), this, SLOT(slotDownSuccess()));
    connect(m_client, SIGNAL(signalCancelDown()), this, SLOT(slotCancelDown()));
}

void HNCloudModel::queryRootDirs()
{
    m_client->sendListDirectory();
}

void HNCloudModel::queryFiles(QString code)
{
    m_client->sendListFiles(code);
}

void HNCloudModel::downFile(QString path, QString id, QString tmpfile)
{
    m_path = path;
    m_servname = tmpfile;
    m_localname = tmpfile.split("_").at(1);
    pline() << m_path << m_servname << m_localname;
    QString localname = path + "/" + tmpfile;
    m_client->sendDownDevFiles(id, localname);
}

void HNCloudModel::delFile(QString code, QString id)
{
    m_client->sendDelFile(code, id);
}

void HNCloudModel::slotDownSuccess()
{
    QString downedFile = m_servname;
    QString localname = QString("%1/%2").arg(m_path).arg(m_localname);
    pline() << "down ok" << downedFile << localname;
    system(QString("mv %1 %2").arg(downedFile).arg(localname).toAscii().data());
}

void HNCloudModel::slotCancelDown()
{
    QString tmpfile = m_servname;
    if(tmpfile.isEmpty())
        return;
    pline() << "cancel" << tmpfile;
    QFile::remove(tmpfile);
    system(QString("rm %1").arg(tmpfile).toAscii().data());
}

void HNCloudModel::queryRootDirsResult()
{
    QTCloudListDirResult r = m_client->GetDirList();
    _QTCloudListDirResult _r;
    removeRows(0, rowCount());
    int row = 0;
    foreach (_r, r.m_dir) {
        insertRows(row, 1);
        if("Method" == _r.m_name)
            setData(index(row, DIR_NAME), tr("Method"));
        else if("Data" == _r.m_name)
            setData(index(row, DIR_NAME), tr("Data"));
        setData(index(row, DIR_CODE), _r.m_code);
        if("001" == _r.m_code)
            setData(index(row, DIR_PATH), DB_METHOD_PATH);
        else if("002" == _r.m_code)
            setData(index(row, DIR_PATH), DB_DATA_PATH);
        row++;
    }
    submit();
    emit sigQueryRootDirSuccess();
}

void HNCloudModel::queryFilesResult()
{
    QTCloudListFileResult r = m_client->GetListedFiles();
    _QTCloudListFileResult _r;

    QStandardItem* dir = findDirByCode(r.m_code);
    if(NULL == dir)
        return;
    dir->removeRows(0, dir->rowCount());
    dir->setColumnCount(FILE_MAX);
    dir->setRowCount(0);
    int row = 0;
    foreach (_r, r.m_file) {
        dir->insertRows(row, 1);
        setData(dir->index().child(row, FILE_NAME), _r.m_name);
        setData(dir->index().child(row, FILE_ID), _r.m_id);
        setData(dir->index().child(row, FILE_SIZE), _r.m_size);
        setData(dir->index().child(row, FILE_DATE), _r.m_date);
        row++;
    }
    submit();
}

QStandardItem *HNCloudModel::findDirByCode(QString code)
{
    for(int i = 0; i < rowCount(); i++)
    {
        if(data(index(i, 1)).toString() == code)
            return item(i, 0);
    }
    return NULL;
}
