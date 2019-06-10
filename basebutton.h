/*
 *@author: 缪庆瑞
 *@date:   2019.6.4
 *@brief:  继承QLabel,构建按钮基类.
 * 1.提供构建不同类型(ButtonType)按钮的接口
 * 2.为"单选按钮组"设计了一些专有属性，并完成了相关样式的处理
 */
#ifndef BASEBUTTON_H
#define BASEBUTTON_H

#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>

class BaseButton : public QLabel
{
    Q_OBJECT
public:
    enum ButtonType{//按钮类型
        TEXT_TYPE=0,//显示文本
        IMAGE_TYPE,//显示图标
        IMAGE_TEXT_TYPE,//显示图标+文本(上下结构)
    };
    enum ButtonStyleSheet{
        NORMAL_STYLE=0,//正常样式
        PRESS_STYLE,//按下样式
        RELEASE_STYLE,//释放(选中)样式
    };

    BaseButton(ButtonType btnType,int btnIndex = -1,
               bool isCheckedEnabled=false,bool isPressResponse=false,QWidget *parent=0);

    void setBtnStyleSheet(const QString &normalStyle,const QString &pressStyle,const QString &releaseStyle);
    void selectBtnStyleSheet(ButtonStyleSheet btnStyleSheet);

    void setBtnText(const QString &text,QFont font = QFont(),Qt::Alignment alignments = Qt::AlignCenter);
    void setBtnImage(const QString &imageUrl,QMargins margins = QMargins(2,2,2,2));

    void setBtnEnabled(bool enabled);

    int getBtnIndex(){return this->btnIndex;}//获取按钮索引

signals:
    void pressSig(int btnIndex);//按下信号
    void releaseSig(int btnIndex);//释放信号

protected:
    //重写QLabel的鼠标按下释放事件
    virtual void mousePressEvent(QMouseEvent *ev);
    virtual void mouseReleaseEvent(QMouseEvent *ev);

private:
    ButtonType btnType;//构建的按钮类型
    ButtonStyleSheet btnCurrentStyle;//按钮当前样式
    int btnIndex;//按钮索引号,方便在槽内判断是哪个按钮触发
    //"单选按钮组"参数
    bool isCheckedEnabled;//按钮选中使能标志  适用于“单选按钮组”
    bool isChecked;//按钮选中标志
    bool isPressResponse;//按钮槽的触发信号
    //不同状态下按钮的样式
    QString btnNormalStyle;
    QString btnPressStyle;
    QString btnReleaseStyle;
    //IMAGE_TEXT类型按钮需要单独的label控件
    QLabel *labelImage;
    QLabel *labelText;
    QHBoxLayout *labelImageLayout;//对图片label单独布局
};

#endif // BASEBUTTON_H
