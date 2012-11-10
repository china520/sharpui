// 华勤科技版权所有 2010-2011
// 
// 文件名：ItemsControl.h
// 功  能：实现Item的基类
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// =============================================================

# ifndef _UIITEMSCONTROL_H_
# define _UIITEMSCONTROL_H_

#include <sui/sharpuiconfig.h>
#include <sui/scrollbar.h>
#include <suicore/uicontentcontrol.h>
#include <suicore/uielementcollection.h>
#include <sui/itemcontainer.h>

#include <sui/VisualizePanel.h>
#include <sui/ScrollViewer.h>

#define IMPLCHECKITEMS(dr,cr)\
    dr* pItem = dynamic_cast<dr*>(cr.get());\
    if (!pItem)\
    {\
        pItem = new dr();\
        pItem->SetContent(cr);\
        cr = pItem;\
    }\

namespace ui
{

class ItemCollection;

/// <summary>
/// ItemsControl,所有选择项的基类。
/// </summary>
class SHARPUI_API ItemsControl : public suic::Control
{
public:

    ItemsControl();
    virtual ~ItemsControl();

    suic::ObjectPtr FocusedItem() const;

public:

    bool HasItems() const;
    bool IsGrouping() const;

    ItemCollectionPtr GetItems() const;

    int GetItemsCount() const;

    /// <summary>
    ///     增加子项对象
    /// </summary>
    /// <remarks>
    ///     如果不是从Element派生，则会使用TextBloch进行包装
    /// </remarks>
    /// <param name="value">
    ///     子项对象
    /// </param>
    /// <returns>子项对象索引</returns>
    int AddChild(suic::ObjectPtr value);
    int InsertChild(int index, suic::ObjectPtr value);
    int AddText(const suic::String& text);
    
    void RemoveChild(suic::ObjectPtr ePtr);

    virtual void RemoveAt(int iIndex);
    virtual void ClearChildren();

    virtual suic::ObjectPtr GetItem(int iIndex) const;
    virtual suic::String GetItemText(int iIndex) const;

    virtual void OnNotifyCollectionChanged(suic::ObjectPtr sender, suic::NotifyCollectionChangedArg& e);

public:

    suic::Element* GetChild(int index);
    suic::Int32 GetChildrenCount();

    virtual void OnItemsChanged(suic::NotifyCollectionChangedArg& e);

    virtual suic::Size MeasureOverride(const suic::Size& size);
    virtual suic::Size ArrangeOverride(const suic::Size& size);

    virtual void OnInitialized();
    virtual void OnUnloaded(suic::LoadedEventArg& e);

    virtual void OnRender(suic::DrawingContext * drawing);

    virtual void OnTextInput(suic::KeyEventArg& e);
    virtual void OnKeyDown(suic::KeyEventArg& e);

    virtual void OnMouseEnter(suic::MouseEventArg& e);
    virtual void OnMouseMove(suic::MouseEventArg& e);
    virtual void OnMouseLeave(suic::MouseEventArg& e);

    virtual void OnPreviewMouseLeftButtonDown(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonDown(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonDbclk(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonUp(suic::MouseEventArg& e);

    virtual void OnMouseWheel(suic::MouseWheelEventArg& e);

protected:

    virtual void InitializeScrollView();
    virtual void CheckAddingItem(suic::ObjectPtr& itemObj);

protected:

    // 元素存储容器
    ItemCollectionPtr _items;
    // 布局对象
    suic::PanelPtr _itemsHost;
    // 视图对象
    ScrollViewerPtr _scrollHost;
    //ScrollData _scrollData;
    // 当前拥有焦点的子项元素
    suic::ObjectPtr _focusedItem;
};

typedef suic::shared<ItemsControl> ItemsControlPtr;

inline suic::ObjectPtr ItemsControl::FocusedItem() const
{
    return _focusedItem;
}

};

# endif
