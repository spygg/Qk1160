#ifndef QCHECKFROM_H
#define QCHECKFROM_H

#include <QWidget>
#include <QTimer>
#include <QTextCodec>
#include "qmainscreen.h"
#include "Serial/qserialprotcol.h"

namespace Ui {
class QCheckFrom;
}

class QCheckFrom : public QWidget
{
    Q_OBJECT

public:
    QCheckFrom(QWidget *parent = 0);
    QCheckFrom(QWidget *parent = 0, QWidget *parent1 = 0);
    ~QCheckFrom();

private:
    void InitOCX();
    void StateProcess(QByteArray pData);
    void StateResualt(QByteArray pData);
private:
    QByteArray  m_Serialcmd;
    QByteArray  m_Serialdata;
    QMainScreen *m_pScreen;
    QTextCodec  *m_ptc;
    Ui::QCheckFrom *ui;
    QTimer       *m_pCheckProcessTimer;
public:
    QSerialProtcol *m_pSerialCheckopro;
public slots:
    void AnalysisData(QByteArray pData);
    void CheckStateShow();
};

#endif // QCHECKFROM_H
