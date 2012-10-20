// 华勤科技版权所有 2010-2011
// 
// 文件名：Window.h
// 功  能：实现标准的窗口样式。
// 
// 作  者：汪荣
// 时  间：2010-12-12
// 
// ============================================================================

# ifndef _UIWINDOW_H_
# define _UIWINDOW_H_

#include <suicore/uipanel.h>
#include <suicore/uiassigner.h>

namespace suic
{

typedef delegate<void(suic::Element*, CancelEventArg&)> CancelEventHandler;

class SUICORE_API Window : public Panel
{
public:

    EventHandler Closed;
    CancelEventHandler Closing;
    EventHandler LocationChanged;
    EventHandler StateChanged;

    Window();
    virtual ~Window();

    virtual ElementPtr CreateElement() const;

    virtual Int32 Show();
    virtual Int32 ShowNoActivate();
    virtual int ShowDialog();

    void CenterWindow();

    Int32 GetDialogResult();

    virtual void Hide();
    virtual void Close();

    void Activate();
    bool Enable(bool val);

    void StartDragMove();
    void DragMove();
    void EndDragMove();

    void SetLocation(suic::Point pt);
    suic::Point GetLocation() const;

    void SetWindowStyle(Uint32 val);
    void SetWindowState(Uint32 val);

    Uint32 GetWindowStyle() const;
    Uint32 GetWindowState() const;

public:

    virtual void OnClosed(EventArg& e);
    virtual void OnClosing(CancelEventArg& e);
    virtual void OnActivated(EventArg& e);
    virtual void OnDeactivated(EventArg& e);

protected:
    
    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

    void OnLoaded(suic::LoadedEventArg& e);

    void OnSetterChanged(SetterChangedEventArg& e);

    void OnRenderSizeChanged(RenderSizeChangedEventArg& e);
    void OnRenderSizeModeChanged(SizeModeChangedEventArg& e);

    void OnHitTest(HitResultEventArg& e);
    void OnRender(suic::DrawingContext * drawing);

    void OnKeyDown(suic::KeyEventArg& e);
    void OnMouseLeftButtonDown(suic::MouseEventArg& e);

protected:

    bool CreateWindowDuringShow();
    bool InitializeComponent(const String& resLocator, String resid);

protected:

    suic::ObjectPtr _data;

    suic::Point _location;
    bool _isClosing;
    bool _appShuttingDown;
    bool _isActivate;

    Int32 _dialogResult;
    bool _showingAsDialog;

    Handle _dialogPreviousActiveHandle;
    AssignerFramePtr _frame;

    suic::Point _prevLocation;
    ElementPtr _disWindows;

    Uint32 _wndStyle;
    Uint32 _wndState;
    bool _canResize;
};

typedef shared<Window> WindowPtr;

inline void Window::SetWindowStyle(Uint32 val)
{
    _wndStyle = val;
}

inline void Window::SetWindowState(Uint32 val)
{
    _wndState = val;
}

inline Uint32 Window::GetWindowStyle() const
{
    return _wndStyle;
}

inline Uint32 Window::GetWindowState() const
{
    return _wndState;
}

};

# endif
