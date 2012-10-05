// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// ListBox.cpp

#include <sui/listbox.h>
#include <suicore/uimousedriver.h>
#include <suicore/drawing/uirender.h>

namespace ui
{

ListBox::ListBox()
    : _timerid(0)
{
    SetClassName(suic::LISTBOX);
    SetOrientation(CoreFlags::Vertical);
}

ListBox::~ListBox()
{
}

int ListBox::AddText(const suic::String& text)
{
    ListBoxItem* item(new ListBoxItem());

    item->SetText(text);

    return GetItems()->AddItem(item);
}

void ListBox::OnInitialized()
{
    __super::OnInitialized();

    _panel->SetOrientation(GetOrientation());
}

void ListBox::OnUnloaded(suic::LoadedEventArg& e)
{
    __super::OnUnloaded(e);

    suic::SystemHelper::KillTimer(this, _timerid);
    _timerid = 0;
}

void ListBox::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

void ListBox::OnTimer(int iTimerId)
{
    if (_timerid == iTimerId)
    {
        suic::Point pt(suic::VisualHelper::GetCursorPoint(this));
        suic::Rect rect(suic::VisualHelper::GetRenderRect(this));

        if (pt.y > rect.bottom)
        {
            _scrollView->LineDown();
        }

        if (pt.y < rect.top)
        {
            _scrollView->LineUp();
        }

        if (pt.x > rect.right)
        {
            _scrollView->LineRight();
        }

        if (pt.x < rect.left)
        {
            _scrollView->LineLeft();
        }
    }
}

void ListBox::OnTextInput(suic::KeyEventArg& e)
{
    __super::OnTextInput(e);
}

void ListBox::OnKeyDown(suic::KeyEventArg& e)
{
    __super::OnKeyDown(e);
}

void ListBox::OnGotFocus(suic::FocusEventArg& e)
{
    __super::OnGotFocus(e);
    e.Handled(true);
}

void ListBox::OnLostFocus(suic::FocusEventArg& e)
{
    __super::OnLostFocus(e);
}

void ListBox::OnMouseMove(suic::MouseEventArg& e)
{
    __super::OnMouseMove(e);

    e.Handled(true);

    if (e.LeftButton() != suic::eMousePress)
    {
        return;
    }

    if (!IsMouseCaptured())
    {
        suic::SystemHelper::KillTimer(this, _timerid);
        _timerid = 0;
        SetCaptureMouse();
    }

    suic::Rect rect(suic::VisualHelper::GetRenderRect(this));

    suic::SystemHelper::Trace(_T("L:%d;T:%d;R:%d;B:%d; x:%d;y:%d\n")
        , rect.left, rect.top, rect.right, rect.bottom,
        e.MousePoint().x, e.MousePoint().y);

    if (rect.PointIn(e.MousePoint()) && 
        e.MousePoint().y < 0)
    {
        suic::SystemHelper::KillTimer(this, _timerid);
        _timerid = 0;
    }
    else
    {
        if (_timerid == 0)
        {
            _timerid = suic::SystemHelper::SetTimer(this, 50, -1);
        }
    }

    suic::Element* pOver = NULL;

    for (int i = 0; i < _panel->GetVisualChildrenCount(); ++i)
    {
        suic::ElementPtr pItem(_panel->GetVisualChild(i));

        if (pItem)
        {
            if (suic::VisualHelper::GetRenderRect(pItem).PointIn(e.MousePoint()))
            {
                pOver = pItem.get();

                break;
            }
        }
    }

    if (pOver != _focusItem)
    {
        if (_focusItem)
        {
            Selector::SelectItem(_focusItem, false);
        }

        if (pOver)
        {
            Selector::SelectItem(pOver, true);
            suic::MouseDriver::HandleMouseEnter(pOver, e.MousePoint());
        }

        _focusItem = pOver;
    }

    e.Handled(true);
}

void ListBox::OnMouseWheel(suic::MouseWheelEventArg& e)
{
    // 转发消息给视图类处理
    _scrollView->OnMouseWheel(e);
}

void ListBox::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDown(e);

    suic::SystemHelper::KillTimer(this, _timerid);
    _timerid = 0;

    SetCaptureMouse();
}

void ListBox::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonUp(e);

    ReleaseCaptureMouse();

    suic::SystemHelper::KillTimer(this, _timerid);
    _timerid = 0;
}

void ListBox::OnItemSelected(suic::ObjectPtr item, ItemSelectionEventArg& e)
{
    __super::OnItemSelected(item, e);

    if (e.GetSelectionType() == 1)
    {
        SetCaptureMouse();
    }
}

};
