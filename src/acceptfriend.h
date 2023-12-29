#ifndef ACCEPTFRIEND_H
#define ACCEPTFRIEND_H

#include <QWidget>

namespace Ui {
class Acceptfriend;
}

class Acceptfriend : public QWidget
{
    Q_OBJECT

public:
    explicit Acceptfriend(QWidget *parent = nullptr);
    ~Acceptfriend();

private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

private:
    Ui::Acceptfriend *ui;
};

#endif // ACCEPTFRIEND_H
