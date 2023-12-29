#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H
//注册界面
#include <QWidget>
#include <QSystemTrayIcon>
#include <QMouseEvent>
#include <QMovie>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class registerWidget;
}

class registerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit registerWidget(QWidget *parent = nullptr);
    ~registerWidget();

private:
    Ui::registerWidget *ui;

signals:
    void registerTologin();
private slots:
    void on_returnpushButton_clicked();
    void on_nextpagepushButton_clicked();
    void on_toolButton_clicked();
    void on_toolButton_2_clicked();

    void on_prepagepushButton_clicked();

    void on_choosepushButton_clicked();

private:
    bool isPressedWidget;
    QPoint last;
    void mousePressEvent(QMouseEvent *event);//鼠标点击
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动
    void mouseReleaseEvent(QMouseEvent *event);//鼠标释放
    QSystemTrayIcon  * systemtrayicon;  //系统托盘

private:
    QMovie *m_movie;
};

#endif // REGISTERWIDGET_H
