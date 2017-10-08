#ifndef QMANUALTESTFORM_H
#define QMANUALTESTFORM_H

#include <QWidget>
#include <QTextCodec>
#include <qdatabasequery.h>
#include "qmlabel.h"
#include "Serial/qserialprotcol.h"

namespace Ui {
class QManualTestForm;
}

class QManualTestForm : public QWidget
{
    Q_OBJECT

public:
    explicit QManualTestForm(QWidget *parent = 0);
    ~QManualTestForm();
private:
    void InitOCX();
    void InitSings();
    void StateSensor(QByteArray pData);
    bool checkusername(QString strname);
private slots:
    void xiaohuaguan();
    void jieshoubei();

    void checknum(QString strNum);
    void checkpengsuan();
    void checkjian();
    void checkxishishui();
    void checkdiding();
    void checkzhengliu();
    void on_pb_manualtest_1_clicked();

    void on_pb_manualtest_2_clicked();

    void on_pb_manualtest_3_clicked();

    void on_pb_manualtest_4_clicked();

    void on_pb_manualtest_5_clicked();

    void on_pb_manualtest_6_clicked();

    void on_pb_manualtest_7_clicked();

    void on_pb_manualtest_8_clicked();

    void on_pb_manualtest_9_clicked();

    void on_pb_manualtest_0_clicked();

    void on_pb_manualtest_c_clicked();

    void on_pb_manualtest_ok_clicked();

    void on_pb_manualtest_clean_clicked();
    void on_pb_manualtest_save_clicked();

public slots:
    void AnalysisData(QByteArray pData);
private:
    Ui::QManualTestForm *ui;
    QTextCodec  *m_ptc;
    QDatabasequery *pdataquery;
    QStringList linstname;
    QStringList linstvalues;
    QString     strtable;
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

    QMLabel     *m_pLbjieshoubeoonoff;
    QMLabel     *m_pLbxiaohuaguanonoff;

    QMLabel     *m_plbcheckpengsuan;
    QMLabel     *m_plbcheckxishishui;
    QMLabel     *m_plbcheckdiding;
    QMLabel     *m_plbcheckjian;
    QMLabel     *m_plbcheckzhengliu;

    bool        m_blbcheckpengsuan;
    bool        m_blbcheckxishishui;
    bool        m_blbcheckdiding;
    bool        m_blbcheckjian;
    bool        m_blbcheckzhengliu;

    bool        m_bxiaohuaguanflag;
    bool        m_bjieshoubeiflag;
    QByteArray  m_Serialcmd;
    QByteArray  m_Serialdata;
public:
    QSerialProtcol *m_pSerialManual;
    bool m_brunning;
};

#endif // QMANUALTESTFORM_H
