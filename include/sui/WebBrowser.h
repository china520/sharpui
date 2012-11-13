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
#include <sui/ActiveXHost.h>

namespace ui
{

/// <summary>
///  WebBrowser，实现标准的WEB控件。
/// </summary>
class SHARPUI_API WebBrowser : public ActiveXHost
{
public:

    WebBrowser();
    virtual ~WebBrowser();

    DECLAREBUILD(WebBrowser)

    bool CanGoBack() const;
    bool CanGoForward() const;

    suic::String GetSource() const;
    void SetSource(suic::String uri);

    void GoBack();
    void GoForward();

    suic::ObjectPtr InvokeScript(suic::String scriptName);

    void Navigate(const suic::String& source);
    void Refresh();

protected:

    suic::Size ArrangeOverride(const suic::Size& size);

    void OnInitialized();
    void OnLoaded(suic::LoadedEventArg& e);

    void OnVisibilityChanged(bool visible);

    void OnRender(suic::DrawingContext * drawing);

    void OnTextInput(suic::KeyEventArg& e);
    void OnKeyDown(suic::KeyEventArg& e);

    void OnGotFocus(suic::FocusEventArg& e);
    void OnLostFocus(suic::FocusEventArg& e);

    void OnSetCursor(suic::CursorEventArg& e);

    void OnMouseEnter(suic::MouseEventArg& e);
    void OnMouseMove(suic::MouseEventArg& e);
    void OnMouseLeave(suic::MouseEventArg& e);
    void OnMouseLeftButtonDown(suic::MouseEventArg& e);
    void OnMouseLeftButtonDbclk(suic::MouseEventArg& e);
    void OnMouseLeftButtonUp(suic::MouseEventArg& e);

protected:

    void* _webHost;
    suic::String _uri;
};

typedef suic::shared<WebBrowser> WebBrowserPtr;

inline suic::String WebBrowser::GetSource() const
{
    return _uri;
}

inline void WebBrowser::SetSource(suic::String uri)
{
    _uri = uri;
}

};

# endif
