#ifndef LISTWIDGET_H
#define LISTWIDGET_H
//主界面
#include "basewindow.h"
#include "iconchange.h"
#include "addfriend.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QList>
#include <QScrollArea>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class ListWidget; }
QT_END_NAMESPACE

//好友信息
struct FriMessage
{
    QString name;               //好友昵称
    QString icon;               //好友头像
    QString sign;               //好友签名
    QString lastnews;           //用户与好友发的最后一条消息
    QString direct;             //最后一条消息发送方向，send代表用户发送，rece代表好友发送
    QString lastime;            //最后一条消息的时间
};

class newsBox : public QWidget
{
    Q_OBJECT

public:
    explicit newsBox(const QString &name
                    ,const QString &icon
                    ,const QString &news
                    ,const QString &time
                    ,const QString &dir
                    ,QWidget *parent = nullptr);
    ~newsBox();
    QString Fname;
    QString Ficon;
    QString Fnews;
    QString Ftime;
    QString Fdir;
//******这里要加*******//
    int nR;
    int nG;
    int nB;
    int nr;
    int ng;
    int nb;
    int mode;

protected:
    bool eventFilter(QObject *object, QEvent *event)override;

};

class ListWidget : public BaseWindow
{
    Q_OBJECT

public:
    ListWidget(QWidget *parent = nullptr);
    ~ListWidget();
    void initTitleBar();
    void themeChange(int br, int bg, int bb, int tr, int tg, int tb, int mode);

//******这里要加*******//
    QList<newsBox *> boxList; //好友消息列表

    //从服务器传入用户信息，其中用户和好友的头像需添加入资源文件，再记录图片路径即icon
    QString username;           //用户昵称
    QString usericon;           //用户头像
    QString usersign;           //用户签名
    int FriNum;                 //好友数量
    QList<FriMessage> FriMess;  //好友信息列表
    void initMessage(const QString name, const QString icon, const QString usersign);

protected slots:
    void recvsignal(const QString &iconPath);

private slots:
    void on_messagepushButton_clicked();
    void on_friendspushButton_clicked();
    void on_mode_clicked();
    void headChange();
    void on_addFri_clicked();

private:
    Ui::ListWidget *ui;
    QVBoxLayout* vLayout;
    QWidget* pWidget;
    QScrollBar* verticalBar;
    QPushButton *head;
    iconChange* iconchange;
    Addfriend *addwindow;
//******这里要加*******//
    int R;
    int G;
    int B;
    int tR;
    int tG;
    int tB;
};
#endif // LISTWIDGET_H
