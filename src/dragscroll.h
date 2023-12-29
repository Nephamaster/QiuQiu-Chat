#ifndef DRAGSCROLL_H
#define DRAGSCROLL_H

#include <QScrollArea>

class DragScroll : public QScrollArea
{
    Q_OBJECT

public:
    DragScroll(QWidget *parent);
    ~DragScroll();

protected:
    virtual bool event(QEvent* event);
};

#endif // DRAGSCROLL_H
