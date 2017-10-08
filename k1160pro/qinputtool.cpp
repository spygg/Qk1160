
#include "qinputtool.h"
#include "ui_qinputtool.h"
#include "qdesktopwidget.h"
#include "DataDef.h"
#include <QDebug>
#include "QHBoxLayout"

QInputTool *QInputTool::_instance = 0;
QInputTool::QInputTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QInputTool)
{
    ui->setupUi(this);
    this->InitProperty();
    this->InitForm();
    this->ChangeStyle();
    m_ptc =  QTextCodec::codecForName("UTF-8");

}

QInputTool::~QInputTool()
{
    delete ui;
}

void QInputTool::Init(QString position, QString style, int btnFontSize, int labFontSize)
{
    this->currentPosition = position;
    this->currentStyle = style;
    this->btnFontSize = btnFontSize;
    this->labFontSize = labFontSize;
    this->ChangeStyle();
    this->ChangeFont();
}

void QInputTool::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void QInputTool::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void QInputTool::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void QInputTool::InitForm()
{
    this->mousePressed = false;
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    //this->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint);



    QDesktopWidget w;
    deskWidth = w.availableGeometry().width();
    deskHeight = w.availableGeometry().height();
    frmWidth = this->width();
    frmHeight = this->height();

    QSqlDatabase DbConn;
    DbConn = QSqlDatabase::addDatabase("QSQLITE", "pinyin");
    //qDebug() << qApp->applicationDirPath();
    DbConn.setDatabaseName(qApp->applicationDirPath() + "/db/PinYin.db");
    DbConn.open();

    isFirst = true;
    isPress = false;
    timerPress = new QTimer(this);
    connect(timerPress, SIGNAL(timeout()), this, SLOT(reClicked()));

    currentWidget = 0;
    currentLineEdit = 0;
    currentTextEdit = 0;
    currentPlain = 0;
    currentBrowser = 0;
    currentEditType = "";
    bLetterFlag = true;

    //如果需要更改输入法面板的显示位置,改变currentPosition这个变量即可
    //control--显示在对应输入框的正下方 bottom--填充显示在底部  center--窗体居中显示
    currentPosition = "";

    //如果需要更改输入法面板的样式,改变currentStyle这个变量即可
    //blue--淡蓝色  dev--dev风格  black--黑色  brown--灰黑色  lightgray--浅灰色  darkgray--深灰色  gray--灰色  silvery--银色
    currentStyle = "";

    //输入法面板字体大小,如果需要更改面板字体大小,该这里即可
    btnFontSize = 10;
    labFontSize = 10;

    //如果需要更改输入法初始模式,改变currentType这个变量即可
    //min--小写模式  max--大写模式  chinese--中文模式
    currentType = "min";
    changeType(currentType);
    clickNum();

    QList<QPushButton *> btn = this->findChildren<QPushButton *>();
    foreach (QPushButton * b, btn) {
        connect(b, SIGNAL(clicked()), this, SLOT(btn_clicked()));
    }

    //绑定全局改变焦点信号槽
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)),
            this, SLOT(focusChanged(QWidget *, QWidget *)));

    //绑定按键事件过滤器
    qApp->installEventFilter(this);
}

