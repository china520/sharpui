// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// TreeView.cpp

#include <sui/treeviewitem.h>
#include <sui/treeview.h>
#include <sui/TextBlock.h>
#include <suic/graphics/uiImageBrush.h>
#include <suic/render/uirender.h>

#include <sui/stackpanel.h>
#include <sui/label.h>

namespace ui
{

typedef delegate<void()> TreeButtonClickEventHandler;

class TreeButton : public ui::Button
{
public:

    TreeButtonClickEventHandler Expanded;
    TreeButtonClickEventHandler Collapsed;

    TreeButton()
        : _bCollapsed(false)
    {
        SetClassName(_T("TreeButton"));
    }

    void SetButton(suic::ImageBrushPtr exp, suic::ImageBrushPtr cop)
    {
        SetMinWidth(16);
        SetMinHeight(16);

        _expanded = exp;
        _collapsed = cop;
    }

    void OnClick(suic::RoutedEventArg& e)
    {
        _bCollapsed = !_bCollapsed;

        if (_bCollapsed)
        {
            if (Collapsed)
            {
                Collapsed();
            }
        }
        else
        {
            if (Expanded)
            {
                Expanded();
            }
        }
    }

    suic::Rect GetDrawRect(suic::Rect rc)
    {
        suic::Rect rect;

        rect.left = (RenderSize().cx - rc.Width()) / 2;
        rect.top = (RenderSize().cy - rc.Height()) / 2;
        rect.right = rect.left + RenderSize().cx;
        rect.bottom = rect.top + RenderSize().cy;

        return rect;
    }

    void OnRender(suic::DrawingContext * drawing)
    {
        if (_expanded)
        {
            if (_bCollapsed)
            {
                suic::Rect rc = _expanded->GetContentBrounds();

                _expanded->Draw(drawing, &GetDrawRect(rc));
            }
            else
            {
                suic::Rect rc = _collapsed->GetContentBrounds();

                _collapsed->Draw(drawing, &GetDrawRect(rc));
            }
        }
    }

    suic::Size MeasureOverride(const suic::Size& size)
    {
        suic::Size retSize;

        if (_expanded)
        {
            suic::Rect rect = _expanded->GetContentBrounds();
            retSize.cx = rect.Width();
            retSize.cy = rect.Height();
        }

        MeasureCheck(retSize);

        return retSize;
    }

    void SetCollapsed(bool bCollapsed)
    {
        _bCollapsed = bCollapsed;
    }

    void OnGotFocus(suic::FocusEventArg& e)
    {
        ;
    }

protected:

    suic::ImageBrushPtr _expanded;
    suic::ImageBrushPtr _collapsed;

