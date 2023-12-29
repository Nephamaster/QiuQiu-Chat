#include "listwidget.h"
#include "ui_listwidget.h"
#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "frilist.h"
#include "basewindow.h"
#include <QString>
#include <QtDebug>
newsBox::newsBox(const QString &name
                 ,const QString &icon
                 ,const QString &news
                 ,const QString &time
                 ,const QString &dir
                 ,QWidget *parent) :
    QWidget(parent)
{
//*ui设定*//
    //水平布局1
    //QWidget *hlayout_widget = new QWidget(parent);
    QHBoxLayout *hLayout = new QHBoxLayout(this);

    //竖直布局
    QWidget *vlayout_widget = new QWidget(this);
    QVBoxLayout *vLayout = new QVBoxLayout(vlayout_widget);

    //水平布局2
    QWidget *hlayout_widget_2 = new QWidget(vlayout_widget);
    QHBoxLayout *hLayout_2 = new QHBoxLayout(hlayout_widget_2);//水平布局2

    //水平布局3
    QWidget *hlayout_widget_3 = new QWidget(vlayout_widget);
    QHBoxLayout *hLayout_3 = new QHBoxLayout(hlayout_widget_3);//水平布局3

    QPushButton *qqicon = new QPushButton(this);    //头像
    QLabel *qqname = new QLabel(this);     //名字
    QLabel *qqmessage = new QLabel(this);
    QLabel *msg_date_label = new QLabel(this);

    //头像，qq名，qq信息，最后信息时间，发送方向
    Fname = name;
    Ficon = icon;
    Fnews = news;
    Ftime = time;
    Fdir = dir;
    qqicon->setStyleSheet(QString("width:50px;height:50px;border:0px;border-radius:25px;border-image:url(:/image/toolicon/%1);").arg(icon));
    qqname->setText(name);
    qqmessage->setText(news);
    qqmessage->setStyleSheet("font: 100 8pt Microsoft YaHei;color: rgb(116, 120, 122);}");
    msg_date_label->setText(time);
    msg_date_label->setStyleSheet("font: 100 8pt Microsoft YaHei;color: rgb(116, 120, 122);}");

    hLayout->addWidget(qqicon);
    hLayout->addWidget(vlayout_widget);
    vLayout->addWidget(hlayout_widget_2);
    vLayout->addWidget(hlayout_widget_3);
    hLayout_2->addWidget(qqname);
    hLayout_2->addStretch(2);
    hLayout_2->addWidget(msg_date_label);
    hLayout_3->addWidget(qqmessage);

    hLayout_2->setContentsMargins(0,20,0,0);
    hLayout_3->setContentsMargins(0,0,0,20);

    this->resize(290,125);
//******这里要加*******//
    nR = nG = nB = 255;
    nr = 74;
    ng = 144;
    nb = 255;
}

newsBox::~newsBox()
{

}

//双击消息框进入聊天
bool newsBox::eventFilter(QObject *obj, QEvent *eve)
{
    if(obj == this)
    {
        if (eve->type() == QEvent::MouseButtonDblClick)
        {
            ChatWindow* chat = new ChatWindow(Fname, Ficon, Fnews, Fdir, nR, nG, nB, nr, ng, nb, mode);
            chat->show();
            return true;
        }
    }
     return false;
}

