// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// menuitemhelper.cpp

#include "menuitemhelper.h"
#include <sui/Menu.h>
#include <suicore/hwndadapter.h>
#include <suicore/drawing/uirender.h>

namespace ui
{

//---------------------------------------------------------------
static suic::PopupPtr g_trackmenu;
static suic::PopupPtr g_menuPop;
static MenuPtr g_mainmenu;
static MenuItemPtr g_trackmenuitem;
static HwndSourceHookMenuPopupPtr g_trackmenupopup;

static int g_x = 0;
static int g_y = 0;

HwndSourceHookMenuPopup::HwndSourceHookMenuPopup(suic::PopupPtr popup, MenuPtr menu)
    : _popup(popup)
    , _mouseCapture(false)
    , _mainMenu(menu)
{
    _popups = suic::CreateEnumerator();
    _popups->Add(_popup.get());
}

void HwndSourceHookMenuPopup::HandleMouseDown(HWND hwnd)
{
    MenuPtr focusMenu = HitTestPopup();

    if (!focusMenu)
    {
        _popup->ReleaseCaptureMouse();
        _popup->Close();
        suic::SystemHelper::RemoveHwndMessageSystemHook(this);

        if (g_trackmenuitem)
        {
            suic::ElementPtr cur = suic::SystemHelper::GetMouseOverElement(g_trackmenuitem);

            //
            // 对焦点菜单项处理
            //
            if (cur != g_trackmenuitem)
            {
                Selector::SelectItem(g_trackmenuitem, false);
            }

            g_trackmenuitem->InvalidateVisual();
            g_trackmenuitem = NULL;
        }
    }
}

void HwndSourceHookMenuPopup::HandleMouseUp()
{
    _popup->ReleaseCaptureMouse();

    MenuPtr focusMenu = HitTestPopup();

    if (focusMenu)
    {
        bool bIsMain = (focusMenu == _mainMenu);

        suic::ElementPtr hot = suic::SystemHelper::GetMouseOverElement(focusMenu.get());
        MenuItemPtr menuPtr = MenuItemPtr::cast(hot);

        if (menuPtr)
        {
            if (menuPtr->IsEnabled())
            {
                if (!bIsMain && !menuPtr->IsSubmenu())
                {
                    InternalCloseTrackMenuPopup();
                }

                menuPtr->OnClick(focusMenu.get(), bIsMain);

                if (menuPtr->MenuItemClick)
                {
                    menuPtr->MenuItemClick(focusMenu.get(), menuPtr);
                }
                else if (focusMenu->MenuItemClick)
                {
                    focusMenu->MenuItemClick(focusMenu.get(), menuPtr);
                }
            }
        }
    }
    else
    {
        InternalCloseTrackMenuPopup();
    }
}

bool HwndSourceHookMenuPopup::HandleMouseMove(suic::MessageParameter& mp)
{
    bool handled = false;
    MenuPtr hotMenu = HitTestPopup();

    if (IsMouseCapture())
    {
        handled = true;

        if (!hotMenu)
        {
            if (_focusMenu)
            {
                suic::MouseEventArg ef(NULL, mp.point);

                _focusMenu->OnMouseLeave(ef);
            }

            _focusMenu = hotMenu;
        }
        else
        {
            suic::MouseEventArg e(hotMenu.get(), suic::SystemHelper::GetCursorPoint(hotMenu.get()));

            if (_focusMenu && _focusMenu != hotMenu)
            {
                suic::MouseEventArg ef(hotMenu.get(), mp.point);

                _focusMenu->OnMouseLeave(ef);
            }

            hotMenu->OnMouseMove(e);
            _focusMenu = hotMenu;
        }
    }
    else if (!hotMenu)
    {
        handled = true;
        suic::HwndHelper::HandleDefWndMessage(mp);
    }

    return handled;
}

bool HwndSourceHookMenuPopup::IsMouseOverOwer()
{
    suic::ElementPtr ower(_mainMenu.get());

    if (ower)
    {
        suic::Rect rect(0, 0, ower->RenderSize().cx, ower->RenderSize().cy);
        suic::Point point = suic::SystemHelper::GetCursorPoint(ower.get());

        point = ower->PointFromScreen(point);

        if (rect.PointIn(point))
        {
            return true;
        }
    }

    return false;
}

bool HwndSourceHookMenuPopup::OnFilterMessage(suic::ObjectPtr sender, suic::MessageParameter& mp)
{
    suic::ElementPtr rootElement  = suic::ElementPtr::cast(sender);
    bool handled = false;
    HWND hwnd = HandleToHwnd(mp.hwnd);

    switch (mp.message)
    {
    case WM_NCLBUTTONDOWN:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONDBLCLK:
        HandleMouseDown(hwnd);
        break;
    case WM_NCRBUTTONDOWN:
    case WM_RBUTTONDOWN:
        HandleMouseDown(hwnd);
        break;
    case WM_LBUTTONUP:
        HandleMouseUp();
        break;
    case WM_MOUSEMOVE:
    case WM_NCMOUSEMOVE:
        handled = HandleMouseMove(mp);
        break;

    case WM_MOUSEACTIVATE:
        mp.result = MA_NOACTIVATE;
        handled = true;
        break;

    case WM_CLOSE:
        ClosePopup(rootElement.get());
        break;
    }

    return handled;
}

void HwndSourceHookMenuPopup::ClosePopup(suic::Element* pElem)
{
    int start = -1;

    for (int i = _popups->GetCount() - 1; i >= 0; --i)
    {
        suic::PopupPtr pop = suic::PopupPtr::cast(_popups->GetAt(i));

        if (pop.get() == pElem)
        {
            start = i;
            break;
        }
    }

    _popups->Remove(pElem);

    if (start >= 0 && start < _popups->GetCount())
    {
        suic::PopupPtr pop = suic::PopupPtr::cast(_popups->GetAt(start));

        pop->Close();
    }
}

MenuPtr HwndSourceHookMenuPopup::HitTestPopup()
{
    suic::PopupPtr popover;

    for (int i = 0; i < _popups->GetCount(); ++i)
    {
        suic::PopupPtr pop = suic::PopupPtr::cast(_popups->GetAt(i));
        suic::Rect rcpop(0, 0, pop->RenderSize().cx, pop->RenderSize().cy);
        suic::Point pt = suic::SystemHelper::GetCursorPoint(pop.get());

        if (rcpop.PointIn(pt))
        {
            popover = pop;
            break;
        }
    }

    if (!popover)
    {
        if (IsMouseOverOwer())
        {
            return _mainMenu;
        }
        else
        {
            return MenuPtr();
        }
    }
    else
    {
        return MenuPtr::cast(popover->GetPopupRoot());
    }
}

bool HwndSourceHookMenuPopup::IsMouseCapture() const
{        
    for (int i = 0; i < _popups->GetCount(); ++i)
    {
        suic::PopupPtr pop = suic::PopupPtr::cast(_popups->GetAt(i));
        suic::VisualHostPtr pHost = suic::HwndHelper::GetVisualHost(pop);

        if (!pHost)
        {
            return false;
        }

        HWND hwnd = HandleToHwnd(pHost->GetHandle());

        if (GetCapture() == hwnd)
        {
            return true;
        }
    }
    return _mouseCapture;
}

void HwndSourceHookMenuPopup::SetMouseCapture(bool value)
{
}

void HwndSourceHookMenuPopup::AddMenuPopup(MenuItemPtr item, suic::PopupPtr popup)
{
    _popups->Add(popup.get());
}

void HwndSourceHookMenuPopup::SetMainMenu(MenuPtr mainMenu)
{
    _mainMenu = mainMenu;
}

//===================================================
//

suic::PopupPtr GetTrackMenu()
{
    return g_trackmenu;
}

bool IsValidTrackMenu()
{
    if (!g_trackmenu)
    {
        return false;
    }
    
    if (g_trackmenu->IsClosed())
    {
        return false;
    }

    return true;
}

void UpdateMainMenu(MenuItemPtr itemPtr, MenuPtr mainMenu)
{
    if (!g_mainmenu || (g_trackmenuitem 
        && g_trackmenuitem->GetParent() == itemPtr->GetParent()))
    {
        g_trackmenuitem = itemPtr;
        g_mainmenu = mainMenu;
    }
}

void SetTrackMenu(suic::PopupPtr menu)
{
    g_trackmenu = menu;
}

void SetPopupMenu(MenuItemPtr itemPtr, int x, int y, suic::PopupPtr menu)
{
    if (g_menuPop)
    {
        g_menuPop->Close();
    }

    g_x = x;
    g_y = y;
    g_menuPop = menu;
    g_trackmenuitem = itemPtr;
}

void AddMenuItemIntoPopup(MenuItem* pItem, suic::PopupPtr& popup)
{
    g_trackmenupopup->AddMenuPopup(pItem, popup);
}

void InternalCloseTrackMenuPopup()
{
    if (GetTrackMenu())
    {
        GetTrackMenu()->Close();
    }
}

int InternalTrackPopupMenu(MenuPtr mainMenu)
{
    MenuPtr trMenu = mainMenu;
    g_mainmenu = mainMenu;

    while (g_menuPop)
    {
        suic::PopupPtr menuPop = g_menuPop;
        suic::Size availableSize;

        MenuPtr menu(MenuPtr::cast(menuPop->GetPopupRoot()));
        g_menuPop = suic::PopupPtr();

        if (!menu->GetStyle())
        {
            menu->SetStyle(menu->FindResource(_T("Menu")));
        }

        menu->Measure(availableSize);

        int cx = menu->GetDesiredSize().cx;
        int cy = menu->GetDesiredSize().cy;

        menuPop->SetWidth(cx);
        menuPop->SetHeight(cy);

        SetTrackMenu(menuPop);

        if (g_mainmenu != trMenu)
        {
            trMenu = g_mainmenu;
        }
        g_trackmenupopup = new HwndSourceHookMenuPopup(menuPop, trMenu);

        // 去掉焦点
        menuPop->SetFocusable(false);
        menuPop->WriteFlag(CoreFlags::IsLayeredWindow, true);
        menuPop->TrackingPopup(g_x, g_y, true, cx, cy, g_trackmenupopup.get());

        suic::SystemHelper::RemoveHwndMessageSystemHook(g_trackmenupopup.get());

        g_trackmenupopup = NULL;
        SetTrackMenu(NULL);
    }

    g_mainmenu = MenuPtr();
    g_trackmenuitem = MenuItemPtr();

    return 0;
}

int TrackPopupMenuItem(MenuItemPtr itemPtr, int x, int y, MenuPtr mainMenu, suic::PopupPtr menuPop)
{
    MenuPtr menu(MenuPtr::cast(menuPop->GetPopupRoot()));

    if (!menu)
    {
        return -1;
    }
    else
    {
        SetPopupMenu(itemPtr, x, y, menuPop);

        return InternalTrackPopupMenu(mainMenu);
    }
}

}
