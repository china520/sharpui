// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// ItemsControl.cpp

#include <suicore/drawing/uirender.h>
#include <sui/ItemsControl.h>
#include <sui/textblock.h>
#include <util/vector.h>

namespace ui
{

/// <summary>
///  ItemContainer，Item的容器
/// </summary>
ItemContainer::ItemContainer(suic::Element* itemControl)
    : _itemControl(itemControl)
{

}

ItemContainer::~ItemContainer()
{
}

int ItemContainer::GetCount()
{
    return (int)_items.size();
}

suic::ObjectPtr ItemContainer::GetItem(int iIndex) const
{
    suic::ObjectPtr obj = _items[iIndex];

    return obj;
}

suic::String ItemContainer::GetItemText(int iIndex) const
{
    return _items[iIndex]->ToString();
}

void ItemContainer::HandleItem(suic::ObjectPtr& obj)
{
    suic::ElementPtr item(obj);

    if (item)
    {
        suic::VisualHelper::SetLogicalParent(_itemControl, item.get());

        if (!item->IsInitialized())
        {
            if (_itemControl->ReadFlag(CoreFlags::IsInitPending))
            {
                item->BeginInit();
            }
            else if (_itemControl->ReadFlag(CoreFlags::IsInitialized))
            {
                item->BeginInit();
                item->EndInit();
            }
        }

        if (_itemControl->ReadFlag(CoreFlags::IsLoaded))
        {
            if (!item->ReadFlag(CoreFlags::IsLoaded))
            {
                suic::HwndHelper::LoadedElement(item.get());
            }
        }
    }

    if (ContainerChanged)
    {
        NotifyContainerChangedArg e(NotifyContainerChangedAction::Add);

        e.AddNewItem(obj);

        ContainerChanged(_itemControl, e);
    }
}

int ItemContainer::InsertItem(int index, suic::ObjectPtr item)
{
    _items.insert(_items.begin() + index, item);

    HandleItem(item);

    return index;
}

int ItemContainer::AddItem(suic::ObjectPtr item)
{
    int index = _items.size();

    _items.push_back(item);
    HandleItem(item);

    return index;
}

void ItemContainer::Clear()
{
    _items.clear();
}

bool ItemContainer::Contains(suic::ObjectPtr item)
{
    return (IndexOf(item) >= 0);
}

int ItemContainer::IndexOf(suic::ObjectPtr item) const
{
    for (int i = 0; i < (int)_items.size(); ++i)
    {
        if (_items[i].get() == item.get())
        {
            return i;
        }
    }

    return -1;
}

void ItemContainer::Remove(suic::ObjectPtr item)
{
    for (int i = 0; i < (int)_items.size(); ++i)
    {
        if (_items[i].get() == item.get())
        {
            RemoveAt(i);

            break;
        }
    }
}

void ItemContainer::RemoveAt(int index)
{
    suic::ObjectPtr itemPtr = _items[index];

    _items.erase(_items.begin() + index);

    if (ContainerChanged)
    {
        NotifyContainerChangedArg e(NotifyContainerChangedAction::Remove);

        e.AddOldItem(itemPtr);

        ContainerChanged(_itemControl, e);
    }
}

void ItemContainer::RemoveRange(int index, int count)
{
    _items.erase(_items.begin() + index, _items.begin() + index + count);
}

/// <summary>
///  ItemsControl，Item的基类
/// </summary>
ItemsControl::ItemsControl()
{
    SetClassName(_T(""));

    _container = new ItemContainer(this);
    _container->ContainerChanged.Add(this, &ItemsControl::OnNotifyContainerChanged);

    InitializeScrollView();
}

ItemsControl::~ItemsControl()
{
}

void ItemsControl::InitializeScrollView()
{
    _panel = new VisualizePanel(_container);
    _scrollView = new ScrollViewer();

    _scrollView->SetContent(_panel);
}

bool ItemsControl::HasItems() const
{
    return (GetItems()->GetCount() > 0);
}

bool ItemsControl::IsGrouping() const
{
    return false;
}

ItemContainerPtr ItemsControl::GetItems() const
{
    return _container;
}

void ItemsControl::CheckAddingItem(suic::ObjectPtr& itemObj)
{
    ;
}

int ItemsControl::GetItemsCount() const
{
    return GetItems()->GetCount();
}

int ItemsControl::Add(suic::ObjectPtr value)
{
    CheckAddingItem(value);

    return GetItems()->AddItem(value);
}

int ItemsControl::Insert(int index, suic::ObjectPtr value)
{
    CheckAddingItem(value);

    return GetItems()->InsertItem(index, value);
}

int ItemsControl::AddText(const suic::String& text)
{
    return 0;
}

void ItemsControl::RemoveAt(int iIndex)
{
    if (iIndex < GetItems()->GetCount() && iIndex >= 0)
    {        
        GetItems()->RemoveAt(iIndex);
    }
}

void ItemsControl::Remove(suic::ObjectPtr ePtr)
{
    GetItems()->Remove(ePtr);
}

void ItemsControl::RemoveAll()
{
    GetItems()->Clear();
}

suic::ObjectPtr ItemsControl::GetItem(int iIndex) const
{
    return GetItems()->GetItem(iIndex);
}

suic::String ItemsControl::GetItemText(int iIndex) const
{
    return GetItems()->GetItemText(iIndex);
}

/////////////////////////////////////////////////////////////////
// ItemsControl
//
suic::Size ItemsControl::MeasureOverride(const suic::Size& availableSize)
{
    _scrollView->Measure(availableSize);

    return _scrollView->GetDesiredSize();
}

suic::Size ItemsControl::ArrangeOverride(const suic::Size& availableSize)
{
    suic::Rect finalRect(0, 0, availableSize.cx, availableSize.cy);

    finalRect.Deflate(GetBorderThickness());

    _scrollView->Arrange(finalRect);

    return availableSize;
}

void ItemsControl::OnUnloaded(suic::LoadedEventArg& e)
{
    __super::OnUnloaded(e);

    //_scrollView->OnUnloaded(e);
}

void ItemsControl::OnInitialized()
{
    __super::OnInitialized();

    suic::VisualHelper::SetLogicalParent(this, _scrollView.get());
    // 加入可视树
    AddVisualChild(_scrollView.get());

    _scrollView->BeginInit();
    _scrollView->EndInit();

    _scrollView->SetHorizontalAlignment(suic::STRETCH);
    _scrollView->SetVerticalAlignment(suic::STRETCH);

    _scrollView->SetMargin(GetMargin());
}

void ItemsControl::AddLogicalChild(suic::Element* child)
{
    Add(child);
}

void ItemsControl::RemoveLogicalChild(suic::Element* child)
{
    GetItems()->Remove(child);
}

suic::Element* ItemsControl::GetLogicalChild(int index)
{
    return dynamic_cast<suic::Element*>(GetItems()->GetItem(index).get());
}

suic::Int32 ItemsControl::GetLogicalChildrenCount()
{
    return GetItems()->GetCount();
}

void ItemsControl::OnNotifyContainerChanged(suic::ObjectPtr sender, NotifyContainerChangedArg& e)
{
    OnItemsChanged(e);
}

void ItemsControl::OnItemsChanged(NotifyContainerChangedArg& e)
{
    WriteFlag(CoreFlags::IsMeasureDirty, true);

    if (e.NewItems()->GetCount() > 0)
    {
        suic::Size availableSize;

        if (e.GetAction() == NotifyContainerChangedAction::Add)
        {
        }
    }

    if (e.OldItems()->GetCount() > 0)
    {
        if (e.GetAction() == NotifyContainerChangedAction::Remove)
        {
        }
    }
}

void ItemsControl::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

void ItemsControl::OnTextInput(suic::KeyEventArg& e)
{
    _scrollView->OnKeyDown(e);
}

void ItemsControl::OnKeyDown(suic::KeyEventArg& e)
{
    _scrollView->OnKeyDown(e);

    if (!e.Handled())
    {
        ;
    }
}

void ItemsControl::OnMouseEnter(suic::MouseEventArg& e)
{
    e.Handled(true);
    __super::OnMouseEnter(e);
}

void ItemsControl::OnMouseMove(suic::MouseEventArg& e)
{
    e.Handled(true);
    __super::OnMouseMove(e);
}

void ItemsControl::OnMouseLeave(suic::MouseEventArg& e)
{
    e.Handled(true);
    __super::OnMouseLeave(e);
}

void ItemsControl::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    e.Handled(true);
    __super::OnMouseLeftButtonDown(e);
}

void ItemsControl::OnPreviewMouseLeftButtonDown(suic::MouseEventArg& e)
{
    //e.Handled(true);
}

void ItemsControl::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    e.Handled(true);
    __super::OnMouseLeftButtonDbclk(e);
}

void ItemsControl::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    e.Handled(true);
    __super::OnMouseLeftButtonUp(e);
}

void ItemsControl::OnMouseWheel(suic::MouseWheelEventArg& e)
{
    e.Handled(true);
}

};
