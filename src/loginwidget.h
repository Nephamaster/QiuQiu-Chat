#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "registerwidget.h"
#include "listwidget.h"
#include <QPoint>
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMovie>

//登录界面
QT_BEGIN_NAMESPACE
namespace Ui { class loginWidget; }
QT_END_NAMESPACE

class loginWidget : public QWidget
{
    Q_OBJECT

public:
    loginWidget(QWidget *parent = nullptr);
    ~loginWidget();

private slots:
    void on_loginpushButton_clicked();
    void on_registerpushButton_clicked();
    void on_register_received();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

private:
    Ui::loginWidget *ui;
    registerWidget regwin;
    ListWidget mainwin;

private:
    bool isPressedWidget;
    QPoint last;
    void mousePressEvent(QMouseEvent *event);//鼠标点击
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动
    void mouseReleaseEvent(QMouseEvent *event);//鼠标释放
    QSystemTrayIcon  * systemtrayicon;  //系统托盘

private:
    QMenu * menu;
    QAction *m_pShowAction;
    QAction *m_pCloseAction;
private slots:
    void showwidget();
    void closewidget();

private:
    QMovie *m_movie;

};
#endif // LOGINWIDGET_H