    bool _bCollapsed;
};

//======================================================
// TreeViewItem

static TreeView* GetParentTreeView(suic::Element* pElem)
{
    TreeView* pTree = NULL;
    suic::Element* pParent = pElem->GetParent();

    while (pParent)
    {
        pTree = dynamic_cast<TreeView*>(pParent);

        if (pTree)
        {
            break;
        }

        pParent = pParent->GetParent();
    }

    return pTree;
}

ImplementTypeofInfo(TreeViewItem, HeaderedItemsControl)

TreeViewItem::TreeViewItem(const suic::String& text)
{
    this->TreeViewItem::TreeViewItem();
    SetText(text);
}

TreeViewItem::TreeViewItem()
    : _showDotLine(false)
    , _internalIndent(0)
{
    SetClassName(_T("TreeViewItem"));

    WriteFlag(CoreFlags::IsSupportMouseOver, true);

    SetHorizontalContentAlignment(HoriContentAlignment::Left);
    SetVerticalContentAlignment(VertContentAlignment::Center);

    SetPadding(suic::Rect(2,0,0,0));

    _check.SetAutoDelete(false);
    _icon.SetAutoDelete(false);

    _expand = new TreeButton();

    _check.SetVerticalAlignment(VertAlignment::Center);
    _icon.SetVerticalAlignment(VertAlignment::Center);    
    _expand->SetVerticalAlignment(VertAlignment::Center);

    _headerHost->AddChild(_expand.get());
    _headerHost->AddChild(&_check);
    _headerHost->AddChild(&_icon);

    SetHeader(new ui::Label());
    _header->SetMinHeight(16);
}

suic::PanelPtr TreeViewItem::GetHeaderHost()
{
    return _headerHost;
}

void TreeViewItem::Select()
{
    TreeView* pTree = GetParentTreeView(this);

    if (pTree)
    {
        suic::RoutedEventArg e(this);
        OnSelected(e);
    }
}

void TreeViewItem::Unselect()
{
    TreeView* pTree = GetParentTreeView(this);

    if (pTree)
    {
        suic::RoutedEventArg e(this);
        OnUnselected(e);
    }
}

bool TreeViewItem::RemoveItem(TreeViewItem* pItem)
{
    bool bRet = false;
    int count = GetItems()->GetCount();

    for (int i = 0; i < count; ++i)
    {
        TreeViewItemPtr item(GetItems()->GetItem(i));

        if (item.get() == pItem)
        {
            RemoveChild(pItem);
            bRet = true;

            break;
        }
        else if (bRet=item->RemoveItem(pItem))
        {
            break;
        }
    }

    return bRet;
}

TreeViewItemPtr TreeViewItem::HitTreeItem(suic::Point pt)
{
    if (GetHeader())
    {
        suic::Rect rect = suic::VisualHelper::GetRenderRect(GetHeaderHost().get());

        if (rect.PointIn(pt))
        {
            return this;
        }
    }

    TreeViewItemPtr ret;
    int count = GetItems()->GetCount();

    for (int i = 0; i < count; ++i)
    {
        TreeViewItemPtr item(GetItems()->GetItem(i));

        if (item.get() && (ret=item->HitTreeItem(pt)))
        {
            break;
        }
    }

    return ret;
}

TreeViewItemPtr TreeViewItem::HitTreeItemByUserData(suic::ObjectPtr obj)
{
    if (GetUserData() == obj)
    {
        return this;
    }

    TreeViewItemPtr ret;
    int count = GetItems()->GetCount();

    for (int i = 0; i < count; ++i)
    {
        TreeViewItemPtr item(GetItems()->GetItem(i));

        if (item.get() && (ret=item->HitTreeItemByUserData(obj)))
        {
            break;
        }
    }

    return ret;
}

void TreeViewItem::Expand()
{
    WriteFlag(CoreFlags::IsCollapsed, false);

    int count = GetItems()->GetCount();

    for (int i = 0; i < count; ++i)
    {
        TreeViewItemPtr item = TreeViewItemPtr::cast(GetItems()->GetItem(i));

        if (item)
        {
            item->Expand();
        }
    }
}

void TreeViewItem::Collapse()
{
    WriteFlag(CoreFlags::IsCollapsed, true);

    int count = GetItems()->GetCount();

    for (int i = 0; i < count; ++i)
    {
        TreeViewItemPtr item = TreeViewItemPtr::cast(GetItems()->GetItem(i));

        if (item)
        {
            item->Collapse();
        }
    }
}

/////////////////////////////////////////////////////////////////////
//
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

ImageBox* TreeViewItem::GetIcon()
{
    return &_icon;
}

void TreeViewItem::
OnHeaderChanged(suic::Element* oldHeader, suic::Element* newHeader)
{
    _header = newHeader;

    if (IsInitialized())
    {
        AddLogicalChild(_header.get());
        _header->DoInit();
    }
}

void TreeViewItem::OnPropertyChanged(suic::PropertyChangedEventArg& e)
{
    //
    // 初始化控件本身资源
    //
    if (e.GetName().Equals(_T("Header")))
    {
        SetText(e.GetSetter()->ToString());
    }
    else if (e.GetName().Equals(_T("Icon")))
    {
        _icon.SetSource(e.GetSetter()->ToString());
    }
    else if (e.GetName().Equals(_T("CheckButton")))
    {
        _check.SetVisible(e.GetSetter()->ToBool());
    }
    else if (e.GetName().Equals(_T("Indent")))
    {
        //SetIndent(e.GetSetter()->ToInt32());
    }
    else
    {
        //
        // 必须调用基类初始化基本数据
        //
        __super::OnPropertyChanged(e);
    }
}

void TreeViewItem::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDbclk(e);

    if (GetItems()->GetCount() > 0)
    {
        suic::RoutedEventArg er(this);
        _expand->OnClick(er);
    }

    e.SetHandled(true);
}

void TreeViewItem::OnInitialized()
{
    __super::OnInitialized();

    _headerHost->SetClassName(_T("TreeViewItem"));

    TreeButton* pBtn = dynamic_cast<TreeButton*>(_expand.get());

    suic::ObjectPtr Expanded = FindResource(_T("Expanded"));
    suic::ObjectPtr Collapsed = FindResource(_T("Collapsed"));

    _check.SetVisible(false);
    pBtn->SetButton(Expanded, Collapsed);

    pBtn->Expanded += TreeButtonClickEventHandler(this, &TreeViewItem::OnExpanded);
    pBtn->Collapsed += TreeButtonClickEventHandler(this, &TreeViewItem::OnCollapsed);

    SetWidth(suic::NonInt);
    SetHeight(suic::NonInt);

    SetMinHeight(16);
    _headerHost->DoInit();
}

