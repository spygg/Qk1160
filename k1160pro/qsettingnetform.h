#ifndef QSETTINGNETFORM_H
#define QSETTINGNETFORM_H

#include <QWidget>
#include <QTextCodec>
#include "qmlabel.h"
#include "hnwifiwidget.h"

namespace Ui {
class QSettingNetForm;
}

class QSettingNetForm : public QWidget
{
    Q_OBJECT

public:
    explicit QSettingNetForm(QWidget *parent = 0);
    ~QSettingNetForm();
private slots:
    void on_pb_zhixing_clicked();
private slots:
    void dhcp();
    void NetChanged();
private:
    void InitOCX();
    void InitSings();
private:
    HNEthManager *m_pwifiManager;
    QMLabel *m_pDHCP;
    QMLabel *m_pDHCPText;
    bool    m_bDHCP;
    Ui::QSettingNetForm *ui;
    QTextCodec  *m_ptc;
};

#endif // QSETTINGNETFORM_H
