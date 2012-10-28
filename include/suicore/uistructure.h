// 华勤科技版权所有 2010-2011
// 
// 文件名：UIInterface.h
// 功  能：定义核心库的用户注册接口。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UISTRUCTURE_H_
# define _UISTRUCTURE_H_

#include <suicore/uiconst.h>
#include <suicore/uievent.h>
#include <util/vector.h>

namespace suic 
{

class IEnumerator : public RefObject
{
public:

    virtual ~IEnumerator() {}

    virtual Int32 GetCount() = 0;
    virtual ObjectPtr GetAt(Int32) = 0;
    virtual void Add(ObjectPtr) = 0;
    virtual bool Remove(ObjectPtr) = 0;
    virtual ObjectPtr RemoveAt(Int32) = 0;
    virtual void Reset() = 0;
};

typedef Vector<int> IntVector;

typedef shared<IEnumerator> EnumeratorPtr;

SUICORE_API EnumeratorPtr CreateEnumerator();

class IStringMap : public RefObject
{
public:

    virtual ~IStringMap() {}

    virtual void Add(String key, ObjectPtr value) = 0;
    virtual bool ContainsKey(String key) = 0;
    virtual bool Remove(String key) = 0;
    virtual bool TryGetValue(String key, ObjectPtr& value) = 0;

    virtual int GetCount() = 0;
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool HasNext() = 0;
    virtual String GetKey() = 0;
    virtual ObjectPtr GetValue() = 0;

    virtual void Clear() = 0;
};

typedef shared<IStringMap> StringMapPtr;

SUICORE_API StringMapPtr CreateStringMap();

class IIntMap : public RefObject
{
public:

    virtual ~IIntMap() {}

    virtual void Add(Int32 key, ObjectPtr value) = 0;
    virtual bool ContainsKey(Int32 key) = 0;
    virtual bool Remove(Int32 key) = 0;
    virtual bool TryGetValue(Int32 key, ObjectPtr& value) = 0;

    virtual int GetCount() = 0;
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool HasNext() = 0;
    virtual Int32 GetKey() = 0;
    virtual ObjectPtr GetValue() = 0;

    virtual void Clear() = 0;
};

typedef shared<IIntMap> IntMapPtr;

SUICORE_API IntMapPtr CreateIntMap();

class SUICORE_API URect : public RefObject
{
public:

    URect(const Rect * rc)
        : _rect(*rc)
    {
    }

    Rect ToRect()
    {
        return _rect;
    }

    String ToString();

protected:

    Rect _rect;
};

typedef shared<URect> RectPtr;

class SUICORE_API UColor : public RefObject
{
public:

    UColor(String value)
        : _value(0)
    {
        _value = String::HexToAlphaColor(value);
    }

    virtual Color ToColor()
    {
        return _value;
    }

protected:

    Uint32 _value;
};

typedef shared<UColor> ColorPtr;

class SUICORE_API UInt : public RefObject
{
public:

    UInt(int value)
        : _value(value)
    {
    }

    virtual Int32 ToInt32()
    {
        return _value;
    }

protected:

    Uint32 _value;
};

typedef shared<UInt> IntPtr;

class SUICORE_API UDouble : public RefObject
{
public:

    UDouble(double value)
        : _value(value)
    {
    }

    virtual Int32 ToInt32()
    {
        return (Int32)_value;
    }

    virtual double ToDouble()
    {
        return _value;
    }

protected:

    double _value;
};

typedef shared<UDouble> DoublePtr;

class SUICORE_API ItemContentList
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

class SUICORE_API NotifyCollectionChangedAction
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

class SUICORE_API NotifyCollectionChangedArg : public suic::RoutedEventArg
{
public:

    NotifyCollectionChangedArg(int ac);

    int GetAction() const;

    void AddNewItem(suic::ObjectPtr item);
    void AddOldItem(suic::ObjectPtr item);

    ItemContentList* NewItems();
    ItemContentList* OldItems();

protected:

    int _action;
    ItemContentList _newItems;
    ItemContentList _oldItems;
};

inline int NotifyCollectionChangedArg::GetAction() const
{
    return _action;
}

typedef delegate<void(suic::ObjectPtr, NotifyCollectionChangedArg&)> NotifyCollectionChangedHandler;


}

# endif
