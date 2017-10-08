#ifndef HNWIFIMODEL_H
#define HNWIFIMODEL_H

#include "hnstandarditemmodel.h"
#include "HNEthManager.h"

class HNWIFIModel : public HNStandardItemModel
{
    Q_OBJECT
public:
    explicit HNWIFIModel(QObject *parent = 0);

    TWifi currentWifi();
    bool setCurrentWifi(QString bssid_mac, QString password = "");

signals:

public slots:
    void wifiRefreshed();
private:
    HNEthManager* m_pManager;
};

#endif // HNWIFIMODEL_H
