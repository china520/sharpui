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
#include <suic/framework/uicontentcontrol.h>
#include <suic/types/uistructure.h>

namespace ui
{

class SHARPUI_API ItemSelectionEventArg : public suic::RoutedEventArg
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

static const int MENUITEM_MINHEIGHT = 18;
static const int MENUITEM_ICONSIZE = 18;

class SHARPUI_API ItemCollection : public suic::RefObject
{
public:

    suic::NotifyCollectionChangedHandler ContainerChanged;

    ItemCollection(suic::Element* itemControl);
    virtual ~ItemCollection();

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

typedef suic::shared<ItemCollection> ItemCollectionPtr;

};

# endif
