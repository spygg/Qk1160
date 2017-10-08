#ifndef QSETTINGDEBUGFORM_H
#define QSETTINGDEBUGFORM_H

#include <QWidget>
#include <QTextCodec>
#include "qmlabel.h"
#include "Serial/qserialprotcol.h"

namespace Ui {
class QSettingDebugForm;
}

class QSettingDebugForm : public QWidget
{
    Q_OBJECT

public:
    explicit QSettingDebugForm(QWidget *parent = 0);
    ~QSettingDebugForm();
private:
    void    StateSensor(QByteArray pData);
    void    InitOCX();
    void    InitSings();
    void    jiashuibeng();
    void    xishihuisantongfa();
    void    qingxibengfun();
    void    pengsuanbengfun();
    void    paifeifafun();
    void    jiaguanfafun();
    void    jiaobandianjifun();
    void    yanseledfun();
    void    zhengqisantongfafun();
    void    jianfafun();
    void    didingsantongfun();
    void    zhaomingledfun();
    void    paifeibengfun();
    void    paifeifafunA();
    void    jinshuifafun();
    void    Setcolor(QByteArray pData);
private slots:
    void Stateshow();
    void jianshuibeng();
    void suantongfa();
    void qingxibeng();
    void pengsuanbeng();
    void paifeifa();
    void jianguanfa();
    void jiaobanji();
    void yanseled();
    void zhengqisantongfa();
    void jianbeng();
    void didingsantongfa();
    void zhaomingled();
    void jieshoubeioaifeibeng();
    void jieshoubeipaifeifa();
    void lengningshuijinshuifa();

    void on_pb_zhusaibengup_clicked();

    void on_pb_zhusaibengdown_clicked();

private:
    bool        m_bjianshuibeng;
    bool        m_bsuantongfa;
    bool        m_bqingxibeng;
    bool        m_bpengsuanbeng;
    bool        m_bpaifeifa;
    bool        m_bjianguanfa;
    bool        m_bjiaobanji;
    bool        m_byanseled;
    bool        m_bzhengqisantongfa;
    bool        m_bjianbeng;
    bool        m_bdidingsantongfa;
    bool        m_bzhaomingled;
    bool        m_bjieshoubeioaifeibeng;
    bool        m_bjieshoubeipaifeifa;
    bool        m_blengningshuijinshuifa;

    QByteArray  m_Serialcmd;
    QByteArray  m_Serialdata;

    QMLabel     *m_plbjiashuibeng;
    QMLabel     *m_plbsantongfa;
    QMLabel     *m_plbqingxibeng;
    QMLabel     *m_plbpengsuanbeng;
    QMLabel     *m_plbpaifeifa;
    QMLabel     *m_plbjiaguanfa;
    QMLabel     *m_plbjiaobanji;
    QMLabel     *m_plbyanseled;
    QMLabel     *m_plbzhengqisantongfa;
    QMLabel     *m_plbjianbeng;
    QMLabel     *m_plbdidingsantongfa;
    QMLabel     *m_plbzhaopmingled;
    QMLabel     *m_plbjieshoubeipaifeibeng;
    QMLabel     *m_plbjieshoubeipaifeifa;
    QMLabel     *m_plblengningshuijinshuifa;


    QMLabel     *m_pLbfeiyetong;
    QMLabel     *m_pLbdidingsuantong;
    QMLabel     *m_pLbpengsuantong;
    QMLabel     *m_pLbjiantong;
    QMLabel     *m_pLbshuitong;
    QMLabel     *m_pLbzhengqifashengqi;
    QMLabel     *m_pLblengningshui;
    QMLabel     *m_pLbzhengqifashengqiyewei;
    QMLabel     *m_pLbjieshoubei;
    QMLabel     *m_pLbxiaohuaguan;
    QMLabel     *m_pLbanquanmen;

    QTimer       *m_pStateDebugTimer;
    Ui::QSettingDebugForm *ui;
    QTextCodec  *m_ptc;
public:
    QSerialProtcol *m_pSerialDebug;
public slots:
    void AnalysisData(QByteArray pData);
};

#endif // QSETTINGDEBUGFORM_H
