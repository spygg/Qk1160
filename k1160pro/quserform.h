#ifndef QUSERFORM_H
#define QUSERFORM_H

#include <QWidget>
#include <QTextCodec>
#include "qmlabel.h"
#include "qdatabasequery.h"

namespace Ui {
class QUserForm;
}

class QUserForm : public QWidget
{
    Q_OBJECT

public:
    explicit QUserForm(QWidget *parent = 0);
    ~QUserForm();
private:
    void InitOCX();
    void InitSings();
private slots:
    void head1();
    void head2();
    void head3();
    void head4();

    void theme1();
    void theme2();
    void theme3();
    void theme4();
    void on_pb_logout_save_clicked();

    void on_pb_user_logout_clicked();
signals:
    void emitHeadIndex(int index);
    void emitScreenIndex(int index);
private:
    bool        m_bhead1;
    bool        m_bhead2;
    bool        m_bhead3;
    bool        m_bhead4;

    bool        m_btheme1;
    bool        m_btheme2;
    bool        m_btheme3;
    bool        m_btheme4;

    QMLabel     *m_plbhead1;
    QMLabel     *m_plbhead2;
    QMLabel     *m_plbhead3;
    QMLabel     *m_plbhead4;

    QMLabel     *m_plbtheme1;
    QMLabel     *m_plbtheme2;
    QMLabel     *m_plbtheme3;
    QMLabel     *m_plbtheme4;
    QString     m_strexpress;
    QStringList linstname;
    QStringList linstvalues;
    QString     strtable;
    QDatabasequery *pdataquery;
    Ui::QUserForm *ui;
    QTextCodec  *m_ptc;
};

#endif // QUSERFORM_H
