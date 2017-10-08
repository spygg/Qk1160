#include "qpicifrom.h"
#include "ui_qpicifrom.h"
#include "qautotest.h"

#include <QMessageBox>

QPiciFrom::QPiciFrom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QPiciFrom),
    m_bData(false),
    m_iRow(0),
    m_iCol(0)
{
    ui->setupUi(this);
    m_ptc =  QTextCodec::codecForName("UTF-8");
    InitOCX();
    InitOCXData();
    InitComboxData();
    InitSings();
    QAutoTest *pWidget = static_cast<QAutoTest *>(this->parent());
    m_pListPiciTestData = &(pWidget->m_pListTestData);

    this->setWindowModality(Qt::WindowModal);
    connect(this,SIGNAL(emitTestData(int)),parent,SLOT(UpTestData(int)));
}

QPiciFrom::~QPiciFrom()
{
    this->clearFocus();
    delete ui;
}


void QPiciFrom::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setStyleSheet("QWidget#QPiciFrom{image:url(:/images/bk/bk_pici.png)}""QCheckFrom{background-color:transparent;}");
    this->setGeometry(0, 0, 904, 658);
    this->setFocusPolicy(Qt::ClickFocus);
    setFocus();

    //edit
    ui->ed_pici_name->setGeometry(137,148,291, 35);
    ui->ed_pici_name->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");

    ui->ed_pici_shuliang->hide();
    //ui->ed_pici_shuliang->setGeometry(137, 204, 287, 31);
    //ui->ed_pici_shuliang->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");

    ui->ed_pici_tiji->setGeometry(137, 372, 291, 35);
    ui->ed_pici_tiji->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");

    ui->ed_pici_suannongdu->setGeometry(137, 428,291, 35);
    ui->ed_pici_suannongdu->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");

    //bt
    /*
    ui->pb_pici_pgup->setFlat(true);
    ui->pb_pici_pgup->setFocusPolicy(Qt::NoFocus);
    ui->pb_pici_pgup->setGeometry(144,599,108,44);
    ui->pb_pici_pgup->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_pgup_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_pgup_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_pgup_press.png);}");

    ui->pb_pici_pgdn->setFlat(true);
    ui->pb_pici_pgdn->setFocusPolicy(Qt::NoFocus);
    ui->pb_pici_pgdn->setGeometry(271,599,108,44);
    ui->pb_pici_pgdn->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_pgdn_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_pgdn_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_pgdn_press.png);}");
    */
    ui->pb_pici_pgup->hide();
    ui->pb_pici_pgdn->hide();

    ui->pb_pici_save->setFlat(true);
    //ui->pb_pici_save->setFocusPolicy(Qt::NoFocus);
    ui->pb_pici_save->setGeometry(207,599,108,44);
    ui->pb_pici_save->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_save_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_save_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_save_press.png);}");

    ui->pb_pici_delete->setFlat(true);
    //ui->pb_pici_delete->setFocusPolicy(Qt::NoFocus);
    ui->pb_pici_delete->setGeometry(384,599,108,44);
    ui->pb_pici_delete->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_delete_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_delete_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_delete_press.png);}");

    ui->pb_pici_back->setFlat(true);
    //ui->pb_pici_back->setFocusPolicy(Qt::NoFocus);
    ui->pb_pici_back->setGeometry(570,599,108,44);
    ui->pb_pici_back->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_back_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_back_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_back_press.png);}");

    //combox
    ui->cb_pici_yangpinshuliang->setGeometry(137, 204, 291, 35);
    ui->cb_pici_yangpinshuliang->setStyleSheet("QComboBox{border:1px solid gray;}"
                                               "QComboBox QAbstractItemView::item{height:50px;}"
                                               "QComboBox::down-arrow{image:url(:/images/bt/arrowdownBo.png);}"
                                               "QComboBox::drop-down{border:0px;}");
    ui->cb_pici_yangpinshuliang->setView(new QListView());


    ui->cb_pici_danwei->setGeometry(137, 260, 291, 35);
    ui->cb_pici_danwei->setStyleSheet("QComboBox{border:1px solid gray;}"
                                      "QComboBox QAbstractItemView::item{height:50px;}"
                                      "QComboBox::down-arrow{image:url(:/images/bt/arrowdownBo.png);}"
                                      "QComboBox::drop-down{border:0px;}");
    ui->cb_pici_danwei->setView(new QListView());

    ui->cb_pici_leixing->setGeometry(137, 316, 291, 35);
    ui->cb_pici_leixing->setStyleSheet("QComboBox{border:1px solid gray;}"
                                       "QComboBox QAbstractItemView::item{height:50px;}"
                                       "QComboBox::down-arrow{image:url(:/images/bt/arrowdownBo.png);}"
                                       "QComboBox::drop-down{border:0px;}");
    ui->cb_pici_leixing->setView(new QListView());

    //lab
    ui->label->setGeometry(20, 3, 120, 30);
    ui->label->setText(m_ptc->toUnicode("批次输入"));
    ui->label->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->lb_pici_yangpinmingcheng->setGeometry(31, 153, 120, 30);
    ui->lb_pici_yangpinmingcheng->setText(m_ptc->toUnicode("样品名称："));
    ui->lb_pici_yangpinmingcheng->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_pici_shuliang->setGeometry(31, 209, 120, 30);
    ui->lb_pici_shuliang->setText(m_ptc->toUnicode("样品数量："));
    ui->lb_pici_shuliang->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_pici_danwei->setGeometry(31, 265, 120, 30);
    ui->lb_pici_danwei->setText(m_ptc->toUnicode("样品量单位："));
    ui->lb_pici_danwei->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_pici_leixing->setGeometry(31, 321, 120, 30);
    ui->lb_pici_leixing->setText(m_ptc->toUnicode("结果类型："));
    ui->lb_pici_leixing->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_pici_tiji->setGeometry(31, 377, 120, 30);
    ui->lb_pici_tiji->setText(m_ptc->toUnicode("空白体积："));
    ui->lb_pici_tiji->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_pici_nongdu->setGeometry(31, 433, 120, 30);
    ui->lb_pici_nongdu->setText(m_ptc->toUnicode("滴定酸浓度："));
    ui->lb_pici_nongdu->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_pici_ml->setGeometry(428, 377, 40, 30);
    ui->lb_pici_ml->setText(m_ptc->toUnicode("mL"));
    ui->lb_pici_ml->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_pici_mol->setGeometry(428, 433, 40, 30);
    ui->lb_pici_mol->setText(m_ptc->toUnicode("mol/L"));
    ui->lb_pici_mol->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    m_ItemModel = new ListModel(this);
    m_ItemModel->setColumnCount(3);
    m_ItemModel->setRowCount(20);

    m_ItemModel->setHorizontalHeaderLabels(QStringList() /*<< m_ptc->toUnicode("序号") */<< m_ptc->toUnicode("样品批号") << m_ptc->toUnicode("测试类型") << m_ptc->toUnicode("样品量"));

    ui->tb_pici_param->setAlternatingRowColors(true);
    ui->tb_pici_param->setGeometry(486, 142, 393, 331);
    ui->tb_pici_param->setStyleSheet("QTableView::item{background-color:rgb(255,255,255)}""QTableView::item{width:180px; height:140px}""QTableView::item{selection-background-color:rgb(232,232,232)}");
    ui->tb_pici_param->verticalHeader()->setHidden(false);
    //ui->tb_pici_param->setSelectionBehavior(QAbstractItemView::SelectedClicked);
    //ui->tb_pici_param->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->tb_pici_param->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tb_pici_param->setFrameShape(QFrame::NoFrame);
    ui->tb_pici_param->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
                                                            "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
                                                            "QScrollBar::handle:hover{background:gray;}"
                                                            "QScrollBar::sub-line{background:transparent;}"
                                                            "QScrollBar::add-line{background:transparent;}");
    ui->tb_pici_param->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
                                                          "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
                                                          "QScrollBar::handle:hover{background:gray;}"
                                                          "QScrollBar::sub-line{background:transparent;}"
                                                          "QScrollBar::add-line{background:transparent;}");
    ui->tb_pici_param->setModel(m_ItemModel);
    ui->tb_pici_param->setSelectionBehavior(QAbstractItemView::SelectRows);
