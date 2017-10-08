#ifndef QSETTINGCLEANFORM_H
#define QSETTINGCLEANFORM_H

#include <QWidget>
#include <QTextCodec>
#include "qmlabel.h"
#include "Serial/qserialprotcol.h"

namespace Ui {
class QSettingCleanForm;
}

class QSettingCleanForm : public QWidget
{
    Q_OBJECT

public:
    explicit QSettingCleanForm(QWidget *parent = 0);
    ~QSettingCleanForm();
private:
    void InitOCX();
    void InitSings();
    void PushData();
private slots:
    void zijian();
    void on_pb_settingclean_save_clicked();

public:
    QSerialProtcol *m_pSerialSettingClean;
private:
    bool        m_bzijian;
    QByteArray  m_Serialcmd;
    QByteArray  m_Serialdata;
    QMLabel     *m_plbzijian;
    Ui::QSettingCleanForm *ui;
    QTextCodec  *m_ptc;
};

#endif // QSETTINGCLEANFORM_H