void TreeViewItem::OnStyleUpdated()
{
    if (_expand)
    {
        _expand->UpdateStyle();
    }

    _check.UpdateStyle();
}

void TreeViewItem::OnRender(suic::DrawingContext * drawing)
{
    suic::Rect rect(0, 0, RenderSize().cx, _headerHost->RenderSize().cy);
    suic::BrushPtr bkgnd;

    if (IsFocused() || ReadFlag(CoreFlags::IsSelected))
    {
        if (GetStyle()->GetTrigger(_T("IsFocused")))
        {
            bkgnd = GetStyle()->GetTrigger(_T("IsFocused"))->GetValue(_T("Background"));
        }
    }
    else if (_headerHost->IsMouseOver() && GetStyle()->GetTrigger(_T("IsMouseOver")))
    {
        bkgnd = GetStyle()->GetTrigger(_T("IsMouseOver"))->GetValue(_T("Background"));
    }

    if (bkgnd)
    {
        bkgnd->Draw(drawing, &rect);
    }
}

suic::Size TreeViewItem::MeasureOverride(const suic::Size& availableSize)
{
    suic::FrameworkElementPtr frame(LogicalParent());
    ui::TreeViewItemPtr parent(frame);
    suic::Rect rcPad = _headerHost->GetPadding();

    if (!frame)
    { 
        rcPad.left = frame->GetPadding().left;
        _headerHost->SetPadding(rcPad);
    }
    else if (parent)
    {
        rcPad.left = parent->_headerHost->GetPadding().left + 16;
        _headerHost->SetPadding(rcPad);
    }

    suic::Size size = __super::MeasureOverride(availableSize);

    size.cx += frame->GetPadding().left;

    return size;
}

suic::Size TreeViewItem::ArrangeOverride(const suic::Size& finalSize)
{
    if (GetItemsCount() == 0)
    {
        _expand->SetVisible(false);
    }

    return __super::ArrangeOverride(finalSize);
}

void TreeViewItem::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    suic::Element::OnMouseLeftButtonDown(e);
    suic::ElementPtr pHeader = suic::ElementPtr::cast(GetHeader());

    if (!e.IsHandled())
    {
        suic::Rect rect = suic::VisualHelper::GetRenderRect(pHeader);
        e.SetHandled(true);

        rect.left = 0;
        rect.right = RenderSize().cx;

        if (rect.PointIn(e.MousePoint()))
        {
            Select();
        }
    }
}

void TreeViewItem::OnGotFocus(suic::FocusEventArg& e)
{
    return __super::OnGotFocus(e);

    e.SetHandled(true);
}

void TreeViewItem::OnLostFocus(suic::FocusEventArg& e)
{
}

void TreeViewItem::OnItemsChanged(suic::NotifyCollectionChangedArg& e)
{
    __super::OnItemsChanged(e);

    if (e.GetAction() == suic::NotifyCollectionChangedAction::Add)
    {
        for (int i = 0; i < e.NewItems()->GetCount(); ++i)
        {
            TreeViewItemPtr itemPtr(e.NewItems()->GetAt(i));

            if (itemPtr)
            {
                itemPtr->ItemSelected = ItemSelected;
                itemPtr->ItemUnselected = ItemUnselected;
            }
        }
    }
}

void TreeViewItem::OnStateChanged(suic::StateChangedEventArg& e)
{
    if (e.GetType() == CoreFlags::IsSelected)
    {
        suic::ElementPtr pHeader = suic::ElementPtr::cast(GetHeader());

        if (pHeader)
        {
            pHeader->WriteFlag(e.GetType(), e.GetValue());
        }
    }
}

void TreeViewItem::OnExpanded()
{
    WriteFlag(CoreFlags::IsCollapsed, false);

    TreeView* pTree = GetParentTreeView(this);

    pTree->UpdateLayout();
}

void TreeViewItem::OnCollapsed()
{
    //
    // 取得树对象指针
    //
    TreeView* pTree = GetParentTreeView(this);


    WriteFlag(CoreFlags::IsCollapsed, true);

    TreeViewItemPtr selPtr(pTree->SelectedItem());

    //
    // 如果自己的子孙选择了，取消，选中本节点
    //
    if (selPtr && selPtr.get() != this)
    {
        selPtr->Unselect();
        Select();
    }

    if (pTree)
    {
        pTree->UpdateLayout();
    }
}

void TreeViewItem::OnSelected(suic::RoutedEventArg& e)
{
    if (ItemSelected)
    {
        ItemSelected(this);
    }
}

void TreeViewItem::OnUnselected(suic::RoutedEventArg& e)
{
    if (ItemUnselected)
    {
        ItemUnselected(this);
    }
}

};