#ifdef _MIPS_LINUX_ENV_
    ui->tb_pici_param->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tb_pici_param->horizontalHeader()->setStretchLastSection(true);
#else
    ui->tb_pici_param->horizontalHeader()->setStretchLastSection(true);
    ui->tb_pici_param->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif
    for(int i = 0; i < 20; i++)
    {
        ui->tb_pici_param->setRowHeight(i,50);
    }
    ReadOnlyDelegate *preadonlydelegate = new ReadOnlyDelegate(this);
    TestDelegate *pTestDelegate = new TestDelegate(this);
    IDDelegate *pIDdelegate = new IDDelegate(this);
    NameDelegate *pNamedelegate = new NameDelegate(this);
    //re *preadonlydelegate = new (this);
    ui->tb_pici_param->setItemDelegateForColumn(0, pNamedelegate);
    ui->tb_pici_param->setItemDelegateForColumn(1, pTestDelegate);
    ui->tb_pici_param->setItemDelegateForColumn(2, pIDdelegate);
    //ui->tb_pici_param->setItemDelegateForColumn(3, pIDdelegate);

    QFile styleFile("://HNWidgets.qss");
    styleFile.open(QIODevice::ReadOnly);
    QString styleString(styleFile.readAll());;
    ui->tb_pici_param->verticalScrollBar()->setStyleSheet(styleString);
    styleFile.close();

}

