#ifndef QCALBASE_H
#define QCALBASE_H

#include <QObject>

class QCalBase : public QObject
{
    Q_OBJECT
public:
    explicit QCalBase(QObject *parent = 0);
    ~QCalBase();
    float CalmgNml(float f1, float f2, float f3, float f4, float f5);
    float CalmgN100ml(float f1, float f2, float f3, float f4, float f5);
    float CalXrecovery(float f1, float f2, float f3);
    float CalXProtein(float f1, float f2, float f3, float f4, float f5, float f6);
    float CalmgProtein(float f1, float f2, float f3, float f4, float f5);
    float CalmgN100g(float f1, float f2, float f3, float f4, float f5);
    float CalgNKg(float f1, float f2, float f3, float f4, float f5);
    float Calml(float f1);
    float CalNitrongen(float f1, float f2, float f3, float f4, float f5);
    float CalmgNKg(float f1, float f2, float f3, float f4, float f5);
    float CalmgNg(float f1, float f2, float f3, float f4, float f5);
    float CalmgNH3Kg(float f1, float f2, float f3, float f4, float f5);
    float CalmgN(float f1, float f2, float f3, float f4);

signals:

public slots:

};

#endif // QCALBASE_H