void QInputTool::InitStyle()
{
    QString        style = QString(DEFAULT_STYLE_BUTTON) + QString(DEFAULT_BACKGROUND_BUTTON);

    QPalette palette;
    QPixmap pixmap(":/images/bk/keyboardw.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    this->setPalette(palette);

    ui->btna->setStyleSheet(style);
    ui->btnb->setStyleSheet(style);
    ui->btnc->setStyleSheet(style);
    ui->btnd->setStyleSheet(style);
    ui->btne->setStyleSheet(style);
    ui->btnf->setStyleSheet(style);
    ui->btng->setStyleSheet(style);
    ui->btnh->setStyleSheet(style);
    ui->btni->setStyleSheet(style);
    ui->btnj->setStyleSheet(style);
    ui->btnk->setStyleSheet(style);
    ui->btnl->setStyleSheet(style);
    ui->btnm->setStyleSheet(style);
    ui->btnn->setStyleSheet(style);
    ui->btno->setStyleSheet(style);
    ui->btnp->setStyleSheet(style);
    ui->btnq->setStyleSheet(style);
    ui->btnr->setStyleSheet(style);
    ui->btns->setStyleSheet(style);
    ui->btnt->setStyleSheet(style);
    ui->btnu->setStyleSheet(style);
    ui->btnv->setStyleSheet(style);
    ui->btnw->setStyleSheet(style);
    ui->btnx->setStyleSheet(style);
    ui->btny->setStyleSheet(style);
    ui->btnz->setStyleSheet(style);

    ui->btnDot->setStyleSheet(style);
    ui->btnSpace->setStyleSheet(style);
    ui->btnDelete->setStyleSheet(style);
    ui->btnType->setStyleSheet(style);
    ui->btnType_2->setStyleSheet(style);
    ui->btnType_123->setStyleSheet(style);
    ui->btnClose->setStyleSheet(style);
    ui->btnPre->setStyleSheet(style);
    ui->btnNext->setStyleSheet(style);


    ui->btn0->setStyleSheet(style);
    ui->btn1->setStyleSheet(style);
    ui->btn2->setStyleSheet(style);
    ui->btn3->setStyleSheet(style);
    ui->btn4->setStyleSheet(style);
    ui->btn5->setStyleSheet(style);
    ui->btn6->setStyleSheet(style);
    ui->btn7->setStyleSheet(style);
    ui->btn8->setStyleSheet(style);
    ui->btn9->setStyleSheet(style);

    ui->btnOther1->setStyleSheet(style);
    ui->btnOther2->setStyleSheet(style);
    ui->btnOther3->setStyleSheet(style);
    ui->btnOther4->setStyleSheet(style);
    ui->btnOther5->setStyleSheet(style);
    ui->btnOther6->setStyleSheet(style);
    ui->btnOther7->setStyleSheet(style);
    ui->btnOther8->setStyleSheet(style);
    ui->btnOther9->setStyleSheet(style);
    ui->btnOther10->setStyleSheet(style);
    ui->btnOther11->setStyleSheet(style);
    ui->btnOther12->setStyleSheet(style);
    ui->btnOther13->setStyleSheet(style);
    ui->btnOther14->setStyleSheet(style);
    ui->btnOther15->setStyleSheet(style);
    ui->btnOther16->setStyleSheet(style);
    ui->btnOther17->setStyleSheet(style);
    ui->btnOther18->setStyleSheet(style);
    ui->btnOther19->setStyleSheet(style);
    ui->btnOther20->setStyleSheet(style);
    ui->btnOther21->setStyleSheet(style);

}

void QInputTool::InitProperty()
{

    InitStyle();
    ui->btnOther1->setProperty("btnOther", true);
    ui->btnOther2->setProperty("btnOther", true);
    ui->btnOther3->setProperty("btnOther", true);
    ui->btnOther4->setProperty("btnOther", true);
    ui->btnOther5->setProperty("btnOther", true);
    ui->btnOther6->setProperty("btnOther", true);
    ui->btnOther7->setProperty("btnOther", true);
    ui->btnOther8->setProperty("btnOther", true);
    ui->btnOther9->setProperty("btnOther", true);
    ui->btnOther10->setProperty("btnOther", true);
    ui->btnOther11->setProperty("btnOther", true);
    ui->btnOther12->setProperty("btnOther", true);
    ui->btnOther13->setProperty("btnOther", true);
    ui->btnOther14->setProperty("btnOther", true);
    ui->btnOther15->setProperty("btnOther", true);
    ui->btnOther16->setProperty("btnOther", true);
    ui->btnOther17->setProperty("btnOther", true);
    ui->btnOther18->setProperty("btnOther", true);
    ui->btnOther19->setProperty("btnOther", true);
    ui->btnOther20->setProperty("btnOther", true);
    ui->btnOther21->setProperty("btnOther", true);

    ui->btnDot->setProperty("btnOther", true);
    ui->btnSpace->setProperty("btnOther", true);
    ui->btnDelete->setProperty("btnOther", true);
    ui->btnType_2->setProperty("btnOther", true);
    ui->btnType_123->setProperty("btnOther", true);

    ui->btn0->setProperty("btnNum", true);
    ui->btn1->setProperty("btnNum", true);
    ui->btn2->setProperty("btnNum", true);
    ui->btn3->setProperty("btnNum", true);
    ui->btn4->setProperty("btnNum", true);
    ui->btn5->setProperty("btnNum", true);
    ui->btn6->setProperty("btnNum", true);
    ui->btn7->setProperty("btnNum", true);
    ui->btn8->setProperty("btnNum", true);
    ui->btn9->setProperty("btnNum", true);
    //ui->btn00->setProperty("btnNum", true);

    ui->btna->setProperty("btnLetter", true);
    ui->btnb->setProperty("btnLetter", true);
    ui->btnc->setProperty("btnLetter", true);
    ui->btnd->setProperty("btnLetter", true);
    ui->btne->setProperty("btnLetter", true);
    ui->btnf->setProperty("btnLetter", true);
    ui->btng->setProperty("btnLetter", true);
    ui->btnh->setProperty("btnLetter", true);
    ui->btni->setProperty("btnLetter", true);
    ui->btnj->setProperty("btnLetter", true);
    ui->btnk->setProperty("btnLetter", true);
    ui->btnl->setProperty("btnLetter", true);
    ui->btnm->setProperty("btnLetter", true);
    ui->btnn->setProperty("btnLetter", true);
    ui->btno->setProperty("btnLetter", true);
    ui->btnp->setProperty("btnLetter", true);
    ui->btnq->setProperty("btnLetter", true);
    ui->btnr->setProperty("btnLetter", true);
    ui->btns->setProperty("btnLetter", true);
    ui->btnt->setProperty("btnLetter", true);
    ui->btnu->setProperty("btnLetter", true);
    ui->btnv->setProperty("btnLetter", true);
    ui->btnw->setProperty("btnLetter", true);
    ui->btnx->setProperty("btnLetter", true);
    ui->btny->setProperty("btnLetter", true);
    ui->btnz->setProperty("btnLetter", true);

    labCh.append(ui->labCh0);
    labCh.append(ui->labCh1);
    labCh.append(ui->labCh2);
    labCh.append(ui->labCh3);
    labCh.append(ui->labCh4);
    labCh.append(ui->labCh5);
    labCh.append(ui->labCh6);
    labCh.append(ui->labCh7);
    labCh.append(ui->labCh8);
    labCh.append(ui->labCh9);
    for (int i = 0; i < 10; i++) {
        labCh[i]->installEventFilter(this);
    }
}

void QInputTool::ShowPanel()
{
    this->setVisible(true);

    int width = ui->btn0->width();
    width = width > 40 ? width : 40;
    ui->btnPre->setMinimumWidth(width);
    ui->btnPre->setMaximumWidth(width);
    ui->btnNext->setMinimumWidth(width);
    ui->btnNext->setMaximumWidth(width);
    //ui->btnClose->setMinimumWidth(width);
    //ui->btnClose->setMaximumWidth(width);
}

//事件过滤器,用于识别鼠标单击汉字标签处获取对应汉字
bool QInputTool::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        btnPress = (QPushButton *)obj;


        if(obj == ui->labCh0)
            setChinese(0);
        else if(obj == ui->labCh1)
            setChinese(1);
        else if(obj == ui->labCh2)
            setChinese(2);
        else if(obj == ui->labCh3)
            setChinese(3);
        else if(obj == ui->labCh4)
            setChinese(4);
        else if(obj == ui->labCh5)
            setChinese(5);
        else if(obj == ui->labCh6)
            setChinese(6);
        else if(obj == ui->labCh7)
            setChinese(7);
        else if(obj == ui->labCh8)
            setChinese(8);
        else if(obj == ui->labCh9)
            setChinese(9);
        else if (currentEditType != "" && obj != ui->btnClose && currentEditType != "QWidget") {
            //qDebug() << "currentEditType 111:"<< currentEditType;
            //qDebug() << "str_btnPress 111:"<< str_btnPress;
            //if(str_btnPress != "K1160PRO")
            {
                //qDebug() << "str_btnPress 222:"<< str_btnPress;
                ShowPanel();
            }

        }

        btnPress = (QPushButton *)obj;
        if (checkPress()) {
            isPress = true;
            timerPress->start(500);
        }
        return false;
    } else if (event->type() == QEvent::MouseButtonRelease) {
        btnPress = (QPushButton *)obj;
        if (checkPress()) {
            isPress = false;
            timerPress->stop();
        }
        return false;
    } else if (event->type() == QEvent::KeyPress) {
        //如果输入法窗体不可见,则不需要处理
        if (!isVisible()) {
            return QWidget::eventFilter(obj, event);
        }

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        //Shift切换输入法模式,esc键关闭输入法面板,空格取第一个汉字,退格键删除
        //中文模式下回车键取拼音,中文模式下当没有拼音时可以输入空格
        if (keyEvent->key() == Qt::Key_Space) {
            if (ui->labPY->text() != "") {
                setChinese(0);
                return true;
            } else {
                return false;
            }
        } else if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            insertValue(ui->labPY->text());
            ui->labPY->setText("");
            selectChinese();
            return true;
        } else if (keyEvent->key() == Qt::Key_Shift) {
            ui->btnType->click();
            return true;
        } else if (keyEvent->key() == Qt::Key_Escape) {
            ui->btnClose->click();
            return true;
        } else if (keyEvent->key() == Qt::Key_Backspace) {
            ui->btnDelete->click();
            return true;
        } else if (keyEvent->text() == "+" || keyEvent->text() == "=") {
            if (ui->labPY->text() != "") {
                ui->btnNext->click();
                return true;
            } else {
                return false;
            }
        } else if (keyEvent->text() == "-" || keyEvent->text() == "_") {
            if (ui->labPY->text() != "") {
                ui->btnPre->click();
                return true;
            } else {
                return false;
            }
        } else if (keyEvent->key() == Qt::Key_CapsLock) {
            if (currentType != "max") {
                currentType = "max";
            } else {
                currentType = "min";
            }
            changeType(currentType);
            return true;
        } else {
            if (currentEditType == "QWidget") {
                return false;
            }
            QString key;
            if (currentType == "chinese") {
                key = keyEvent->text();
            } else if (currentType == "min") {
                key = keyEvent->text().toLower();
            } else if (currentType == "max") {
                key = keyEvent->text().toUpper();
            }
            QList<QPushButton *> btn = this->findChildren<QPushButton *>();
            foreach (QPushButton * b, btn) {
                if (b->text() == key) {
                    b->click();
                    return true;
                }
            }
        }
        return false;
    }
    return QWidget::eventFilter(obj, event);
}

