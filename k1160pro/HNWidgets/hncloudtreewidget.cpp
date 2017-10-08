#include "hncloudtreewidget.h"
#include "ui_hncloudtreewidget.h"
#include <QFileInfo>
#include <QFile>
#include "HNDefine.h"
#include "hnprinter.h"
#include "hnclient.h"
#include "hnmsgbox.h"

HNCloudTreeWidget::HNCloudTreeWidget(QWidget *parent) :
    HNCloudTreeView(parent),
    ui(new Ui::HNCloudTreeWidget)
{
    ui->setupUi(this);
    m_client = HNClientInstance(this);
    connect(m_client, SIGNAL(connected()), this, SLOT(slotConnected()));
    model = new HNCloudModel(this);
    setModel(model);

    setColumnHidden(FILE_ID, true);
    setColumnHidden(FILE_SIZE, true);
    setColumnHidden(FILE_DATE, true);

    m_box = new HNMsgBox(this);

    QFont cloudFont = this->font();
    cloudFont.setPointSize(16);
    setFont(cloudFont);
    connect(this->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(currentRowChanged()));

    m_progDown = new HNProgressDialog(this);

    connect(m_client, SIGNAL(signalUpdateProgress(int)),
            m_progDown, SLOT(setValue(int)));
    connect(m_client, SIGNAL(signalDownSucc()),
            m_progDown, SLOT(accept()));
    connect(m_progDown, SIGNAL(rejected()),
            m_client, SLOT(sendCancelDown()));

    //connect(m_client, SIGNAL(signalDownSucc()),
    //        this, SLOT(slotDownSuccess()));
    //connect(m_client, SIGNAL(signalCancelDown()),
    //        this, SLOT(slotDownSuccess()));
}

HNCloudTreeWidget::~HNCloudTreeWidget()
{
    delete ui;
}

void HNCloudTreeWidget::slotConnect(){
    m_box->warning(tr("Connecting..."));
    m_client->SendConnectMessage();
}

void HNCloudTreeWidget::slotConnected()
{
    m_box->accept();
    //m_client->sendLoginMessage();
}

void HNCloudTreeWidget::slotDisConnect(){
    //m_client->sendLogoutMessage();
    m_client->SendDisConnectFromHost();
}

void HNCloudTreeWidget::downFile()
{
    QModelIndex curIndex = currentIndex();
    QModelIndex parIndex = curIndex.parent();
    if(!parIndex.isValid())
        return;
    QString path = model->index(parIndex.row(), DIR_PATH).data().toString();
    QString fileid = model->index(curIndex.row(), FILE_ID, parIndex).data().toString();
    QString filename = model->index(curIndex.row(), FILE_NAME, parIndex).data().toString();
    QString localname = filename.split("_").at(1);
    m_localfile = QString("%1/%2").arg(path).arg(localname);
    m_tmpfile = QString("%1/%2").arg(path).arg(filename);
    model->downFile(path, fileid, m_tmpfile);
    m_progDown->initAll();
    m_progDown->show();
}

void HNCloudTreeWidget::delFile()
{
    QModelIndex curIndex = currentIndex();
    QModelIndex parIndex = curIndex.parent();
    if(!parIndex.isValid())
        return;
    QString code = model->index(parIndex.row(), DIR_CODE).data().toString();
    QString fileid = model->index(curIndex.row(), FILE_ID, parIndex).data().toString();
    pline() << code << fileid;
    model->delFile(code, fileid);
}

void HNCloudTreeWidget::slotDownSuccess()
{
    if(QDialog::Accepted == m_progDown->result() )
        HNMsgBox::warning(this, "Download Success");
    else
        HNMsgBox::warning(this, "Download Canceled");
}

void HNCloudTreeWidget::currentRowChanged()
{
    QModelIndex curIndex = currentIndex();
    QModelIndex parIndex = curIndex.parent();
    if(!parIndex.isValid())
        model->queryFiles(model->index(curIndex.row(), DIR_CODE).data().toString());
    expand(curIndex);
}
