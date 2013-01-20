// 华勤科技版权所有 2010-2011
// 
// 文件名：RadioButton.h
// 功  能：实现标准选项控件。
// 
// 作  者：汪荣
// 时  间：2010-10-31
// 
// ============================================================================

# ifndef _UIRADIOBUTTON_H_
# define _UIRADIOBUTTON_H_

#include <sui/sharpuiconfig.h>
#include <sui/CheckButton.h>

namespace ui
{

class SHARPUI_API RadioButton : public CheckButton
{
public:

    RadioButton();
    virtual ~RadioButton();

    DeclareTypeofInfo(RadioButton, CheckButton)

    virtual void SetCheck();
    virtual void SetUncheck();

// 属性访问定义
public:

    /// <summary>
    ///     设置是否自动计算大小
    /// </summary>
    /// <param name="val">true:自动；false:显式</param>
    /// <returns>无</returns>
    suic::String GetGroup() const;
    void SetGroup(suic::String val);

protected:

    virtual void OnPropertyChanged(suic::PropertyChangedEventArg& e);

    virtual void OnRender(suic::DrawingContext * drawing);
    virtual void OnLoaded(suic::LoadedEventArg& e);

    virtual void OnKeyDown(suic::KeyboardEventArg& e);
    virtual void OnMouseLeftButtonUp(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonDbclk(suic::MouseEventArg& e);

    virtual void OnGotFocus(suic::FocusEventArg& e);
    virtual void OnLostFocus(suic::FocusEventArg& e);

protected:

    suic::String _sGrpName;
};

typedef suic::shared<RadioButton> RadioButtonPtr;

};

# endif