bool QInputTool::checkPress()
{
    //只有属于输入法键盘的合法按钮才继续处理
    bool num_ok = btnPress->property("btnNum").toBool();
    bool other_ok = btnPress->property("btnOther").toBool();
    bool letter_ok = btnPress->property("btnLetter").toBool();
    if (num_ok || other_ok || letter_ok) {
        return true;
    }
    return false;
}

void QInputTool::reClicked()
{
    if (isPress) {
        timerPress->setInterval(30);
        btnPress->click();
    }
}

void QInputTool::focusChanged(QWidget *oldWidget, QWidget *nowWidget)
{

    //qDebug() << "oldWidget:" << oldWidget << " nowWidget:" << nowWidget;
    if (nowWidget != 0 && !this->isAncestorOf(nowWidget)) {
        //在Qt5和linux系统中(嵌入式linux除外),当输入法面板关闭时,焦点会变成无,然后焦点会再次移到焦点控件处
        //这样导致输入法面板的关闭按钮不起作用,关闭后马上有控件获取焦点又显示.
        //为此,增加判断,当焦点是从有对象转为无对象再转为有对象时不要显示.
        //这里又要多一个判断,万一首个窗体的第一个焦点就是落在可输入的对象中,则要过滤掉
#ifndef _MIPS_LINUX_ENV_
        if (oldWidget == 0x0 && !isFirst) {
            return;
        }
#endif

        isFirst = false;
        if (nowWidget->inherits("QLineEdit")) {
            currentLineEdit = (QLineEdit *)nowWidget;
            currentEditType = "QLineEdit";
            ShowPanel();
        } else if (nowWidget->inherits("QTextEdit")) {
            currentTextEdit = (QTextEdit *)nowWidget;
            currentEditType = "QTextEdit";
            //ShowPanel();
        } else if (nowWidget->inherits("QPlainTextEdit")) {
            currentPlain = (QPlainTextEdit *)nowWidget;
            currentEditType = "QPlainTextEdit";
            //ShowPanel();
        } else if (nowWidget->inherits("QComboBox")) {
            QComboBox *cbox = (QComboBox *)nowWidget;
            //只有当下拉选择框处于编辑模式才可以输入
            if (cbox->isEditable()) {
                currentLineEdit = cbox->lineEdit() ;
                currentEditType = "QLineEdit";
                //ShowPanel();
            }
        } else if (nowWidget->inherits("QSpinBox") ||
                   nowWidget->inherits("QDoubleSpinBox") ||
                   nowWidget->inherits("QDateEdit") ||
                   nowWidget->inherits("QTextBrowser") ||
                   nowWidget->inherits("QTimeEdit") ||
                   nowWidget->inherits("QPushButton") ||
                   nowWidget->inherits("QLabel") ||
                   nowWidget->inherits("QDateTimeEdit")) {
            currentWidget = nowWidget;
            currentEditType = "QWidget";
            //ShowPanel();
        } else if(nowWidget->inherits("QPushButton")){
            //需要将输入法切换到最初的原始状态--小写,同时将之前的对象指针置为零
            currentWidget = 0;
            currentLineEdit = 0;
            currentTextEdit = 0;
            currentPlain = 0;
            currentBrowser = 0;
            currentEditType = "";
            currentType = "min";
            changeType(currentType);
            this->setVisible(false);
        }else {
            //需要将输入法切换到最初的原始状态--小写,同时将之前的对象指针置为零
            currentWidget = 0;
            currentLineEdit = 0;
            currentTextEdit = 0;
            currentPlain = 0;
            currentBrowser = 0;
            currentEditType = "";
            currentType = "min";
            changeType(currentType);
            this->setVisible(false);
        }


        //根据用户选择的输入法位置设置-居中显示-底部填充-显示在输入框正下方
        if (currentPosition == "center") {
            QPoint pos = QPoint(deskWidth / 2 - frmWidth / 2, deskHeight / 2 - frmHeight / 2);
            this->setGeometry(pos.x(), pos.y(), frmWidth, frmHeight);
        } else if (currentPosition == "bottom") {
            this->setGeometry(0, deskHeight - frmHeight, deskWidth, frmHeight);
        } else if (currentPosition == "control") {
            int frmRealHeight = frmHeight;
            QWidget* currentFocusWidget = nowWidget;

            if(currentFocusWidget == NULL)
                return;

            QRect rect = currentFocusWidget->rect();
            QPoint pos = QPoint(rect.left(), rect.top() + 31 + 2);
            QPoint pos2 = QPoint(rect.left(), rect.bottom() + 2);
            pos = currentFocusWidget->mapToGlobal(pos);
            pos2 = currentFocusWidget->mapToGlobal(pos2);
            int ih2 = pos2.y() + frmHeight;
            int ih = pos.y() + frmHeight;

            int HN_SCRN_WIDTH = QApplication::desktop()->availableGeometry().width();
            int HN_SCRN_HEIGHT = QApplication::desktop()->availableGeometry().height();

            if(ih > 768 && ih2 > 768)
                //up
                this->setGeometry(( HN_SCRN_WIDTH - frmWidth) / 2, 0, frmWidth, frmRealHeight);
            else
                //down
                this->setGeometry(( HN_SCRN_WIDTH - frmWidth) / 2,
                                  ( HN_SCRN_HEIGHT - frmRealHeight),
                                  frmWidth, frmRealHeight);
        }
    }
}

