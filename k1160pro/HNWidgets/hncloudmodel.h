#ifndef QCLOUDMODEL_H
#define QCLOUDMODEL_H

#include "hnstandarditemmodel.h"
#include "hnclient.h"
#include "hnprogressdialog.h"

class HNCloudModel : public HNStandardItemModel
{
    Q_OBJECT
public:
    explicit HNCloudModel(QObject *parent = 0);

signals:
    void sigQueryRootDirSuccess();
public slots:
    // 用户不可以创建文件夹
    void  queryRootDirs();
    // 查询文件
    void queryFiles(QString code = "001");
    void downFile(QString path, QString id, QString tmpfile);
    void delFile(QString code, QString id);

private slots:
    void slotDownSuccess();
    void slotCancelDown();
    void queryRootDirsResult();
    void queryFilesResult();
private:
    QStandardItem* findDirByCode(QString code);

private:
    HNClient* m_client;
    QString m_path, m_servname, m_localname;
};

#endif // QCLOUDMODEL_H
