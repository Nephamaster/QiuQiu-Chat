#ifndef BBTPASSWORDEDIT_H
#define BBTPASSWORDEDIT_H
//密码输入框及可见性（本类暂时没用）
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QValidator>
#include <QRegExp>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QEvent>
#include <QDebug>

class bbtPasswordEdit : public QWidget
{
    Q_OBJECT
public:
    explicit bbtPasswordEdit(QWidget *parent = 0);
    QString text() const;
    void setFont(const QFont &font);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    QLineEdit *lineEdit;
    QLabel *pngLabel;
};

#endif // BBTPASSWORDEDIT_H
