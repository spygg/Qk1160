#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:08:11
#
#-------------------------------------------------

QT       += core gui network sql

CONFIG += serialport

DEFINES += _TTY_POSIX_

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD

QT_KIT = $$(QKIT)

message(HNWidget $${QT_KIT} )

#K1160图形 __HNWIDGETS_K1160__
#MIPS __MIPS_LINUX__
#PC64 __LINUX64__

DEFINES += __HNWIDGETS_K1160__

equals(QT_KIT, MIPS32) {
    QT += multimedia
    DEFINES += __MIPS_LINUX__
} else {
    DEFINES += __LINUX64__
}

CONFIG(debug, debug|release) {
} else {
    DEFINES -= QT_NO_DEBUG_OUTPUT
}

RESOURCES += \
    $$PWD/HNWidgets.qrc \
    $$PWD/HNWidgetsK1160.qrc

RC_FILE += \
    $$PWD/hnversion.rc

OTHER_FILES += \
    $$PWD/HNWidgets.qss \
    $$PWD/hnversion.rc

SOURCES += $$PWD/hncheckbox.cpp \
    $$PWD/HNDefine.cpp \
    $$PWD/hndialog.cpp \
    $$PWD/HNEthManager.cpp \
    $$PWD/hnheaderview.cpp \
    $$PWD/HNInput.cpp \
    $$PWD/hnlistview.cpp \
    $$PWD/hnmsgbox.cpp \
    $$PWD/hnprinter.cpp \
    $$PWD/hnprogressbar.cpp \
    $$PWD/hnpushbutton.cpp \
    $$PWD/hnradiobutton.cpp \
    $$PWD/hntabbar.cpp \
    $$PWD/hntableview.cpp \
    $$PWD/hntabwidget.cpp \
    $$PWD/hntabwidgetb.cpp \
    $$PWD/hntreeview.cpp \
    $$PWD/hnwidget.cpp \
    $$PWD/hnwifimodel.cpp \
    $$PWD/hnwifiview.cpp \
    $$PWD/hnwifiwidget.cpp \
    $$PWD/qcpdocumentobject.cpp \
    $$PWD/qcustomplot.cpp \
    $$PWD/hnclient.cpp \
    $$PWD/hnclientmessage.cpp \
    $$PWD/hncloudwidget.cpp \
    $$PWD/hncloudlocalmodel.cpp \
    $$PWD/hncloudlocaltreewidget.cpp \
    $$PWD/hncloudmodel.cpp \
    $$PWD/hncloudtreeview.cpp \
    $$PWD/hncloudtreewidget.cpp \
    $$PWD/hnexceptionmodel.cpp \
    $$PWD/hnexceptionview.cpp \
    $$PWD/hnexceptionwidget.cpp \
    $$PWD/HNLineEditWithSearch.cpp \
    $$PWD/hnpeermessage.cpp \
    $$PWD/hnpeerport.cpp \
    $$PWD/hnplayermodel.cpp \
    $$PWD/hnplayerwidget.cpp \
    $$PWD/hnpluginwatcher.cpp \
    $$PWD/hnprogressdialog.cpp \
    $$PWD/hnserialmessage.cpp \
    $$PWD/hnserialport.cpp \
    $$PWD/hnserver.cpp \
    $$PWD/hntablemodel.cpp \
    $$PWD/hnstandarditemmodel.cpp \
    $$PWD/hnsyseventmodel.cpp \
    $$PWD/hnsyseventview.cpp \
    $$PWD/hnsyseventwidget.cpp \
    $$PWD/hnupgradewidget.cpp \
    $$PWD/hnpassworddialog.cpp \
    $$PWD/qdevicewatcher.cpp \
    $$PWD/qdevicewatcher_linux.cpp \
    $$PWD/hnprintpreviewdialog.cpp \
    $$PWD/hnmanageethenetwidget.cpp \
    $$PWD/HNPreviewWidget.cpp \
    $$PWD/dmmu.c \
    $$PWD/hnuserinfomodel.cpp \
    $$PWD/hnuserinfoview.cpp \
    $$PWD/hnuserinfowidget.cpp \
    $$PWD/hnmanageuserwidget.cpp \
    $$PWD/hncreateuserdialog.cpp \
    $$PWD/hnmptablewidget.cpp \
    $$PWD/hntablewidget.cpp \
    $$PWD/hngraphicsscene.cpp \
    $$PWD/hngraphicsitem.cpp \
    $$PWD/hngraphicsview.cpp \
    $$PWD/hnprintinfodialog.cpp \
    $$PWD/hnword.cpp \
    $$PWD/hnreport.cpp \
    $$PWD/hnobjectfactory.cpp \
    HNWidgets/hntreemodel.cpp \
    HNWidgets/hnfilesystem.cpp \
    HNWidgets/hntreewidget.cpp