void QInputTool::changeType(QString type)
{
    if (type == "max") {
        changeLetter(true);
        //ui->btnType->setText(tr("大写"));
       // ui->labInfo->setText(tr("中文输入法--大写"));
        //ui->btnType->setText(m_ptc->toUnicode("大写"));
        //ui->labInfo->setText(m_ptc->toUnicode("中文输入法--大写"));
        ui->btnOther12->setText("/");
        ui->btnOther14->setText(":");
        ui->btnOther17->setText(",");
        ui->btnOther18->setText("\\");
        ui->btnOther21->setText("\"");
    } else if (type == "min") {
        changeLetter(false);
        //ui->btnType->setText(m_ptc->toUnicode("小写"));
        //ui->labInfo->setText(m_ptc->toUnicode("中文输入法--小写"));
        ui->btnOther12->setText("/");
        ui->btnOther14->setText(":");
        ui->btnOther17->setText(",");
        ui->btnOther18->setText("\\");
        ui->btnOther21->setText("\"");
    } else {
        changeLetter(false);
        //ui->btnType->setText(m_ptc->toUnicode("中文"));
        //ui->labInfo->setText(m_ptc->toUnicode("中文输入法--中文"));
        ui->btnOther12->setText("。");
        ui->btnOther14->setText("：");
        ui->btnOther17->setText("，");
        ui->btnOther18->setText("；");
        ui->btnOther21->setText("“");
    }
    //每次切换到模式,都要执行清空之前中文模式下的信息
    clearChinese();
    ui->labPY->setText("");
}

