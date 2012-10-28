// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// Menu.cpp

#include <sui/menu.h>
#include <suicore/uimousedriver.h>

#include "menuitemhelper.h"

namespace ui
{

Menu::Menu()
{
    SetClassName(_T("Menu"));
    SetOrientation(CoreFlags::Vertical);
    SetFocusable(false);
}

Menu::~Menu()
{
}

MenuItemPtr Menu::GetMenuItem(int index)
{
    return MenuItemPtr::cast(GetItem(index));
}

int Menu::TrackPopupMenu(int x, int y, MenuPtr menu)
{
    suic::PopupPtr menuPopup(new suic::UIPopup());
    menuPopup->SetPopupRoot(menu.get());

    return TrackPopupMenuItem(NULL, x, y, NULL, menuPopup);
}

void Menu::AddSubMenu(MenuItemPtr item, MenuPtr subMenu)
{
    if (!item->_submenuPopup)
    {
        item->_submenuPopup = new suic::UIPopup();
    }

    if (!subMenu->GetStyle())
    {
        subMenu->SetStyle(item->FindResource(_T("Menu")));
    }

    item->_submenuPopup->SetPopupRoot(subMenu.get());
}

int Menu::AddText(const suic::String& text)
{
    MenuItem* item(new MenuItem());

    item->SetText(text);

    return GetItems()->AddItem(item);
}

suic::Size Menu::MeasureOverride(const suic::Size& size)
{
    suic::Size availableSize;

    if (CoreFlags::Horizontal == GetOrientation())
    {
        for (int i = 0; i < GetItems()->GetCount(); ++i)
        {
            MenuItemPtr itemPtr(GetItems()->GetItem(i));

            itemPtr->Measure(size);

            availableSize.cx += itemPtr->GetDesiredSize().cx;

            if (itemPtr->GetDesiredSize().cy > availableSize.cy)
            {
                availableSize.cy = itemPtr->GetDesiredSize().cy;
            }
        }
    }
    else
    {
        for (int i = 0; i < GetItems()->GetCount(); ++i)
        {
            suic::ObjectPtr obj = GetItems()->GetItem(i);
            MenuItemPtr itemPtr = MenuItemPtr::cast(obj);

            itemPtr->Measure(size);

            availableSize.cy += itemPtr->GetDesiredSize().cy;

            if (itemPtr->GetDesiredSize().cx > availableSize.cx)
            {
                availableSize.cx = itemPtr->GetDesiredSize().cx;
            }
        }
    }

    availableSize.cx += GetBorderThickness().left + GetBorderThickness().right;
    availableSize.cy += GetBorderThickness().top + GetBorderThickness().bottom;

    availableSize.cx += GetPadding().left + GetPadding().right;
    availableSize.cy += GetPadding().top + GetPadding().bottom;

    return availableSize;
}

suic::Size Menu::ArrangeOverride(const suic::Size& size)
{
    ClearVisualChildren();

    suic::Size availableSize(size.cx, size.cy);
    suic::Rect finalRect(0, 0, availableSize.cx, availableSize.cy);

    finalRect.Deflate(GetBorderThickness());
    finalRect.Deflate(GetPadding());
    
    if (CoreFlags::Horizontal == GetOrientation())
    {
        for (int i = 0; i < GetItems()->GetCount(); ++i)
        {
            MenuItemPtr itemPtr(GetItems()->GetItem(i));

            finalRect.right = finalRect.left + itemPtr->GetDesiredSize().cx;

            AddVisualChild(itemPtr.get());
            itemPtr->Arrange(finalRect);

            finalRect.left = finalRect.right;
        }
    }
    else
    {
        for (int i = 0; i < GetItems()->GetCount(); ++i)
        {
            MenuItemPtr itemPtr(GetItems()->GetItem(i));

            finalRect.bottom = finalRect.top + itemPtr->GetDesiredSize().cy;

            AddVisualChild(itemPtr.get());
            itemPtr->Arrange(finalRect);

            finalRect.top = finalRect.bottom;
        }
    }

    return availableSize;
}

void Menu::OnItemLeftButtonDown(MenuItem* item, suic::MouseEventArg& e)
{
    e.Handled(true);
    e.SetSource(this);

    _focusedItem = item;

    if (GetTrackMenu() == item->_submenuPopup 
        && item->IsSubmenuOpen())
    {
        item->_submenuPopup->Close();
    }
    else
    {
        if (!GetTrackMenu())
        {
            if (item->IsSubmenu())
            {
                suic::Point pt = suic::SystemHelper::CalcScreenElementPoint(item, CoreFlags::eLeftBottom);

                TrackPopupMenuItem(item, pt.x, pt.y, this, item->_submenuPopup);
            }
        }
        else
        {
            GetTrackMenu()->SetCaptureMouse();
            UpdateMainMenu(item, this);
            item->OnMouseEnter(e);
        }    
    }
}

void Menu::OnInitialized()
{
    __super::OnInitialized();
}

void Menu::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

void Menu::OnTextInput(suic::KeyEventArg& e)
{
}

void Menu::OnKeyDown(suic::KeyEventArg& e)
{
}

void Menu::OnGotFocus(suic::FocusEventArg& e)
{
}

void Menu::OnLostFocus(suic::FocusEventArg& e)
{
}

void Menu::OnSetCursor(suic::CursorEventArg& e)
{
}

void Menu::OnMouseEnter(suic::MouseEventArg& e)
{
    __super::OnMouseEnter(e);

    OnMouseMove(e);
}

void Menu::OnMouseMove(suic::MouseEventArg& e)
{
    __super::OnMouseMove(e);

    if (e.LeftButton() != suic::eMousePress)
    {
        return;
    }

    MenuItem* pOver = NULL;

    for (int i = 0; i < GetVisualChildrenCount(); ++i)
    {
        MenuItem* pItem = dynamic_cast<MenuItem*>(GetVisualChild(i));

        if (pItem)
        {
            if (suic::VisualHelper::GetRenderRect(pItem).PointIn(e.MousePoint()))
            {
                pOver = pItem;

                break;
            }
        }
    }

    if (pOver != _focusedItem)
    {
        if (_focusedItem)
        {
            Selector::SelectItem(_focusedItem, false);
        }

        if (pOver)
        {
            Selector::SelectItem(pOver, true);
            suic::MouseDriver::HandleMouseEnter(pOver, e.MousePoint());
        }

        _focusedItem = pOver;
    }

    e.Handled(true);
}

void Menu::OnMouseLeave(suic::MouseEventArg& e)
{
    __super::OnMouseLeave(e);

    suic::FrameworkElementPtr frame(_focusedItem);

    if (frame)
    {
        suic::MouseEventArg ef(NULL, e.MousePoint());
        ef.SetSource(frame);
        frame->OnMouseLeave(ef);

        _focusedItem = NULL;
    }
}

void Menu::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDown(e);
}

void Menu::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDbclk(e);
}

void Menu::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonUp(e);

    //
    // 先释放鼠标控制权
    //
    if (GetTrackMenu())
    {
        GetTrackMenu()->ReleaseCaptureMouse();
    }

    return;
}

void Menu::OnSelectionChanged(SelectionChangedEventArg& e)
{
    __super::OnSelectionChanged(e);
}

};
