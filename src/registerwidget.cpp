#include "registerwidget.h"
#include "ui_registerwidget.h"

registerWidget::registerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registerWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("注册");
//关闭系统标题
    this->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
    ui->stackedWidget->setCurrentIndex(0);

    ui->returnpushButton->setFlat(true);

//设置任务栏图标
    this->setWindowIcon(QIcon(":/image/toolicon/ball.png"));

//设置背景
    m_movie = new QMovie(":/new/pic/background/pokemon-pikachu.gif");
    m_movie->setScaledSize(QSize(571,201));
    ui->giflabel->setMovie(m_movie);
    m_movie->start();

    //返回键
    ui->returnpushButton->setFlat(true);
    //上一页
    ui->prepagepushButton->setFlat(true);
    //下一页
    ui->nextpagepushButton->setFlat(true);
    //确定键
    ui->pushButton->setFlat(true);
    //选择头像
    ui->choosepushButton->setFlat(true);
}

registerWidget::~registerWidget()
{
    delete ui;
}

void registerWidget::on_returnpushButton_clicked()
{
    this->hide();
    emit registerTologin();
    ui->stackedWidget->setCurrentIndex(0);
}

void registerWidget::on_nextpagepushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void registerWidget::on_toolButton_clicked()
{
    this->hide();
}

void registerWidget::on_toolButton_2_clicked()
{
    this->close();
    qApp->quit();
}

void registerWidget::mousePressEvent(QMouseEvent *event)
{
    isPressedWidget = true; // 当前鼠标按下的即是QWidget而非界面上布局的其它控件
    last = event->globalPos();
}

void registerWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (isPressedWidget)
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        last = event->globalPos();
        move(x()+dx, y()+dy);
    }
}

void registerWidget::mouseReleaseEvent(QMouseEvent *event)
{
    int dx = event->globalX() - last.x();
    int dy = event->globalY() - last.y();
    move(x()+dx, y()+dy);
    isPressedWidget = false; // 鼠标松开时，置为false
}

void registerWidget::on_prepagepushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void registerWidget::on_choosepushButton_clicked()
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this, tr("选择头像"), "", tr("Images(*.png *.bmp *.jpg *.tif *.jpeg)"));
    if(!filename.isEmpty())
    {
        QImage* img=new QImage;
        if(! ( img->load(filename) ) ) //加载图像
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("打开图像失败!"));
            delete img;
        }
        ui->headlabel->setStyleSheet("border-width:0px");
        ui->headlabel->setPixmap(QPixmap::fromImage(*img));
        ui->headlabel->setScaledContents(true);
    }
}
