// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// ScrollView.cpp

#include <sui/ScrollViewer.h>
#include <sui/textblock.h>
#include <suic/tools/vector.h>
#include <suic/render/uirender.h>

namespace ui
{

ImplementTypeofInfo(ScrollViewer, suic::ContentControl)

ScrollViewer::ScrollViewer()
    : _iBegin(0)
    , _iCurPos(0)
    , _barVisible(Auto)
    , _scrollLineDelta(16.0)
    , _mouseWheelDelta(48.0)
{
    SetClassName(_T("ScrollView"));

    _hScroll = ScrollBarPtr(new ScrollBar());
    _vScroll = ScrollBarPtr(new ScrollBar());

    _hScroll->SetOrientation(CoreFlags::Horizontal);
    _vScroll->SetOrientation(CoreFlags::Vertical);

    _hScroll->SetOwner(this);
    _vScroll->SetOwner(this);

    _hScroll->SetScrollStep(5);
    _vScroll->SetScrollStep(5);

    _vScroll->SetVisible(false);
    _hScroll->SetVisible(false);

    SetFocusable(true);
}

ScrollViewer::~ScrollViewer()
{
}

double ScrollViewer::HorizontalOffset()
{
    return _hScroll->GetScrollSize();
}

double ScrollViewer::VerticalOffset()
{
    return _vScroll->GetScrollSize();
}

double ScrollViewer::HorizontalVisualPos()
{
    return _hScroll->GetScrollPos();
}

double ScrollViewer::VerticalVisualPos()
{
    return _vScroll->GetScrollPos();
}

void ScrollViewer::LineUp()
{
    _vScroll->LineUp();
}

void ScrollViewer::LineDown()
{
    _vScroll->LineDown();
}

void ScrollViewer::LineLeft()
{
    _hScroll->LineLeft();
}

void ScrollViewer::LineRight()
{
    _hScroll->LineRight();
}

void ScrollViewer::PageUp()
{
    _vScroll->PageUp();
}

void ScrollViewer::PageDown()
{
     _vScroll->PageDown();
}

void ScrollViewer::PageLeft()
{

}

void ScrollViewer::PageRight()
{

}

void ScrollViewer::ScrollToLeftEnd()
{
    _hScroll->ScrollToBegin();
}

void ScrollViewer::ScrollToRightEnd()
{
    _hScroll->ScrollToEnd();
}

void ScrollViewer::ScrollToHome()
{
    _vScroll->ScrollToBegin();
}

void ScrollViewer::ScrollToEnd()
{
    _vScroll->ScrollToEnd();
}

void ScrollViewer::ScrollToTop()
{
    _vScroll->ScrollToBegin();
}

void ScrollViewer::ScrollToBottom()
{
    _vScroll->ScrollToEnd();
}

void ScrollViewer::ScrollToHorizontalPos(double Pos, bool bRepaint)
{
    _hScroll->ScrollTo(Pos, false);

    if (bRepaint)
    {
        UpdateLayout();
    }
}

void ScrollViewer::ScrollToVerticalPos(double Pos, bool bRepaint)
{
    _vScroll->ScrollTo(Pos, false);

    if (bRepaint)
    {
        UpdateLayout();
    }
}

void ScrollViewer::ScrollToHorizontalOffset(double offset, bool bRepaint)
{
    _hScroll->ScrollTo((int)((double)offset / (double)_hScroll->GetScrollStep()), false);

    if (bRepaint)
    {
        UpdateLayout();
    }
}

void ScrollViewer::ScrollToVerticalOffset(double offset, bool bRepaint)
{
    _vScroll->ScrollTo((int)((double)offset / (double)_vScroll->GetScrollStep()), false);

    if (bRepaint)
    {
        UpdateLayout();
    }
}

void ScrollViewer::OnHorizontalScroll(suic::ElementPtr eScroll, ScrollEventArg& scroll)
{
    suic::Int32 curpos = (int)_hScroll->GetScrollSize();

    suic::PanelPtr cont(GetContent());

    if (cont)
    {
        cont->SetHorizontalOffset(curpos);

        cont->InvalidateArrange();
        cont->InvalidateVisual();
    }
}

void ScrollViewer::OnVerticalScroll(suic::ElementPtr eScroll, ScrollEventArg& scroll)
{
    suic::Int32 curpos = (int)_vScroll->GetScrollSize();

    suic::PanelPtr cont(GetContent());

    if (cont)
    {
        cont->SetVerticalOffset(curpos);

        cont->InvalidateArrange();
        cont->InvalidateVisual();
    }
}

void ScrollViewer::InvalidateScrollBar()
{
    _hScroll->InvalidateVisual();
    _vScroll->InvalidateVisual();
}

/////////////////////////////////////////////////////////////////////
//
suic::Size ScrollViewer::MeasureOverride(const suic::Size& availableSize)
{
    _hScroll->Measure(availableSize);
    _vScroll->Measure(availableSize);

    suic::Size retSize(GetDesiredSize());
    suic::ElementPtr cont(GetContent());

    if (cont)
    {
        cont->Measure(availableSize);

        return cont->GetDesiredSize();
    }
    else
    {
        return retSize;
    }
}

void ScrollViewer::ComputeScrollBar(long& cxVisual, long& cyVisual, long cxLogic, long cyLogic)
{
    if (_barVisible == eScrollBarVisibility::Hidden)
    {
        return;
    }

    // 出现水平滚动条
    if (cxLogic > cxVisual)
    {
        suic::Rect rcHorz(0, cyVisual - _hScroll->GetDesiredSize().cy, 
            cxVisual, _hScroll->GetDesiredSize().cy);

        _hScroll->SetVisible(true);

        int iVertHei = cyVisual - _hScroll->GetDesiredSize().cy;

        // 垂直滚动条出现
        if (cyLogic > iVertHei)
        {
            _vScroll->SetVisible(true);

            rcHorz.right -= _vScroll->GetDesiredSize().cx;

            suic::Rect rcVert(cxVisual - _vScroll->GetDesiredSize().cx
                , 0, _vScroll->GetDesiredSize().cx, iVertHei);

            cxVisual -= _vScroll->GetDesiredSize().cx;

            AddVisualChild(_vScroll.get());
            _vScroll->Arrange(rcVert);
        }

        // 客户区减去滚动条高度
        cyVisual -= rcHorz.Height();

        AddVisualChild(_hScroll.get());
        _hScroll->Arrange(rcHorz);
    }
    else if (cyLogic > cyVisual)
    {
        suic::Rect rcVert(cxVisual - _vScroll->GetDesiredSize().cx
            , 0, _vScroll->GetDesiredSize().cx, cyVisual);

        _vScroll->SetVisible(true);

        int iHorzWid = cxVisual - _vScroll->GetDesiredSize().cx;

        // 水平滚动条出现
        if (cxLogic > iHorzWid)
        {
            _hScroll->SetVisible(true);

            rcVert.bottom -= _hScroll->GetDesiredSize().cy;

            suic::Rect rcHorz(0, cyVisual - _hScroll->GetDesiredSize().cy
                , iHorzWid, _hScroll->GetDesiredSize().cy);

            cyVisual -= _hScroll->GetDesiredSize().cy;

            AddVisualChild(_hScroll.get());
            _hScroll->Arrange(rcHorz);
        }

        // 客户区减去滚动条高度
        cxVisual -= rcVert.Width();

        AddVisualChild(_vScroll.get());
        _vScroll->Arrange(rcVert);
    }
}

suic::Size ScrollViewer::ArrangeOverride(const suic::Size& availableSize)
{
    ClearVisualChildren();

    suic::FrameworkElementPtr cont(GetContent());

    if (cont)
    {
        cont->MeasureInArranging(availableSize);

        suic::Rect rect;

        rect.right = availableSize.cx;
        rect.bottom = availableSize.cy;

        _vScroll->SetVisible(false);
        _hScroll->SetVisible(false);

        suic::Size desiredSize = cont->GetDesiredSize();

        //
        // 计算是否有滚动条
        //
        _hScroll->UpdateScrollInfo(rect.right, desiredSize.cx, false);
        _vScroll->UpdateScrollInfo(rect.bottom, desiredSize.cy, false);

        ComputeScrollBar(rect.right, rect.bottom, desiredSize.cx, desiredSize.cy);

        suic::ScrollChangedEventArg sce(_hScroll->GetScrollSize(), _vScroll->GetScrollSize());

        cont->OnScrollChanged(sce);

        rect.left += _contentOffset.x;
        rect.top += _contentOffset.y;

        if (rect.bottom > rect.top)
        {
            rect.Deflate(GetPadding());
            AddVisualChild(cont.get());
            cont->Arrange(rect);
        }
    }

    return availableSize;
}

void ScrollViewer::OnInitialized()
{
    __super::OnInitialized();

    suic::StylePtr hPtr(FindResource(_T("HScrollBar")));
    suic::StylePtr vPtr(FindResource(_T("VScrollBar")));

    _hScroll->SetStyle(hPtr);
    _vScroll->SetStyle(vPtr);

    _hScroll->BeginInit();
    _hScroll->EndInit();

    _vScroll->BeginInit();
    _vScroll->EndInit();

    _hScroll->Scroll += ScrollEventHandler(this, &ScrollViewer::OnHorizontalScroll);
    _vScroll->Scroll += ScrollEventHandler(this, &ScrollViewer::OnVerticalScroll);

    _iCurPos = GetBorderThickness().top;
}

void ScrollViewer::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

void ScrollViewer::OnTextInput(suic::KeyboardEventArg& e)
{
}

void ScrollViewer::OnKeyDown(suic::KeyboardEventArg& e)
{
    bool handled = true;

    if (e.IsPageup())
    {
        PageUp();
    }
    else if (e.IsPagedown())
    {
        PageDown();
    }
    else if (e.IsHomeKey())
    {
        ScrollToHome();
    }
    else if (e.IsEndKey())
    {
        ScrollToEnd();
    }
    else
    {
        handled = false;
    }

    e.SetHandled(handled);
}

void ScrollViewer::OnMouseWheel(suic::MouseWheelEventArg& e)
{
    if (_vScroll->IsVisible())
    {
        int zDelta = e.Delta();
        int nPos = _vScroll->GetScrollPos();

        if (zDelta < 0)
        {
            _vScroll->ScrollTo(nPos + 4, false);
        }
        else
        {
            _vScroll->ScrollTo(nPos - 4, false);
        }

        if (_vScroll->GetScrollPos() != nPos)
        {
            _vScroll->UpdateScrollBar();

            _vScroll->DoScroll();
        }

        e.SetHandled(true);
    }
}

};
