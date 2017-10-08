#ifndef QSETTINGCALIBRATIONFORM_H
#define QSETTINGCALIBRATIONFORM_H

#include <QWidget>
#include <QTextCodec>
#include "qmlabel.h"
#include "Serial/qserialprotcol.h"
#include <QLineEdit>

namespace Ui {
class QSettingCalibrationForm;
}

class QSettingCalibrationForm : public QWidget
{
    Q_OBJECT

public:
    explicit QSettingCalibrationForm(QWidget *parent = 0);
    ~QSettingCalibrationForm();
private:
    void InitOCX();
    void InitSings();
    void zhusaibengfun(int index);
    void pengsuanfun(int index);
    void jianbengfun(int index);
    void xishishuifun(int index);
    void yansefun(int index);
    void yansejiaozhun(int index);
private slots:
    void zhusaibeng();
    void pengsuanbeng();
    void jianbeng();
    void xishishuibeng();
    void yansejieshouye();
    void yanse();
    void on_pb_next_clicked();

    void on_pb_back_clicked();
    void on_pb_1_clicked();

    void on_pb_5_clicked();

    void on_pb_10_clicked();

    void on_pb_jianhao_clicked();

    void on_pb_jiahao_clicked();

    void on_pb_baipingheng_clicked();

public:
    QSerialProtcol *m_pSerialSetCal;
private:
    QByteArray  m_Serialcmd;
    QByteArray  m_Serialdata;
    bool        m_bzhusaibeng;
    bool        m_bpengsuanbeng;
    bool        m_bjianbeng;
    bool        m_bxishishui;
    bool        m_byansejieshouye;
    bool        m_byanse;
    int         m_iIndex;
    int         m_iStep;
    bool        m_bstepFlag;
    QMLabel     *m_pLbzhusaibeng;
    QMLabel     *m_pLbpengsuanbeng;
    QMLabel     *m_pLbjianbeng;
    QMLabel     *m_pLbxishishuibeng;
    QMLabel     *m_pLbyansejieshouye;
    QMLabel     *m_pLbyanse;

    Ui::QSettingCalibrationForm *ui;
    QTextCodec  *m_ptc;
};

#endif // QSETTINGCALIBRATIONFORM_H