void QInputTool::changeLetter(bool isUpper)
{
    QList<QPushButton *> btn = this->findChildren<QPushButton *>();
    foreach (QPushButton * b, btn) {
        if (b->property("btnLetter").toBool()) {
            if (isUpper) {
                b->setText(b->text().toUpper());
            } else {
                b->setText(b->text().toLower());
            }
        }
    }
}

void QInputTool::selectChinese()
{
    clearChinese();
    QSqlQuery query(QSqlDatabase::database("pinyin"));
    QString currentPY = ui->labPY->text();
    QString sql = "select [word] from [pinyin] where [pinyin]='" + currentPY + "';";
    query.exec(sql);
    //逐个将查询到的字词加入汉字队列
    while(query.next()) {
        QString result = query.value(0).toString();
        QStringList text = result.split(" ");
        foreach (QString txt, text) {
            if (txt.length() > 0 && txt.length() < 2) {
                allPY.append(txt);
                currentPY_count++;
            }
        }
    }
    showChinese();
}

void QInputTool::showChinese()
{
    //每个版面最多显示10个汉字
    int count = 0;
    currentPY.clear();
    for (int i = 0; i < 10; i++) {
        labCh[i]->setText("");
    }

    for (int i = currentPY_index; i < currentPY_count; i++) {
        if (count == 10) {
            break;
        }
        QString txt = QString("%1. %2").arg(count).arg(allPY[currentPY_index]);
        currentPY.append(allPY[currentPY_index]);
        labCh[count]->setText(txt);
        count++;
        currentPY_index++;
    }
    qDebug() << "currentPY_index:" << currentPY_index << "currentPY_count:" << currentPY_count;
}

