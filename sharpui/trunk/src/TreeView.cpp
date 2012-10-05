// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// TreeView.cpp

#include <sui/treeview.h>
#include <sui/TextBlock.h>
#include <suicore/drawing/uiImageBrush.h>
#include <suicore/drawing/uirender.h>

namespace ui
{

//////////////////////////////////////////////////////////////
// TreeView
//
TreeView::TreeView()
{
    SetClassName(_T("TreeView"));
    SetPadding(suic::Rect(2,2,2,2));
}

TreeView::~TreeView()
{
}

static void DrawVertTreeDot(suic::DrawingContext * drawing, int by, int ey, int x)
{
    for (int i = by; i <= ey; ++i)
    {
        drawing->SetPixel(x, i++, ARGB(255,180,180,180));
    }
}

static void DrawHorzTreeDot(suic::DrawingContext * drawing, int bx, int ex, int y)
{
    for (int i = bx; i <= ex; ++i)
    {
        drawing->SetPixel(i++, y, ARGB(255,180,180,180));
    }
}

void TreeView::ExpandSubtrees()
{
    int count = GetItems()->GetCount();

    for (int i = 0; i < count; ++i)
    {
        TreeViewItemPtr treePtr = TreeViewItemPtr::cast(GetItems()->GetItem(i));

        if (treePtr)
        {
            treePtr->Expand();
        }
    }
}

void TreeView::OnSelectTreeItem(TreeViewItem* pItem)
{
    if (_focusedItem.get() != pItem)
    {
        if (_focusedItem)
        {
            _focusedItem->Unselect();
        }

        _focusedItem = pItem;

        pItem->GetHeader()->WriteFlag(CoreFlags::IsSelected, true);
        pItem->WriteFlag(CoreFlags::IsSelected, true);

        pItem->GetHeader()->InvalidateVisual();

        if (ItemSelected)
        {
            ItemSelected(_focusedItem.get());
        }
    }
}

void TreeView::OnUnselectTreeItem(TreeViewItem* pItem)
{
    pItem->WriteFlag(CoreFlags::IsSelected, false);
    pItem->GetHeader()->WriteFlag(CoreFlags::IsSelected, false);

    pItem->GetHeader()->InvalidateVisual();

    if (_focusedItem.get() == pItem)
    {
        _focusedItem = NULL;
    }

    if (ItemUnselected)
    {
        ItemUnselected(pItem);
    }
}

void TreeView::OnItemsChanged(NotifyContainerChangedArg& e)
{
    __super::OnItemsChanged(e);

    if (e.GetAction() == NotifyContainerChangedAction::Add)
    {
        for (int i = 0; i < e.GetNewItems()->GetCount(); ++i)
        {
            TreeViewItemPtr itemPtr(e.GetNewItems()->GetAt(i));

            if (itemPtr)
            {
                itemPtr->ItemSelected += SelectTreeItemHandler(this, &TreeView::OnSelectTreeItem);
                itemPtr->ItemUnselected += SelectTreeItemHandler(this, &TreeView::OnUnselectTreeItem);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//

void TreeView::OnInitialized()
{
    __super::OnInitialized();
}

void TreeView::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);

    const int ITEMSPACE = 2;
}

void TreeView::OnMouseWheel(suic::MouseWheelEventArg& e)
{
    _scrollView->OnMouseWheel(e);

    /*int zDelta = e.Delta();
    int nPos = _vScroll->GetVisualPos();

    if (zDelta < 0)
    {
        _vScroll->ScrollTo(nPos + 4, false);
    }
    else
    {
        _vScroll->ScrollTo(nPos - 4, false);
    }

    if (_vScroll->GetVisualPos() != nPos)
    {
        _vScroll->UpdateScrollBar();

        UpdateLayout();
    }

    e.Handled(true);*/
}

void TreeView::OnTextInput(suic::KeyEventArg& e)
{
    __super::OnTextInput(e);
}

void TreeView::OnKeyDown(suic::KeyEventArg& e)
{
    __super::OnKeyDown(e);
}

void TreeView::OnGotFocus(suic::FocusEventArg& e)
{
    __super::OnGotFocus(e);

    e.Handled(true);
}


void TreeView::OnLostFocus(suic::FocusEventArg& e)
{
    __super::OnLostFocus(e);
}

};
