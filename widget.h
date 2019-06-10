#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "basebutton.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void singleButtonsSlot(int btnIndex);//单选按钮触发槽

private:
    Ui::Widget *ui;
    QList<BaseButton *> singleBtns;//单选按钮组
};

#endif // WIDGET_H
