#include "bbtpasswordedit.h"

// 密码编辑框控件
// 鼠标指着pngLabel显示密码，离开隐藏密码

bbtPasswordEdit::bbtPasswordEdit(QWidget *parent) : QWidget(parent)
{
    QString bgColor = "#FFFFFF";    //背景颜色
    QString borderColor = "#A6B5B8";//边框颜色

    pngLabel = new QLabel;
    pngLabel->setAlignment(Qt::AlignCenter);
    pngLabel->setPixmap(QPixmap(":/image/toolicon/preview-close.png").scaled(10,10));

    lineEdit = new QLineEdit;
    lineEdit->setObjectName("lineEdit");
    lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    QRegExp regx("[0-9]+$");        // 限制只能输入数字
//    QValidator *validator = new QRegExpValidator(regx, lineEdit);
//    lineEdit->setValidator( validator );
//    lineEdit->setMaxLength(6);      // 限制只能输入6位


    lineEdit->setEchoMode(QLineEdit::Password);
    pngLabel->installEventFilter(this);

    QFrame *frame = new QFrame;
    frame->setObjectName("framePassword");

    QStringList qss;
    qss.append(QString("QFrame#framePassword{border:1px solid %1;}").arg(borderColor));
    qss.append(QString("QLabel{min-width:15px;background-color:%1;}").arg(bgColor));
    qss.append(QString("QLineEdit{background-color:%1;border:none;}").arg(bgColor));
    frame->setStyleSheet(qss.join(""));

    //将控件按照横向布局排列
    QHBoxLayout *layout = new QHBoxLayout(frame);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(lineEdit);
    layout->addWidget(pngLabel);

    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    verticalLayout->setMargin(0);
    verticalLayout->setSpacing(0);
    verticalLayout->addWidget(frame);
}

bool bbtPasswordEdit::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
        case QEvent::Enter:
            pngLabel->setPixmap(QPixmap(":/image/toolicon/preview-open.png").scaled(10,10));
            lineEdit->setEchoMode(QLineEdit::Normal);
            break;
        case QEvent::Leave:
            lineEdit->setEchoMode(QLineEdit::Password);
            break;
        default:
            break;
    }
    return QWidget::eventFilter(watched, event);
}

void bbtPasswordEdit::setFont(const QFont &font)
{
    lineEdit->setFont(font);
}

QString bbtPasswordEdit::text() const
{
    return lineEdit->text();
}
