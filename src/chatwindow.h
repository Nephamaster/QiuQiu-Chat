#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include "basewindow.h"
#include "sendfile.h"

#include <QWidget>
#include <QFrame>
#include <QDialog>
#include <QScrollArea>
#include <QLabel>
#include <QScrollBar>
#include <QWidget>
#include <QTextEdit>
#include <QMouseEvent>

class QHBoxLayout;
class QVBoxLayout;

namespace Ui {
class ChatWindow;
}

//消息信息从服务端获取
typedef struct Message
{
    QString name;               //消息发送者名称
    QString icon;               //消息发送者头像
    QString datetime;           //消息时间
    QString type;               //消息类型 image/file/text
    QString direct;             //消息方向 Send/Receive
    QString message_id;         //消息id
    QString content;            //消息内容   消息内容，文件全路径
    QString filename;           //文件名称
    QString filesize;           //文件大小
}Message;

class Bubble : public QFrame
{
    Q_OBJECT
public:
    explicit Bubble(Message msg, QWidget *parent = nullptr);
    ~Bubble()override;

private:
    void initUI();
    QHBoxLayout* mainLayout;
    Message pCurMessage;
    QTextEdit* messageEdit;

private slots:
    void adjustContent();
};

class ChatWindow : public BaseWindow
{
    Q_OBJECT

public:
    //*这里要改
    explicit ChatWindow(const QString &name
                        ,const QString &icon
                        ,const QString &news
                        ,const QString &dir,
                        int r,
                        int g,
                        int b,
                        int tr,
                        int tg,
                        int tb,
                        int mode,
                        QWidget *parent = nullptr);
    ~ChatWindow();

    void initTitleBar(const QString &name,const QString &icon);
//******这里要加*******//
    void setTheme(int, int, int, int, int, int, int);
    void sendfiles(); //发送文件
    void updateSendProgress(qint64); //更新发送进度条
    void updateRecvProgress(); //更新接受进度

    SendFile sender; //文件收发窗口

protected:
    bool eventFilter(QObject *object, QEvent *event)override;

private:
//  QTcpSocket *tcpSocket;
//	QTcpSocket *fileSocket;
    Ui::ChatWindow *ui;
    QVBoxLayout* vLayout;
    QVBoxLayout* titlebar;
    QScrollBar* verticalBar;
    QList<Bubble *> pMessages;

//******这里要加*******//
    int R;
    int G;
    int B;
    int tR;
    int tG;
    int tB;

    //文件发送相关成员
    QFile *file;
    //文件大小
    qint64 totalsize;  //文件总字节数
    qint64 byteToWrite;//尚未发送的字节数
    qint64 bytewritten;//已发送的字节数
    qint64 bytesReceived;   //接收的字节数
    qint64 filenameSize;    //文件名字的字节数
    //每次发送数据大小
    qint64 perDataSize;
    //数据缓冲区
    QByteArray inBlock;
    QByteArray outBlock;

    //发送消息功能
    void sendMessage();
    void addMessage(Message msg);

    //鼠标拖动窗口事件
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    //记录鼠标，窗口位置
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;

private slots:
    void onButtonCloseClicked();
};

#endif // CHATWINDOW_H
