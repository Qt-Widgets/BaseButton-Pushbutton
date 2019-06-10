/*
 *@author: 缪庆瑞
 *@date:   2019.6.4
 *@brief:  继承QLabel,构建按钮基类.
 * 1.提供构建不同类型(ButtonType)按钮的接口
 * 2.为"单选按钮组"设计了一些专有属性，并完成了相关样式的处理
 */
#include "basebutton.h"
#include <QVBoxLayout>
#include <QDebug>

/*这里默认提供一组样式表(选择器默认就是QLabel，这里只有声明(属性名:属性值))
 * border-radius:边角弧度半径
 * padding:填充区域宽度,可用来控制content区域(比如图片)的大小
 * color:前景色
 * background-color:背景色
 * 注意:Qt的样式表默认具有子部件继承性，一旦该按钮(baseButton)的父部件显式设置了stylesheet,那么
 * 某些属性就有可能被按钮继承，导致显示异常。解决方法就是父部件设置样式表时指定选择器(特定某个
 * 对象或某个类，不让子部件继承)，或者在该类中显式设置异常的样式属性，避免继承父部件对应的属性。
 */
#define BTN_NORMAL_STYLE "border-radius:5px;padding:2px;color:black;background-color:lightGray;"
#define BTN_PRESS_STYLE "border-radius:5px;padding:2px;color:white;background-color:orange;"
#define BTN_RELEASE_STYLE "border-radius:5px;padding:2px;color:black;background-color:lightGray;"
/*
 *@brief:   构造函数，根据button类型，构建对应结构的按钮
 *@author:  缪庆瑞
 *@date:    2019.6.4
 *@param:   btnType: 按钮类型
 *@param:   btnIndex:按钮索引号,不需要用时默认初始化为-1
 *@param:   isCheckedEnabled:按钮选中使能，适用于"单选按钮组"，默认为false
 *@param:   isPressResponse:按钮槽的触发信号,适用于"单选按钮组"，默认响应释放信号
 *@param:   parent:父对象
 */
BaseButton::BaseButton(ButtonType btnType, int btnIndex, bool isCheckedEnabled, bool isPressResponse, QWidget *parent)
    :QLabel(parent)
{
    this->btnType = btnType;
    this->btnIndex = btnIndex;
    this->isCheckedEnabled = isCheckedEnabled;
    this->isChecked = false;
    this->isPressResponse = isPressResponse;

    this->btnNormalStyle = BTN_NORMAL_STYLE;
    this->btnPressStyle = BTN_PRESS_STYLE;
    this->btnReleaseStyle = BTN_RELEASE_STYLE;

    if(btnType == IMAGE_TEXT_TYPE)
    {
        labelImage = new QLabel();
        labelImageLayout = new QHBoxLayout();
        labelImageLayout->addWidget(labelImage);
        //子部件label设置样式背景色为无色透明，避免继承父部件的背景色(可能导致透明度叠加)
        labelImage->setStyleSheet("background-color:rgba(255,255,255,0);");
        labelText = new QLabel();
        labelText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
        labelText->setStyleSheet("background-color:rgba(255,255,255,0);");
        QVBoxLayout *vBoxLayout = new QVBoxLayout();
        vBoxLayout->setMargin(0);
        vBoxLayout->setSpacing(0);
        vBoxLayout->addLayout(labelImageLayout);
        vBoxLayout->addWidget(labelText);
        this->setLayout(vBoxLayout);
    }
    this->setStyleSheet(btnNormalStyle);
    this->btnCurrentStyle = NORMAL_STYLE;
}
/*
 *@brief:   设置按钮三种状态的样式,不调用该方法则会使用代码中默认的一组样式表。
 * (具体样式表声明可参考默认样式(BTN_NORMAL_STYLE等))
 *@author:  缪庆瑞
 *@date:    2019.6.5
 *@param:   normalStyle:正常样式
 *@param:   pressStyle:按下样式
 *@param:   releaseStyle:释放(选中)样式,释放样式通常设置与normalStyle相同。但若用于单选按钮组
 * 的话，该样式又可被称做选中样式，一般不同于normal样式
*/
void BaseButton::setBtnStyleSheet(const QString &normalStyle, const QString &pressStyle, const QString &releaseStyle)
{
    this->btnNormalStyle = normalStyle;
    this->btnPressStyle = pressStyle;
    this->btnReleaseStyle = releaseStyle;
    this->setStyleSheet(btnNormalStyle);//默认设置正常样式
    this->btnCurrentStyle = NORMAL_STYLE;
}
/*
 *@brief:   选择某种样式设置为当前状态样式，适用于非鼠标事件和鼠标事件造成的状态改变
 *@author:  缪庆瑞
 *@date:    2019.6.5
 *@param:   btnStyleSheet:样式
 */
