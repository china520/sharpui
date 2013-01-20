// 华勤科技版权所有 2010-2011
// 
// 文件名：ScrollBar.h
// 功  能：实现滚动条
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UISCROLLBAR_H_
# define _UISCROLLBAR_H_

#include <sui/RangeBase.h>
#include <sui/UIDefine.h>
#include <sui/RepeatedButton.h>

namespace ui
{

enum ScrollEventType
{
    EndScroll = 0,
    First = 1,
    LargeDecrement = 2,
    LargeIncrement = 3,
    Last = 4,
    SmallDecrement = 5,
    SmallIncrement = 6,
    ThumbPosition = 7,
    ThumbTrack = 8,
};

class SHARPUI_API ScrollEventArg : public suic::RoutedEventArg
{
public:

    ScrollEventArg(double curVal) 
        : currentVal(curVal) 
        , RoutedEventArg(suic::ObjectPtr())
    {
    }

    double CurrentValue() 
    { 
        return currentVal; 
    }

    ui::ScrollEventType EventType() 
    { 
        return scrollType;
    }

    void EventType(ui::ScrollEventType t) 
    { 
        scrollType = t; 
    }

protected:

    ui::ScrollEventType scrollType;

    double currentVal;
};

// 定义滚动条处理类
typedef delegate<void(suic::ElementPtr, ui::ScrollEventArg&)> ScrollEventHandler;

class ThumbButton : public ui::Button
{
public:

    void OnRender(suic::DrawingContext * drawing);
};

class SHARPUI_API ScrollBar : public ui::RangeBase
{
public:

    ScrollBar();
    virtual ~ScrollBar();

    DeclareTypeofInfo(ScrollBar, RangeBase)

    ui::ScrollEventHandler Scroll;
    ui::ScrollEventHandler TrackScroll;

    int GetScrollPos();
    void SetScrollPos(int iPos);

    int GetScrollSize();

    int MaxScrollPos();

    /// <summary>
    ///     设置滚动条信息
    /// </summary>
    /// <param name="iStep">计算步长(每次滚动一行的距离)</param>
    /// <returns>无</returns>
    void SetScrollStep(int iStep);
    int GetScrollStep();
    int GetLogicSize() const;

    void ScrollToBegin(bool bRepaint=true);
    void ScrollTo(int nNewPos, bool bRepaint=true);
    void ScrollToEnd(bool bRepaint=true);

    /// <summary>
    ///     设置滚动条信息
    /// </summary>
    /// <param name="iVisual">可视区域大小(水平为宽度;垂直为高度)</param>
    /// <param name="iLogic">逻辑区域大小</param>
    /// <returns>无</returns>
    void SetScrollInfo(int iVisual, int iLogic, bool bRepaint);
    void UpdateScrollInfo(int iVisual, int iLogic, bool bCalc);

    void UpdateScrollVisual(int iVisual, bool bRepaint);
    void UpdateScrollLogic(int iLogic, bool bRepaint);
    void AddScrollLogic(int iLogic, bool bRepaint=false);

    void UpdateScrollBar();

    void ShowFirstScrollButton(bool bShow);
    void ShowSecondScrollButton(bool bShow);

    void LineUp();
    void LineDown();

    void LineLeft();
    void LineRight();

    void PageUp();
    void PageDown();

    void DoScroll(bool bUpdate=true);

public:

    virtual void OnInitialized();
    virtual void OnLoaded(suic::LoadedEventArg& e);
    virtual void OnUnloaded(suic::LoadedEventArg& e);
    virtual void OnStyleUpdated();

    virtual void OnRender(suic::DrawingContext * drawing);
    virtual void OnPropertyChanged(suic::PropertyChangedEventArg& e);

protected:

    int PosFromThumb(int thumb, const suic::Size & szClamp);
    suic::Rect GetScrollThumbRect(const suic::Size & size, bool bThumb=false);
    suic::Rect CalcScrollThumbSize();
    void CalcScrollPos();

    void InternalInit();

protected:

    virtual suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

    void OnBeginTrack(suic::Element* pSender, suic::MouseEventArg& e);
    void OnEndTrack(suic::Element* pSender, suic::MouseEventArg& e);

    void OnHorzTrack(suic::Element* pSender, suic::MouseEventArg& e);
    void OnVertTrack(suic::Element* pSender, suic::MouseEventArg& e);

    void OnPageUp(suic::Element* pSender, suic::MouseEventArg& e);
    void OnPageDown(suic::Element* pSender, suic::MouseEventArg& e);

    void OnPageLeft(suic::Element* pSender, suic::MouseEventArg& e);
    void OnPageRight(suic::Element* pSender, suic::MouseEventArg& e);

    void OnLineLeft(suic::Element* pSender, suic::MouseEventArg& e);
    void OnLineRight(suic::Element* pSender, suic::MouseEventArg& e);

    void OnLineUp(suic::Element* pSender, suic::MouseEventArg& e);
    void OnLineDown(suic::Element* pSender, suic::MouseEventArg& e);

protected:

    // 滑块滚动信息
    suic::Rect _rcTrack;
    suic::Rect _rcTrackStart;
    suic::Point _ptTrackStart;

    suic::PanelPtr _panel;
    // 滑块对象
    ThumbButton _thumb;

    // 上箭头或左箭头
    RepeatedButton _decreaseBtn;
    RepeatedButton _increaseBtn;

    // 页对象
    RepeatedButton _decreasePage;
    RepeatedButton _increasePage;

    UIScrollInfo _scroInfo;

    // 实际可视大小
    int _iVisualSize;
    // 逻辑大小
    int _iLogicSize;
    // 滚动步长
    int _iStep;
};

typedef suic::shared<ScrollBar> ScrollBarPtr;

inline int ScrollBar::GetLogicSize() const
{
    return _iLogicSize;
}


};

# endif