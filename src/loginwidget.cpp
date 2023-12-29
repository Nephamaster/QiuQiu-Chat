#include "loginwidget.h"
#include "ui_loginwidget.h"

#include <QDebug>

loginWidget::loginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::loginWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("QiuQiu");
//关闭系统标题和任务栏
    this->setWindowFlags(Qt::SplashScreen|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
//右下角系统托盘
    //初始化系统托盘
    systemtrayicon = new QSystemTrayIcon(this);
    QIcon icon = QIcon(":/image/toolicon/ball.png");
    //添加图标
    systemtrayicon->setIcon(icon);
    //当鼠标悬浮，显示文字
    systemtrayicon->setToolTip(QObject::tr("QiuQiu"));
    //显示图标
    systemtrayicon->show();
//右下角右击菜单
    menu = new QMenu(this);
    m_pShowAction = new QAction("打开主界面");
    m_pCloseAction = new QAction("退出");
    menu->addAction(m_pShowAction);
    menu->addSeparator();
    menu->addAction(m_pCloseAction);
    systemtrayicon->setContextMenu(menu);
    connect(m_pShowAction, &QAction::triggered, this, &loginWidget::showwidget);
    connect(m_pCloseAction, &QAction::triggered, this, &loginWidget::closewidget);

//设置背景
    m_movie = new QMovie(":/new/pic/background/pokemon-pokemon-sun-and-moon.gif");
    m_movie->setScaledSize(QSize(661,221));
    ui->giflabel->setMovie(m_movie);
    m_movie->start();

//ID文本框
    QAction *searchAction = new QAction(ui->idlineEdit);
    searchAction->setIcon(QIcon(":/image/toolicon/pokeid.png"));
    ui->idlineEdit->addAction(searchAction,QLineEdit::LeadingPosition);//表示action所在方位（左侧）。
//密码文本框
    QAction *searchAction_2 = new QAction(ui->pwlineEdit);
    searchAction_2->setIcon(QIcon(":/image/toolicon/lock.png"));
    ui->pwlineEdit->addAction(searchAction_2,QLineEdit::LeadingPosition);//表示action所在方位（左侧）。
    QAction *searchAction_3 = new QAction(ui->pwlineEdit);
    searchAction_3->setIcon(QIcon(":/image/toolicon/preview-close.png"));
    ui->pwlineEdit->addAction(searchAction_3,QLineEdit::TrailingPosition);//表示action所在方位（右侧）。

    //连接注册窗口返回
    connect(&regwin, &registerWidget::registerTologin, this, &loginWidget::on_register_received);

//添加icon
    ui->signlabel->setPixmap(QPixmap(":/image/toolicon/pokeball.png"));
    ui->signlabel->setScaledContents(true);
    //ui->signlabel->resize(150,150);

    //设置密码是否可见

    //设置找回密码按钮
    ui->pushButton->setFlat(true);
    //设置注册按钮
//    QStringList *list = new QStringList();
//    list->append("color:rgb(38,133,227)");
//    //list.append("background-color:rgb(255,0,0)");
//    list->append("border-style:outset");
//    list->append("border-width:0px");
//    //list.append("border-color:rgb(255,0,0)");
//    list->append("border-radius:10px");//顶角弧度
//    //list->append("font:bold 15px");
//    list->append("padding:1px");

    ui->registerpushButton->setFlat(true);
    //ui->registerpushButton->setStyleSheet(list->join(';'));

    //pressed
    //list->replace(4, "font:bold 20px");
//    connect(ui->registerpushButton, &QPushButton::pressed, [=]()
//    {
//        ui->registerpushButton->setStyleSheet(list->join(';'));
//    });

    //released
//    list->replace(4, "font:bold 15px");
//    connect(ui->registerpushButton, &QPushButton::released, [=]()
//    {
//        ui->registerpushButton->setStyleSheet(list->join(';'));
//    });

    //设置登录按钮
    QStringList *list = new QStringList();
    list->append("color:rgb(255,255,255)");
    list->append("background-color:rgb(95,188,255)");
    //list->append("border-width:0px");
    //list->append("border-color:rgb(255,0,0)");
    list->append("border-radius:5px");//顶角弧度
    list->append("font-size: 15px");
    //list->append("padding:1px");
    ui->loginpushButton->setStyleSheet(list->join(';'));

    QStringList *list2 = new QStringList();
    list2->append("color:rgb(255,255,255)");
    list2->append("background-color:rgb(95,188,255)");
    //list2->append("border-width:0px");
    //list2->append("border-color:rgb(255,0,0)");
    list2->append("border-radius:5px");//顶角弧度
    list2->append("padding-left:2px");
    list2->append("padding-top:2px");

    //pressed
    //list->replace(5, "font-size: 20px");
    connect(ui->registerpushButton, &QPushButton::pressed, [=]()
    {
        ui->registerpushButton->setStyleSheet(list2->join(';'));
    });

    //released
    //list->replace(5, "font-size: 15px");
    connect(ui->registerpushButton, &QPushButton::released, [=]()
    {
        ui->registerpushButton->setStyleSheet(list->join(';'));
    });
}

loginWidget::~loginWidget()
{
    delete ui;
}

void loginWidget::on_loginpushButton_clicked()
{
    qDebug()<<"login successed";
    this->hide();
    mainwin.show();
}

void loginWidget::on_registerpushButton_clicked()//切换至注册界面
{
    this->hide();
    regwin.show();
}

void loginWidget::on_register_received()//接收到返回信号
{
    this->show();
}

void loginWidget::on_toolButton_clicked()
{
    this->hide();
}

void loginWidget::on_toolButton_2_clicked()
{
    this->close();
    qApp->quit();
}

void loginWidget::mousePressEvent(QMouseEvent *event)
{
    isPressedWidget = true; // 当前鼠标按下的即是QWidget而非界面上布局的其它控件
    last = event->globalPos();
}

void loginWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (isPressedWidget)
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        last = event->globalPos();
        move(x()+dx, y()+dy);
    }
}

void loginWidget::mouseReleaseEvent(QMouseEvent *event)
{
    int dx = event->globalX() - last.x();
    int dy = event->globalY() - last.y();
    move(x()+dx, y()+dy);
    isPressedWidget = false; // 鼠标松开时，置为false
}

void loginWidget::showwidget()
{
    this->show();
}

void loginWidget::closewidget()
{
    this->close();
    qApp->quit();
}