void QInputTool::btn_clicked()
{
    //如果当前焦点控件类型为空,则返回不需要继续处理
    if (currentEditType == "") {
        return;
    }

    QPushButton *btn = (QPushButton *)sender();
    QString objectName = btn->objectName();

    if (objectName == "btnType") {
        if (currentType == "chinese") {
            currentType = "min";
        }
        else if(currentType == "min")
        {
            currentType = "max";
        }
        else
           currentType = "min";
        /*
        if (currentType == "min") {
            currentType = "max";
        } else if (currentType == "max") {
            currentType = "chinese";
        } else if (currentType == "chinese") {
            currentType = "min";
        }
        */
        bLetterFlag = true;
        clickNum();

        changeType(currentType);
    } else if(objectName == "btnType_2")
    {
        if (currentType == "min") {
            currentType = "chinese";
        }
        else
           currentType = "chinese";
        bLetterFlag = true;
        clickNum();
        changeType(currentType);
    }else if (objectName == "btnDelete") {
        //如果当前是中文模式,则删除对应拼音,删除完拼音之后再删除对应文本输入框的内容
        if (currentType == "chinese") {
            QString txt = ui->labPY->text();
            int len = txt.length();
            if (len > 0) {
                ui->labPY->setText(txt.left(len - 1));
                selectChinese();
            } else {
                deleteValue();
            }
        } else {
            deleteValue();
        }
    } else if (objectName == "btnPre") {
        if (currentPY_index >= 20) {
            //每次最多显示10个汉字,所以每次向前的时候索引要减20
            if (currentPY_index % 10 == 0) {
                currentPY_index -= 20;
            } else {
                currentPY_index = currentPY_count - (currentPY_count % 10) - 10;
            }
        } else {
            currentPY_index = 0;
        }
        showChinese();
    } else if (objectName == "btnNext") {
        if (currentPY_index < currentPY_count - 1) {
            showChinese();
        }
    } else if (objectName == "btnClose") {
        this->setVisible(false);
        this->hide();
    } else if (objectName == "btnSpace") {
        insertValue(" ");
    } else {
        QString value = btn->text();
        //如果是&按钮，因为对应&被过滤,所以真实的text为去除前面一个&字符
        if (objectName == "btnOther7") {
            value = value.right(1);
        }
        if(objectName == "btnType_123")
        {
            bLetterFlag = false;
            clickNum();
        }
        //当前不是中文模式,则单击按钮对应text为传递参数
        if ((currentType != "chinese")&&(objectName != "btnType_123")&&(objectName != "btnType_2")) {
            insertValue(value);
        } else {
            //中文模式下,不允许输入特殊字符,单击对应数字按键取得当前索引的汉字
            if (btn->property("btnOther").toBool()) {
                if ((ui->labPY->text().length() == 0)&&(objectName != "btnType_123")&&(objectName != "btnType_2")) {
                    insertValue(value);
                }

            } else if (btn->property("btnNum").toBool()) {
                if ((ui->labPY->text().length() == 0)&&(objectName != "btnType_123")&&(objectName != "btnType_2")) {
                    insertValue(value);
                } else if (objectName == "btn0") {
                    setChinese(0);
                } else if (objectName == "btn1") {
                    setChinese(1);
                } else if (objectName == "btn2") {
                    setChinese(2);
                } else if (objectName == "btn3") {
                    setChinese(3);
                } else if (objectName == "btn4") {
                    setChinese(4);
                } else if (objectName == "btn5") {
                    setChinese(5);
                } else if (objectName == "btn6") {
                    setChinese(6);
                } else if (objectName == "btn7") {
                    setChinese(7);
                } else if (objectName == "btn8") {
                    setChinese(8);
                } else if (objectName == "btn9") {
                    setChinese(9);
                }
            } else if (btn->property("btnLetter").toBool()) {
                ui->labPY->setText(ui->labPY->text() + value);
                selectChinese();
            }
        }
    }
}

