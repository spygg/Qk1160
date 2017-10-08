#ifndef QSETTINGMETHODFORM_H
#define QSETTINGMETHODFORM_H

#include <QWidget>
#include <QTextCodec>
#include <QScrollBar>
#include <qdatabasequery.h>
#include "qmlabel.h"
#include "qlistgui.h"
#include "NetSource/simplenetwork.h"
#include "NetSource/NetDataCode.h"
#include "NetSource/NetControl.h"

namespace Ui {
class QSettingMethodForm;
}

class QSettingMethodForm : public QWidget
{
    Q_OBJECT

public:
    explicit QSettingMethodForm(QWidget *parent = 0);
    ~QSettingMethodForm();
    void StartSendFile();
    void Senddata();
    void updatedatabase();
    bool m_bDataDNOFalg;
    bool m_bSendFileFalg;
    int m_iIndex;
    int m_iLen;
private:
    void InitOCX();
    void InitSings();
    void cleandata();
    void settableview(QStringList &strdata);
private slots:
    void xiaohuaguan();
    void jieshoubei();
    void on_pb_settingmethod_save_clicked();

    void on_pb_settingmethod_add_clicked();

    void on_pb_settingmethod_delete_clicked();

    void on_tb_method_param_doubleClicked(const QModelIndex &index);

    void on_tb_method_param_clicked(const QModelIndex &index);
    void SendFileInfo();
    void on_pb_settingmethod_colud_clicked();
    bool checkname(QString strName);

    void on_cb_settingmethod_zhengliudanwei_currentIndexChanged(int index);

private:
    bool        m_bjieshoubei;
    bool        m_bxiaohuaguan;
    bool        m_bfromview;
    QStringList linstname;
    QStringList linstvalues;
    QString     strtable;
    QDatabasequery *pdataquery;
    QMLabel     *m_pLbjieshoubei;
    QMLabel     *m_pLbxiaohuaguan;
    ListModel   *m_ItemModel;

    NetControl  *m_pNetControl;
    QStringList m_strFileList;
    QString     m_strexpress;
    Ui::QSettingMethodForm *ui;
    QTextCodec  *m_ptc;
    int m_RemFileSize;
    QFile m_File;
};

#endif // QSETTINGMETHODFORM_H
