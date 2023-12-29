#include "iconchange.h"
#include "ui_iconchange.h"
#include <QFileDialog>
#include <QPainter>
#include <QtDebug>
iconChange::iconChange(QWidget *parent) :
    BaseWindow(parent),
    ui(new Ui::iconChange)
{
    ui->setupUi(this);
    initTitleBar();
    ui->Slider->setEnabled(true);
    ui->scrollArea->setFrameStyle(QFrame::NoFrame);
    m_pDivWidget = new QWidget(ui->scrollArea);
    m_pDivWidget->setAttribute(Qt::WA_TranslucentBackground);
    m_pDivWidget->hide();
    m_pDivWidget->installEventFilter(this);

    //connect(ui.pushButton_close, &QPushButton::clicked, this, &QWidget::close);
    connect(ui->upload, &QPushButton::clicked, this, &iconChange::onUpload);
    connect(ui->Slider, &QSlider::valueChanged, this, &iconChange::onScaledChanged);
    connect(ui->anti, &QPushButton::clicked, std::bind(&iconChange::RotateHeader, this, false));
    connect(ui->clock, &QPushButton::clicked, std::bind(&iconChange::RotateHeader, this, true));
    connect(ui->OK, &QPushButton::clicked, this, &iconChange::onOk);
    connect(ui->Cancel, &QPushButton::clicked, this, &iconChange::onCancel);
    connect(ui->OK, SIGNAL(clicked()), this, SLOT(onOk()));
}

iconChange::~iconChange()
{
    delete ui;
}

void iconChange::initTitleBar()
{
    m_titleBar->setButtonType(ONLY_CLOSE_BUTTON);
    m_titleBar->setTitleWidth(this->width());
}

void iconChange::RotateHeader(bool bClock)
{
    QPixmap pixmap = *(ui->head->pixmap());
    QMatrix matrix;
    matrix.rotate(bClock ? 90 : -90);
    pixmap = pixmap.transformed(matrix);
    ui->head->setPixmap(pixmap);
}

void iconChange::LoadHeader(const QPixmap &pixmap)
{
    m_sourceHeader = pixmap;
    int nSliderMinmum = 0;
    QPixmap scaledPixmap;
    if (m_sourceHeader.width() > m_sourceHeader.height())
    {
        scaledPixmap = m_sourceHeader.scaledToHeight(ui->scrollArea->height());
        nSliderMinmum = scaledPixmap.height() * ui->Slider->maximum() / m_sourceHeader.height();
    }
    else
    {
        scaledPixmap = m_sourceHeader.scaledToWidth(ui->scrollArea->width());
        nSliderMinmum = scaledPixmap.width() * ui->Slider->maximum() / m_sourceHeader.width();
    }
    ui->scrollAreaWidgetContents->resize(m_sourceHeader.size());
    ui->Slider->setEnabled(true);
    ui->Slider->setMinimum(nSliderMinmum);
    ui->Slider->setValue(nSliderMinmum);
    ui->head->setPixmap(scaledPixmap);
    m_pDivWidget->show();
}

bool iconChange::eventFilter(QObject* watched, QEvent* event)
{
    if (m_pDivWidget == watched && QEvent::Paint == event->type())	//绘制遮罩层
    {
        m_pDivWidget->resize(ui->scrollArea->size());
        QPainterPath path;
        path.addRect(m_pDivWidget->geometry());
        path.addEllipse(m_pDivWidget->geometry().adjusted(2, 2, -2, -2));
        QPainter p(m_pDivWidget);
        p.setRenderHint(QPainter::Antialiasing);
        p.setBrush(QColor(100, 100, 100, 200));
        p.setClipPath(path);
        p.drawRect(m_pDivWidget->geometry());
    }
    return QWidget::eventFilter(watched, event);
}

void iconChange::onUpload()
{
    QString strFilePath = QFileDialog::getOpenFileName(this, QString/*::fromLocal8Bit*/("选择上传图片"), "./", "*.jpg;*.png;*.bmp");
    if (strFilePath.isEmpty())
    {
        return;
    }
    iconName = strFilePath;
    LoadHeader(QPixmap(strFilePath));
}

void iconChange::onScaledChanged(int nValue)
{
    QPixmap pixmap = m_sourceHeader.scaled(m_sourceHeader.size() * ((double)nValue / ui->Slider->maximum()));
    ui->scrollAreaWidgetContents->resize(pixmap.size());
    ui->head->setPixmap(pixmap);
}

void iconChange::onOk()
{
    if (const QPixmap* pHeader = ui->head->pixmap())
    {
        QFileInfo info(iconName);
        usericon = info.fileName();
        qDebug()<<usericon;
        ui->labeltip->setText(QString/*::fromLocal8Bit*/("修改头像成功"));
        emit updateHeader(usericon);
    }
    else
    {
        ui->labeltip->setText(QString/*::fromLocal8Bit*/("还未加载头像"));
    }
}

void iconChange::onCancel()
{
    ui->labeltip->setText(QString::fromLocal8Bit("取消修改头像"));
    m_pDivWidget->hide();
    ui->labeltip->clear();
}
