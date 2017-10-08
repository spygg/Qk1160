#ifndef QCLOUDTREEVIEW_H
#define QCLOUDTREEVIEW_H

#include "hntreeview.h"

namespace Ui {
class HNCloudTreeView;
}

class HNCloudTreeView : public HNTreeView
{
    Q_OBJECT

public:
    explicit HNCloudTreeView(QWidget *parent = 0);
    ~HNCloudTreeView();

private:
    Ui::HNCloudTreeView *ui;
};

#endif // QCLOUDTREEVIEW_H