ListWidget::ListWidget(QWidget *parent)
    : BaseWindow(parent)
    , ui(new Ui::ListWidget)
{
    ui->setupUi(this);
    iconchange = new iconChange;
    head = NULL;
//*从服务器载入用户所有信息并显示，这里只展示demo*//
    FriNum = 5;//好友数量
    QList<FriMessage> allmsg;//好友信息列表
    FriMessage msg1, msg2, msg3, msg4, msg5;
    msg1.name = "周振翔";
    msg2.name = "周佳慧";
    msg3.name = "田东琦";
    msg4.name = "罗嘉宇";
    msg5.name = "何宇轩";
    msg1.icon = "xiang.jpg";
    msg2.icon = "hui.jpg";
    msg3.icon = "tian.jpg";
    msg4.icon = "Luo.jpg";
    msg5.icon = "usericon.jpg";
    msg2.sign = msg2.sign = msg3.sign = msg4.sign = msg5.sign = "好累啊";
    msg1.lastime = msg2.lastime = msg3.lastime = msg4.lastime = msg5.lastime = "23:59";
    msg1.lastnews = msg2.lastnews = msg3.lastnews = msg4.lastnews = msg5.lastnews = "哈哈哈";
    msg1.direct = msg2.direct = msg4.direct = "rece";
    msg3.direct = msg5.direct = "send";
    allmsg.append(msg1);
    allmsg.append(msg2);
    allmsg.append(msg3);
    allmsg.append(msg4);
    allmsg.append(msg5);
    FriMess = allmsg;
    initMessage("小学期", //用户昵称
                "usericon.jpg", //用户头像
                "好累啊" //用户签名
               );
    vLayout = new QVBoxLayout;
    vLayout->setSpacing(0);
    vLayout->setContentsMargins(0,0,0,0);
    vLayout->addStretch(10);
    //将好友加入消息列表
    for(int i=0;i<FriNum;i++)
    {
        newsBox* box = new newsBox(FriMess[i].name, FriMess[i].icon, FriMess[i].lastnews, FriMess[i].lastime, FriMess[i].direct, this);
        box->installEventFilter(box);
        box->setStyleSheet("QWidget::hover{background-color:rgb(235,235,235)}");
        boxList.append(box);
        vLayout->addWidget(boxList[i]);
    }
    QWidget* pWidget = new QWidget(this);
    pWidget->setLayout(vLayout);
    ui->newslist->setWidget(pWidget);

    //将好友加入联系人列表
    FriList *toolBox = new FriList(ui->friendspage);
    toolBox->resize(350,500);
    toolBox->addFriend(10001,"kid","01","hahah");
    toolBox->addFriend(10002,"一只猪","02","?????");
    toolBox->addGroup(11111,"itKim","03","交流");
    toolBox->addGroup(22222,"睿信","04","年级群");

    //打开修改头像窗口
    connect(head,&QPushButton::clicked,this,&ListWidget::headChange);
    //修改头像
    connect(iconchange, &iconChange::updateHeader, this, &ListWidget::recvsignal);

//*ui设定*//
    // FramelessWindowHint属性设置窗口去除边框;
    // WindowMinimizeButtonHint 属性设置在窗口最小化时，点击任务栏窗口可以显示出原窗口;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    initTitleBar();
    //消息列表区域ScrollArea基本设定
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
    ui->newslist->setFrameStyle(QFrame::NoFrame);
    ui->newslist->setWidgetResizable(true);
    ui->newslist->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->newslist->setVerticalScrollBar(verticalBar);
    ui->newslist->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    //添加好友按钮
    ui->addFri->setStyleSheet(QString("border-image:url(:/image/toolicon/addfri.png);"));
    ui->addFri->setToolTip("添加好友");
    //日间夜间模式切换按钮
    ui->mode->setStyleSheet(QString("border-image:url(:/image/toolicon/sun.png);"));
    ui->mode->setToolTip("切换夜间模式");

    //设置任务栏图标
    this->setWindowIcon(QIcon(":/image/toolicon/ball.png"));
//******这里要加*******//
    //"消息"按钮样式
    ui->messagepushButton->setStyleSheet(QString("QPushButton{background-color:rgba(255,255,255,0);"//背景颜色和透明度
                                                 "color:rgb(74,144,255);"//字体颜色
                                                 "border-radius:0px;"//边框圆角
                                                 "font: 10pt Microsoft YaHei;"//字体类型和字体大小
                                                 "}"
                                                 "QPushButton:hover{"//按下时的状态
                                                 "background-color:rgb(74,144,255);"
                                                 "color:rgb(255,255,255);"
                                                 "}"
                                                 "QPushButton:pressed{"//按下时的状态
                                                 "background-color:rgb(74,144,255);"
                                                 "color:rgb(255,255,255);"
                                                 "}"));
    ui->friendspushButton->setStyleSheet(QString("QPushButton{background-color:rgba(255,255,255,0);"//背景颜色和透明度
                                                 "color:rgb(74,144,255);"//字体颜色
                                                 "border-radius:0px;"//边框圆角
                                                 "font: 10pt Microsoft YaHei;"//字体类型和字体大小
                                                 "}"
                                                 "QPushButton:hover{"//按下时的状态
                                                 "background-color:rgb(74,144,255);"
                                                 "color:rgb(255,255,255);"
                                                 "}"
                                                 "QPushButton:pressed{"//按下时的状态
                                                 "background-color:rgb(74,144,255);"
                                                 "color:rgb(255,255,255);"
                                                 "}"));
//******这里要加*******//
    //设置皮肤
    ui->userBox->setStyleSheet(QString("background-color:rgb(74,144,255)"));
    ui->toolBar->setStyleSheet(QString("background-color:rgb(74, 144, 255)"));
}