void QInputTool::insertValue(QString value)
{
    if (currentEditType == "QLineEdit") {
        currentLineEdit->insert(value);
    } else if (currentEditType == "QTextEdit") {
        currentTextEdit->insertPlainText(value);
    } else if (currentEditType == "QPlainTextEdit") {
        currentPlain->insertPlainText(value);
    } else if (currentEditType == "QTextBrowser") {
        currentBrowser->insertPlainText(value);
    } else if (currentEditType == "QWidget") {
        QKeyEvent keyPress(QEvent::KeyPress, 0, Qt::NoModifier, QString(value));
        QApplication::sendEvent(currentWidget, &keyPress);
    }
}

void QInputTool::deleteValue()
{
    if (currentEditType == "QLineEdit") {
        currentLineEdit->backspace();
    } else if (currentEditType == "QTextEdit") {
        //获取当前QTextEdit光标,如果光标有选中,则移除选中字符,否则删除光标前一个字符
        QTextCursor cursor = currentTextEdit->textCursor();
        if(cursor.hasSelection()) {
            cursor.removeSelectedText();
        } else {
            cursor.deletePreviousChar();
        }
    } else if (currentEditType == "QPlainTextEdit") {
        //获取当前QTextEdit光标,如果光标有选中,则移除选中字符,否则删除光标前一个字符
        QTextCursor cursor = currentPlain->textCursor();
        if(cursor.hasSelection()) {
            cursor.removeSelectedText();
        } else {
            cursor.deletePreviousChar();
        }
    } else if (currentEditType == "QTextBrowser") {
        //获取当前QTextEdit光标,如果光标有选中,则移除选中字符,否则删除光标前一个字符
        QTextCursor cursor = currentBrowser->textCursor();
        if(cursor.hasSelection()) {
            cursor.removeSelectedText();
        } else {
            cursor.deletePreviousChar();
        }
    } else if (currentEditType == "QWidget") {
        QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier, QString());
        QApplication::sendEvent(currentWidget, &keyPress);
    }
}

void QInputTool::setChinese(int index)
{
    int count = currentPY.count();
    if (count > index) {
        insertValue(currentPY[index]);
        //添加完一个汉字后,清空当前汉字信息,等待重新输入
        clearChinese();
        ui->labPY->setText("");
    }
}

void QInputTool::clearChinese()
{
    //清空汉字,重置索引
    for (int i = 0; i < 10; i++) {
        labCh[i]->setText("");
    }
    allPY.clear();
    currentPY.clear();
    currentPY_index = 0;
    currentPY_count = 0;
}

void QInputTool::ChangeStyle()
{
    if (currentStyle == "blue") {
        changeStyle("#DEF0FE", "#C0DEF6", "#C0DCF2", "#386487");
    } else if (currentStyle == "dev") {
        //changeStyle("#C0D3EB", "#BCCFE7", "#B4C2D7", "#324C6C");
    } else if (currentStyle == "gray") {
        //changeStyle("#E4E4E4", "#A2A2A2", "#A9A9A9", "#000000");
    } else if (currentStyle == "lightgray") {
        //changeStyle("#EEEEEE", "#E5E5E5", "#D4D0C8", "#6F6F6F");
    } else if (currentStyle == "darkgray") {
        //changeStyle("#D8D9DE", "#C8C8D0", "#A9ACB5", "#5D5C6C");
    } else if (currentStyle == "black") {
        //changeStyle("#4D4D4D", "#292929", "#D9D9D9", "#CACAD0");
    } else if (currentStyle == "brown") {
        //changeStyle("#667481", "#566373", "#C2CCD8", "#E7ECF0");
    } else if (currentStyle == "silvery") {
        //changeStyle("#E1E4E6", "#CCD3D9", "#B2B6B9", "#000000");
    }
}

void QInputTool::ChangeFont()
{
    QFont btnFont(this->font().family(), btnFontSize);
    QFont labFont(this->font().family(), labFontSize);
/*
    QList<QPushButton *> btns = ui->widgetMain->findChildren<QPushButton *>();
    foreach (QPushButton * btn, btns) {
        btn->setFont(btnFont);
    }

    QList<QLabel *> labs = ui->widgetTop->findChildren<QLabel *>();
    foreach (QLabel * lab, labs) {
        lab->setFont(labFont);
    }
*/
    ui->btnPre->setFont(labFont);
    ui->btnNext->setFont(labFont);
    ui->btnClose->setFont(labFont);
}

