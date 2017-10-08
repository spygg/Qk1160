#include "hnwifiwidget.h"
#include "ui_hnwifiwidget.h"
#include "hnlinux.h"
#include "HNDefine.h"
#include "HNDefine.h"
#include "hnmsgbox.h"

HNWIFIWidget::HNWIFIWidget(QWidget *parent) :
    HNWIFIView(parent),
    ui(new Ui::HNWIFIWidget)
{
    ui->setupUi(this);

    connect(this, SIGNAL(clicked(QModelIndex)),
            this, SLOT(clickWIFI()), Qt::QueuedConnection);
    m_pass = new HNPasswordDialog(this);

    m_model = new HNWIFIModel(this);
    setModel(m_model);
    for(int i = ESSID_TYPE; i < ESSID_MAX; i++)
        setColumnHidden(i, true);
    horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
    setColumnWidth(ESSID_STATUS, 40);
}

HNWIFIWidget::~HNWIFIWidget()
{
    delete ui;
}

void HNWIFIWidget::clickWIFI()
{
    QString name = m_model->data(m_model->index(currentIndex().row(), ESSID_NAME)).toString();
    QString encryt = m_model->data(m_model->index(currentIndex().row(), ESSID_ENCRYP)).toString();
    QString type = m_model->data(m_model->index(currentIndex().row(), ESSID_TYPE)).toString();
    QString mac = m_model->data(m_model->index(currentIndex().row(), ESSID_BSSID)).toString();

    HNEthManager::Instance()->setRefresh(false);
    do
    {
        if("YES" == encryt)
        {
            m_pass->setWifiName(name);
            if(HNPasswordDialog::Rejected == m_pass->exec())
                break;
        }

        bool ok = m_model->setCurrentWifi(mac, m_pass->wifiPwd());

        pline() << ok;

        if(!ok)
        {
            HNMsgBox::warning(this, tr("Password error"));
            break;
        }

        pline() << name << encryt << m_pass->wifiPwd();
    }while(0);
    HNEthManager::Instance()->setRefresh();
}

