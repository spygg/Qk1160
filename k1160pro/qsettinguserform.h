#ifndef QSETTINGUSERFORM_H
#define QSETTINGUSERFORM_H

#include <QWidget>
#include <QTextCodec>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QScrollBar>
#include <QDateTime>
#include "qdatabasequery.h"
#include "qlistgui.h"
#include "qmlabel.h"


class QUserSetViewTextDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    QUserSetViewTextDelegate(QObject *parent = 0): QItemDelegate(parent) { }

    // QItemDelegate interface
protected:
    void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;
};


namespace Ui {
class QSettingUserForm;
}

class QSettingUserForm : public QWidget
{
    Q_OBJECT

public:
    explicit QSettingUserForm(QWidget *parent = 0);
    ~QSettingUserForm();
    void setOCXEnable(bool bFlag);
    bool checkUserName(QString strName);
private slots:
    void on_pb_settinguser_save_clicked();

    void on_pb_settinguser_add_clicked();

    void on_pb_settinguser_delete_clicked();

    void on_tb_settinguser_list_doubleClicked(const QModelIndex &index);

    void on_tb_settinguser_list_clicked(const QModelIndex &index);

    void on_pb_settinguser_change_clicked();

private:
    void InitOCX();
    void InitSings();
    QString GetDate();
    void cleardata();
    void settableview(QStringList &strdata, QStringList &strdata1);
    int GetUserLevel(QString strName);
private slots:
    void currentRowChanged(QModelIndex,QModelIndex);
    void on_checkBoxDefaultLogin_toggled(bool checked);

private:
    bool        m_bfromChange;
    QString     m_strexpress;
    QStringList linstname;
    QStringList linstvalues;
    QString     strtable;
    QDatabasequery *pdataquery;
    Ui::QSettingUserForm *ui;
    QTextCodec  *m_ptc;
    QStandardItemModel  *m_ItemModel;
};

#endif // QSETTINGUSERFORM_H