ListWidget::~ListWidget()
{
    delete ui;
}

//标题栏初始化
void ListWidget::initTitleBar()
{
//******这里要改*******//
    m_titleBar->setTitleIcon("ball.png", QSize(20,20));
    m_titleBar->setTitleContent("QiuQiu", 10);
    m_titleBar->setButtonType(MIN_BUTTON);
    m_titleBar->setTitleWidth(this->width());
}

//用户信息初始化
void ListWidget::initMessage(const QString name, const QString icon, const QString sign)
{
//******这里要改*******//
    //用户信息布局
    head = new QPushButton(this);
    QLineEdit *username = new QLineEdit(this);     //名字
    QLineEdit *usersign = new QLineEdit(this);
    head->setMouseTracking(true);
    head->setStyleSheet(QString("width:70px;height:70px;border:0px;border-radius:35px;"
                                    "border-image:url(:/image/toolicon/%1);").arg(icon));
    username->setText(name);
    username->setStyleSheet("QLineEdit{"
                            "font: 500 11pt Microsoft YaHei;"
                            "color: white;"
                            "border: 0px;"
                            "background-color: rgba(0,0,0,0)}");
    usersign->setText(sign);
    usersign->setStyleSheet("QLineEdit{"
                            "font: 100 8pt Microsoft YaHei;"
                            "color: white;"
                            "border: 0px;"
                            "background-color: rgba(0,0,0,0)}");
    //竖直布局
    QWidget *vlayout_widget = new QWidget(this);
    QVBoxLayout *vLayout = new QVBoxLayout(vlayout_widget);
    //水平布局2
    QWidget *hlayout_widget_2 = new QWidget(vlayout_widget);
    QHBoxLayout *hLayout_2 = new QHBoxLayout(hlayout_widget_2);//水平布局2
    //水平布局3
    QWidget *hlayout_widget_3 = new QWidget(vlayout_widget);
    QHBoxLayout *hLayout_3 = new QHBoxLayout(hlayout_widget_3);//水平布局3
    ui->userLayout->addWidget(head);
    ui->userLayout->addWidget(vlayout_widget);
    vLayout->addWidget(hlayout_widget_2);
    vLayout->addWidget(hlayout_widget_3);
    hLayout_2->addWidget(username);
    hLayout_2->addStretch(2);
    //hLayout_2->addWidget(qqmessage);
    hLayout_3->addWidget(usersign);
    hLayout_2->setContentsMargins(0,10,0,0);
    hLayout_3->setContentsMargins(0,0,0,15);
}

