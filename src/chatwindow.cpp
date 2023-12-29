#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "basewindow.h"
#include "sendfile.h"

#include <QEvent>
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QPushButton>
#include <QFont>
#include <QApplication>
#include <QPainter>
#include <QtDebug>
#include<QFileDialog>
#include <QPoint>
#include <QFileInfo>

//*聊天气泡*//
Bubble::Bubble(Message msg, QWidget* parent)
    : QFrame (parent)
{
    mainLayout = new QHBoxLayout;
    pCurMessage = msg;
    initUI();
    setLayout(mainLayout);
    mainLayout->setContentsMargins(0,0,0,0);
    setFrameShape(QFrame::NoFrame);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

Bubble::~Bubble()
{

}
//气泡样式设定
void Bubble::initUI()
{
    QVBoxLayout* plv = new QVBoxLayout;
    QHBoxLayout* plh = new QHBoxLayout;

    messageEdit = new QTextEdit;
    //根据文本容量改变气泡大小
    connect(messageEdit->document(),&QTextDocument::contentsChange,this,&Bubble::adjustContent);
    //设定基本样式
    messageEdit->setMaximumWidth(300);
    messageEdit->setText(pCurMessage.content);
    messageEdit->setTextColor(Qt::white);
    messageEdit->setReadOnly(true);
    messageEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    messageEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    messageEdit->setStyleSheet("background-color:rgba(74,144,255,1); color:white;border-radius:10px;");
    messageEdit->viewport()->setContentsMargins(20,0,20,0);
    messageEdit->setMouseTracking(true);
    messageEdit->viewport()->setMouseTracking(true);
    messageEdit->viewport()->installEventFilter(this);
    messageEdit->setAlignment(Qt::AlignJustify);

    plh->addStretch(10);
    plh->addWidget(messageEdit);
    plv->addLayout(plh);
    plv->setSpacing(0);
    mainLayout->addLayout(plv);
}

//气泡尺寸自适应（功能未完善）
void Bubble::adjustContent()
{
    QTextDocument *document=qobject_cast<QTextDocument*>(sender());
    document->adjustSize();
    if(document)
    {
        document->setDocumentMargin(10);
        QTextEdit *editor = qobject_cast<QTextEdit*>(document->parent()->parent());
        if (editor)
        {
            QString text = editor->toPlainText().trimmed();
            if (text.isEmpty())
               return;
            QFontMetrics mert  = editor->viewport()->fontMetrics();
            int nCount = text.count("\n");
            int width = mert.width(text);
            int height = mert.height();

            if (width > editor->maximumWidth() || (width < editor->maximumWidth() && nCount > 0))
            {
                float fheight = (width / (300*1.0)) + nCount;
                int nheight = (width / (300*1.0)) + nCount;
                float d = fheight - nheight;
                if (d > 0)
                {
                    if(width > editor->maximumWidth())
                        nheight ++;
                }
                    editor->setFixedSize(editor->maximumWidth(), nheight * height);
            }
            else
                editor->setFixedSize(width + 21, 36);
        }
    }
}

ChatWindow::ChatWindow(const QString &name
                       ,const QString &icon
                       ,const QString &news
                       ,const QString &dir,
                       //******这里要加*******//
                       int r,
                       int g,
                       int b,
                       int tr,
                       int tg,
                       int tb,
                       int mode,
                       QWidget *parent) :
    BaseWindow(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);

//*好友信息载入*//
    //载入上次聊天的最后一条消息
    Message lastmsg;
    lastmsg.direct = dir;
    lastmsg.content = news;
    //addMessage(lastmsg);

//*信息收发*//
    //“发送”按钮槽函数
        connect(ui->Send,&QPushButton::clicked,this,&ChatWindow::sendMessage);
    //发送文件按钮槽函数
        connect(ui->file,&QPushButton::clicked,this,&ChatWindow::sendfiles);
    //接收文件槽函数 具体参考这条博客的client.cpp中 https://blog.csdn.net/weixin_42579072/article/details/103667913?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166114679916782246423637%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=166114679916782246423637&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-103667913-null-null.142^v42^new_blog_pos_by_title,185^v2^control&utm_term=qt%20%E6%96%87%E4%BB%B6%E4%BC%A0%E8%BE%93&spm=1018.2226.3001.4187
//    connect(fileSocket,&QTcpSocket::readyRead,[=](){};


//*ui设定*//
    setWindowFlags(Qt::FramelessWindowHint); //去掉窗口边框
    initTitleBar(name, icon);
    setTheme(r,g,b,tr,tg,tb,mode);//******这里要加*******//
    verticalBar = new QScrollBar;
    //滚动条样式设置 后续在qss中实现
    verticalBar->setStyleSheet("QScrollBar:vertical"
                               "{"
                               "width:8px;"
                               "background:rgba(0,0,0,0%);"
                               "margin:0px,0px,0px,0px;"
                               "padding-top:9px;"
                               "padding-bottom:9px;"
                               "}"
                               "QScrollBar::handle:vertical"
                               "{"
                               "width:8px;"
                               "background:rgba(0,0,0,25%);"
                               " border-radius:4px;"
                               "min-height:20;"
                               "}"
                               "QScrollBar::handle:vertical:hover"
                               "{"
                               "width:8px;"
                               "background:rgba(0,0,0,50%);"
                               " border-radius:4px;"
                               "min-height:20;"
                               "}"
                               "QScrollBar::add-line:vertical"
                               "{"
                               "height:9px;width:8px;"
                               "border-image:url(:/image/toolicon/arrowdown.png);"
                               "subcontrol-position:bottom;"
                               "}"
                               "QScrollBar::sub-line:vertical"
                               "{"
                               "height:9px;width:8px;"
                               "border-image:url(:/image/toolicon/arrowup.png);"
                               "subcontrol-position:top;"
                               "}"
                               "QScrollBar::add-line:vertical:hover"
                               "{"
                               "height:9px;width:8px;"
                               //"border-image:url(:/images/a/4.png);"
                               "subcontrol-position:bottom;"
                               "}"
                               "QScrollBar::sub-line:vertical:hover"
                               "{"
                               "height:9px;width:8px;"
                               //"border-image:url(:/images/a/2.png);"
                               "subcontrol-position:top;"
                               "}"
                               "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical"
                               "{"
                               "background:rgba(0,0,0,10%);"
                               "border-radius:4px;"
                               "}");
    ui->scrollArea->setFrameStyle(QFrame::NoFrame);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea->setVerticalScrollBar(verticalBar);
    ui->scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->scrollArea->setStyleSheet(QString("background-color: rgb(255, 255, 255);"));
    //气泡装入widget 从而在滚动显示区域scrollArea显示
    QWidget* pWidget = new QWidget(this);
    vLayout = new QVBoxLayout;
    vLayout->setSpacing(10);
    vLayout->setContentsMargins(10,10,10,10);
    vLayout->addStretch(10);
    pWidget->setLayout(vLayout);
    ui->scrollArea->setWidget(pWidget);
    //编辑区
    ui->textEdit->setFrameStyle(QFrame::NoFrame);
    ui->textEdit->setFontFamily("Microsoft YaHei");
    ui->textEdit->setPlaceholderText(QString("发一条友善的消息吧"));
    ui->textEdit->installEventFilter(this);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

//设定标题栏
void ChatWindow::initTitleBar(const QString &name, const QString &icon)
{
    m_titleBar->setTitleIcon(icon, QSize(20,20));
    m_titleBar->setButtonType(MIN_BUTTON);//******这里要改*******//
    m_titleBar->setTitleWidth(this->width());
    m_titleBar->m_pTitleContent->setText(name);
    QFont font = QFont("Microsoft YaHei", 11);
    m_titleBar->m_pTitleContent->setFont(font);
    m_titleBar->m_pTitleContent->setStyleSheet("QLabel{color:rgb(255, 255, 255);}");
    connect(m_titleBar, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));
}