void BaseButton::selectBtnStyleSheet(ButtonStyleSheet btnStyleSheet)
{
    //所选样式与当前样式相同
    if(btnCurrentStyle == btnStyleSheet)
    {
        //qDebug()<<"styleSheet is same.";
        return;
    }
    switch(btnStyleSheet)
    {
    case NORMAL_STYLE:
        isChecked = false;
        this->setStyleSheet(btnNormalStyle);
        btnCurrentStyle = btnStyleSheet;
        break;
    case PRESS_STYLE:
        this->setStyleSheet(btnPressStyle);
        btnCurrentStyle = btnStyleSheet;
        break;
    case RELEASE_STYLE:
        isChecked = true;
        this->setStyleSheet(btnReleaseStyle);
        btnCurrentStyle = btnStyleSheet;
        break;
    default:
        qDebug()<<"selectBtnStyleSheet():param is error.";
        break;
    }
}
/*
 *@brief:   设置按钮显示文本
 *@author:  缪庆瑞
 *@date:    2019.6.5
 *@param:   text:文本内容
 *@param:   font:文本字体，默认系统字体
 *@param:   alignments:文本对齐方式，默认居中
 */
void BaseButton::setBtnText(const QString &text, QFont font, Qt::Alignment alignments)
{
    if(btnType == TEXT_TYPE)
    {
        this->setText(text);
        this->setFont(font);
        this->setAlignment(alignments);
    }
    else if(btnType == IMAGE_TEXT_TYPE)
    {
        labelText->setText(text);
        labelText->setFont(font);
        labelText->setAlignment(alignments);
    }
}
/*
 *@brief:   设置按钮显示图片
 *@author:  缪庆瑞
 *@date:    2019.6.5
 *@param:   imageUrl:图片路径
 *@param:   margins:IMAGE_TEXT类型按钮图片所在布局的margins,用来控制图片的显示大小
 */
void BaseButton::setBtnImage(const QString &imageUrl, QMargins margins)
{
    QPixmap pixmap(imageUrl);
    if(btnType == IMAGE_TYPE)
    {
        /*QLabel支持box model，pixmap默认填充到label的content区域，即图片是占据整个label的。
         *要使图片居中占据"部分"label空间，可以使用边缘透明的图片(比如ico，这样看起来图片只占据
         * label的部分空间)，或者在样式表中设置padding值，使content区域往里压缩*/
        this->setPixmap(pixmap);
        this->setScaledContents(true);//图片可根据label大小进行放缩，但如果label放顶级布局里，默认只能缩小到图片的size，可以用fixed固定大小
    }
    else if(btnType == IMAGE_TEXT_TYPE)
    {
        labelImage->setPixmap(pixmap);
        labelImage->setScaledContents(true);
        labelImageLayout->setContentsMargins(margins);
    }
}
/*
 *@brief:   设置按钮使能状态(决定是否响应鼠标事件)
 *@author:  缪庆瑞
 *@date:    2019.6.5
 *@param:   enabled:true=使能  false=禁用
 */
void BaseButton::setBtnEnabled(bool enabled)
{
    //这里调用父类的方法，禁用状态下父类有自己默认的样式，也可以在这里单独设置
    this->setEnabled(enabled);
}
/*
 *@brief:   鼠标按下事件处理函数
 *@author:  缪庆瑞
 *@date:    2019.6.4
 *@param:   ev: 传递的鼠标事件
 */
void BaseButton::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        if(isCheckedEnabled && isChecked)
        {//选中使能且是选中状态，按钮不再响应鼠标按下事件
            return;
        }
        this->selectBtnStyleSheet(PRESS_STYLE);//设置鼠标按下的样式
        emit pressSig(btnIndex);
    }
}
/*
 *@brief:   鼠标释放事件处理函数
 *@author:  缪庆瑞
 *@date:    2019.6.4
 *@param:   ev: 传递的鼠标事件
 */
void BaseButton::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        if(isCheckedEnabled && isChecked)
        {//选中使能且是选中状态，按钮不再响应鼠标释放事件
            return;
        }
        if(this->rect().contains(ev->pos()))//鼠标释放的位置在按钮上
        {
            this->selectBtnStyleSheet(RELEASE_STYLE);//设置释放(选中)样式
            emit releaseSig(btnIndex);
        }
        else//在按钮位置之外释放鼠标
        {
            /*选中使能且是按下响应。即此时按钮的槽已经被响应了,无论在什么位置释放鼠标，按钮
             * 都已经被选中了。通常该情况下按下和释放的样式是一致的*/
            if(isCheckedEnabled && isPressResponse)
            {
                this->selectBtnStyleSheet(RELEASE_STYLE);//设置释放(选中)样式
            }
            else
            {
                this->selectBtnStyleSheet(NORMAL_STYLE);//设置回到普通样式
            }
        }
    }
}
