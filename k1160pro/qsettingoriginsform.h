#ifndef QSETTINGORIGINSFORM_H
#define QSETTINGORIGINSFORM_H

#include <QWidget>
#include <QTextCodec>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QScrollBar>
#include <QSqlQueryModel>
#include "qlistgui.h"
#include "qmlabel.h"

namespace Ui {
class QSettingOriginsForm;
}

class QSettingOriginsForm : public QWidget
{
    Q_OBJECT

public:
    explicit QSettingOriginsForm(QWidget *parent = 0);
    ~QSettingOriginsForm();
    void RecordQuery(int ilimit);
    void UpdateStatus();

private slots:
    void on_pb_pgdn_clicked();

    void on_pb_pgup_clicked();

    void on_le_page_textEdited(const QString &arg1);

private:
    void InitOCX();
    void InitSings();
    int GetTotalCount(QString &strTable);
    int GetPageCount();

    void SetPageCount();

private:
    int m_icurrentpage;
    int m_itotalpage;
    int m_itotalcount;
    enum {m_epagecount = 14};

    QString     strtable;
    QSqlDatabase m_db;
    QSqlQueryModel *m_querymodel;
    Ui::QSettingOriginsForm *ui;
    QTextCodec  *m_ptc;
    QStandardItemModel  *m_ItemModel;
};

void HNCreateSysEvent(QString content, QString status ="成功");

#endif // QSETTINGORIGINSFORM_H
