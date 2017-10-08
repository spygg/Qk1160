#ifndef QHELPFORM_H
#define QHELPFORM_H

#include <QWidget>
#include "Serial/qserialprotcol.h"

namespace Ui {
class QHelpForm;
}

class QHelpForm : public QWidget
{
    Q_OBJECT

public:
    explicit QHelpForm(QWidget *parent = 0);
    ~QHelpForm();
private:
    void InitOCX();
    void InitSings();
private slots:
    void AnalysisData(QByteArray);
private:
    Ui::QHelpForm *ui;
    QSerialProtcol *m_pSerialDebug;
};

#endif // QHELPFORM_H
