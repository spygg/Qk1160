#include "mainwindow.h"
#include "qmainscreen.h"
#include "qpicifrom.h"
#include "qautotest.h"
#include "qautotestaprocessform.h"
#include "qmanualtestform.h"
#include "qcleanform.h"
#include "qsettingmethodform.h"
#include "qsettingmachineform.h"
#include "qsettingcleanform.h"
#include "qsettingcalibrationform.h"
#include "qsettingnetform.h"
#include "qsettingdebugform.h"
#include "qsettinguserform.h"
#include "qsettingoriginsform.h"
#include "qhelpform.h"
#include "quserform.h"
#include "qcloudform.h"
#include "qinputtool.h"
#include "hnwindow.h"
#include "QWSServer"
#include <QApplication>
#include <QTextCodec>
#include <QFontDatabase>
#include "hnapp.h"
#include "hntreewidget.h"
#include "hnlocaldbdialog.h"
#include "hnprogressdialog.h"

int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(rc01);
    HNApp a(argc, argv);

    system("rm -f /tmp/LCK..ttyS*");

    QInputTool::Instance()->Init("control", "brown", 10, 10);
    QInputTool::Instance()->hide();

    QWidget w;

#ifdef _MIPS_LINUX_ENV_
    w.setFixedSize(1024, 768);
    w.setWindowFlags(Qt::FramelessWindowHint|w.windowFlags());
    //keyboard
    //QWSInputMethod* im = new SyszuxIM;
    //QWSServer::setCurrentInputMethod(im);
#else
    w.setFixedSize(1024, 768);

#endif
    QVBoxLayout l;
    l.setMargin(0);
    w.setLayout(&l);

    MainWindow m;
    l.addWidget(&m);

    w.show();
    return a.exec();
}


