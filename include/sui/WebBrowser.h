// 华勤科技版权所有 2010-2011
// 
// 文件名：WebBrowser.h
// 功  能：实现标准的WEB控件
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UIWEBBROWSER_H_
# define _UIWEBBROWSER_H_

#include <sui/sharpuiconfig.h>
#include <suicore/uicontrol.h>

namespace ui
{

// ============================================================================
// WebBrowser，实现标准的WEB控件。
// ============================================================================

class SHARPUI_API WebBrowser : public suic::Control
{
public:

    WebBrowser();
    virtual ~WebBrowser();

    DECLAREBUILD(WebBrowser)

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

typedef suic::shared<WebBrowser> WebBrowserPtr;

};

# endif