void QPiciFrom::InitOCXData()
{
    QRegExp rx("^-?(100|1?[0-9]?\\d(\\.\\d{1,6})?)$");
    QRegExpValidator *pReg = new QRegExpValidator(rx, this);
    ui->ed_pici_suannongdu->setValidator(pReg);
    ui->ed_pici_tiji->setValidator(pReg);
    //ui->ed_autotest_nongdu->setValidator(pReg);
    //ui->ed_autotest_pihao->setValidator(new QIntValidator(1, 1000,  this));
}

void QPiciFrom::InitComboxData()
{
    ui->cb_pici_yangpinshuliang->addItem(m_ptc->toUnicode("20"));
    ui->cb_pici_yangpinshuliang->addItem(m_ptc->toUnicode("40"));
    ui->cb_pici_yangpinshuliang->addItem(m_ptc->toUnicode("60"));

    ui->cb_pici_danwei->addItem(m_ptc->toUnicode("mL"));
    ui->cb_pici_danwei->addItem(m_ptc->toUnicode("g"));

    ui->cb_pici_leixing->addItem(m_ptc->toUnicode("mL"));
    ui->cb_pici_leixing->addItem(m_ptc->toUnicode("% Nitrogen"));
    ui->cb_pici_leixing->addItem(m_ptc->toUnicode("% Protein"));
    ui->cb_pici_leixing->addItem(m_ptc->toUnicode("mg N/kg"));
    ui->cb_pici_leixing->addItem(m_ptc->toUnicode("mg N/g"));
    ui->cb_pici_leixing->addItem(m_ptc->toUnicode("mg NH3/kg"));
    ui->cb_pici_leixing->addItem(m_ptc->toUnicode("mg N"));
    ui->cb_pici_leixing->addItem(m_ptc->toUnicode("mg N/mL"));
    ui->cb_pici_leixing->addItem(m_ptc->toUnicode("mg N/100mL"));
    ui->cb_pici_leixing->addItem(m_ptc->toUnicode("% Recovery"));
    ui->cb_pici_leixing->addItem(m_ptc->toUnicode("mg Protein"));
    ui->cb_pici_leixing->addItem(m_ptc->toUnicode("mg N/100g"));
    ui->cb_pici_leixing->addItem(m_ptc->toUnicode("g N/kg"));
}

void QPiciFrom::InitSings()
{

}

