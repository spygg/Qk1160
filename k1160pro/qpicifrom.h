#ifndef QPICIFROM_H
#define QPICIFROM_H

#include <QWidget>
#include <QTextCodec>
#include <QComboBox>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QScrollBar>
#include "qlistgui.h"
#include "DataDef.h"

namespace Ui {
class QPiciFrom;
}

class QPiciFrom : public QWidget
{
    Q_OBJECT

public:
    explicit QPiciFrom(QWidget *parent = 0);
    ~QPiciFrom();
    QList<TestData *> *m_pListPiciTestData;
private slots:
    void on_pb_pici_back_clicked();

    void on_cb_pici_leixing_currentIndexChanged(int index);

    void on_cb_pici_danwei_currentIndexChanged(const QString &arg1);

    void on_cb_pici_yangpinshuliang_currentIndexChanged(const QString &arg1);

    void on_cb_pici_danwei_currentIndexChanged(int index);

    void on_pb_pici_save_clicked();

    void on_pb_pici_delete_clicked();

    void on_tb_pici_param_clicked(const QModelIndex &index);

    void on_tb_pici_param_doubleClicked(const QModelIndex &index);
    void on_tb_pici_param_pressed(const QModelIndex &index);

signals:
    void emitTestData(int index);
private:
    void InitOCX();
    void InitOCXData();
    void InitComboxData();
    void InitSings();
    void SetTestData(QString strPihao, int iType, float fSample, int index);
private:
    int         m_iRow;
    int         m_iCol;
    int         m_iIndex;
    bool        m_bData;
    QTextCodec  *m_ptc;
    ListModel   *m_ItemModel;

    //QStandardItemModel  *m_ItemModel;
private:
    Ui::QPiciFrom *ui;
};

#endif // QPICIFROM_H
