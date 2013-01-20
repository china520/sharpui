// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// VisualizePanel.cpp

#include <sui/VisualizePanel.h>

namespace ui
{

//////////////////////////////////////////////////////////////
// VisualizeLayout
//
ImplementTypeofInfo(VisualizePanel, suic::Panel)

VisualizePanel::VisualizePanel(ItemCollectionPtr container)
    :  _container(container)
{
    SetClassName(_T("VisualizePanel"));
    SetOrientation(CoreFlags::Vertical);
}

VisualizePanel::~VisualizePanel()
{
}

void VisualizePanel::OnInitialized()
{
    __super::OnInitialized();
}

void VisualizePanel::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

suic::Size VisualizePanel::MeasureOverride(const suic::Size& size)
{
    suic::Size desiredSize;

    if (GetOrientation() == CoreFlags::Vertical)
    {
        for (int i = 0; i < _container->GetCount(); ++i)
        {
            suic::FrameworkElementPtr itemPtr(_container->GetItem(i));

            if (itemPtr->IsVisible())
            {
                itemPtr->Measure(size);
                desiredSize.cy += itemPtr->GetDesiredSize().cy;
                desiredSize.cy += itemPtr->GetMargin().top;
                desiredSize.cy += itemPtr->GetMargin().bottom;

                if (itemPtr->GetDesiredSize().cx > desiredSize.cx)
                {
                    desiredSize.cx = itemPtr->GetDesiredSize().cx;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < _container->GetCount(); ++i)
        {
            suic::ElementPtr itemPtr(_container->GetItem(i));

            if (itemPtr->IsVisible())
            {
                itemPtr->Measure(size);
                desiredSize.cx += itemPtr->GetDesiredSize().cx;

                if (itemPtr->GetDesiredSize().cy > desiredSize.cy)
                {
                    desiredSize.cy = itemPtr->GetDesiredSize().cy;
                }
            }
        }
    }

    desiredSize.cx += GetPadding().SumLR();
    desiredSize.cy += GetPadding().SumTB();

    return desiredSize;
}

suic::Size VisualizePanel::ArrangeHorizontal(const suic::Size& size)
{
    int iWid = 0;
    int i = 0;

    if (_horizontalOffset > 0)
    {
        for (i = 0; i < _container->GetCount(); ++i)
        {
            suic::FrameworkElementPtr itemPtr(_container->GetItem(i));

            if (itemPtr->IsVisible())
            {
                iWid += itemPtr->GetDesiredSize().cx;
                iWid += itemPtr->GetMargin().SumLR();
            }

            if (iWid >= _horizontalOffset)
            {
                iWid -= itemPtr->GetDesiredSize().cx;
                iWid -= itemPtr->GetMargin().SumLR();
                break;
            }
        }
    }

    _visibleStart = i;

    suic::Rect rect(iWid - _horizontalOffset + GetPadding().left
        , -_verticalOffset + GetPadding().top, 0, size.cy + _verticalOffset);

    for (; i < _container->GetCount(); ++i)
    {
        suic::FrameworkElementPtr itemPtr(_container->GetItem(i));

        if (itemPtr->IsVisible())
        {
            rect.right = rect.left + itemPtr->GetDesiredSize().cx;

            rect.left += itemPtr->GetMargin().left;
            rect.right = rect.left + itemPtr->GetDesiredSize().cx;
            rect.right += itemPtr->GetMargin().right;

            AddVisualChild(itemPtr.get());
            itemPtr->Arrange(rect);
        }

        rect.left = rect.right;

        if (rect.left >= size.cx)
        {
            break;
        }
    }

    _visibleCount = i - _visibleStart;

    return size;
}

suic::Size VisualizePanel::ArrangeVertical(const suic::Size& size, int iOffset)
{
    int iHei = 0;
    int i = 0;

    if (_verticalOffset > 0)
    {
        for (i = 0; i < _container->GetCount(); ++i)
        {
            suic::FrameworkElementPtr itemPtr(_container->GetItem(i));

            if (itemPtr->IsVisible())
            {
                iHei += itemPtr->GetDesiredSize().cy;
                iHei += itemPtr->GetMargin().top;
                iHei += itemPtr->GetMargin().bottom;
            }

            if (iHei >= _verticalOffset)
            {
                iHei -= itemPtr->GetDesiredSize().cy;
                iHei -= itemPtr->GetMargin().top;
                iHei -= itemPtr->GetMargin().bottom;

                break;
            }
        }
    }

    _visibleStart = i;

    int iTopOffset = iHei - _verticalOffset + iOffset + GetPadding().top;

    suic::Rect rect(-_horizontalOffset + GetPadding().left
        , iTopOffset, size.cx + _horizontalOffset, 0);

    for (; i < _container->GetCount(); ++i)
    {
        suic::FrameworkElementPtr itemPtr(_container->GetItem(i));

        if (itemPtr->IsVisible())
        {
            rect.top += itemPtr->GetMargin().top;
            rect.bottom = rect.top + itemPtr->GetDesiredSize().cy;
            rect.bottom += itemPtr->GetMargin().bottom;

            AddVisualChild(itemPtr.get());
            itemPtr->Arrange(rect);
        }

        rect.top = rect.bottom;

        if (rect.top >= size.cy)
        {
            break;
        }
    }

    _visibleCount = i - _visibleStart;

    return size;
}

suic::Size VisualizePanel::ArrangeOverride(const suic::Size& size)
{
    ClearVisualChildren();

    if (GetOrientation() == CoreFlags::Horizontal)
    {
        return ArrangeHorizontal(size);
    }
    else
    {
        return ArrangeVertical(size, 0);
    }
}

//====================================================
//
VisualizeHeaderPanel::VisualizeHeaderPanel(ItemCollectionPtr container)
    : VisualizePanel(container)
{
}

suic::FrameworkElementPtr VisualizeHeaderPanel::GetHeader()
{
    return _header;
}

void VisualizeHeaderPanel::SetHeader(suic::FrameworkElementPtr val)
{
    _header = val;
}

suic::Size VisualizeHeaderPanel::MeasureOverride(const suic::Size& size)
{
    suic::Size finalSize = __super::MeasureOverride(size);

    if (GetHeader())
    {
        GetHeader()->Measure(size);

        if (GetHeader()->GetDesiredSize().cx > finalSize.cx)
        {
            finalSize.cx = GetHeader()->GetDesiredSize().cx;
        }

        finalSize.cy += GetHeader()->GetDesiredSize().cy;
    }

    return finalSize;
}

suic::Size VisualizeHeaderPanel::ArrangeOverride(const suic::Size& size)
{
    ClearVisualChildren();

    if (GetOrientation() == CoreFlags::Horizontal)
    {
        return ArrangeHorizontal(size);
    }
    else
    {
        suic::Size finalSize;

        if (!GetHeader())
        {
            finalSize = ArrangeVertical(size, 0);
        }
        else
        {
            finalSize = ArrangeVertical(size, GetHeader()->GetDesiredSize().cy);

            suic::Rect rect(-_horizontalOffset, 0, size.cx + _horizontalOffset
                , GetHeader()->GetDesiredSize().cy);

            AddVisualChild(GetHeader().get());
            GetHeader()->Arrange(rect);
        }

        return finalSize;
    }
}

}
