#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QWidget>

namespace Ui {
class Addfriend;
}

class Addfriend : public QWidget
{
    Q_OBJECT

public:
    explicit Addfriend(QWidget *parent = nullptr);
    ~Addfriend();

private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

private:
    Ui::Addfriend *ui;
};

#endif // ADDFRIEND_H
