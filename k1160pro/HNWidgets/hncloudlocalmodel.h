#ifndef QCLOUDLOCALMODEL_H
#define QCLOUDLOCALMODEL_H

#include "hnstandarditemmodel.h"
#include "hnclient.h"

class HNCloudLocalModel : public HNStandardItemModel
{
    Q_OBJECT
public:
    explicit HNCloudLocalModel(QObject *parent = 0);

    void queryRootDirs();
    void queryFiles(QString code);
    void uploadFile(QString code, QString path, QString filename, int len);

protected:
    QStandardItem *findDirByCode(QString code);

signals:
    void sigQueryRootDirSuccess();
private slots:
    void slotUploadSuccess();
public slots:
private:
    HNClient* m_client;
    QString m_path;
    QString m_filename;
};

#endif // QCLOUDLOCALMODEL_H
