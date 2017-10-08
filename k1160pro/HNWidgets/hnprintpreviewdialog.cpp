#include "hnprintpreviewdialog.h"
#include "ui_hnprintpreviewdialog.h"
#include "qcpdocumentobject.h"
#include "hnprinter.h"
#include "hngui-qt.h"
#include "HNDefine.h"


HNPrintPreviewDialog::HNPrintPreviewDialog(QWidget *parent) :
    HNDialog(parent),
    ui(new Ui::QReportViewDialog)
{
    ui->setupUi(this);
    connect(ui->btn_back, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->btn_print, SIGNAL(clicked()), this, SLOT(accept()));
    m_db = newDatabaseConn();
    setDatabaseName(m_db, QString("Data/%1").arg("Report"));
    QSettings set;
    if(set.value("SerialNo").toString().isEmpty())
    {
        set.setValue("SerialNo", 60000);
        set.sync();
    }
    if(set.value("Company").toString().isEmpty())
    {
        set.setValue("Company", "Hanon");
        set.sync();
    }
}

HNPrintPreviewDialog::~HNPrintPreviewDialog()
{
    closeDatabase(m_db);
    delete ui;
}

QString HNPrintPreviewDialog::newReport(QString library, QString method)
{
    QSettings set;
    QString company = set.value("Company").toString();
    QString serialNo = QString::number(set.value("SerialNo").toInt()+1);
    set.setValue("SerialNo", serialNo);
    set.sync();

    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
    QSqlQuery query(m_db);
    QString sql;
    //QString sql = QString("INSERT INTO %1 VALUES(null, '%2', '%3', '%4', '%5', '%6', '%7', null, null, null, null)")
   //         .arg("Report").arg(serialNo).arg(company).arg(gUserName).arg(library).arg(method).arg(time);
    //pline() << sql;
    query.exec(sql);
    //pline() << sql;
    query.finish();
    pline() << method << time;

    return serialNo;
}

void HNPrintPreviewDialog::endReport(QString serialNo, QString Exception, QString stopReason, QByteArray &plot)
{
    QSqlQuery query(m_db);
    query.prepare(QString("UPDATE %1 SET Exception='%2',StopReason='%3',Plot=? WHERE serialNo = '%4'")
                  .arg("Report").arg(Exception).arg(stopReason).arg(serialNo));
    query.addBindValue(plot);
    query.exec();
    query.finish();
}

void HNPrintPreviewDialog::initAll(QString name)
{
    QStringList lsl = name.split("_");
    if(lsl.size() < 1)
        return;

    QString mname = lsl.at(0);
    QString time = lsl.at(1);

    pline() << mname << time;

    QSqlQuery query(m_db);
    query.exec(QString("SELECT * FROM %1 WHERE Method = '%2' AND StartTime = '%3'")
               .arg("Report").arg(mname).arg(time));

    QString serialNo, company, user, library;
    QString method, starttime, stoptime, exception, stopreason;
    QByteArray plot;

    if(query.next())
    {
        serialNo = query.record().value("SerialNo").toString();
        company = query.record().value("Company").toString();
        user = query.record().value("User").toString();
        library = query.record().value("Library").toString();
        method = query.record().value("Method").toString();
        starttime = query.record().value("StartTime").toString();
        stoptime = query.record().value("StopTime").toString();
        exception = query.record().value("Exception").toString();
        stopreason = query.record().value("StopReason").toString();
        plot = query.record().value("Plot").toByteArray();
    }
    query.finish();

    pline() << serialNo << company << user << library << method << starttime << stoptime
            << exception << stopreason << plot;

    QTextBrowser* m_text = ui->txtView;
    m_text->clear();
    QString cpy = QString(tr("Company:%1")).arg(company);
    m_text->append(cpy);
    QString ur = QString(tr("User:%1")).arg(user);
    m_text->append(ur);
    QString lib = QString(tr("Library:%1")).arg(library);
    m_text->append(lib);
    QString mt = QString(tr("Method:%1")).arg(method);
    m_text->append(mt);
    QString sn = QString(tr("SerialNo:%1")).arg(serialNo);
    m_text->append(sn);
    QString st = QString(tr("StartTime:%1")).arg(starttime);
    m_text->append(st);
    m_text->append(tr("Plot:"));
    if(plot.size()>0)
    {
        pline() << plot.size();
        QImage image;
        image.loadFromData(plot, "BMP");
        //pline();
        QTextCursor cursor = m_text->textCursor();
        cursor.insertImage(image.scaled(300, 200, Qt::IgnoreAspectRatio));
        m_text->setTextCursor(cursor);
    }
    QString ex = QString(tr("Exception:%1")).arg(exception);
    m_text->append(ex);
    QString se = QString(tr("StopReason:%1")).arg(stopreason);
    m_text->append(se);
    QString et = QString(tr("StopTime:%1")).arg(stoptime);
    m_text->append(et);
}

void HNPrintPreviewDialog::printToPdf()
{
    QString fileName = QString("Report.pdf");
    QFile::remove(fileName);

    //只有这个构造函数决定输出高分辨率PDF。
    QPrinter printer(QPrinter::HighResolution);
    printer.setColorMode(QPrinter::Color);
    printer.setFullPage(true);
    printer.setPaperSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    QTextBrowser* m_text = ui->txtView;
    m_text->print(&printer);
}

void HNPrintPreviewDialog::print()
{
}

void HNPrintPreviewDialog::htmltopdf(QString pdf, QString html)
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setColorMode(QPrinter::Color);
    printer.setFullPage(true);
    printer.setPaperSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(pdf);

    QTextDocument textDocument;
    textDocument.setHtml(html);
    textDocument.print(&printer);
}

void HNPrintPreviewDialog::printpdf(QString pdf)
{
    // 此处不会影响打印质量，不必再调试
    QString cmd;
    QString path="./Output.pbm";

    cmd = cmd.sprintf("gs -q -dBATCH -dSAFER -dQUIET -dNOPAUSE -sPAPERSIZE=a4 -r600*600 -sDEVICE=pbmraw -sOutputFile=%s %s", path.toLatin1().data(), pdf.toLatin1().data());
    system(cmd.toLatin1().data());

    cmd = cmd.sprintf("foo2zjs -z3 -p9 -r600*600 %s > /dev/usb/lp0", path.toLatin1().data());
    system(cmd.toLatin1().data());
}
