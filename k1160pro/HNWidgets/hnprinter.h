#ifndef _HNPRINTER_H
#define _HNPRINTER_H

#include <QPrinter>

class HNPrinter : public QPrinter
{
public:
    HNPrinter(PrinterMode mode = HighResolution);

    void setOutputFileName(const QString &);
    void print();

private:
    QString m_outputname;
};

#endif // HNPRINTER_H
