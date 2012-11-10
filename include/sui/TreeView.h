// 华勤科技版权所有 2010-2011
// 
// 文件名：TreeView.h
// 功  能：实现标准的ListView控件
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UITREEVIEW_H_
# define _UITREEVIEW_H_

#include <sui/sharpuiconfig.h>
#include <sui/itemscontrol.h>
#include <sui/treeviewitem.h>

namespace ui
{

class SHARPUI_API TreeView : public ItemsControl
{
public:

    SelectTreeItemHandler ItemUnselected;
    SelectTreeItemHandler ItemSelected;

    TreeView();
    virtual ~TreeView();

    DECLAREBUILD(TreeView)

    bool RemoveItem(TreeViewItem* pItem);
    TreeViewItemPtr HitTreeItem(suic::Point pt);

    void ExpandSubtrees();

    suic::ObjectPtr SelectedItem();

    void OnSelectTreeItem(TreeViewItem* pItem);
    void OnUnselectTreeItem(TreeViewItem* pItem);

protected:

    void CheckAddingItem(suic::ObjectPtr& itemObj);

    void OnItemsChanged(suic::NotifyCollectionChangedArg& e);

    void OnInitialized();
    void OnRender(suic::DrawingContext * drawing);

    void OnMouseWheel(suic::MouseWheelEventArg& e);
    void OnMouseRightButtonDown(suic::MouseEventArg& e);

    void OnTextInput(suic::KeyEventArg& e);
    void OnKeyDown(suic::KeyEventArg& e);

    void OnGotFocus(suic::FocusEventArg& e);
    void OnLostFocus(suic::FocusEventArg& e);

protected:
    
    TreeViewItemPtr _focusedItem;
};

typedef suic::shared<TreeView> TreeViewPtr;

inline suic::ObjectPtr TreeView::SelectedItem()
{
    return _focusedItem.get();
}

};

# endif