#ifndef QAUTOTESTAPROCESSFORM_H
#define QAUTOTESTAPROCESSFORM_H

#include <QWidget>
#include <QTextCodec>
#include <QTimer>
#include "qmlabel.h"
#include "qdatabasequery.h"
#include "Serial/qserialprotcol.h"
#include "qcustomplot.h"

namespace Ui {
class QAutoTestaProcessForm;
}

class QAutoTestaProcessForm : public QWidget
{
    Q_OBJECT

public:
    explicit QAutoTestaProcessForm(QWidget *parent = 0);
    ~QAutoTestaProcessForm();
     void InitData();
     void InitSerial();
     void InitDiagram();
     void SetTextdata();
     bool GetState();
     void SetToDataBase();
private slots:
    //void realtimeDataSlot(double v0, double v1);
private slots:
    void on_pb_autotestpt_back_clicked();
    void on_pb_autotestpt_naoh_clicked();

private:
    void realtimeData(double v0, double v1);
    void InitOCX();
    void InitSings();
    void initCharts();
    void StateProcess(QByteArray pData);
    void StateZhengliu(QByteArray pData);
    void StateRGB(QByteArray pData);
    void StateSensor(QByteArray pData);
    void CalNitrogen();
    void AutoScroll();
    void loadInjection(const QString &  file );
    void AutoLine(double dLineV, double lineColor);
private:
    QStringList linstname;
    QStringList linstvalues;
    QString     strtable;
    QDatabasequery *pdataquery;

    Ui::QAutoTestaProcessForm *ui;
    QByteArray  m_Serialcmd;
    QByteArray  m_Serialdata;
    QByteArray  m_Buffer[5];
    qint32      m_iIndex;
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
    QTextCodec  *m_ptc;
    QTimer       *m_pProcessTimer;
    QTimer       *m_pStateTimer;
    QTimer       *m_pRGBTimer;
    QTimer       *m_pdataTimer;
    QString       m_strV;
    QCustomPlot *customPlot;
    QEvent      *pWheelUp;
    QEvent      *pWheelDown;
    bool        m_bIsFirst;
    int         m_iprFlag;
    bool        m_bRunning;
    double      m_dIndex;
    bool m_bback;
    double m_initPointKey;
    double m_pausePointKey;
    double m_lastPointKey;
    QString m_didingV;
public:
    QSerialProtcol *m_pSerialAutopro;
public slots:
    void AnalysisData(QByteArray pData);
    void SerialCal();
    void RGBState();
    void StateShow();
};

#endif // QAUTOTESTAPROCESSFORM_H