void QPiciFrom::SetTestData(QString strPihao, int iType, float fSample, int index)
{
    if((strPihao.isEmpty()))
    {
        return;
    }
    m_iIndex = index;
    QString strName = "";
    //QString strpihao = "";
    int iTestType = 0;
    //tring strSampleNumber = "";
    int iResualtType = 0;
    QString strtiji = "";
    QString strnongdu = "";
    QString strNote = "";

    strName = ui->ed_pici_name->text();
    //strpihao = ui->ed_autotest_pihao->text();
    iTestType = ui->cb_pici_danwei->currentIndex();
    //strSampleNumber = ui->ed_autotest_yangpinliang->text();
    //iSampleType = ui->cb_autotest_yangpinliang->currentIndex();
    iResualtType = ui->cb_pici_leixing->currentIndex();
    strtiji = ui->ed_pici_tiji->text();
    strnongdu = ui->ed_pici_suannongdu->text();




    //for(int i = 0; i < index; i++)
    {
        m_pListPiciTestData->append(new TestData());
        m_pListPiciTestData->at(index)->m_strName = strName;
        m_pListPiciTestData->at(index)->m_strpihao = strPihao;

        if(0 == iType)
        {
            m_pListPiciTestData->at(index)->m_enumSampleType = _enumEmpty;
        }
        else
        {
            m_pListPiciTestData->at(index)->m_enumSampleType = _enumSample;
        }

        if(0 == iTestType)
        {
            m_pListPiciTestData->at(index)->m_enumSampleNumberType = _enum_Sampleml;
        }
        else
        {
            m_pListPiciTestData->at(index)->m_enumSampleNumberType = _enum_Sampleg;
        }

        m_pListPiciTestData->at(index)->m_enumResualtType =(RESUALTTYPE)iResualtType;

        m_pListPiciTestData->at(index)->m_fSampleNumber = fSample;
        m_pListPiciTestData->at(index)->m_fEmptyvolum = strtiji.toFloat();
        m_pListPiciTestData->at(index)->m_fdiding = strnongdu.toFloat();
        m_pListPiciTestData->at(index)->m_strNote = strNote;
    }

    m_bData = true;
}

void QPiciFrom::on_pb_pici_back_clicked()
{

    if(false == m_bData)
    {
#ifdef      _MIPS_LINUX_ENV_
        QMessageBox::StandardButton rb  = QMessageBox::question(this, m_ptc->toUnicode(""), m_ptc->toUnicode("数据未保存，是否退出？"), QMessageBox::Yes | QMessageBox::No);
        if(rb == QMessageBox::Yes)
        {
            this->close();
        }

        if(rb == QMessageBox::No)
        {
        }
        return;
#endif
    }
    else
        this->close();

    m_bData = false;
    emit emitTestData(m_iIndex);
    this->close();
}

void QPiciFrom::on_cb_pici_leixing_currentIndexChanged(int index)
{
    switch(index)
    {
    case _enum_Nitrongen:
    case       _enum_mgNkg:
    case      _enum_mgNg:
    case      _enum_mgNH3kg:
    case _enum_XRecovery:
    case _enum_XPreotein:
    case _enum_mgN100g:
    case _enum_gNkg:

    {
        if(ui->cb_pici_danwei->currentIndex() == 0)
        {
            ui->cb_pici_leixing->setCurrentIndex(0);
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("算法与样品量单位不匹配请重新选择"), QMessageBox::Ok);
        }
    }
        break;


    case _enum_mgNml:
    case _enum_mgN100ml:
    {
        if(ui->cb_pici_danwei->currentIndex() == 1)
        {
            ui->cb_pici_leixing->setCurrentIndex(0);
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("算法与样品量单位不匹配请重新选择"), QMessageBox::Ok);
        }
    }
        break;
    default:
        break;
    }
}

void QPiciFrom::on_cb_pici_danwei_currentIndexChanged(const QString &arg1)
{

}

void QPiciFrom::on_cb_pici_yangpinshuliang_currentIndexChanged(const QString &arg1)
{

    m_ItemModel->setRowCount(arg1.toInt());
    ui->tb_pici_param->setModel(m_ItemModel);
    for(int i = 0; i < arg1.toInt(); i++)
    {
        ui->tb_pici_param->setRowHeight(i,50);
    }
}

