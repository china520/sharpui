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

    DECLAREBUILD(RadioButton)

    void SetGroup(const suic::String & name);
    suic::String GetGroup();

    virtual void SetCheck();
    virtual void SetUncheck();

protected:

    virtual void OnSetterChanged(suic::SetterChangedEventArg& e);

    virtual void OnRender(suic::DrawingContext * drawing);
    virtual void OnLoaded(suic::LoadedEventArg& e);

    virtual void OnKeyDown(suic::KeyEventArg& e);
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