#include "sendfile.h"
#include "ui_sendfile.h"

SendFile::SendFile(QWidget *parent) :
    BaseWindow(parent),
    ui(new Ui::SendFile)
{
    ui->setupUi(this);
    ui->lineEdit->setFrame(QFrame::NoFrame);
    ui->lineEdit->setStyleSheet(QString("font: 25 9pt Microsoft YaHei;"));
    ui->filesize->setStyleSheet(QString("font: 25 8pt Microsoft YaHei;"));
    ui->progressBar->setTextVisible(false);
    ui->progressBar->setStyleSheet(
                    "QProgressBar{color:rgb(0,0,0);border-radius: 5px;"
                    "background: rgb(245, 245, 245);}"
                    "QProgressBar::chunk {border-radius: 5px;"
                    "background: rgb(0,191,255);}");
    initTitleBar();
}

SendFile::~SendFile()
{
    delete ui;
}

void SendFile::initsender(QFileInfo info, qint64 size)
{
    ui->lineEdit->setText(info.fileName());
    int siz = static_cast<int>(size) / 1024;
    QString str =  tr("%1kb").arg(siz);
    ui->filesize->setText(str);
    ui->progressBar->setValue(50);
    QString suffix = info.completeSuffix();
    if(suffix == "doc")
        {
            ui->fileicon->setStyleSheet(QString("border-image: url(:/image/fileicon/doc.png)"));
        }
        else if(suffix == "exe")
        {
            ui->fileicon->setStyleSheet(QString("border-image: url(:/image/fileicon/exe.png)"));
        }
        else if(suffix == "jpg" || suffix == "png")
        {
            ui->fileicon->setStyleSheet(QString("border-image: url(:/image/fileicon/jpg.png)"));
        }
        else if(suffix == "mp3")
        {
            ui->fileicon->setStyleSheet(QString("border-image: url(:/image/fileicon/mp3.png)"));
        }
        else if(suffix == "mp4")
        {
            ui->fileicon->setStyleSheet(QString("border-image: url(:/image/fileicon/mp4.png)"));
        }
        else if(suffix == "pdf")
        {
            ui->fileicon->setStyleSheet(QString("border-image: url(:/image/fileicon/pdf.png)"));
        }
        else if(suffix == "ppt" || suffix == "pptx")
        {
            ui->fileicon->setStyleSheet(QString("border-image: url(:/image/fileicon/ppt.png)"));
        }
        else if(suffix == "rar")
        {
            ui->fileicon->setStyleSheet(QString("border-image: url(:/image/fileicon/rar.png)"));
        }
        else if(suffix == "txt")
        {
            ui->fileicon->setStyleSheet(QString("border-image: url(:/image/fileicon/txt.png)"));
        }
        else if(suffix == "xls" || suffix == "xlsx" )
        {
            ui->fileicon->setStyleSheet(QString("border-image: url(:/image/fileicon/xlsx.png)"));
        }
        else if(suffix == "zip")
        {
            ui->fileicon->setStyleSheet(QString("border-image: url(:/image/fileicon/zip.png)"));
        }
        else
        {
            ui->fileicon->setStyleSheet(QString("border-image: url(:/image/fileicon/file.png)"));
        }
}

void SendFile::initTitleBar()
{
    m_titleBar->setButtonType(ONLY_CLOSE_BUTTON);
    m_titleBar->setTitleWidth(this->width());
}

void SendFile::updateBar(qint64 total, qint64 written)
{
    ui->progressBar->setMaximum(total);
    ui->progressBar->setValue(written);
}
