#include "acceptfriend.h"
#include "ui_acceptfriend.h"

Acceptfriend::Acceptfriend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Acceptfriend)
{
    ui->setupUi(this);
//关闭系统标题
    this->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
//设置任务栏图标
    this->setWindowIcon(QIcon(":/image/toolicon/ball.png"));
}

Acceptfriend::~Acceptfriend()
{
    delete ui;
}

void Acceptfriend::on_toolButton_clicked()
{
    this->hide();
}

void Acceptfriend::on_toolButton_2_clicked()
{
    this->close();
}
