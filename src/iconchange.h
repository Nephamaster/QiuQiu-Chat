#ifndef ICONCHANGE_H
#define ICONCHANGE_H

#include <QWidget>
#include "basewindow.h"

namespace Ui {
class iconChange;
}

class iconChange : public BaseWindow
{
    Q_OBJECT

public:
    explicit iconChange(QWidget *parent = nullptr);
    ~iconChange();
    void LoadHeader(const QPixmap& pixmap);
    void RotateHeader(bool bClock);
    void initTitleBar();
    QString usericon;

protected:
    virtual bool eventFilter(QObject* watched, QEvent* event);

signals:
    void updateHeader(const QString &iconPath);

protected slots:
    void onUpload();
    void onScaledChanged(int nValue);
    void onOk();
    void onCancel();

private:
    Ui::iconChange *ui;
    QWidget* m_pDivWidget;	//选择头像区域的遮罩层
    QPixmap m_sourceHeader;
    QString iconName;

};

#endif // ICONCHANGE_H
