#include "qcalbase.h"

QCalBase::QCalBase(QObject *parent) :
    QObject(parent)
{
}

 QCalBase::~QCalBase()
{

}

float QCalBase::CalmgNml(float f1, float f2, float f3, float f4, float f5)
 {
    float fResualt;
    f1 = f1 * 10;
    fResualt = f1 * f2 * (f3 - f4)/f5;
    return fResualt;
 }

 float QCalBase::CalmgN100ml(float f1, float f2, float f3, float f4, float f5)
{
     float fResualt;
     f1 = f1 * 100;
     fResualt = f1 * f2 * (f3 - f4)/f5;
     return fResualt;
}
 float QCalBase::CalXrecovery(float f1, float f2, float f3)
 {
     float fResualt;
     fResualt = f1 * (f2 - f3) * 100;
     return fResualt;
 }

 float QCalBase::CalXProtein(float f1, float f2, float f3, float f4, float f5, float f6)
 {
     float fResualt;
     fResualt = f1 * f2 * (f3 - f4)/f5;
     fResualt = fResualt * f6;
     return fResualt;
 }
float QCalBase::CalmgProtein(float f1, float f2, float f3, float f4, float f5)
{
    float fResualt;
    f1 = f1 * 10;
    fResualt = f1 * f2 * (f3 - f4);
    fResualt = fResualt * f5;
    return fResualt;
}

 float QCalBase::CalmgN100g(float f1, float f2, float f3, float f4, float f5)
 {
     float fResualt;
     f1 = f1 * 100;
     fResualt = f1 * f2 * (f3 - f4)/f5;
     return fResualt;
 }

 float QCalBase::CalgNKg(float f1, float f2, float f3, float f4, float f5)
 {
     float fResualt;
     f1 = f1 * 10;
     fResualt = f1 * f2 * (f3 - f4)/f5;
     return fResualt;
 }

 float QCalBase::Calml(float f1)
 {
     float fResualt;
     fResualt = f1;
     return fResualt;
 }

 float QCalBase::CalNitrongen(float f1, float f2, float f3, float f4, float f5)
 {
     float fResualt;
     fResualt = f1 * f2 * (f3 - f4)/f5;
     return fResualt;
 }
 float QCalBase::CalmgNKg(float f1, float f2, float f3, float f4, float f5)
 {
     float fResualt;
     fResualt = f1 * f2 * (f3 - f4)/f5;
     fResualt = fResualt * 100000;
     return fResualt;
 }

 float QCalBase::CalmgNg(float f1, float f2, float f3, float f4, float f5)
 {
     float fResualt;
     f1 = f1 * 10;
     fResualt = f1 * f2 * (f3 - f4)/f5;
     return fResualt;
 }

 float QCalBase::CalmgNH3Kg(float f1, float f2, float f3, float f4, float f5)
 {
     float fResualt;
     fResualt = f1 * f2 * (f3 - f4)/f5;
     fResualt = fResualt * 100000;
     return fResualt;
 }

 float QCalBase::CalmgN(float f1, float f2, float f3, float f4)
 {
     float fResualt;
     f1 = f1 * 10;
     fResualt = f1 * f2 * (f3 - f4);
     return fResualt;
 }


