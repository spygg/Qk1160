#ifndef QPICWIDGET_H
#define QPICWIDGET_H

#include <QWidget>

namespace Ui {
class HNWidget;
}

class HNWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HNWidget(QWidget *parent = 0);
    ~HNWidget();

    enum {
        HNCENTER,
        HNTILEDWIDTH,
        HNTILEDHEIGHT,
        HNZOOMWIDTH,
        HNZOOMHEIGHT,
    };
    void setPixmap(QString pic = QString());
    void setType(quint32 type = 0) { m_type = type; }
private:
    Ui::HNWidget *ui;
    QString m_pic;
    quint32 m_type;
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
};

#endif // QPICWIDGET_H
