// 华勤科技版权所有 2010-2011
// 
// 文件名：Selector.h
// 功  能：实现Item的基类
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UISELECTOR_H_
# define _UISELECTOR_H_

#include <sui/sharpuiconfig.h>
#include <sui/ItemsControl.h>

namespace ui
{

class SHARPUI_API SelectionChangedEventArg : public suic::RoutedEventArg
{
public:

    SelectionChangedEventArg();

    void AddItem(suic::ObjectPtr item, bool bAdd);

    suic::ItemContentList* AddedItems();
    suic::ItemContentList* RemovedItems();

protected:

    suic::ItemContentList _addItems;
    suic::ItemContentList _removeItems;
};

class SHARPUI_API ItemFocusChangedEventArg : public suic::RoutedEventArg
{
public:

    ItemFocusChangedEventArg(suic::Element* oldFocus,suic::Element* newFocus);

    suic::Element* GetOldFocus() const { return _oldFocus; }
    suic::Element* GetNewFocus() const { return _newFocus; }

protected:

    suic::Element* _oldFocus;
    suic::Element* _newFocus;
};

class Selector;
typedef delegate<void(SelectionChangedEventArg&)> SelectionChangedHandler;
typedef delegate<void(suic::Element*)> ItemSelectedHandler;
typedef delegate<void(suic::Element*)> ItemUnselectedHandler;
typedef delegate<void(Selector*,ItemFocusChangedEventArg&)> ItemFocusChangedHandler;

class SelectionMode
{
public:

    enum eSelectionMode
    {
        Single = 0,
        Multiple = 1,
        Extended = 2,
    };
};

/// <summary>
///  处理有选择项的元素逻辑。
/// </summary>
class SHARPUI_API Selector : public ItemsControl
{
public:

    SelectionChangedHandler SelectionChanged;
    ItemUnselectedHandler ItemUnselected;
    ItemSelectedHandler ItemSelected;
    ItemFocusChangedHandler ItemFocusChanged;

    Selector();
    virtual ~Selector();

    DeclareAbstractTypeofInfo(Selector, ItemsControl)

    /// <summary>
    ///     从一个子项获取Selector对象
    /// </summary>
    /// <remarks>
    ///     此方法获取指定子项的第一个Selector对象
    /// </remarks>
    /// <param name="pElem">子项对象</param>
    /// <returns>直接Selector对象</returns> 
    static Selector* SelectorFromItem(suic::Element* pElem);

    /// <summary>
    ///  选择或取消一个子项
    /// </summary>
    /// <remarks>
    ///  此方法获使用SelectorFromItem获取Selector对象
    ///  然后设置元素的IsSelected标志，同时触发Selector
    ///  对象的OnItemSelected事件
    /// </remarks>
    /// <param name="item">子项对象</param>
    /// <param name="selected">选择标志</param>
    /// <returns>无</returns> 
    static void SelectItem(suic::ObjectPtr item, bool selected);
    static void SetItemFocus(suic::ElementPtr focusItem);
    
    SelectionMode::eSelectionMode GetSelectionMode() const;

    int SelectedIndex();
    void SelectedIndex(int iIndex);

    suic::ObjectPtr SelectedItem();
    void SelectedItem(suic::ObjectPtr obj);

    void SetItemFocus(int index);

    /// <summary>
    ///     取消所有的选择项
    /// </summary>
    /// <returns>无</returns> 
    void UnselectAllItems();

public:

    virtual void OnItemSelected(suic::ObjectPtr item, ItemSelectionEventArg& e);
    virtual void OnSelectionChanged(SelectionChangedEventArg& e);
    virtual void OnItemFocusChanged(ItemFocusChangedEventArg& e);

protected:

    void ScrollByUpDown(suic::Element* pElem, bool bUp);

    virtual int GetVisualStartIndex();
    virtual int GetVisualEndIndex();

    void OnInitialized();

    void OnTextInput(suic::KeyboardEventArg& e);
    void OnKeyDown(suic::KeyboardEventArg& e);

protected:

    int _iSelected;

    suic::ItemContentList _selectedItems;
    // 选择模式
    SelectionMode::eSelectionMode _selectMode;
};

inline SelectionMode::eSelectionMode Selector::GetSelectionMode() const
{
    return _selectMode;
}

inline int Selector::GetVisualStartIndex()
{
    return 0;
}

inline int Selector::GetVisualEndIndex()
{
    return _itemsHost->GetVisualChildrenCount();
}

};

# endif