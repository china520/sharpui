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

namespace ui
{

class ItemContainer;

/// <summary>
/// ItemsControl,所有选择项的基类。
/// </summary>
class SHARPUI_API ItemsControl : public suic::Control
{
public:

    ItemsControl();
    virtual ~ItemsControl();

public:

    bool HasItems() const;
    bool IsGrouping() const;

    ItemContainerPtr GetItems() const;

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
    virtual int Add(suic::ObjectPtr value);
    virtual int Insert(int index, suic::ObjectPtr value);
    virtual int AddText(const suic::String& text);

    virtual void RemoveAt(int iIndex);
    virtual void Remove(suic::ObjectPtr ePtr);
    virtual void RemoveAll();

    virtual suic::ObjectPtr GetItem(int iIndex) const;
    virtual suic::String GetItemText(int iIndex) const;

    void OnNotifyContainerChanged(suic::ObjectPtr sender, NotifyContainerChangedArg& e);

public:

    virtual void AddLogicalChild(suic::Element* child);
    virtual void RemoveLogicalChild(suic::Element* child);
    virtual suic::Element* GetLogicalChild(int index);
    virtual suic::Int32 GetLogicalChildrenCount();

    virtual void OnItemsChanged(NotifyContainerChangedArg& e);

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
    ItemContainerPtr _container;
    // 布局对象
    suic::PanelPtr _panel;
    // 视图对象
    ScrollViewPtr _scrollView;
    //ScrollData _scrollData;
};

typedef suic::shared<ItemsControl> ItemsControlPtr;

};

# endif
