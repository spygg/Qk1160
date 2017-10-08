#ifndef HNUSERINFOWIDGET_H
#define HNUSERINFOWIDGET_H

#include "hnuserinfoview.h"
#include "hnuserinfomodel.h"
#include <QDataWidgetMapper>

namespace Ui {
class HNUserInfoWidget;
}

class HNUserInfoWidget : public HNUserInfoView
{
    Q_OBJECT

public:
    explicit HNUserInfoWidget(QWidget *parent = 0);
    ~HNUserInfoWidget();

    void refresh();
    void selectUser(int id = 0);
    void selectUser(QString userName);
    QString currentUser();
    QString currentUserAuthority();
    QString currentUserPassword();
    void setUserName(QString newName);
    inline QDataWidgetMapper* mapper() { return m_mapper; }
    inline HNUserInfoModel* model() { return m_model; }
    inline void addMap(QWidget* w, int section) { m_mapper->addMapping(w, section); }
    inline void addMap(QWidget* w, int section, const QByteArray &propertyName) { m_mapper->addMapping(w, section, propertyName); }
    void initLanguage();

public slots:
    void newUser(QString name, QString pwd, QString auth, QString comt);
    void delUser();
    void updateMap();
    void saveMap();

private slots:
    void currentItemChanged(QModelIndex,QModelIndex);
private:
    Ui::HNUserInfoWidget *ui;

    HNUserInfoModel* m_model;
    QDataWidgetMapper* m_mapper;
};

#endif // HNUSERINFOWIDGET_H
