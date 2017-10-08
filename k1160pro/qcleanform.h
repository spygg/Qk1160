#ifndef QCLEANFORM_H
#define QCLEANFORM_H

#include <QWidget>
#include <QTextCodec>
#include "qmlabel.h"
#include "Serial/qserialprotcol.h"

namespace Ui {
class QCleanForm;
}

class QCleanForm : public QWidget
{
    Q_OBJECT

public slots:
    void AnalysisData(QByteArray pData);
public:
    explicit QCleanForm(QWidget *parent = 0);
    ~QCleanForm();
private slots:
    void jieshoubei();
    void huansuan();
    void pengsuan();
    void xiaohuaguan();
    void jianguan();
    void yiqi();
    void on_pb_clean_start_clicked();

private:
    void InitOCX();
    void InitSings();
private:
    bool        m_bFlag;
    QByteArray  m_Serialcmd;
    QByteArray  m_Serialdata;
    QMLabel     *m_pLbjieshoubei;
    QMLabel     *m_pLbhuansuan;
    QMLabel     *m_pLbpengsuan;
    QMLabel     *m_pLbxiaohuaguan;
    QMLabel     *m_pLbjianguan;
    QMLabel     *m_pLbyiqi;
    bool        m_bjieshoubei;
    bool        m_bhuansuan;
    bool        m_bpengsuan;
    bool        m_bxiaohuaguan;
    bool        m_bjianguan;
    bool        m_byiqi;
    QTextCodec  *m_ptc;
    Ui::QCleanForm *ui;
public:
    QSerialProtcol *m_pSerialClean;
};

#endif // QCLEANFORM_H