//按键功能实现
void ListWidget::on_messagepushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void ListWidget::on_friendspushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//******这里要改*******//
void ListWidget::on_mode_clicked()
{
    if(ui->mode->toolTip() == "切换夜间模式")
    {
        ui->mode->setStyleSheet(QString("border-image:url(:/image/toolicon/moon.png);"));
        ui->mode->setToolTip("切换日间模式");
        themeChange(72, 61, 120, 72, 61, 139, 1);
    }
    else if(ui->mode->toolTip() == "切换日间模式")
    {
        ui->mode->setStyleSheet(QString("border-image:url(:/image/toolicon/sun.png);"));
        ui->mode->setToolTip("切换夜间模式");
        themeChange(255, 255, 255, 74, 144, 255, 0);
    }
}

//******这里要加*******//
void ListWidget::themeChange(int br, int bg, int bb, int tr, int tg, int tb, int mode)
{
    R = br;
    G = bg;
    B = bb;
    tR = tr;
    tG = tg;
    tB = tb;
    bgR = br;
    bgG = bg;
    bgB = bb;
    for(int i=0;i<FriNum;i++)
    {
        boxList[i]->nR = R;
        boxList[i]->nG = G;
        boxList[i]->nB = B;
        boxList[i]->nr = tr;
        boxList[i]->ng = tg;
        boxList[i]->nb = tb;
        boxList[i]->mode = mode;
    }
    setColor();
    ui->userBox->setStyleSheet(QString("background-color: rgb(%1,%2,%3)").arg(tr).arg(tg).arg(tb));
    ui->toolBar->setStyleSheet(QString("background-color: rgb(%1,%2,%3)").arg(tr).arg(tg).arg(tb));
    m_titleBar->setBackgroundColor(tr, tg, tb);
    //"消息"按钮样式
    int bgr, bgg, bgb;
    if(mode == 0)
    {
        bgr = bgg = bgb = 255;
    }
    else
    {
        bgr = tr;
        bgg = tg;
        bgb = tb;
        tr = tg = tb = 255;
    }
    ui->messagepushButton->setStyleSheet(QString("QPushButton{background-color:rgb(%4,%5,%6);"//背景颜色和透明度
                                                 "color:rgb(%1,%2,%3);"//字体颜色
                                                 "font: 10pt Microsoft YaHei;"//字体类型和字体大小
                                                 "border-radius:0px;"//边框圆角
                                                 "}"
                                                 "QPushButton:hover{"//按下时的状态
                                                 "background-color:rgb(%1,%2,%3);"
                                                 "color:rgb(%4,%5,%6);"
                                                 "}"
                                                 "QPushButton:pressed{"//按下时的状态
                                                 "background-color:rgb(%1,%2,%3);"
                                                 "color:rgb(%4,%5,%6);"
                                                 "}").arg(tr).arg(tg).arg(tb).arg(bgr).arg(bgg).arg(bgb));
    ui->friendspushButton->setStyleSheet(QString("QPushButton{background-color:rgb(%4,%5,%6);"//背景颜色和透明度
                                                 "color:rgb(%1,%2,%3);"//字体颜色
                                                 "font: 10pt Microsoft YaHei;"//字体类型和字体大小
                                                 "border-radius:0px;"//边框圆角
                                                 "}"
                                                 "QPushButton:hover{"//按下时的状态
                                                 "background-color:rgb(%1,%2,%3);"
                                                 "color:rgb(%4,%5,%6);"
                                                 "}"
                                                 "QPushButton:pressed{"//按下时的状态
                                                 "background-color:rgb(%1,%2,%3);"
                                                 "color:rgb(%4,%5,%6);"
                                                 "}").arg(tr).arg(tg).arg(tb).arg(bgr).arg(bgg).arg(bgb));
}

void ListWidget::headChange()
{
    iconchange->show();
}

void ListWidget::recvsignal(const QString &iconPath)
{
    usericon = iconPath;
    qDebug()<<usericon;
    head->setStyleSheet(QString("width:70px;height:70px;border:0px;border-radius:35px;border-image:url(:/image/toolicon/%1);").arg(usericon));
///客户端组实现将本地头像上传至云端
//*...*//
}

void ListWidget::on_addFri_clicked()
{
    addwindow = new Addfriend;
    addwindow->show();
}
