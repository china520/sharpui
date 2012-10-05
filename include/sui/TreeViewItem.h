// 华勤科技版权所有 2010-2011
// 
// 文件名：TreeView.h
// 功  能：实现标准的ListView控件
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// =======================================================

# ifndef _UITREEVIEWITEM_H_
# define _UITREEVIEWITEM_H_

#include <sui/sharpuiconfig.h>
#include <sui/selector.h>
#include <sui/checkbutton.h>
#include <sui/headeritemscontrol.h>

namespace ui
{

class TreeViewItem;
typedef suic::shared<TreeViewItem> TreeViewItemPtr;

class TreeItemHeader : public suic::ContentControl
{
public:

    TreeItemHeader();

protected:

    void OnRender(suic::DrawingContext * drawing);

};

typedef suic::shared<TreeItemHeader> TreeItemHeaderPtr;

typedef delegate<void(TreeViewItem*)> SelectTreeItemHandler;

// =======================================================
// TreeViewItem，实现树节点。
// =======================================================

class TreeViewItem : public HeaderedItemsControl
{
public:

    SelectTreeItemHandler ItemUnselected;
    SelectTreeItemHandler ItemSelected;

    TreeViewItem();

    DECLAREBUILD(TreeViewItem)

    void Select();
    void Unselect();

    void SetCheck(bool value);
    bool IsChecked() const;

    void Expand();
    void Collapse();

    bool IsExpanded() const;
    bool IsSelectionActive() const;

    void ExpandSubtree();

    suic::ImageBrush* GetIcon();

    void ShowDotLine(bool show);
    void ShowExpandedButton(bool show);
    void ShowCheckButton(bool show);

    virtual void OnSelected(suic::RoutedEventArg& e);
    virtual void OnUnselected(suic::RoutedEventArg& e);

protected:

    bool CanExpand() const;

    void OnItemsChanged(NotifyContainerChangedArg& e);
    void OnInitialized();
    void OnStyleUpdated();

    void OnRender(suic::DrawingContext * drawing);

    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

    void OnHeaderChanged(suic::Element* oldHeader, suic::Element* newHeader);
    void OnSetterChanged(suic::SetterChangedEventArg& e);

    void OnMouseLeftButtonDbclk(suic::MouseEventArg& e);
    void OnMouseLeftButtonDown(suic::MouseEventArg& e);

    void OnGotFocus(suic::FocusEventArg& e);
    void OnLostFocus(suic::FocusEventArg& e);

    void OnStateChanged(suic::StateChangedEventArg& e);

    virtual void OnExpanded();
    virtual void OnCollapsed();

protected:

    // 隐藏和显示按钮
    ui::ButtonPtr _expand;
    // 选择按钮
    ui::CheckButton _check;
    // 图标
    suic::ImageBrushPtr _icon;

    bool _showDotLine;
};

inline void TreeViewItem::ShowDotLine(bool show)
{
    _showDotLine = show;
}

inline void TreeViewItem::ShowExpandedButton(bool show)
{
    _expand->SetVisible(show);
}

inline void TreeViewItem::ShowCheckButton(bool show)
{
    _check.SetVisible(show);
}

inline void TreeViewItem::SetCheck(bool value)
{
    _check.SetCheck(value);
}

inline bool TreeViewItem::IsChecked() const
{
    return _check.IsChecked();
}

};

# endif
