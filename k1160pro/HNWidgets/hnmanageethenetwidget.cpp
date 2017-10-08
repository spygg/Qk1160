#include "hnmanageethenetwidget.h"
#include "ui_hnmanageethenetwidget.h"

HNManageEthenetWidget::HNManageEthenetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNManageEthenetWidget)
{
    ui->setupUi(this);
    connect(HNEthManager::Instance(), SIGNAL(sigConnected()), this, SLOT(wifiConnected()));
    connect(HNEthManager::Instance(), SIGNAL(sigDisConnected()), this, SLOT(wifiDisConnected()));
    connect(HNEthManager::Instance(), SIGNAL(sigLanConnected()), this, SLOT(netChanged()));
    connect(HNEthManager::Instance(), SIGNAL(sigLanDisConnected()), this, SLOT(netChanged()));
}

HNManageEthenetWidget::~HNManageEthenetWidget()
{
    delete ui;
}

void HNManageEthenetWidget::initAll()
{
    QString ip, mask, gw, dns;
    HNEthManager::Instance()->getAddr(ip, mask, gw, dns);
    ui->lineEdit_ip->setText(ip);
    ui->lineEdit_mask->setText(mask);
    ui->lineEdit_gateway->setText(gw);
    ui->lineEdit_dns->setText(dns);

    QSettings setting;
    int bCheked = false;
    bCheked = setting.value("EnableDHCP").toInt();
    ui->chk_dhcp->setChecked(bCheked);
}

void HNManageEthenetWidget::netChanged()
{
    QString netName;
    if("Wired Lan" == HNEthManager::Instance()->currentNetName())
    {
        netName = tr("Current:Wired Lan");
        ui->tableView_Wifi->setEnabled(false);
    }
    else
    {
        netName = tr("Current:%1").arg(HNEthManager::Instance()->currentNetName());
        ui->tableView_Wifi->setEnabled(true);
    }
    ui->label->setText(netName);

}

void HNManageEthenetWidget::wifiConnected()
{

}

void HNManageEthenetWidget::wifiDisConnected()
{

}

void HNManageEthenetWidget::on_btn_saveip_clicked()
{
    HNEthManager::Instance()->setAddr(ui->lineEdit_ip->text(), ui->lineEdit_mask->text(),
                                              ui->lineEdit_gateway->text(), ui->lineEdit_dns->text());
    HNEthManager::Instance()->ipconfig();
}

void HNManageEthenetWidget::on_chk_dhcp_stateChanged(int arg1)
{
    QSettings setting;
    setting.setValue("EnableDHCP", arg1);
    setting.sync();

    bool bChecked = arg1?true:false;
    HNEthManager::Instance()->setDHCP(bChecked);
    ui->lineEdit_ip->setDisabled(bChecked);
    ui->lineEdit_mask->setDisabled(bChecked);
    ui->lineEdit_gateway->setDisabled(bChecked);
    ui->lineEdit_dns->setDisabled(bChecked);
}
