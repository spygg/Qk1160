#ifndef QAUTOTEST_H
#define QAUTOTEST_H

#include <QWidget>
#include <QTextCodec>
#include <QList>
#include <qdatabasequery.h>
#include "DataDef.h"
#include "qmlabel.h"
#include "qpicifrom.h"
#include "qautotestaprocessform.h"

namespace Ui {
class QAutoTest;
}

class QAutoTest : public QWidget
{
    Q_OBJECT

public:
    explicit QAutoTest(QWidget *parent = 0);
    ~QAutoTest();
    void SetState(bool bFlag);
    bool GetState();
    void updatabase();
    QString GetUserName();
    void UpData();
private:
    void InitOCX();
    void InitOCXData();
    void InitComboxData();
    void InitSings();
private slots:
    void AutoTestDlg();
    void ManualTestDlg();
    void CleanDlg();
    void UpTestData(int index);
    void on_pb_autotest_pici_clicked();
    void AnalysisData(QByteArray pData);
    void StateSensor(QByteArray pData);

    void on_pb_autotest_start_clicked();

    void on_cb_autotest_ceshileixing_currentIndexChanged(int index);

    void on_cb_autotest_jieguoleixing_currentIndexChanged(int index);

    void on_cb_autotest_yangpinliang_currentIndexChanged(int index);
    void on_cb_autotest_fangfamingcheng_currentIndexChanged(const QString &arg1);

public:
    QList<TestData *> m_pListTestData;
    QList<TestMethod *> m_pListTestMethod;
    bool    m_bpiciFlag;
    int        m_iIndex;
private:
    QPiciFrom *m_pPici;
    QAutoTestaProcessForm *m_pTestPro;
    Ui::QAutoTest *ui;
    QMLabel     *m_pLbAutoTest;
    QMLabel     *m_pLbManualTest;
    QMLabel     *m_pLbClean;
    QMLabel     *m_pLbxiaohuaguanpaifei;
    QMLabel     *m_pLbjieshoubeipaifei;

    QMLabel     *m_pLbfeiyetong;
    QMLabel     *m_pLbdidingsuantong;
    QMLabel     *m_pLbpengsuantong;
    QMLabel     *m_pLbjiantong;
    QMLabel     *m_pLbshuitong;
    QMLabel     *m_pLblengningshui;
    QMLabel     *m_pLbzhengqifashengqi;
    QMLabel     *m_pLbzhengqifashengqiyewei;
    QMLabel     *m_pLbanquanmen;
    QMLabel     *m_pLbxiaohuaguan;
    QDatabasequery *pdataquery;
    QStringList linstname;
    QStringList linstvalues;
    QString     strtable;
    QStringList strlist;
    QTextCodec  *m_ptc;
    bool m_bRunFlag;
public:
    QByteArray  m_Serialcmd;
    QByteArray  m_Serialdata;
    QSerialProtcol *m_pSerialAuto;
};

#endif // QAUTOTEST_H
