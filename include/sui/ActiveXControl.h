// 华勤科技版权所有 2010-2011
// 
// 文件名：ActiveXControl.h
// 功  能：实现ActiveX控件的封装
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UIACTIVEX_H_
# define _UIACTIVEX_H_

#include <sui/sharpuiconfig.h>
#include <suicore/uicontrol.h>

namespace ui
{

// ============================================================================
// ActiveX，封装ActiveX控件。
// ============================================================================

class SHARPUI_API ActiveX : public suic::Control
{
public:

    ActiveX();
    virtual ~ActiveX();

    DECLAREBUILD(ActiveX)

protected:

    virtual void OnInitialized();

    virtual void OnRender(suic::DrawingContext * drawing);

    virtual void OnTextInput(suic::KeyEventArg& e);
    virtual void OnKeyDown(suic::KeyEventArg& e);

    virtual void OnGotFocus(suic::FocusEventArg& e);
    virtual void OnLostFocus(suic::FocusEventArg& e);
    virtual void OnSetCursor(suic::CursorEventArg& e);

    virtual void OnMouseEnter(suic::MouseEventArg& e);
    virtual void OnMouseMove(suic::MouseEventArg& e);
    virtual void OnMouseLeave(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonDown(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonDbclk(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonUp(suic::MouseEventArg& e);

protected:
};

typedef suic::shared<ActiveX> ActiveXPtr;

};

# endif
