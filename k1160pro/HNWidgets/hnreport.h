#ifndef HNREPORT_H
#define HNREPORT_H

#include "hnword.h"

class HNReport : public HNWord
{
    Q_OBJECT
public:
    explicit HNReport(QObject *parent = 0);

    void createSampleReport(const QString& head, const QString& foot, const QString& title,
                              const QTableView* table);

    void CreateComplexReport(const QString &head, const QString &foot,
                               const QString &title, const QList<QTableView *> &table);

signals:

public slots:


    // HNWord interface
protected:

private:
};

HNReport* HNReportInstance(QObject* parent);

#endif // HNREPORT_H
