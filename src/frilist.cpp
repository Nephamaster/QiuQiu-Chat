#include "frilist.h"
#include <QGroupBox>
#include <QVBoxLayout>

FriList::FriList(QWidget *parent,Qt::WindowFlags f)
    :QToolBox(parent,f)
{
    friendBox = new QGroupBox;
    groupBox = new QGroupBox;

    this->resize(400, 600);

    this->setLayFri();
    this->setLayGro();
    this->setWindowTitle("QiuQiu");
    //设置背景
}

void FriList::setLayFri()
{
    //好友页布局
    layout_fri = new QVBoxLayout(friendBox);
    layout_fri->setContentsMargins(0, 0, 0, 0);
    layout_fri->setAlignment(Qt::AlignTop);
    this->addItem((QWidget*)friendBox,QString("好友列表"));

    //设置背景
}

void FriList::setLayGro()
{
    //群组页布局
    layout_group = new QVBoxLayout(groupBox);
    layout_group->setContentsMargins(0, 0, 0, 0);
    layout_group->setAlignment(Qt::AlignTop);
    this->addItem((QWidget*)groupBox,QString("群组列表"));
}

void FriList::addFriend(int id, QString user, QString icon, QString desc)
{
    QToolButton *tempButton = new QToolButton;
    QString iconpath = QString(":/new/pic/head/%1.jpeg").arg(icon);
    QString text = QString("%1 : %2").arg(user).arg(desc);
    tempButton->setText(text);
    qDebug()<<iconpath;
    tempButton->setIcon(QPixmap(iconpath));
    tempButton->setIconSize(QSize(100,30)); //设置按钮尺寸
    tempButton->setAutoRaise(true);   //当鼠标离开时，按钮恢复为弹起状态
    tempButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); //设置按钮文字显示在图标旁边
    friend_list.append(tempButton);
    layout_fri->addWidget(friend_list.last());
}

void FriList::addGroup(int id, QString name, QString icon, QString desc)
{
    QToolButton *tempButton = new QToolButton;
    QString iconpath = QString(":/new/pic/head/%1.jpeg").arg(icon);
    QString text = QString("%1 : %2").arg(name).arg(desc);
    tempButton->setText(text);
    qDebug()<<iconpath;
    tempButton->setIcon(QPixmap(iconpath));
    tempButton->setIconSize(QSize(100,30)); //设置按钮尺寸
    tempButton->setAutoRaise(true);   //当鼠标离开时，按钮恢复为弹起状态
    tempButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); //设置按钮文字显示在图标旁边
    group_list.append(tempButton);
    layout_group->addWidget(group_list.last());
}
