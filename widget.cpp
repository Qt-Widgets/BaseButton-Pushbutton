#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //ui->widget->setStyleSheet(".QWidget {border-image: url(./images/1.png)}");
    //纯文本按钮
    BaseButton *textBtn1 = new BaseButton(BaseButton::TEXT_TYPE);
    textBtn1->setBtnText("abcd");
    BaseButton *textBtn2 = new BaseButton(BaseButton::TEXT_TYPE);
    textBtn2->setBtnText("中文",this->font());
    textBtn2->setFrameShape(QFrame::Box);
    textBtn2->setBtnStyleSheet(
                "padding:2px;background-color:lightGray;",
                "padding:4px 2px 1px 2px;background-color:cyan;",
                "padding:2px;background-color:lightGray;"
                );
    BaseButton *textBtn3 = new BaseButton(BaseButton::TEXT_TYPE);
    textBtn3->setBtnText("disabled");
    textBtn3->setBtnStyleSheet(
                "border-radius:50px;background-color:lightGray;",
                "border-radius:50px;background-color:yellow;",
                "border-radius:50px;background-color:lightGray;"
                );
    textBtn3->setBtnEnabled(false);
    ui->horizontalLayout->addWidget(textBtn1);
    ui->horizontalLayout->addWidget(textBtn2);
    ui->horizontalLayout->addWidget(textBtn3);
    //纯图片按钮
    BaseButton *imageBtn1 = new BaseButton(BaseButton::IMAGE_TYPE);
    imageBtn1->setBtnImage("./images/2.ico");
    BaseButton *imageBtn2 = new BaseButton(BaseButton::IMAGE_TYPE);
    imageBtn2->setBtnImage("./images/4.ico");
    imageBtn2->setBtnStyleSheet(
                "padding:20px;",
                "padding:10px;",
                "padding:20px;"
                );
    BaseButton *imageBtn3 = new BaseButton(BaseButton::IMAGE_TYPE);
    imageBtn3->setBtnImage("./images/3.ico");
    imageBtn3->setBtnEnabled(false);
    ui->horizontalLayout_2->addWidget(imageBtn1);
    ui->horizontalLayout_2->addWidget(imageBtn2);
    ui->horizontalLayout_2->addWidget(imageBtn3);
    //图片+文本按钮
    BaseButton *imageTextBtn1 = new BaseButton(BaseButton::IMAGE_TEXT_TYPE);
    imageTextBtn1->setBtnText("QQ");
    imageTextBtn1->setBtnImage("./images/2.ico");
    BaseButton *imageTextBtn2 = new BaseButton(BaseButton::IMAGE_TEXT_TYPE);
    imageTextBtn2->setBtnText("WeChat",QFont("",22));
    imageTextBtn2->setBtnImage("./images/4.ico",QMargins(12,12,12,0));
    imageTextBtn2->setBtnStyleSheet(
                "padding:2px;",
                "padding:0px;",
                "padding:2px"
                );
    BaseButton *imageTextBtn3 = new BaseButton(BaseButton::IMAGE_TEXT_TYPE);
    imageTextBtn3->setBtnText("weibo",QFont("",25));
    imageTextBtn3->setBtnImage("./images/5.ico",QMargins(20,10,20,0));
    imageTextBtn3->setBtnStyleSheet(
                "",
                "background-color:rgba(0,0,0,127);",
                ""
                );
    //imageTextBtn3->setBtnEnabled(false);
    ui->horizontalLayout_3->addWidget(imageTextBtn1);
    ui->horizontalLayout_3->addWidget(imageTextBtn2);
    ui->horizontalLayout_3->addWidget(imageTextBtn3);
    //单选按钮组
    BaseButton *singleBtn1 = new BaseButton(BaseButton::IMAGE_TYPE,1,true);
    singleBtn1->setBtnImage("./images/2.ico");
    singleBtn1->setBtnStyleSheet(
                "border-radius:5px;padding:2px;color:black;background-color:lightGray",
                "border-radius:5px;padding:2px;color:black;background-color:orange",
                "border-radius:5px;padding:2px;color:black;background-color:blue"
                );
    singleBtns.append(singleBtn1);
    connect(singleBtn1,SIGNAL(releaseSig(int)),this,SLOT(singleButtonsSlot(int)));
    BaseButton *singleBtn2 = new BaseButton(BaseButton::IMAGE_TYPE,2,true);
    singleBtn2->setBtnImage("./images/4.ico");
    singleBtn2->setBtnStyleSheet(
                "border-radius:5px;padding:2px;color:black;background-color:lightGray",
                "border-radius:5px;padding:2px;color:black;background-color:orange",
                "border-radius:5px;padding:2px;color:black;background-color:blue"
                );
    singleBtns.append(singleBtn2);
    connect(singleBtn2,SIGNAL(releaseSig(int)),this,SLOT(singleButtonsSlot(int)));
    BaseButton *singleBtn3 = new BaseButton(BaseButton::IMAGE_TYPE,3,true);
    singleBtn3->setBtnImage("./images/3.ico");
    singleBtn3->setBtnStyleSheet(
                "border-radius:5px;padding:2px;color:black;background-color:lightGray",
                "border-radius:5px;padding:2px;color:black;background-color:orange",
                "border-radius:5px;padding:2px;color:black;background-color:blue"
                );
    singleBtns.append(singleBtn3);
    connect(singleBtn3,SIGNAL(releaseSig(int)),this,SLOT(singleButtonsSlot(int)));
    ui->horizontalLayout_6->addWidget(singleBtn1);
    ui->horizontalLayout_6->addWidget(singleBtn2);
    ui->horizontalLayout_6->addWidget(singleBtn3);

}

Widget::~Widget()
{
    delete ui;
}
//单选按钮触发槽
void Widget::singleButtonsSlot(int btnIndex)
{
    for(int i=0;i<singleBtns.size();i++)
    {
        if(singleBtns.at(i)->getBtnIndex() != btnIndex)
        {
            singleBtns.at(i)->selectBtnStyleSheet(BaseButton::NORMAL_STYLE);
        }
    }
}
