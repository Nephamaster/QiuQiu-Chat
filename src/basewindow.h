#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QWidget>
#include "titlebar.h"

class BaseWindow : public QWidget
{
    Q_OBJECT

public:
    BaseWindow(QWidget *parent = 0);
    ~BaseWindow();
    void initTitleBar();
    void paintEvent(QPaintEvent *event);
    //背景默认色
    int bgR = 255;
    int bgG = 255;
    int bgB = 255;
    //标题栏默认色
    int titleR;
    int titleG;
    int titleB;
    void setColor();

private:
    void loadStyleSheet(const QString &sheetName);

private slots:
    void onButtonMinClicked();
    void onButtonRestoreClicked();
    void onButtonMaxClicked();
    void onButtonCloseClicked();

protected:
    TitleBar* m_titleBar;

};

#endif // BASEWINDOW_H