//******这里要加*******//
void ChatWindow::setTheme(int r, int g, int b, int tr, int tg, int tb, int mode)
{
    bgR = r;
    bgG = g;
    bgB = b;
    setColor();
    m_titleBar->setBackgroundColor(tr, tg, tb);
    if(mode == 0)
    {
        ui->scrollArea->setStyleSheet(QString("background-color: rgb(255, 255, 255);"));
        ui->textEdit->setStyleSheet(QString("background-color: rgb(238, 242, 255);"));
        ui->Close->setStyleSheet(QString("font: 25 12pt Microsoft YaHei;"
                                         "color: rgb(255, 255, 255);"
                                         "background-color: rgb(255, 129, 131);"
                                         "border-radius:5px"));
        ui->Send->setStyleSheet(QString("font: 25 12pt Microsoft YaHei;"
                                         "color: rgb(255, 255, 255);"
                                         "background-color: rgb(134, 170, 255);"
                                         "border-radius:5px;"));
    }
    else if(mode == 1)
    {
        ui->scrollArea->setStyleSheet(QString("background-color: rgb(128, 118, 163);"));
        ui->textEdit->setStyleSheet(QString("background-color: rgb(128, 118, 163);"));
        ui->Close->setStyleSheet(QString("font: 25 12pt Microsoft YaHei;"
                                         "color: rgb(255, 255, 255);"
                                         "background-color: rgb(%1, %2, %3);"
                                         "border-radius:5px").arg(tr).arg(tg).arg(tb));
        ui->Send->setStyleSheet(QString("font: 25 12pt Microsoft YaHei;"
                                         "color: rgb(255, 255, 255);"
                                         "background-color: rgb(%1, %2, %3);"
                                         "border-radius:5px;").arg(tr).arg(tg).arg(tb));
    }
    else
    {
        ui->scrollArea->setStyleSheet(QString("background-color: rgb(255, 255, 255);"));
        ui->textEdit->setStyleSheet(QString("background-color: rgb(238, 242, 255);"));
        ui->Close->setStyleSheet(QString("font: 25 12pt Microsoft YaHei;"
                                         "color: rgb(255, 255, 255);"
                                         "background-color: rgb(255, 129, 131);"
                                         "border-radius:5px"));
        ui->Send->setStyleSheet(QString("font: 25 12pt Microsoft YaHei;"
                                         "color: rgb(255, 255, 255);"
                                         "background-color: rgb(134, 170, 255);"
                                         "border-radius:5px;"));
    }
}