HEADERS  += $$PWD/hncheckbox.h \
    $$PWD/HNDefine.h \
    $$PWD/hndialog.h \
    $$PWD/HNEthManager.h \
    $$PWD/hngui.h \
    $$PWD/hngui-qt.h \
    $$PWD/hnheaderview.h \
    $$PWD/HNInput.h \
    $$PWD/hnlinux.h \
    $$PWD/hnlistview.h \
    $$PWD/hnmsgbox.h \
    $$PWD/hnprinter.h \
    $$PWD/hnprogressbar.h \
    $$PWD/HNPub.h \
    $$PWD/hnpushbutton.h \
    $$PWD/hnradiobutton.h \
    $$PWD/hntabbar.h \
    $$PWD/hntableview.h \
    $$PWD/hntabwidget.h \
    $$PWD/hntabwidgetb.h \
    $$PWD/hntreeview.h \
    $$PWD/hnwidget.h \
    $$PWD/hnwifimodel.h \
    $$PWD/hnwifiview.h \
    $$PWD/hnwifiwidget.h \
    $$PWD/qcpdocumentobject.h \
    $$PWD/qcustomplot.h \
    $$PWD/hnclient.h \
    $$PWD/hnclientmessage.h \
    $$PWD/hncloudwidget.h \
    $$PWD/hncloudlocalmodel.h \
    $$PWD/hncloudlocaltreewidget.h \
    $$PWD/hncloudmodel.h \
    $$PWD/hncloudtreeview.h \
    $$PWD/hncloudtreewidget.h \
    $$PWD/hnexceptionmodel.h \
    $$PWD/hnexceptionview.h \
    $$PWD/hnexceptionwidget.h \
    $$PWD/HNLineEditWithSearch.h \
    $$PWD/hnpeermessage.h \
    $$PWD/hnpeerport.h \
    $$PWD/hnplayermodel.h \
    $$PWD/hnplayerwidget.h \
    $$PWD/hnpluginwatcher.h \
    $$PWD/hnprogressdialog.h \
    $$PWD/hnserialmessage.h \
    $$PWD/hnserialport.h \
    $$PWD/hnserver.h \
    $$PWD/hntablemodel.h \
    $$PWD/hnstandarditemmodel.h \
    $$PWD/hnsyseventmodel.h \
    $$PWD/hnsyseventview.h \
    $$PWD/hnsyseventwidget.h \
    $$PWD/hnupgradewidget.h \
    $$PWD/hnversion.h \
    $$PWD/hnpassworddialog.h \
    $$PWD/qdevicewatcher.h \
    $$PWD/qdevicewatcher_p.h \
    $$PWD/hnprintpreviewdialog.h \
    $$PWD/hnmanageethenetwidget.h \
    $$PWD/dmmu.h \
    $$PWD/graphics.h \
    $$PWD/hal.h \
    $$PWD/HNPreviewWidget.h \
    $$PWD/jz_cim.h \
    $$PWD/hnuserinfomodel.h \
    $$PWD/hnuserinfoview.h \
    $$PWD/hnuserinfowidget.h \
    $$PWD/hnmanageuserwidget.h \
    $$PWD/hncreateuserdialog.h \
    $$PWD/hnmptablewidget.h \
    $$PWD/hntablewidget.h \
    $$PWD/hngraphicsscene.h \
    $$PWD/hngraphicsitem.h \
    $$PWD/hngraphicsview.h \
    $$PWD/hnprintinfodialog.h \
    $$PWD/hnword.h \
    $$PWD/hnreport.h \
    $$PWD/hnobjectfactory.h \
    HNWidgets/hntreemodel.h \
    HNWidgets/hnfilesystem.h \
    HNWidgets/hntreewidget.h

FORMS    += $$PWD/hncheckbox.ui \
    $$PWD/hndialog.ui \
    $$PWD/HNInput.ui \
    $$PWD/hnlistview.ui \
    $$PWD/hnmsgbox.ui \
    $$PWD/hnprogressbar.ui \
    $$PWD/hnpushbutton.ui \
    $$PWD/hnradiobutton.ui \
    $$PWD/hntableview.ui \
    $$PWD/hntabwidget.ui \
    $$PWD/hntabwidgetb.ui \
    $$PWD/hntreeview.ui \
    $$PWD/hnwidget.ui \
    $$PWD/hnwifiview.ui \
    $$PWD/hnwifiwidget.ui \
    $$PWD/hncloudwidget.ui \
    $$PWD/hncloudlocaltreewidget.ui \
    $$PWD/hncloudtreeview.ui \
    $$PWD/hncloudtreewidget.ui \
    $$PWD/hnexceptionview.ui \
    $$PWD/hnexceptionwidget.ui \
    $$PWD/hnplayerwidget.ui \
    $$PWD/hnprogressdialog.ui \
    $$PWD/hnsyseventview.ui \
    $$PWD/hnsyseventwidget.ui \
    $$PWD/hnupgradewidget.ui \
    $$PWD/hnpassworddialog.ui \
    $$PWD/hnprintpreviewdialog.ui \
    $$PWD/hnmanageethenetwidget.ui \
    $$PWD/HNPreviewWidget.ui \
    $$PWD/hnuserinfoview.ui \
    $$PWD/hnuserinfowidget.ui \
    $$PWD/hnmanageuserwidget.ui \
    $$PWD/hncreateuserdialog.ui \
    $$PWD/hnmptablewidget.ui \
    $$PWD/hntablewidget.ui \
    $$PWD/hnprintinfodialog.ui \
    HNWidgets/hntreewidget.ui
