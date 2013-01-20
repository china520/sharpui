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
#include <suic/graphics/uiImageBrush.h>
#include <suic/render/uirender.h>

namespace ui
{

//////////////////////////////////////////////////////////////
// TreeView
//
ImplementTypeofInfo(TreeView, ItemsControl)

TreeView::TreeView()
{
    SetClassName(_T("TreeView"));
    SetPadding(suic::Rect(2,2,2,2));
}

TreeView::~TreeView()
{
}

void TreeView::CheckAddingItem(suic::ObjectPtr& itemObj)
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

bool TreeView::RemoveItem(TreeViewItem* pItem)
{
    bool bRet = false;
    int count = GetItems()->GetCount();

    for (int i = 0; i < count; ++i)
    {
        TreeViewItemPtr treePtr(GetItems()->GetItem(i));

        if (treePtr && treePtr->RemoveItem(pItem))
        {
            bRet = true;
            break;
        }
    }

    return bRet;
}

TreeViewItemPtr TreeView::HitTreeItem(suic::Point pt)
{
    TreeViewItemPtr ret;
    int count = GetItems()->GetCount();

    for (int i = 0; i < count; ++i)
    {
        TreeViewItemPtr treePtr(GetItems()->GetItem(i));

        if (treePtr && (ret=treePtr->HitTreeItem(pt)))
        {
            break;
        }
    }

    return ret;
}

TreeViewItemPtr TreeView::HitTreeItemByUserData(suic::ObjectPtr obj)
{
    TreeViewItemPtr ret;
    int count = GetItems()->GetCount();

    for (int i = 0; i < count; ++i)
    {
        TreeViewItemPtr treePtr(GetItems()->GetItem(i));

        if (treePtr && (ret=treePtr->HitTreeItemByUserData(obj)))
        {
            break;
        }
    }

    return ret;
}

void TreeView::ExpandSubtrees()
{
    int count = GetItems()->GetCount();

    for (int i = 0; i < count; ++i)
    {
        TreeViewItemPtr treePtr(GetItems()->GetItem(i));

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

        pItem->SetSelected(true);
        pItem->GetHeaderHost()->InvalidateVisual();

        if (ItemSelected)
        {
            ItemSelected(_focusedItem.get());
        }
    }
}

void TreeView::OnUnselectTreeItem(TreeViewItem* pItem)
{
    pItem->SetSelected(false);
    pItem->GetHeaderHost()->InvalidateVisual();

    if (_focusedItem.get() == pItem)
    {
        _focusedItem = NULL;
    }

    if (ItemUnselected)
    {
        ItemUnselected(pItem);
    }
}

void TreeView::OnItemsChanged(suic::NotifyCollectionChangedArg& e)
{
    __super::OnItemsChanged(e);

    if (e.GetAction() == suic::NotifyCollectionChangedAction::Add)
    {
        for (int i = 0; i < e.NewItems()->GetCount(); ++i)
        {
            TreeViewItemPtr itemPtr(e.NewItems()->GetAt(i));

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
    _scrollHost->OnMouseWheel(e);
}

void TreeView::OnMouseRightButtonDown(suic::MouseEventArg& e)
{
    e.SetHandled(true);
}

void TreeView::OnTextInput(suic::KeyboardEventArg& e)
{
    __super::OnTextInput(e);
}

void TreeView::OnKeyDown(suic::KeyboardEventArg& e)
{
    __super::OnKeyDown(e);
}

void TreeView::OnGotFocus(suic::FocusEventArg& e)
{
    __super::OnGotFocus(e);

    e.SetHandled(true);
}


void TreeView::OnLostFocus(suic::FocusEventArg& e)
{
    __super::OnLostFocus(e);
}

}
