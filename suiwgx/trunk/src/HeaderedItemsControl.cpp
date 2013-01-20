// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// HeaderItemsControl.cpp

#include <suic/render/uirender.h>

#include <sui/HeaderedItemsControl.h>
#include <sui/textblock.h>
#include <sui/Selector.h>
#include <sui/stackpanel.h>

#include <suic/tools/vector.h>

namespace ui
{

ImplementTypeofInfo(HeaderedItemsControl, suic::ContentControl)

//======================================================
// HeaderedPanel
class HeaderedPanel : public ui::StackPanel
{
public:

    HeaderedPanel(bool bHorz)
        : ui::StackPanel(bHorz)
    {
        SetClassName(_T("HeaderedPanel"));
        SetFocusable(true);
    }

    void OnRender(suic::DrawingContext * drawing)
    {
        /*suic::Rect rect(0, 0, RenderSize().cx, RenderSize().cy);

        if (IsFocused())
        {
            if (GetStyle()->GetTrigger(suic::FOCUSED))
            {
                suic::Render::DrawBackground(drawing, GetStyle()->GetTrigger(suic::FOCUSED), &rect);
            }
        }
        else if (IsMouseOver() && GetStyle()->GetTrigger(suic::MOUSEOVER))
        {
            suic::Render::DrawBackground(drawing, GetStyle()->GetTrigger(suic::MOUSEOVER), &rect);
        }*/
    }
};

HeaderedItemsControl::HeaderedItemsControl()
{
    SetClassName(_T("HeaderItemsControl"));

    InitializeScrollView();
}

HeaderedItemsControl::~HeaderedItemsControl()
{
}

void HeaderedItemsControl::InitializeScrollView()
{
    // 初始化布局器(垂直)
    _headerHost = new ui::HeaderedPanel(true);
    // Header布局器(水平)
    //_itemsHost = new ui::StackPanel(false);
    _itemsHost = new VisualizePanel(_items);

    _headerHost->SetHorizontalAlignment(HoriAlignment::Stretch);
    _itemsHost->SetHorizontalAlignment(HoriAlignment::Stretch);

    _headerHost->SetMinHeight(18);

    AddLogicalChild(_headerHost.get());
    AddVisualChild(_headerHost.get());

    AddLogicalChild(_itemsHost.get());
    AddVisualChild(_itemsHost.get());
}

suic::ElementPtr HeaderedItemsControl::GetHeader() const
{
    return _header;
}

void HeaderedItemsControl::SetHeader(suic::ElementPtr val)
{
    if (_header.get() != val.get() && val)
    {
        OnHeaderChanged(_header.get(), val.get());
    }
}

void HeaderedItemsControl::SetText(const suic::String & text)
{
    suic::FrameworkElementPtr itemHead(_header);

    if (itemHead)
    {
        itemHead->SetText(text);
    }
}

suic::String HeaderedItemsControl::GetText()
{
    suic::FrameworkElementPtr frame(_header);

    if (frame)
    {
        return frame->GetText();
    }
    else
    {
        return _T("");
    }
}

//=======================================================
//
suic::Size HeaderedItemsControl::
MeasureOverride(const suic::Size& availableSize)
{
    suic::Size retSize;

    _headerHost->Measure(availableSize);

    retSize.cy = _headerHost->GetDesiredSize().cy;
    retSize.cx = _headerHost->GetDesiredSize().cx;

    if (!IsCollapsed())
    {
        suic::Size size = MeasureItems(availableSize, false);

        retSize.cy += size.cy;

        if (size.cx > retSize.cx)
        {
            retSize.cx = size.cx;
        }
    }

    return retSize;
}

suic::Size HeaderedItemsControl::ArrangeOverride(const suic::Size& availableSize)
{
    suic::Rect itemrect(0, 0, availableSize.cx, 0);

    if (_header)
    {
        itemrect.bottom = itemrect.top + _headerHost->GetDesiredSize().cy;
        _headerHost->Arrange(itemrect);
        itemrect.top = itemrect.bottom;
    }

    if (!IsCollapsed())
    {
        itemrect.bottom = availableSize.cy;

        if (itemrect.top < itemrect.bottom)
        {
            _itemsHost->Arrange(itemrect);
        }
    }

    return availableSize;
}

void HeaderedItemsControl::OnPropertyChanged(suic::PropertyChangedEventArg& e)
{
    __super::OnPropertyChanged(e);
}

void HeaderedItemsControl::OnInitialized()
{
    suic::ObjectPtr headerPtr = GetStyle()->GetValue(_T("Header"));

    if (headerPtr)
    {
        SetText(headerPtr->ToString());
    }

    suic::Control::OnInitialized();
}

void HeaderedItemsControl::OnPreviewMouseLeftButtonDown(suic::MouseEventArg& e)
{
    if (GetHeader().get() == e.GetSource())
    {
        Selector::SelectItem(e.GetSource(), true);

        InvalidateVisual();
    }
}

void HeaderedItemsControl::
OnHeaderChanged(suic::Element* oldHeader, suic::Element* newHeader)
{
    if (oldHeader)
    {
        _headerHost->RemoveChild(oldHeader);
    }

    _header = newHeader;
    _headerHost->AddChild(_header);

    _header->SetVerticalAlignment(VertAlignment::Stretch);
    _header->SetVerticalContentAlignment(VertContentAlignment::Center);
}

int HeaderedItemsControl::AddChild(suic::ObjectPtr child)
{
    suic::ElementPtr pElem(child);

    if (pElem->GetWrapper().Equals(_T("Header")))
    {
        SetHeader(child);

        return 0;
    }
    else
    {
        return __super::AddChild(child);
    }
}

void HeaderedItemsControl::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

};