//发送文件功能
void ChatWindow::sendfiles()
{
    //打开文件
    QString filepath = QFileDialog::getOpenFileName(this,"选择文件",QDir::currentPath());
    file = new QFile(filepath);
    QFileInfo info(filepath);
    //显示文件发送窗口
    if(sender.isVisible())
    {
        return;
    }
    sender.initsender(info, file->size());
    sender.move(this->pos() + QPoint(650,0));
    sender.show(); //显示sendfile窗口

/// 客户端组实现部分
    totalsize = file->size(); //文件总字节数
    byteToWrite = file->size(); //尚未发送的字节数

    //更新进度条的连接函数
//connect(fileSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateSendProgress(qint64))); 这里注释掉是因为我没有tcp库，所以无法声明socket变量

/*
需要完善updateSendProgress(qint64)和updateRecvProgress(qint64)槽函数的filesocket部分
具体可参考：
https://blog.csdn.net/sinat_21107433/article/details/80150575?ops_request_misc=&request_id=&biz_id=102&utm_term=qt%E8%81%8A%E5%A4%A9%E6%96%87%E4%BB%B6%E5%8F%91%E9%80%81&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-2-80150575.142^v42^new_blog_pos_by_title,185^v2^control
*/

}

//更新发送进度条 请完善socket部分
void ChatWindow::updateSendProgress(qint64 numBytes)
{
    //已经发送的数据大小
    bytewritten += (int)numBytes;

    //如果已经发送了数据
    if(bytewritten > 0)
    {
        outBlock = file->read(qMin(byteToWrite,perDataSize));
        //发送完一次数据后还剩余数据的大小
//        byteToWrite -= ((int)fileSocket->write(outBlock));
        //清空发送缓冲区
//        outBlock.resize(0);
    }
    else
        file->close();
    //更新进度条
    sender.updateBar(totalsize, bytewritten);
    //如果发送完毕
    if(bytewritten == totalsize)
    {
        file->close();
        //fileSocket->close();
    }
}

