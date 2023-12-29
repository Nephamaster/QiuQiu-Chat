#include "addfriend.h"
#include "ui_addfriend.h"

Addfriend::Addfriend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Addfriend)
{
    ui->setupUi(this);

//关闭系统标题
    this->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
//设置任务栏图标
    this->setWindowIcon(QIcon(":/image/toolicon/ball.png"));
}

Addfriend::~Addfriend()
{
    delete ui;
}

void Addfriend::on_toolButton_clicked()
{
    this->hide();
}

void Addfriend::on_toolButton_2_clicked()
{
    this->close();
}
