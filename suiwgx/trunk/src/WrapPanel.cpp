// ======================================================================
//
// Copyright (c) 2008-2012 Inc. All rights reserved.
//
// 作者：汪荣
// 邮箱：china0851@foxmail.com
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// WrapPanel.cpp

#include <sui/WrapPanel.h>

namespace ui
{

ImplementTypeofInfo(WrapPanel, suic::Panel)

WrapPanel::WrapPanel()
    : _horizontalSpace(4)
    , _verticalSpace(4)
    , _itemWidth(96)
    , _itemHeight(48)
{
    SetClassName(_T("WrapPanel"));

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
}

WrapPanel::~WrapPanel()
{
}

suic::Size WrapPanel::MeasureOverride(const suic::Size& size)
{
    suic::Size desiredSize;

    __super::MeasureOverride(size);

    return desiredSize;
}

suic::Size WrapPanel::ArrangeOverride(const suic::Size& size)
{
    ClearVisualChildren();

    suic::Rect rect;

    int iPerRowCount = size.cx / (_horizontalSpace + _itemWidth);
    int iRight = size.cx - GetBorderThickness().right - _horizontalSpace;
    int iBottom = size.cy - GetBorderThickness().bottom - _verticalSpace;

    if (iPerRowCount == 0)
    {
        ++iPerRowCount;
    }

    int iRowHei = iPerRowCount * (_verticalSpace + _itemHeight);
    int iRowWid = iPerRowCount * (_horizontalSpace + _itemWidth) - _horizontalSpace;

    int iRealCount = 0;

    rect.left = GetBorderThickness().left + _horizontalSpace;
    rect.top = GetBorderThickness().top + _verticalSpace;

    for (int i = 0; i < GetChildrenCount(); ++i)
    {
        suic::Element* pElem = GetChild(i);

        if (pElem->IsVisible())
        {
            ++iRealCount;

            rect.right = rect.left + _itemWidth;
            rect.bottom = rect.top + _itemHeight;

            AddVisualChild(pElem);
            pElem->Arrange(rect);

            rect.left = rect.right + _horizontalSpace;

            if (rect.right >= iRowWid)
            {
                rect.left = GetBorderThickness().left + _horizontalSpace;     
                rect.top = rect.bottom + _verticalSpace;
            }

            if (rect.bottom >= iBottom)
            {
                break;
            }
        }
    }

    return size;
}

};
