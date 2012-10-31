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
    : _isAverage(false)
    , _headerHeight(25)
{
    SetClassName(_T("TabControl"));
    _headerPanel.SetAutoDelete(false);
    _headerPanel.SetHorizontalAlignment(suic::STRETCH);

    _headerPanel.Children()->SetLogicalParent(this);
}

TabControl::~TabControl()
{
}

suic::ObjectPtr TabControl::SelectedContent() const
{
    return suic::ObjectPtr();
}

void TabControl::OnSetterChanged(suic::SetterChangedEventArg& e)
{
    if (e.GetName().Equals(_T("Average")))
    {
        _isAverage = e.GetSetter()->ToBool();
    }
    else
    {
        //
        // 必须调用基类初始化基本数据
        //
        __super::OnSetterChanged(e);
    }
}

void TabControl::ClearChildren()
{
    _headerPanel.ClearChildren();
    __super::ClearChildren();
}

void TabControl::RemoveChild(suic::ObjectPtr child)
{
    _headerPanel.RemoveChild(child);
    __super::RemoveChild(child);
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

        _headerPanel.SetMinHeight(_headerHeight);

        TabItemPtr focusTab(_focusedItem);

        if (focusTab && focusTab->GetTabContent())
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

    _headerPanel.ClearChildren();

    int iItems = GetItems()->GetCount();
    suic::Rect finalRect(0, 0, size.cx, size.cy);

    if (iItems > 0)
    {
        if (_isAverage)
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
                _headerPanel.AddChild(tabItem.get());
            }

            finalRect.bottom = finalRect.top + _headerHeight;

            AddVisualChild(&_headerPanel);
            _headerPanel.Arrange(finalRect);
        }
        else
        {
            for (int i = 0; i < iItems; ++i)
            {
                TabItemPtr tabItem = GetItems()->GetItem(i);

                if (tabItem)
                {
                    _headerPanel.AddChild(tabItem.get());
                }
            }

            finalRect.bottom = finalRect.top + _headerHeight;

            AddVisualChild(&_headerPanel);
            _headerPanel.Arrange(finalRect);
        }

        finalRect.top = finalRect.bottom;
        finalRect.bottom = size.cy;
    }

    TabItemPtr focusTab(_focusedItem);

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

    //AddLogicalChild(&_headerPanel);

    _headerPanel.SetClassName(_T("TabHeader"));
    //_headerPanel.Children()->NotifyCollectionChanged += suic::NotifyCollectionChangedHandler(this, &TabControl::OnNotifyCollectionChanged);

    _headerPanel.BeginInit();
    _headerPanel.EndInit();

    if (GetItems()->GetCount() > 0 && !_focusedItem)
    {
        Selector::SelectItem(GetItems()->GetItem(0), true);
    }

    TabItemPtr focusTab(_focusedItem);

    if (focusTab && focusTab->GetTabContent())
    {
        focusTab->GetTabContent()->Measure(suic::Size());
    }
}

void TabControl::OnLoaded(suic::LoadedEventArg& e)
{
    __super::OnLoaded(e);

    if (_focusedItem)
    {
        Selector::SelectItem(_focusedItem, true);
    }
}

void TabControl::OnStyleUpdated()
{
    _headerPanel.UpdateStyle();
}

void TabControl::OnRender(suic::DrawingContext * drawing)
{
    suic::Rect rect(0, _headerHeight, RenderSize().cx, RenderSize().cy - _headerHeight);
    suic::Render::DrawBackground(drawing, GetStyle()->GetTrigger(), &rect);
}

void TabControl::OnNotifyCollectionChanged(suic::ObjectPtr sender, suic::NotifyCollectionChangedArg& e)
{
    if (sender.get() == &_headerPanel)
    {
        if (e.GetAction() == suic::NotifyCollectionChangedAction::Remove)
        {
            RemoveChild(e.OldItems()->GetAt(0));
        }
    }
    else
    {
        __super::OnNotifyCollectionChanged(sender, e);
    }
}

void TabControl::OnItemsChanged(suic::NotifyCollectionChangedArg& e)
{
    WriteFlag(CoreFlags::IsMeasureDirty, true);

    if (e.NewItems()->GetCount() > 0)
    {        
        TabItemPtr itemPtr = TabItemPtr::cast(e.NewItems()->GetAt(0));
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
