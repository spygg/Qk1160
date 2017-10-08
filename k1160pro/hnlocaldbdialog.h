#ifndef HNLOCALDBDIALOG_H
#define HNLOCALDBDIALOG_H

#include "hngui-qt.h"
#include "hngui.h"

class HNLocalDBDialog : public HNDialog
{
    Q_OBJECT
public:
    explicit HNLocalDBDialog(QWidget *parent = 0);

    void InitOCX();

    bool query(QString path = "local://db");
    void selectedItem(QString & path, QString& name);

signals:

public slots:
private slots:
    void currentRowChanged();
    void selected();

private:
    HNTreeWidget* localWidget;
    HNPushButton* btnSelect;
    QString m_path;
    QString m_name;
};

#endif // HNLOCALDBDIALOG_H
