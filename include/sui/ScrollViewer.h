// 华勤科技版权所有 2010-2011
// 
// 文件名：ScrollView.h
// 功  能：滚动视图，此类仅仅容纳一个界面元素
// 
// 作  者：汪荣
// 时  间：2011-12-25
// 
// ============================================================================

# ifndef _UISCROLLVIEW_H_
# define _UISCROLLVIEW_H_

#include <sui/sharpuiconfig.h>
#include <sui/scrollbar.h>
#include <suic/framework/uicontentcontrol.h>

namespace ui
{

// ============================================================
// ScrollView所有选择项的基类。
// ============================================================
class SHARPUI_API ScrollViewer : public suic::ContentControl
{
public:

    enum eScrollBarVisibility
    { 
        Disabled = 0,
        Auto,
        Hidden, 
        Visible,
    };

    ScrollViewer();
    virtual ~ScrollViewer();

    DeclareTypeofInfo(ScrollViewer, suic::ContentControl)

    void SetScrollBarVisibility(eScrollBarVisibility val);

    bool IsVerticalScrollBarVisible() const;
    int VerticalScrollBarWidth() const;

    bool IsHorizontalScrollBarVisible() const;
    int HorizontalScrollBarHeight() const;

    double HorizontalOffset();
    double VerticalOffset();

    double HorizontalVisualPos();
    double VerticalVisualPos();

    void SetHorizontalStep(int iStep);
    void SetVerticalStep(int iStep);

    double GetHorizontalStep() const;
    double GetVerticalStep() const;

    ScrollBar* HorizontalScrollBar();
    ScrollBar* VerticalScrollBar();

    void SetContentOffset(suic::Point pt);

    void LineUp();
    void LineDown();
    void LineLeft();
    void LineRight();
    void PageUp();
    void PageDown();
    void PageLeft();
    void PageRight();

    void ScrollToLeftEnd();
    void ScrollToRightEnd();
    void ScrollToHome();
    void ScrollToEnd();
    void ScrollToTop();
    void ScrollToBottom();

    void ScrollToHorizontalPos(double pos, bool bRepaint=true);
    void ScrollToVerticalPos(double pos, bool bRepaint=true);

    void ScrollToHorizontalOffset(double offset, bool bRepaint=true);
    void ScrollToVerticalOffset(double offset, bool bRepaint=true);

    void InvalidateScrollBar();

public:

    void OnHorizontalScroll(suic::ElementPtr, ScrollEventArg&);
    void OnVerticalScroll(suic::ElementPtr, ScrollEventArg&);

    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

    void OnInitialized();
    void OnRender(suic::DrawingContext * drawing);

    void OnTextInput(suic::KeyboardEventArg& e);
    void OnKeyDown(suic::KeyboardEventArg& e);

    void OnMouseWheel(suic::MouseWheelEventArg& e);

protected:

    void ComputeScrollBar(long& cxVisual, long& cyVisual, long cxLogic, long cyLogic);

protected:

    int _iBegin;
    int _iCurPos;

    double _scrollLineDelta;
    double _mouseWheelDelta;

    ScrollBarPtr _hScroll;
    ScrollBarPtr _vScroll;

    suic::Point _contentOffset;
    eScrollBarVisibility _barVisible;
};

typedef suic::shared<ScrollViewer> ScrollViewerPtr;

inline double ScrollViewer::GetHorizontalStep() const
{
    return _hScroll->GetScrollStep();
}

inline double ScrollViewer::GetVerticalStep() const
{
    return _vScroll->GetScrollStep();
}

inline ScrollBar* ScrollViewer::HorizontalScrollBar()
{
    return _hScroll.get();
}

inline ScrollBar* ScrollViewer::VerticalScrollBar()
{
    return _vScroll.get();
}

inline void ScrollViewer::SetContentOffset(suic::Point pt)
{
    _contentOffset = pt;
}

inline void ScrollViewer::SetScrollBarVisibility(eScrollBarVisibility val)
{
    _barVisible = val;
}

inline bool ScrollViewer::IsHorizontalScrollBarVisible() const
{
    return _hScroll->IsVisible();
}

inline int ScrollViewer::HorizontalScrollBarHeight() const
{
    return _hScroll->GetDesiredSize().cy;
}

inline bool ScrollViewer::IsVerticalScrollBarVisible() const
{
    return _vScroll->IsVisible();
}

inline int ScrollViewer::VerticalScrollBarWidth() const
{
    return _vScroll->GetDesiredSize().cx;
}

inline void ScrollViewer::SetHorizontalStep(int iStep)
{
    _hScroll->SetScrollStep(iStep);
}

inline void ScrollViewer::SetVerticalStep(int iStep)
{
    _vScroll->SetScrollStep(iStep);
}

};

# endif
