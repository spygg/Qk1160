#ifndef QSETTINGMACHINEFORM_H
#define QSETTINGMACHINEFORM_H

#include <QWidget>
#include <QTextCodec>
#include "qmlabel.h"
#include "qdatabasequery.h"
#include "Serial/qserialprotcol.h"

namespace Ui {
class QSettingMachineForm;
}

class QSettingMachineForm : public QWidget
{
    Q_OBJECT

public:
    explicit QSettingMachineForm(QWidget *parent = 0);
    ~QSettingMachineForm();
private:
    void InitOCX();
    void InitSings();
    void setxishu();
private slots:
    void jiandan();
    void xiangxi();
    void zijian();
    void lengningshui();
    void on_pb_setttingmatchine_save_clicked();

    void on_dial_year_rangeChanged(int min, int max);

    void on_dial_year_valueChanged(int value);

    void on_dial_month_valueChanged(int value);

    void on_dial_day_valueChanged(int value);

    void on_dial_hour_valueChanged(int value);

    void on_dial_muit_valueChanged(int value);

    void on_dial_second_2_valueChanged(int value);

    void on_cb_setttingmatchine_fangfaxishu_currentIndexChanged(int index);

    void on_le_settingmachine_xishu_textChanged(const QString &arg1);

    void on_btnComplex_clicked();

    void on_btnJiandan_clicked();

private:
    bool        m_bjiandan;
    bool        m_bxiangxi;
    bool        m_bzijian;
    bool        m_blengningshui;
    bool        m_bsuyuanfangfaxishu;
    bool        m_bsuyuandingbiaoxishu;
    int         m_isuyuanfangfaxishu;

    QMLabel     *m_plbjiandan;
    QMLabel     *m_plbxiangxi;
    QMLabel     *m_plbzijian;
    QMLabel     *m_plblengningshui;

    QStringList linstname;
    QStringList linstvalues;
    QDatabasequery *pdataquery;

    Ui::QSettingMachineForm *ui;
    QTextCodec  *m_ptc;
    QSerialProtcol *m_pSerial;
    QByteArray  m_Serialcmd;
    QByteArray  m_Serialdata;
};

#endif // QSETTINGMACHINEFORM_H
