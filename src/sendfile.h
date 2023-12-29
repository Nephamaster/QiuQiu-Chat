#ifndef SENDFILE_H
#define SENDFILE_H

#include <QWidget>
#include "basewindow.h"
#include <QFileInfo>

namespace Ui {
class SendFile;
}

class SendFile : public BaseWindow
{
    Q_OBJECT

public:
    explicit SendFile(QWidget *parent = nullptr);
    ~SendFile();
    void updateBar(qint64, qint64);
    void initsender(QFileInfo info, qint64 size);

private:
    Ui::SendFile *ui;
    QString filename;
    qint64 filesize;
    void initTitleBar();
};

#endif // SENDFILE_H
