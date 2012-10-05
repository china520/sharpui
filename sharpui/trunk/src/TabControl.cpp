// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// TabControl.cpp

#include <sui/TabControl.h>
#include <sui/StackPanel.h>
#include <suicore/drawing/uirender.h>

namespace ui
{

TabControl::TabControl()
    : _isAverage(true)
{
    SetClassName(_T("TabControl"));
    _headerPanel.SetAutoDelete(false);
}

TabControl::~TabControl()
{
}

suic::ObjectPtr TabControl::SelectedContent() const
{
    return suic::ObjectPtr();
}

suic::Size TabControl::MeasureOverride(const suic::Size& size)
{
    suic::Size availableSize;

    if (ReadFlag(CoreFlags::IsMeasureDirty))
    {
        _headerHeight = 0;

        int iItems = GetItems()->GetCount();

        for (int i = 0; i < iItems; ++i)
        {
            TabItemPtr tabItem(GetItems()->GetItem(i));

            tabItem->Measure(size);

            if (tabItem->GetDesiredSize().cy > _headerHeight)
            {
                _headerHeight = tabItem->GetDesiredSize().cy;
            }
        }

        TabItemPtr focusTab(_focusItem);

        if (focusTab)
        {
            focusTab->GetTabContent()->Measure(size);
        }

        WriteFlag(CoreFlags::IsMeasureDirty, false);
    }

    return size;
}

suic::Size TabControl::ArrangeOverride(const suic::Size& size)
{
    ClearVisualChildren();

    _headerPanel.ClearLogicalChildren();

    int iItems = GetItems()->GetCount();
    suic::Rect finalRect(0, 0, size.cx, size.cy);

    if (_isAverage && iItems > 0)
    {
        TabItemPtr tabItem;
        int iWid = size.cx / iItems;
        suic::Size itemSize(iWid, _headerHeight);

        for (int i = 0; i < iItems - 1; ++i)
        {
            tabItem = GetItems()->GetItem(i).get();
            tabItem->SetDesiredSize(itemSize);
        }

        tabItem = GetItems()->GetItem(iItems - 1).get();

        itemSize.cx = size.cx - iWid * (iItems - 1);
        tabItem->SetDesiredSize(itemSize);

        for (int i = 0; i < iItems; ++i)
        {
            tabItem = GetItems()->GetItem(i).get();
            _headerPanel.AddLogicalChild(tabItem.get());
        }

        finalRect.bottom = finalRect.top + _headerHeight;

        AddVisualChild(&_headerPanel);
        _headerPanel.Arrange(finalRect);

        finalRect.top = finalRect.bottom;
        finalRect.bottom = size.cy;
    }

    TabItemPtr focusTab(_focusItem);

    if (focusTab)
    {  
        if (focusTab->GetTabContent())
        {
            AddVisualChild(focusTab->GetTabContent());
            focusTab->GetTabContent()->Arrange(finalRect);
        }
    }

    return size;
}

void TabControl::OnInitialized()
{
    __super::OnInitialized();

    suic::VisualHelper::SetLogicalParent(this, &_headerPanel);

    if (GetItems()->GetCount() > 0 && !_focusItem)
    {
        Selector::SelectItem(GetItems()->GetItem(0), true);
    }

    TabItemPtr focusTab(_focusItem);

    if (focusTab)
    {
        focusTab->GetTabContent()->Measure(suic::Size());
    }
}

void TabControl::OnLoaded(suic::LoadedEventArg& e)
{
    __super::OnLoaded(e);

    if (_focusItem)
    {
        Selector::SelectItem(_focusItem, true);
    }
}

void TabControl::OnRender(suic::DrawingContext * drawing)
{
    suic::Rect rect(0, _headerHeight, RenderSize().cx, RenderSize().cy - _headerHeight);
    suic::UIRender::DrawBackground(drawing, GetStyle()->GetTrigger(), &rect);
}

void TabControl::OnItemsChanged(NotifyContainerChangedArg& e)
{
    WriteFlag(CoreFlags::IsMeasureDirty, true);

    if (e.GetNewItems()->GetCount() > 0)
    {        
        TabItemPtr itemPtr = TabItemPtr::cast(e.GetNewItems()->GetAt(0));
        suic::ElementPtr focused;

        //
        // 使当前拥有焦点的元素总是在最上(设置zIndex)
        //
        if (focused)
        {
            //suic::Panel::SetZIndex(focused, _itemLayout->GetLogicalChildrenCount());
        }
    }
}

void TabControl::OnItemSelected(suic::ObjectPtr item, ItemSelectionEventArg& e)
{
    __super::OnItemSelected(item, e);

    //
    // 设置测量大小脏区域标志，使布局管理器重新元素测量大小
    //
    RaisedMeasureDirty();

    //
    // 刷新布局和显示
    //
    InvalidateMeasure();
    InvalidateArrange();
    InvalidateVisual();
}

void TabControl::OnPreviewMouseLeftButtonDown(suic::MouseEventArg& e)
{
    __super::OnPreviewMouseLeftButtonDown(e);
}

void TabControl::OnPreviewMouseLeftButtonUp(suic::MouseEventArg& e)
{
}

void TabControl::OnMouseEnter(suic::MouseEventArg& e)
{
    e.Handled(true);   
}

void TabControl::OnMouseLeave(suic::MouseEventArg& e)
{
    e.Handled(true); 
}

};