void QPiciFrom::on_cb_pici_danwei_currentIndexChanged(int index)
{
    int i_index = ui->cb_pici_leixing->currentIndex();
    if(index == 0)
    {
        if(i_index == 1 || i_index == 2 || i_index == 3 || i_index == 4 || i_index == 9 || i_index == 10 || i_index == 11)
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("算法与样品量单位不匹配请重新选择"), QMessageBox::Ok);
            ui->cb_pici_danwei->setCurrentIndex(1);
        }
    }

    if(index == 1)
    {
        if(i_index == 6 || i_index == 7)
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("算法与样品量单位不匹配请重新选择"), QMessageBox::Ok);
            ui->cb_pici_danwei->setCurrentIndex(0);
        }
    }
}

void QPiciFrom::on_pb_pici_save_clicked()
{
    int irow = 0;
    int icol = 0;
    int iType = 0;
    float f1 = 0;
    QString strpihao = "";
    QByteArray by;
    QString str0, str1, str2;
    irow = m_ItemModel->rowCount();
    icol = m_ItemModel->columnCount();

    m_pListPiciTestData->clear();
    for(int i = 0; i < irow; i++)
    {
        str0 = str1 = str2 = "";
        strpihao = "";
        iType = 0;
        f1 = 0;
        for(int j = 0; j < icol; j++)
        {
            if(0 != m_ItemModel->item(i, j))
            {
                QString str = m_ItemModel->item(i,j)->text();
                if(0 == j)
                {
                    strpihao = str;
                    str0 = str;
                }
                if(1 == j)
                {
                    str1 = str;
                    by.append(str);
                    if(str1 == "样品")
                    {//yangpin
                        iType = 1;
                    }
                    else
                    {//empty
                        iType = 0;
                    }
                }
                if(2 == j)
                {
                    str2 =str;
                    f1 = str.toFloat();
                }
            }

        }

        qDebug() << irow << icol;
        qDebug() << i << str0 << str1 << str2;
        qDebug() << i << strpihao << by << f1;

        if(str0.isEmpty() && str1.isEmpty() && str2.isEmpty())
            break;

        if(str1 == "样品")
        {
            if(f1 <= 0.0)
            {
                QMessageBox::information(this, m_ptc->toUnicode(""),
                                         m_ptc->toUnicode("样品的样品量不能为0，数据保存失败"), QMessageBox::Yes);
                m_bData = false;
                return;
            }
        }

        if(str0.isEmpty())
        {
            QMessageBox::information(this, m_ptc->toUnicode(""),
                                     m_ptc->toUnicode("批号不能空，数据保存失败"), QMessageBox::Yes);
            m_bData = false;
            return;
        }

        SetTestData(strpihao, iType, f1, i);


    }


    QMessageBox::information(this, m_ptc->toUnicode(""),
                             m_ptc->toUnicode("数据保存成功"), QMessageBox::Yes);
}

void QPiciFrom::on_pb_pici_delete_clicked()
{

#ifdef _MIPS_LINUX_ENV_
    QMessageBox::StandardButton rb  = QMessageBox::question(this, m_ptc->toUnicode(""), m_ptc->toUnicode("是否删除当前选中数据"), QMessageBox::Yes | QMessageBox::No);
    if(rb == QMessageBox::Yes)
    {
        int i = ui->tb_pici_param->currentIndex().row();
        m_ItemModel->removeRow(i);
        m_bData = false;
    }

    if(rb == QMessageBox::No)
    {
        return;
    }
#endif
}

void QPiciFrom::on_tb_pici_param_clicked(const QModelIndex &index)
{



}

void QPiciFrom::on_tb_pici_param_doubleClicked(const QModelIndex &index)
{

}

void QPiciFrom::on_tb_pici_param_pressed(const QModelIndex &index)
{

    int irow = index.row();
    int icol = index.column();
    if((irow == 0) && (icol ==0))
        return;
    for(int i = 0; i <= irow; i++)
    {
        for(int j = 0; j <= icol; j++)
        {
            if((i == irow) && (j == icol))
            {
                return;
            }
            if(0 == m_ItemModel->item(i, j))
            {
                QMessageBox::warning(this, m_ptc->toUnicode("ERROR"), m_ptc->toUnicode("检测存在空数据项，请更正后继续输入"), QMessageBox::Yes);
                return;
            }
        }
    }
}
