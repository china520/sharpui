// 华勤科技版权所有 2010-2011
// 
// 文件名：ActiveXControl.h
// 功  能：实现ActiveXHost控件的封装
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UIACTIVEX_H_
# define _UIACTIVEX_H_

#include <sui/sharpuiconfig.h>
#include <suicore/HwndHost.h>

namespace ui
{

/// <summary>
///  ActiveXHost，封装ActiveXHost控件。
/// </summary>
class SHARPUI_API ActiveXHost : public suic::HwndHost
{
public:

    ActiveXHost();
    virtual ~ActiveXHost();

    DECLAREBUILD(ActiveXHost);

    suic::Handle GetControlHandle() const;

protected:

    bool DoVerb(int verb);

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

    // 组件class id
    //CLSID _clsid;

    suic::Handle _hwndParent;
    suic::Handle _axWindow;
    suic::Rect _boundRect;

    // 控件对象
    /*IOleObject* _axOleObject;
    IOleInPlaceObject* _axOleInPlaceObject;
    IOleInPlaceActiveObject* _axOleInPlaceActiveObject;*/
};

typedef suic::shared<ActiveXHost> ActiveXPtr;

};

# endif