void QInputTool::changeStyle(QString topColor, QString bottomColor, QString borderColor, QString textColor)
{
    QStringList qss;
    qss.append(QString("QWidget#QInputTool{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %1,stop:1 %2);}")
               .arg(topColor).arg(bottomColor));
    qss.append("QPushButton{padding:5px;border-radius:3px;}");
    qss.append(QString("QPushButton:hover{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %1,stop:1 %2);}")
               .arg(topColor).arg(bottomColor));
    qss.append(QString("QLabel,QPushButton{color:%1;}").arg(textColor));
    qss.append(QString("QPushButton#btnPre,QPushButton#btnNext,QPushButton#btnClose{padding:5px;}"));
    qss.append(QString("QPushButton{border:1px solid %1;}")
               .arg(borderColor));
    qss.append(QString("QLineEdit{border:1px solid %1;border-radius:5px;padding:2px;background:none;selection-background-color:%2;selection-color:%3;}")
               .arg(borderColor).arg(bottomColor).arg(topColor));
    this->setStyleSheet(qss.join(""));
}

void QInputTool::clickNum()
{
    if(true == bLetterFlag)
    {
        bLetterFlag = false;

        ui->btna->show();
        ui->btnb->show();
        ui->btnc->show();
        ui->btnd->show();
        ui->btne->show();
        ui->btnf->show();
        ui->btng->show();
        ui->btnh->show();
        ui->btni->show();
        ui->btnj->show();
        ui->btnk->show();
        ui->btnl->show();
        ui->btnm->show();
        ui->btnn->show();
        ui->btno->show();
        ui->btnp->show();
        ui->btnq->show();
        ui->btnr->show();
        ui->btns->show();
        ui->btnt->show();
        ui->btnu->show();
        ui->btnv->show();
        ui->btnw->show();
        ui->btnx->show();
        ui->btny->show();
        ui->btnz->show();

        ui->btnDot->show();
        ui->btnOther9->show();
        ui->btnOther15->show();
        ui->btnOther17->show();

        ui->btn0->hide();
        ui->btn1->hide();
        ui->btn2->hide();
        ui->btn3->hide();
        ui->btn4->hide();
        ui->btn5->hide();
        ui->btn6->hide();
        ui->btn7->hide();
        ui->btn8->hide();
        ui->btn9->hide();

        ui->btnOther1->hide();
        ui->btnOther2->hide();
        ui->btnOther3->hide();
        ui->btnOther4->hide();
        ui->btnOther5->hide();
        ui->btnOther6->hide();
        ui->btnOther7->hide();
        ui->btnOther8->hide();
        ui->btnOther10->hide();
        ui->btnOther11->hide();
        ui->btnOther12->hide();
        ui->btnOther13->hide();
        ui->btnOther14->hide();
        //ui->btnOther15->hide();
        ui->btnOther16->hide();
        ui->btnOther18->hide();
        ui->btnOther19->hide();
        ui->btnOther20->hide();
        ui->btnOther21->hide();
    }
    else
    {
        ui->btna->hide();
        ui->btnb->hide();
        ui->btnc->hide();
        ui->btnd->hide();
        ui->btne->hide();
        ui->btnf->hide();
        ui->btng->hide();
        ui->btnh->hide();
        ui->btni->hide();
        ui->btnj->hide();
        ui->btnk->hide();
        ui->btnl->hide();
        ui->btnm->hide();
        ui->btnn->hide();
        ui->btno->hide();
        ui->btnp->hide();
        ui->btnq->hide();
        ui->btnr->hide();
        ui->btns->hide();
        ui->btnt->hide();
        ui->btnu->hide();
        ui->btnv->hide();
        ui->btnw->hide();
        ui->btnx->hide();
        ui->btny->hide();
        ui->btnz->hide();


        ui->btnOther9->hide();
        //ui->btnOther15->hide();
        ui->btnOther17->hide();

        ui->btn0->show();
        ui->btn1->show();
        ui->btn2->show();
        ui->btn3->show();
        ui->btn4->show();
        ui->btn5->show();
        ui->btn6->show();
        ui->btn7->show();
        ui->btn8->show();
        ui->btn9->show();

        ui->btnOther1->show();
        ui->btnOther2->show();
        ui->btnOther3->show();
        ui->btnOther4->show();
        ui->btnOther5->show();
        ui->btnOther6->show();
        ui->btnOther7->show();
        ui->btnOther8->show();
        ui->btnOther10->show();
        ui->btnOther11->show();
        ui->btnOther12->show();
        ui->btnOther13->show();
        ui->btnOther14->show();
        //ui->btnOther15->show();
        ui->btnOther16->show();
        ui->btnOther18->show();
        ui->btnOther19->show();
        ui->btnOther20->show();
        ui->btnOther21->show();
    }
}
