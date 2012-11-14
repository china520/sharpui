// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// ScrollBar.cpp

#include "stdafx.h"

#include <sui/scrollbar.h>
#include <sui/repeatedbutton.h>
#include <sui/stackpanel.h>
#include <suicore/drawing/uirender.h>

#include <math.h>

static const int CSSCROLLTIMER = 258;

namespace ui
{

void ThumbButton::OnRender(suic::DrawingContext * drawing)
{
    // 先绘制背景
    __super::OnRender(drawing);

    suic::TriggerPtr trg(suic::Render::GetTriggerByStatus(this, GetStyle()));
    suic::ImageBrushPtr bkgnd = trg->GetValue(_T("Glyph"));

    if (bkgnd)
    {
        suic::Rect rect = bkgnd->GetContentBrounds();
        suic::Rect rc;

        if (rect.Width() <= RenderSize.cx 
            && rect.Height() <= RenderSize.cy)
        {
            rc.left = (RenderSize.cx - rect.Width()) / 2;
            rc.right = rc.left + rect.Width();

            rc.top = (RenderSize.cy - rect.Height()) / 2;
            rc.bottom = rc.top + rect.Height();

            bkgnd->Draw(drawing, &rc);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
// ScrollBar

ScrollBar::ScrollBar() 
    : _iStep(2)
    , _iVisualSize(0)
    , _iLogicSize(0)
{
    _thumb.SetAutoDelete(false);
    // 上箭头或左箭头
    _decreaseBtn.SetAutoDelete(false);
    _increaseBtn.SetAutoDelete(false);

    // 页面对象
    _decreasePage.SetAutoDelete(false);
    _increasePage.SetAutoDelete(false);

    _decreasePage.SetFocusable(false);
    _increasePage.SetFocusable(false);
    _thumb.SetFocusable(false);
    _decreaseBtn.SetFocusable(false);
    _increaseBtn.SetFocusable(false);

    SetClassName(_T("ScrollBar"));

    _scroInfo.iVisualPos = 0;
    _scroInfo.iLogicPos = 0;
    _scroInfo._iTrackPos = 0;

    CalcScrollPos();

    const int nxHScroll = 16;
    const int nxVScroll = 16;

    _decreaseBtn.SetWidth(nxHScroll);
    _decreaseBtn.SetHeight(nxVScroll);

    _increaseBtn.SetWidth(nxHScroll);
    _increaseBtn.SetHeight(nxVScroll);

    SetWidth(nxHScroll);
    SetHeight(nxVScroll);
}

ScrollBar::~ScrollBar()
{
}

int ScrollBar::GetScrollPos()
{
    return _scroInfo.iVisualPos;
}

int ScrollBar::GetScrollSize()
{
    return (_scroInfo.iVisualPos * _iStep);
}

void ScrollBar::SetScrollPos(int iPos)
{
    _scroInfo.iVisualPos = iPos;

    int iMin = 0;
    int iMaxPos = max(0, (_scroInfo.iMax - iMin + 1 - _scroInfo.iPage));

    if (_scroInfo.iVisualPos < iMin)
    {
        _scroInfo.iVisualPos = iMin;
    }

    _scroInfo.iVisualPos = min(iMaxPos, _scroInfo.iVisualPos);
}

void ScrollBar::UpdateScrollBar()
{
    InvalidateArrange();
}

void ScrollBar::ShowFirstScrollButton(bool bShow)
{
    _decreaseBtn.SetVisible(bShow);
    InvalidateArrange();
    InvalidateVisual();
}

void ScrollBar::ShowSecondScrollButton(bool bShow)
{
    _increaseBtn.SetVisible(bShow);
    InvalidateArrange();
    InvalidateVisual();
}

void ScrollBar::SetScrollStep(int iStep)
{
    _iStep = iStep;
}

int ScrollBar::GetScrollStep()
{
    return _iStep;
}

void ScrollBar::CalcScrollPos()
{
    _scroInfo.iMax = (int)((double)_iLogicSize / (double)_iStep + 0.5);
    _scroInfo.iPage = (int)((double)_iVisualSize / (double)_iStep + 0.5);

    if (_iLogicSize <= _iVisualSize)
    {
        _scroInfo.iVisualPos = 0;
    }

    ScrollTo(_scroInfo.iVisualPos, false);
}

void ScrollBar::ScrollToBegin(bool bRepaint)
{
    if (_scroInfo.iVisualPos != 0)
    {
        _scroInfo.iVisualPos = 0;

        DoScroll(bRepaint);
    }
}

int ScrollBar::MaxScrollPos()
{
    int iMin = 0;
    int iMaxPos = max(0, (_scroInfo.iMax - iMin + 1 - _scroInfo.iPage));

    return iMaxPos;
}

void ScrollBar::ScrollTo(int nNewPos, bool bRepaint)
{
    int iMin = 0;
    int iMaxPos = max(0, (_scroInfo.iMax - iMin + 1 - _scroInfo.iPage));

    if (nNewPos < iMin)
    {
        nNewPos = iMin;
    }

    int iOldPos = _scroInfo.iVisualPos;

    _scroInfo.iVisualPos = min(iMaxPos, nNewPos);

    if (iOldPos != _scroInfo.iVisualPos)
    {
        InvalidateArrange();
    }

    if (bRepaint)
    {
        InvalidateVisual();
    }
}

void ScrollBar::ScrollToEnd(bool bRepaint)
{
    int iMin = 0;
    int iMaxPos = max(0, (_scroInfo.iMax - iMin + 1 - _scroInfo.iPage));

    if (_scroInfo.iVisualPos != iMaxPos)
    {
        _scroInfo.iVisualPos = iMaxPos;

        DoScroll(bRepaint);
    }
}

void ScrollBar::SetScrollInfo(int iVisual, int iLogic, bool bRepaint)
{
    UpdateScrollInfo(iVisual, iLogic, true);

    if (bRepaint)
    {
        InvalidateVisual();
    }
}

void ScrollBar::UpdateScrollInfo(int iVisual, int iLogic, bool bCalc)
{
    _iVisualSize = iVisual;
    _iLogicSize = iLogic;

    CalcScrollPos();

    if (bCalc)
    {
        GetScrollThumbRect(RenderSize);
    }
}

void ScrollBar::UpdateScrollVisual(int iVisual, bool bRepaint)
{
    if (_iVisualSize != iVisual)
    {
        _iVisualSize = iVisual;
    }

    CalcScrollPos();

    if (bRepaint)
    {
        InvalidateVisual();
    }
}

void ScrollBar::UpdateScrollLogic(int iLogic, bool bRepaint)
{
    if (_iLogicSize != iLogic)
    {
        _iLogicSize = iLogic;
    }

    CalcScrollPos();

    if (bRepaint)
    {
        InvalidateVisual();
    }
}

void ScrollBar::AddScrollLogic(int iLogic, bool bRepaint)
{
    UpdateScrollLogic(_iLogicSize + iLogic, bRepaint);
}

const int cst_ScrollMin      = 4;
const int cst_ScrollThumbMin = 8;

suic::Rect ScrollBar::GetScrollThumbRect(const suic::Size & size, bool bThumb)
{
    int iMin = 0;

    int nxHScroll = (int)_decreaseBtn.GetWidth();
    int nxVScroll = (int)_decreaseBtn.GetHeight();

    suic::Rect rectThumb;

	if (bThumb || !_rcTrack.Empty())
	{
		rectThumb = _rcTrack;
	}
	else
	{
        suic::Rect rect(0, 0, size.cx, size.cy);

		rectThumb = rect;

		int nClientSize = 0;
		int nThumbSize  = 0;

		if (GetOrientation() == CoreFlags::Horizontal)
		{
			nThumbSize = nxHScroll;

            if (_decreaseBtn.IsVisible())
            {
                rectThumb.left += nThumbSize;
            }
            if (_increaseBtn.IsVisible())
            {
                rectThumb.right -= nThumbSize;
            }

			nClientSize = rectThumb.Width();
		}
		else
		{
			nThumbSize = nxVScroll;
            
            if (_decreaseBtn.IsVisible())
            {
                rectThumb.top += nThumbSize;
            }
            if (_increaseBtn.IsVisible())
            {
                rectThumb.bottom -= nThumbSize;
            }

			nClientSize = rectThumb.Height();
		}

		if (nClientSize <= cst_ScrollMin)
		{
            rectThumb.SetEmpty();
			return rectThumb;
		}

		int nThumbPos = 0;//nThumbSize;

		if (_scroInfo.iPage != 0)
		{
			nThumbSize = max (::MulDiv(nClientSize, _scroInfo.iPage, _scroInfo.iMax - iMin + 1), cst_ScrollThumbMin);
		}

		if (nClientSize < nThumbSize || nThumbSize == 0)
		{
			rectThumb.SetEmpty ();
            Enable(!rectThumb.Empty());
			return rectThumb;
		}
		else
		{
			nClientSize -= nThumbSize;
			int nMax = _scroInfo.iMax - max (_scroInfo.iPage - 1, 0);

			if (iMin < nMax)
			{
                nThumbPos += ::MulDiv(nClientSize, _scroInfo.iVisualPos - iMin, nMax - iMin);
			}
		}

		if (GetOrientation() == CoreFlags::Horizontal)
		{
			rectThumb.left   = rect.left + nThumbPos
                + (_decreaseBtn.IsVisible() ? (int)_decreaseBtn.GetWidth() : 0);
			rectThumb.right  = rectThumb.left + nThumbSize;
		}
		else
		{
			rectThumb.top    = rect.top + nThumbPos 
                + (_decreaseBtn.IsVisible() ? (int)_decreaseBtn.GetHeight() : 0);
			rectThumb.bottom = rectThumb.top + nThumbSize;
		}

        Enable(!rectThumb.Empty());
	}

    return rectThumb;
}

//////////////////////////////////////////////////////////////////////////////
// 事件函数

void ScrollBar::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

void ScrollBar::InternalInit()
{
    if (GetOrientation() == CoreFlags::Horizontal)
    {
        if (GetHeight() > 0)
        {
            _decreaseBtn.SetWidth(GetHeight());
            _decreaseBtn.SetHeight(GetHeight());
            _increaseBtn.SetWidth(GetHeight());
            _increaseBtn.SetHeight(GetHeight());
        }
    }
    else
    {
        if (GetWidth() > 0)
        {
            _decreaseBtn.SetWidth(GetWidth());
            _decreaseBtn.SetHeight(GetWidth());
            _increaseBtn.SetWidth(GetWidth());
            _increaseBtn.SetHeight(GetWidth());
        }
    }
}

void ScrollBar::OnSetterChanged(suic::SetterChangedEventArg& e)
{
    if (e.GetName().Equals(_T("ShowFirstButton")))
    {
        _decreaseBtn.SetVisible(e.GetSetter()->ToBool());
    }
    else if (e.GetName().Equals(_T("ShowSecondButton")))
    {
        _increaseBtn.SetVisible(e.GetSetter()->ToBool());
    }
    else
    {
        __super::OnSetterChanged(e);

        if (e.GetName().Equals(suic::WIDTH) || e.GetName().Equals(suic::HEIGHT))
        {
            InternalInit();
        }
    }
}

void ScrollBar::OnLoaded(suic::LoadedEventArg& e)
{
    _decreaseBtn.OnLoaded(e);
    _increaseBtn.OnLoaded(e);
    _thumb.OnLoaded(e);
    _decreasePage.OnLoaded(e);
    _increasePage.OnLoaded(e);
}

void ScrollBar::OnUnloaded(suic::LoadedEventArg& e)
{
    __super::OnUnloaded(e);

    _decreaseBtn.OnUnloaded(e);
    _increaseBtn.OnUnloaded(e);
    _thumb.OnUnloaded(e);
    _decreasePage.OnUnloaded(e);
    _increasePage.OnUnloaded(e);
}

void ScrollBar::OnStyleUpdated()
{
    _decreaseBtn.UpdateStyle();
    _increaseBtn.UpdateStyle();
    _thumb.UpdateStyle();
    _decreasePage.UpdateStyle();
    _increasePage.UpdateStyle();
}

void ScrollBar::OnInitialized()
{
    suic::StylePtr & selfStyle = GetStyle();

    suic::StylePtr dBtn(selfStyle->GetStylePart(_T("DecreaseButton")));
    suic::StylePtr iBtn(selfStyle->GetStylePart(_T("IncreaseButton")));

    suic::StylePtr dPage(selfStyle->GetStylePart(_T("DecreasePage")));
    suic::StylePtr iPage(selfStyle->GetStylePart(_T("IncreasePage")));

    suic::StylePtr thumb(selfStyle->GetStylePart(_T("Thumb")));

    if (!dBtn && GetOwner())
    {
        dBtn = GetOwner()->FindResource(GetClassName() + _T(".DecreaseButton"));
        iBtn = GetOwner()->FindResource(GetClassName() + _T(".IncreaseButton"));
        dPage = GetOwner()->FindResource(GetClassName() + _T(".Track.Page"));
        thumb = GetOwner()->FindResource(GetClassName() + _T(".Track.Thumb"));
    }

    if (!iPage || iPage->Setters->GetCount() == 0)
    {
        iPage = dPage;
    }

    _decreasePage.SetOwner(this);

    _decreasePage.SetStyle(dPage);
    _increasePage.SetStyle(iPage);
    _thumb.SetStyle(thumb);

    _decreaseBtn.SetStyle(dBtn);
    _increaseBtn.SetStyle(iBtn);

    if (GetOrientation() == CoreFlags::Horizontal)
    {
        //
        // 附加事件
        //
        _decreasePage.MouseLButtonDown.Add(this, &ScrollBar::OnPageLeft);
        _increasePage.MouseLButtonDown.Add(this, &ScrollBar::OnPageRight);
        _thumb.MouseMove.Add(this, &ScrollBar::OnHorzTrack);

        _decreaseBtn.MouseLButtonDown.Add(this, &ScrollBar::OnLineLeft);
        _increaseBtn.MouseLButtonDown.Add(this, &ScrollBar::OnLineRight);
    }
    else
    {
        _decreasePage.MouseLButtonDown.Add(this, &ScrollBar::OnPageUp);
        _increasePage.MouseLButtonDown.Add(this, &ScrollBar::OnPageDown);
        _thumb.MouseMove.Add(this, &ScrollBar::OnVertTrack);

        _decreaseBtn.MouseLButtonDown.Add(this, &ScrollBar::OnLineUp);
        _increaseBtn.MouseLButtonDown.Add(this, &ScrollBar::OnLineDown);
    }

    _thumb.MouseLButtonDown.Add(this, &ScrollBar::OnBeginTrack);
    _thumb.MouseLButtonUp.Add(this, &ScrollBar::OnEndTrack);

    SetFocusable(false);
    
    // test code
    UpdateScrollLogic(500, false);
}

void ScrollBar::OnPreviewMouseLeftButtonDown(suic::MouseEventArg& e)
{
	if (GetOwner())
	{
		//ui::UISetElementFocus(OwnerElement());

		//e->Handled(true);
	}
}

suic::Size ScrollBar::MeasureOverride(const suic::Size& availableSize)
{
    suic::Size size(availableSize);

    //InternalInit();

    _decreaseBtn.Measure(size);
    _increaseBtn.Measure(size);
    _thumb.Measure(size);
    _decreasePage.Measure(size);
    _increasePage.Measure(size);

    if (GetOrientation() == CoreFlags::Horizontal)
    {
        size.cy = _decreaseBtn.GetDesiredSize().cy;
    }
    else
    {
        size.cx = _decreaseBtn.GetDesiredSize().cx;
    }

    return size;
}

suic::Size ScrollBar::ArrangeOverride(const suic::Size& size)
{
    ClearVisualChildren();

    bool bChanged = false;
    suic::Rect finalRect;
    suic::Rect downRect;

    if (GetOrientation() == CoreFlags::Horizontal)
    {
        UpdateScrollVisual(size.cx, false);

        finalRect.bottom = _decreaseBtn.GetDesiredSize().cy;
    }
    else
    {
        UpdateScrollVisual(size.cy, false);

        finalRect.right = _decreaseBtn.GetDesiredSize().cx;
    }

    suic::Rect rcThumb;
    
    if (!_rcTrack.Empty())
    {
        suic::Point ptSelf = PointToScreen(suic::Point());

        rcThumb = _rcTrack;
        rcThumb.Offset(-ptSelf.x, -ptSelf.y);
    }
    else
    {
        rcThumb = GetScrollThumbRect(size);
    }

    if (GetOrientation() == CoreFlags::Horizontal)
    {
        if (_increaseBtn.IsVisible())
        {
            downRect.bottom = _increaseBtn.GetDesiredSize().cy;
            downRect.right = size.cx;
            downRect.left = size.cx - _increaseBtn.GetDesiredSize().cx;
        }

        /*if (size.cx < downRect.Width() + finalRect.Width())
        {
            return size;
        }*/
    }
    else
    {
        if (_increaseBtn.IsVisible())
        {
            downRect.right = _increaseBtn.GetDesiredSize().cx;
            downRect.bottom = size.cy;
            downRect.top = size.cy - _increaseBtn.GetDesiredSize().cy;
        }

        /*if (size.cy < downRect.Height() + finalRect.Height())
        {
            return size;
        }*/
    }

    if (_decreaseBtn.IsVisible())
    {
        finalRect.right = _decreaseBtn.GetDesiredSize().cx;
        finalRect.bottom = _decreaseBtn.GetDesiredSize().cy;

        AddVisualChild(&_decreaseBtn);
        _decreaseBtn.Arrange(finalRect);
    }

    if (!rcThumb.Empty())
    {
        if (GetOrientation() == CoreFlags::Horizontal)
        {
            finalRect.left = finalRect.right;
            finalRect.right = rcThumb.left;

            if (!finalRect.Empty())
            {
                AddVisualChild(&_decreasePage);
                _decreasePage.Arrange(finalRect);
            }

            finalRect.left = rcThumb.left;
            finalRect.right = rcThumb.right;
            AddVisualChild(&_thumb);
            _thumb.Arrange(finalRect);

            finalRect.left = rcThumb.right;
            finalRect.right = size.cx - downRect.Width();
            AddVisualChild(&_increasePage);
            _increasePage.Arrange(finalRect);
        }
        else
        {
            finalRect.top = finalRect.bottom;
            finalRect.bottom = rcThumb.top;

            if (!finalRect.Empty())
            {
                AddVisualChild(&_decreasePage);
                _decreasePage.Arrange(finalRect);
            }

            finalRect.top = rcThumb.top;
            finalRect.bottom = rcThumb.bottom;
            AddVisualChild(&_thumb);
            _thumb.Arrange(finalRect);

            finalRect.top = rcThumb.bottom;
            finalRect.bottom = size.cy - downRect.Height();
            AddVisualChild(&_increasePage);
            _increasePage.Arrange(finalRect);
        }
    }

    if (!downRect.Empty())
    {
        AddVisualChild(&_increaseBtn);
        _increaseBtn.Arrange(downRect);
    }    

    return size;
}

void ScrollBar::OnBeginTrack(suic::Element* pSender, suic::MouseEventArg& e)
{
    suic::Point pt = PointToScreen(suic::Point());

    _rcTrackStart = GetScrollThumbRect(RenderSize, false);
    _rcTrackStart.Offset(pt.x, pt.y);

    _rcTrack = _rcTrackStart;
    _scroInfo._iTrackPos = _scroInfo.iVisualPos;
    _ptTrackStart = e.MousePoint();
}

void ScrollBar::OnEndTrack(suic::Element* pSender, suic::MouseEventArg& e)
{
    _rcTrack.SetEmpty();
}

void ScrollBar::OnHorzTrack(suic::Element* pSender, suic::MouseEventArg& e)
{
    if (!_rcTrack.Empty())
    {
        int iMin = 0;

        suic::Point ptWindow = e.MousePoint();
        suic::Point ptSelf = PointToScreen(suic::Point());

        suic::Rect rect(ptSelf.x, ptSelf.y, RenderSize.cx, RenderSize.cy);
 
        suic::Size szClamp(0, 0);
		int nThumbLength = 0;

        szClamp.cx = rect.left + (_decreaseBtn.IsVisible() ? (int)_decreaseBtn.GetWidth() : 0);
        szClamp.cy = rect.right - (_increaseBtn.IsVisible() ? (int)_increaseBtn.GetWidth() : 0);

        nThumbLength = _rcTrackStart.Width();

        szClamp.cy -= nThumbLength;

        suic::Point ptOffset(ptWindow.x - _ptTrackStart.x, ptWindow.y - _ptTrackStart.y);
        suic::Rect rectNew(_rcTrackStart);

        if (abs(ptOffset.y) < 150)
        {
            rectNew.Offset(ptOffset.x, 0);

            if (rectNew.left < szClamp.cx)
            {
                rectNew.left  = szClamp.cx;
                rectNew.right = rectNew.left + nThumbLength;
            }
            else if (szClamp.cy < rectNew.left)
            {
                rectNew.left  = szClamp.cy;
                rectNew.right = rectNew.left + nThumbLength;
            }
        }

        if (!rectNew.Equal(&_rcTrack))
		{
			_rcTrack = rectNew;
            int nPosNew = PosFromThumb(_rcTrack.left - szClamp.cx, szClamp);

			if (_scroInfo.iVisualPos != nPosNew)
            {
                _scroInfo.iVisualPos = nPosNew;

                DoScroll(true);
            }
        }
    }
}

int ScrollBar::PosFromThumb(int thumb, const suic::Size & szClamp)
{
	const int iRange1 = szClamp.cy - szClamp.cx;
	const int iMin = 0;
	const int iMax = _scroInfo.iMax - (_scroInfo.iPage - 1);
	const int iRange2 = iMax - iMin;

	if (iRange2 < 0)
	{
		return 0;
	}

	int iPos = iMin + 
		(int)(((double)thumb) * ((double)iRange2) / (double)(iRange1) + 0.5);

	if (iPos < iMin)
	{
		iPos = iMin;
	}

	if (iMax < iPos)
	{
		iPos = iMax;
	}

	return iPos;
}

void ScrollBar::OnVertTrack(suic::Element* pSender, suic::MouseEventArg& e)
{
    if (!_rcTrack.Empty())
    {
        int iMin = 0;

        suic::Point ptWindow = e.MousePoint();
        suic::Point ptSelf = PointToScreen(suic::Point());

        suic::Rect rect(ptSelf.x, ptSelf.y, RenderSize.cx, RenderSize.cy);
 
        suic::Size szClamp(0, 0);
		int nThumbLength = 0;

        szClamp.cx = rect.top + (_decreaseBtn.IsVisible() ? (int)_decreaseBtn.GetHeight() : 0);
        szClamp.cy = rect.bottom - (_increaseBtn.IsVisible() ? (int)_increaseBtn.GetHeight() : 0);
        nThumbLength = _rcTrackStart.Height();

		szClamp.cy -= nThumbLength;

        suic::Point ptOffset(ptWindow.x - _ptTrackStart.x, ptWindow.y - _ptTrackStart.y);
        suic::Rect rectNew(_rcTrackStart);

        if (abs(ptOffset.x) < 150)
        {
            rectNew.Offset(0, ptOffset.y);

            if (rectNew.top < szClamp.cx)
            {
                rectNew.top    = szClamp.cx;
                rectNew.bottom = rectNew.top + nThumbLength;
            }
            else if (szClamp.cy < rectNew.top)
            {
                rectNew.top    = szClamp.cy;
                rectNew.bottom = rectNew.top + nThumbLength;
            }
        }

        if (!rectNew.Equal(&_rcTrack))
		{
			_rcTrack = rectNew;
            int nPosNew = PosFromThumb(_rcTrack.top - szClamp.cx, szClamp);

			if (_scroInfo.iVisualPos != nPosNew)
            {
                _scroInfo.iVisualPos = nPosNew;

                DoScroll(true);
            }
        }
    }
}

void ScrollBar::OnPageUp(suic::Element* pSender, suic::MouseEventArg& e)
{
    OnPageLeft(pSender, e);
}

void ScrollBar::OnPageDown(suic::Element* pSender, suic::MouseEventArg& e)
{
    OnPageRight(pSender, e);
}

void ScrollBar::OnPageLeft(suic::Element* pSender, suic::MouseEventArg& e)
{
    PageUp();
}

void ScrollBar::OnPageRight(suic::Element* pSender, suic::MouseEventArg& e)
{
    PageDown();
}

void ScrollBar::OnLineLeft(suic::Element* pSender, suic::MouseEventArg& e)
{
    LineUp();
}

void ScrollBar::OnLineRight(suic::Element* pSender, suic::MouseEventArg& e)
{
    LineDown();
}

void ScrollBar::OnLineUp(suic::Element* pSender, suic::MouseEventArg& e)
{
    OnLineLeft(pSender, e);
}

void ScrollBar::OnLineDown(suic::Element* pSender, suic::MouseEventArg& e)
{
    OnLineRight(pSender, e);
}

void ScrollBar::LineUp()
{
    if (_scroInfo.iVisualPos > 0)
    {
        --(_scroInfo.iVisualPos);

        DoScroll();
    }
}

void ScrollBar::LineDown()
{
    int iMin = 0;

    int iMaxPos = _scroInfo.iMax - iMin + 1 - _scroInfo.iPage;

    if (_scroInfo.iVisualPos < iMaxPos)
    {
        ++(_scroInfo.iVisualPos);
        DoScroll();
    }
}

void ScrollBar::LineLeft()
{
    LineUp();
}

void ScrollBar::LineRight()
{
    LineDown();
}

void ScrollBar::PageUp()
{
    if (_scroInfo.iVisualPos <= 0)
    {
        return;
    }

    _scroInfo.iVisualPos -= _scroInfo.iPage;

    if (_scroInfo.iVisualPos < 0)
    {
        _scroInfo.iVisualPos = 0;
    }

    DoScroll();
}

void ScrollBar::PageDown()
{
    int iMin = 0;

    int iMaxPos = _scroInfo.iMax - iMin + 1 - _scroInfo.iPage;

    if (_scroInfo.iVisualPos >= iMaxPos)
    {
        return;
    }

    _scroInfo.iVisualPos += _scroInfo.iPage;

    if (_scroInfo.iVisualPos > iMaxPos)
    {
        _scroInfo.iVisualPos = iMaxPos;
    }

    DoScroll();
}

void ScrollBar::DoScroll(bool bUpdate)
{
    bool bAutoDel = SetAutoDelete(false);
    suic::ElementPtr ePtr(this);

    if (Scroll)
    {
        ui::ScrollEventArg scrollEvt(_scroInfo.iVisualPos);

        Scroll(ePtr, scrollEvt);
    }

    if (bUpdate)
    {
        UpdateScrollBar();
    }
    
    InvalidateVisual();
    SetAutoDelete(bAutoDel);
}

}
