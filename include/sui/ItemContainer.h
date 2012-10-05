// 华勤科技版权所有 2010-2011
// 
// 文件名：uiitemcontainer.h
// 功  能：实现界面元素项的集合。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIITEMCONTAINER_H_
# define _UIITEMCONTAINER_H_

#include <sui/sharpuiconfig.h>
#include <suicore/uicontentcontrol.h>

namespace ui
{

class ItemSelectionEventArg : public suic::RoutedEventArg
{
public:

    ItemSelectionEventArg(bool bSelected, int iType)
        : suic::RoutedEventArg(suic::ObjectPtr())
    {
        _selected = bSelected;
        _type = iType;
    }

    bool IsSelected() const
    {
        return _selected;
    }

    int GetSelectionType() const
    {
        return _type;
    }

protected:

    bool _selected;
    int _type;
};

static const int ITEM_MINHEIGHT = 18;

class ItemContentList
{
public:

    ItemContentList();
    virtual ~ItemContentList();

    suic::Int32 GetCount();
    suic::ObjectPtr GetAt(suic::Int32 index);
    void Add(suic::ObjectPtr item);
    bool Remove(suic::ObjectPtr item);
    suic::ObjectPtr RemoveAt(suic::Int32 index);
    void Reset();

protected:

    suic::EnumeratorPtr _items;
};

class NotifyContainerChangedAction
{
public:

    enum eAction 
    {
        Add = 0,
        Remove = 1,
        Replace = 2,
        Move = 3,
        Reset = 4,
    };
};

class NotifyContainerChangedArg : public suic::RoutedEventArg
{
public:

    NotifyContainerChangedArg(int ac);

    int GetAction() const;

    void AddNewItem(suic::ObjectPtr item);
    void AddOldItem(suic::ObjectPtr item);

    ItemContentList* GetNewItems();
    ItemContentList* GetOldItems();

protected:

    int _action;
    ItemContentList _newItems;
    ItemContentList _oldItems;
};

inline int NotifyContainerChangedArg::GetAction() const
{
    return _action;
}

typedef delegate<void(suic::ObjectPtr, NotifyContainerChangedArg&)> NotifyContainerChangedHandler;

class ItemContainer : public suic::RefObject
{
public:

    NotifyContainerChangedHandler ContainerChanged;

    ItemContainer(suic::Element* itemControl);
    virtual ~ItemContainer();

    int GetCount();

    suic::ObjectPtr GetItem(int iIndex) const;
    suic::String GetItemText(int iIndex) const;

    int InsertItem(int index, suic::ObjectPtr item);
    int AddItem(suic::ObjectPtr item);

    void Clear();
    bool Contains(suic::ObjectPtr element);

    int IndexOf(suic::ObjectPtr item) const;

    void Remove(suic::ObjectPtr item);
    void RemoveAt(int index);
    void RemoveRange(int index, int count); 

protected:

    void HandleItem(suic::ObjectPtr& obj);

protected:

    suic::Element* _itemControl;
    suic::Vector<suic::ObjectPtr> _items;
};

typedef suic::shared<ItemContainer> ItemContainerPtr;

};

# endif
