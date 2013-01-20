// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// MenuItem.cpp

#include <sui/menuitem.h>
#include <sui/Menu.h>
#include <suic/framework/hwndadapter.h>
#include <suic/render/uirender.h>

#include "menuitemhelper.h"

namespace ui
{

ImplementTypeofInfo(MenuItem, suic::ContentControl)


static bool StaticInit()
{
    /*suic::EventHelper::RegisterClassHandler(MenuItem::ThisType(), suic::Element::MouseEnterEvent, 
        new suic::MouseEventHandler(&MenuItem::OnMouseEnterThunk), false);*/

    return true;
}

static bool Init_RoutedEvent = StaticInit();

MenuItem::MenuItem()
{
    SetClassName(_T("MenuItem"));
    SetMinHeight(MENUITEM_MINHEIGHT);
    SetHorizontalContentAlignment(HoriAlignment::Left);
    SetFocusable(false);
    SetOrientation(CoreFlags::Vertical);
}

MenuItem::~MenuItem()
{
}

bool MenuItem::IsSubmenuOpen() const
{
    if (!IsSubmenu())
    {
        return false;
    }

    return !_submenuPopup->IsClosed();
}

bool MenuItem::IsSubmenu() const
{
    if (!_submenuPopup)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void MenuItem::SetIcon(suic::ImagePtr icon)
{
    _icon = icon;
}

suic::ImagePtr MenuItem::GetIcon() const
{
    return _icon;
}

////////////////////////////////////////////////////////////////////////////////////////////
// 菜单项事件
//
void MenuItem::OnClick(suic::ObjectPtr menu, bool bIsMain)
{
}

void MenuItem::OnPopupClosed(suic::ObjectPtr source, suic::EventArg& e)
{

}

void MenuItem::OnSubmenuOpened(suic::RoutedEventArg& e)
{

}

void MenuItem::OnChecked(suic::RoutedEventArg& e)
{

}

void MenuItem::OnUnchecked(suic::RoutedEventArg& e)
{

}

////////////////////////////////////////////////////////////////////////////////////////////
// MenuItem
//
suic::ElementPtr MenuItem::FindName(const suic::String& strName)
{
    if (GetName().Equals(strName))
    {
        return this;
    }
    else if (!_submenuPopup)
    {
        return suic::ElementPtr();
    }
    else
    {
        return _submenuPopup->FindName(strName);
    }
}

suic::ObjectPtr MenuItem::GetSubMenu()
{
    if (!_submenuPopup)
    {
        return suic::ObjectPtr();
    }
    else
    {
        return _submenuPopup->GetPopupRoot();
    }
}

int MenuItem::AddChild(suic::ObjectPtr child)
{
    MenuItem* pItem = dynamic_cast<MenuItem*>(child.get());

    if (pItem)
    {
        if (!_submenuPopup)
        {
            MenuPtr subMenu(new Menu());

            subMenu->SetStyle(FindResource(_T("Menu")));
            subMenu->SetOrientation(GetOrientation());

            _submenuPopup = new suic::UIPopup();
            _submenuPopup->SetPopupRoot(subMenu.get());
        }

        return _submenuPopup->GetPopupRoot()->AddChild(child);
    }
    else
    {
        return 0;
    }
}

suic::Size MenuItem::MeasureOverride(const suic::Size& size)
{
    suic::Size availableSize(size);

    availableSize = __super::MeasureOverride(availableSize);
    availableSize.cx += MENUITEM_ICONSIZE;

    return availableSize;
}

void MenuItem::OnInitialized()
{
    __super::OnInitialized();

    SetStyle(FindResource(GetClassName()));

    suic::ObjectPtr headerPtr = GetStyle()->GetValue(_T("Header"));

    if (headerPtr)
    {
        SetText(headerPtr->ToString());
    }
}

void MenuItem::OnStyleUpdated()
{
    if (_submenuPopup)
    {
        _submenuPopup->UpdateStyle();
    }
}

bool MenuItem::IsSelected() const
{
    if (IsSubmenuOpen())
    {
        return true;
    }
    else
    {
        return __super::IsSelected();
    }
}

void MenuItem::CloseSubmenu()
{
    if (_submenuPopup)
    {
        _submenuPopup->Close();

        if (IsSelected())
        {
            SetSelected(false);
            return;
        }
        UpdateSetters(_T(""));
    }
}

void MenuItem::OnRender(suic::DrawingContext * drawing)
{
    suic::Control::OnRender(drawing);
}

//void MenuItem::OnRender(suic::DrawingContext * drawing)
//{
//    suic::Rect rect(0, 0, RenderSize().cx, RenderSize().cy);
//    suic::StylePtr sty(GetStyle());
//    suic::SetterCollectionPtr setc;
//    suic::TriggerPtr trg;
//
//    if (IsEnabled())
//    {
//        if (IsSelected() || IsMouseOver() || IsSubmenuOpen())
//        {
//            trg = sty->GetTrigger(_T("IsFocused"));
//        }
//    }
//    else
//    {
//        trg = sty->GetTrigger(_T("IsDisabled"));
//    }
//
//    if (trg)
//    {
//        setc = trg->Setters();
//    }
//
//    if (!setc)
//    {
//        setc = GetSetters();
//    }
//
//    if (setc)
//    {
//        suic::BrushPtr bkgnd(setc->GetValue(_T("Background")));
//
//        if (bkgnd)
//        {
//            bkgnd->Draw(drawing, &rect);
//        }
//
//        suic::ObjectPtr forebk(setc->GetValue(_T("Foreground")));
//        suic::FontPtr font(setc->GetValue(_T("Font")));
//        suic::FormattedText fmtTxt;
//
//        if (!forebk)
//        {
//            forebk = GetForeground();
//        }
//
//        if (font)
//        {
//            fmtTxt.font = font->GetFont();
//        }
//
//        if (forebk)
//        {
//            fmtTxt.color = forebk->ToColor();
//        }
//
//        fmtTxt.horzAlign = GetHorizontalContentAlignment();
//        fmtTxt.vertAlign = GetVerticalContentAlignment();
//
//        suic::Render::RenderText(drawing, fmtTxt, GetText(), &rect, true);
//    }
//}

void MenuItem::OnTextInput(suic::KeyboardEventArg& e)
{
}

void MenuItem::OnKeyDown(suic::KeyboardEventArg& e)
{
}

void MenuItem::OnGotFocus(suic::FocusEventArg& e)
{
}

void MenuItem::OnLostFocus(suic::FocusEventArg& e)
{
}

void MenuItem::OnSetCursor(suic::CursorEventArg& e)
{
}

void MenuItem::OnMouseEnter(suic::MouseEventArg& e)
{
    if (!IsEnabled())
    {
        return;
    }

    e.SetHandled(true);

    bool bOpenSubmenu = false;
    Menu* pMenu = dynamic_cast<Menu*>(GetParent());

    for (int i = 0; i < pMenu->GetVisualChildrenCount(); ++i)
    {
        MenuItem* pMenuItem = dynamic_cast<MenuItem*>(pMenu->GetVisualChild(i));

        if (pMenuItem->IsSubmenuOpen())
        {
            if (pMenuItem == this)
            {
                return;
            }

            pMenuItem->CloseSubmenu();
            
            bOpenSubmenu = true;

            break;
        }
    }

    Selector::SelectItem(this, true);

    //
    // 如果是子菜单，则弹出
    //
    if (!IsSubmenu())
    {
        ;
    }
    else if (GetTrackMenu())
    {
        MenuPtr menu = MenuPtr::cast(_submenuPopup->GetPopupRoot());
        suic::Size availableSize;

        menu->Measure(availableSize);

        int cx = menu->GetDesiredSize().cx;
        int cy = menu->GetDesiredSize().cy;

        _submenuPopup->SetWidth(cx);
        _submenuPopup->SetHeight(cy);

        if (!GetTrackMenu()->IsClosed())
        {
            suic::Point pt = suic::SystemHelper::CalcScreenElementPoint(this, CoreFlags::eRightTop);

            pt.x -= menu->GetBorderThickness().right;
            _submenuPopup->WriteFlag(CoreFlags::IsLayeredWindow, true);
            AddMenuItemIntoPopup(this, _submenuPopup);
            _submenuPopup->SetPopupPos(true, pt.x, pt.y, true, cx, cy);
        }
        else
        {
            suic::Point pt = suic::SystemHelper::CalcScreenElementPoint(this, CoreFlags::eLeftBottom);
            SetPopupMenu(this, pt.x, pt.y, _submenuPopup);
        }
    }

    __super::OnMouseEnter(e);
}

void MenuItem::OnMouseLeave(suic::MouseEventArg& e)
{
    MenuItemPtr overItem = MenuItemPtr::cast(e.GetOriginalSource());

    //
    // 如果是子菜单弹出并且在同一个菜单元素内，则关闭
    //
    if (IsSubmenuOpen() && overItem
        && overItem->GetParent() == GetParent())
    {
        CloseSubmenu();
    }

    Selector::SelectItem(this, false);
    InvalidateVisual();

    e.SetHandled(true);
    __super::OnMouseLeave(e);
}

void MenuItem::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    suic::Element::OnMouseLeftButtonDown(e);

    if (!e.IsHandled())
    {
        Selector::SelectItem(this, true);

        InvalidateVisual();

        MenuPtr pMenu(GetParent());

        if (pMenu)
        {
            pMenu->OnItemLeftButtonDown(this, e);
        }
    }
}

void MenuItem::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDown(e);
}

void MenuItem::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonUp(e);

    if (GetTrackMenu())
    {
        GetTrackMenu()->ReleaseCaptureMouse();
    }
}

};
