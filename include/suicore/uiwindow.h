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

public:

    virtual void OnClosed(EventArg& e);
    virtual void OnClosing(CancelEventArg& e);
    virtual void OnActivated(EventArg& e);
    virtual void OnDeactivated(EventArg& e);

protected:
    
    virtual suic::Size MeasureOverride(const suic::Size& size);
    virtual suic::Size ArrangeOverride(const suic::Size& size);

    virtual void OnLoaded(suic::LoadedEventArg& e);
    virtual void OnRenderSizeChanged(RenderSizeChangedEventArg& e);
    virtual void OnRenderSizeModeChanged(SizeModeChangedEventArg& e);

    virtual void OnHitTest(HitResultEventArg& e);
    virtual void OnRender(suic::DrawingContext * drawing);

    virtual void OnKeyDown(suic::KeyEventArg& e);
    virtual void OnMouseLeftButtonDown(suic::MouseEventArg& e);

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

    Uint32 _style;
    Uint32 _state;
    bool _canResize;
};

typedef shared<Window> WindowPtr;

};

# endif
