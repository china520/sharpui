// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// Splitter.cpp

#include <sui/Splitter.h>

namespace ui
{

//////////////////////////////////////////////////////////////
// Splitter
//

ImplementTypeofInfo(Splitter, suic::Panel)

Splitter::Splitter()
    : _trackingIndex(-1)
{
    SetClassName(_T("Splitter"));
}

Splitter::~Splitter()
{
}

suic::Size Splitter::MeasureOverride(const suic::Size& size)
{
    return __super::MeasureOverride(size);
}

void Splitter::ArrangeHorizontal(const suic::Size& size)
{
    int iCount = GetChildrenCount();
    suic::Rect finalRect(0, 0, size.cx, size.cy);
    suic::FrameworkElementPtr  stretchPtr;
    int iWid = 0;

    for (int i = 0; i < iCount; ++i)
    {
        suic::FrameworkElementPtr ePtr(GetChild(i));

        if (ePtr->IsVisible())
        {
            if (!stretchPtr && ePtr->GetHorizontalAlignment() == CoreFlags::Stretch)
            {
                stretchPtr = ePtr;

                for (int j = i + 1; j < iCount; ++j)
                {
                    suic::FrameworkElementPtr efPtr(GetChild(j));

                    iWid += efPtr->GetDesiredSize().cx + 4;
                }

                int iRealWid = size.cx - finalRect.left - iWid;

                if (iRealWid < 0)
                {
                    iRealWid = 0;
                }

                finalRect.right = finalRect.left + iRealWid;

                AddVisualChild(ePtr.get());
                ePtr->Arrange(finalRect);

                _splits.push_back(suic::Rect(finalRect.right, 0, 4, size.cy));

                ++i;

                if (i >= iCount)
                {
                    break;
                }

                ePtr = GetChild(i);
                finalRect.left = finalRect.right + 4;
            }

            finalRect.right = finalRect.left + ePtr->GetDesiredSize().cx;

            AddVisualChild(ePtr.get());
            ePtr->Arrange(finalRect);

            _splits.push_back(suic::Rect(finalRect.right, 0, 4, size.cy));

            finalRect.left = finalRect.right + 4;
        }
    }
}

void Splitter::ArrangeVertical(const suic::Size& size)
{
    int iCount = GetChildrenCount();
    suic::Rect finalRect(0, 0, size.cx, size.cy);
    suic::FrameworkElementPtr  stretchPtr;
    int iHei = 0;

    for (int i = 0; i < iCount; ++i)
    {
        suic::FrameworkElementPtr ePtr(GetChild(i));

        if (ePtr->IsVisible())
        {
            if (!stretchPtr && ePtr->GetHorizontalAlignment() == CoreFlags::Stretch)
            {
                stretchPtr = ePtr;

                for (int j = i + 1; j < iCount; ++j)
                {
                    suic::FrameworkElementPtr efPtr(GetChild(j));

                    iHei += efPtr->GetDesiredSize().cy + 4;
                }

                int iRealHei = size.cy - finalRect.top - iHei;

                if (iRealHei < 0)
                {
                    iRealHei = 0;
                }

                finalRect.bottom = finalRect.top + iRealHei;

                AddVisualChild(ePtr.get());
                ePtr->Arrange(finalRect);

                _splits.push_back(suic::Rect(0, finalRect.bottom, size.cx, 4));

                ++i;

                if (i >= iCount)
                {
                    break;
                }

                ePtr = GetChild(i);
                finalRect.top = finalRect.bottom + 4;
            }

            finalRect.bottom = finalRect.top + ePtr->GetDesiredSize().cy;

            AddVisualChild(ePtr.get());
            ePtr->Arrange(finalRect);

            _splits.push_back(suic::Rect(0, finalRect.bottom, size.cx, 4));

            finalRect.top = finalRect.bottom + 4;
        }
    }
}

suic::Size Splitter::ArrangeOverride(const suic::Size& size)
{
    ClearVisualChildren();
    _splits.clear();

    if (CoreFlags::Horizontal == GetOrientation())
    {
        ArrangeHorizontal(size);
    }
    else
    {
        ArrangeVertical(size);
    }

    return size;
}

void Splitter::OnInitialized()
{
    __super::OnInitialized();
}

void Splitter::OnSetCursor(suic::CursorEventArg& e)
{
    suic::CursorPtr cursor = GetCursor();

    if (cursor && cursor->GetHandle())
    {
        HCURSOR hcur = (HCURSOR)(DWORD_PTR)cursor->GetHandle();
        suic::Point pt(PointToScreen(suic::Point()));

        for (int i = 0; i < _splits.size(); ++i)
        {
            suic::Rect rect = _splits[i];
            rect.Offset(pt);

            if (rect.PointIn(e.MousePoint()))
            {
                e.SetHandled(true);
                ::SetCursor(hcur);
                break;
            }
        }
    }
}

void Splitter::OnMouseMove(suic::MouseEventArg& e)
{
    if (_trackingIndex != -1)
    {
        suic::FrameworkElementPtr eCurr(GetChild(_trackingIndex));
        suic::FrameworkElementPtr eNext(GetChild(_trackingIndex + 1));

        if (CoreFlags::Horizontal == GetOrientation())
        {
            int ixOff = e.MousePoint().x - _trackingPt.x;
            int iMinWid = eCurr->GetMinWidth();
            int iFinalWid = eCurr->RenderSize().cx + ixOff;
            int iFinal2Wid = eNext->RenderSize().cx - ixOff;

            if (ixOff != 0 && iFinalWid > iMinWid && iFinal2Wid > eNext->GetMinWidth())
            {
                int iWid = iFinalWid;
                int iNextWid = iFinal2Wid;

                suic::Size desiredSize = eCurr->GetDesiredSize();

                desiredSize.cx = iWid;
                eCurr->SetDesiredSize(desiredSize);

                desiredSize = eNext->GetDesiredSize();
                desiredSize.cx = iNextWid;
                eNext->SetDesiredSize(desiredSize);

                InvalidateArrange();
                InvalidateVisual();

                _trackingPt = e.MousePoint();
            }
        }
        else
        {
            int iyOff = e.MousePoint().y - _trackingPt.y;
            int iMinHei = eCurr->GetMinHeight();
            int iFinalHei = eCurr->RenderSize().cy + iyOff;
            int iFinal2Hei= eNext->RenderSize().cy - iyOff;

            if (iyOff != 0 && iFinalHei > iMinHei && iFinal2Hei > eNext->GetMinHeight())
            {
                suic::Size desiredSize = eCurr->GetDesiredSize();

                desiredSize.cy = iFinalHei;
                eCurr->SetDesiredSize(desiredSize);

                desiredSize = eNext->GetDesiredSize();
                desiredSize.cy = iFinal2Hei;
                eNext->SetDesiredSize(desiredSize);

                InvalidateArrange();
                InvalidateVisual();

                _trackingPt = e.MousePoint();
            }
        }
    }

    e.SetHandled(true);
}

void Splitter::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    SetCaptureMouse();
    
    _trackingIndex = -1;

    if (GetChildrenCount() > 1)
    {
        _trackingPt = e.MousePoint();
        suic::Point pt = PointFromScreen(e.MousePoint());

        for (int i = 0; i < (int)_splits.size(); ++i)
        {
            if (_splits[i].PointIn(pt))
            {
                if (i < (int)_splits.size() - 1)
                {
                    _trackingIndex = i;
                }
                break;
            }
        }
    }

    e.SetHandled(true);
}

void Splitter::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    ReleaseCaptureMouse();

    _trackingIndex = -1;
    e.SetHandled(true);
}

}