//更新接收进度 请完善socket部分
//可以看看上文我在ChatWindow构造函数里提到的在网上看到的接受文件的信号槽函数
//那个可以实现接收文件时更新进度条，也可以试试那个
void ChatWindow::updateRecvProgress()
{
    //QDataStream inFile(this->fileSocket);
    //inFile.setVersion(QDataStream::Qt_4_8);

    //如果接收到的数据小于16个字节，保存到来的文件头结构
    if(bytesReceived <= sizeof(qint64)*2)
    {
        /*if((fileSocket->bytesAvailable()>=(sizeof(qint64))*2) && (filenameSize==0))
        {
            inFile>>totalBytes>>filenameSize;
            bytesReceived += sizeof(qint64)*2;
        }
        if((fileSocket->bytesAvailable()>=filenameSize) && (filenameSize != 0))
        {
            inFile>>filename;
            bytesReceived += filenameSize;
            filename = "ServerData/"+filename;
            file = new QFile(filename);
            if(!file->open(QFile::WriteOnly))
            {
                qDebug()<<"Server::open file error!";
                return;
            }
        }
        else
            return;*/
    }
    //如果接收的数据小于总数据，则写入文件
    if(bytesReceived < totalsize)
    {
        //bytesReceived += fileSocket->bytesAvailable();
        //inBlock = fileSocket->readAll();
        file->write(inBlock);
        inBlock.resize(0);
    }

    //数据接收完成时
    if(bytesReceived == totalsize)
    {
        bytesReceived = 0;
        totalsize = 0;
        filenameSize = 0;
        file->close();
        //fileSocket->close();
    }
}

//添加消息
void ChatWindow::addMessage(Message msg)
{
    Bubble* pFrame = new Bubble(msg, ui->scrollArea);

    int count = vLayout->count();
    //本人气泡显示在左侧，对方气泡显示在右侧
    qDebug()<<msg.direct;
    if(msg.direct == 'rece')
        vLayout->insertWidget(count-1, pFrame, 0, Qt::AlignLeft);
    else vLayout->insertWidget(count-1, pFrame);
    verticalBar->setRange(0, ui->scrollArea->height());
    //所有消息列表
    pMessages.push_back(pFrame);
    verticalBar->setValue(verticalBar->maximum());
}

//发送消息功能
void ChatWindow::sendMessage()
{
    QString msg = ui->textEdit->toPlainText();

    // 把最后一个回车换行符删掉
    while (msg.endsWith("\n")) {
        msg.remove(msg.length() - 2, 2);
    }
    if(msg.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("不能发送空白消息");
        msgBox.exec();
        return;
    }
    // 清除输入框
    ui->textEdit->clear();
    Message message;
    message.content = msg;
    addMessage(message);
}

//编辑区事件过滤器
bool ChatWindow::eventFilter(QObject *object, QEvent *event)
{
    if(object == ui->textEdit)
    {
         if(event->type() == QEvent::KeyPress)
         {
             QKeyEvent* peve = dynamic_cast<QKeyEvent*>(event);
             if((peve->modifiers() & Qt::ControlModifier) && (peve->key() == Qt::Key_Return || peve->key() == Qt::Key_Enter)) //Ctrl + Enter　换行
             {
                 ui->textEdit->insertPlainText(QString(" ") += '\n');
                 return true;
             }
             if(peve->key() == Qt::Key_Return || peve->key() == Qt::Key_Enter) //回车键盘
             {
                 sendMessage();
                 return true;
             }
         }
    }
    return false;
}

//鼠标拖动窗口
void ChatWindow::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();       // 获得部件当前位置
    this->mousePos = event->globalPos(); // 获得鼠标位置
    this->dPos = mousePos - windowPos;   // 移动后部件所在的位置
}

void ChatWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - this->dPos);
    if(sender.isVisible())
    {
        sender.move(event->globalPos() - this->dPos + QPoint(650, 0));
    }
}

void ChatWindow::onButtonCloseClicked()
{
    if(sender.isVisible())
    {
        sender.close();
    }
    close();
}
