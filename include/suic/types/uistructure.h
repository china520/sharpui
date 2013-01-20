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

#include <suic/core/uiconst.h>
#include <suic/framework/uievent.h>
#include <suic/tools/vector.h>
#include <suic/types/integer.h>

namespace suic 
{

class SUICORE_API ORect : public RefObject
{
public:

    ORect() {}
    ORect(const Rect * rc);
    ORect(String value);

    Rect ToRect()
    {
        return _rect;
    }

    String ToString();

protected:

    Rect _rect;
};

typedef shared<ORect> RectPtr;

class SUICORE_API OSize : public RefObject
{
public:

    OSize() {}
    OSize(const Size * size);
    OSize(String value);

    Rect ToRect()
    {
        return Rect(0, 0, _size.cx, _size.cy);
    }

    Size ToSize()
    {
        return _size;
    }

    String ToString();

protected:

    Size _size;
};

typedef shared<OSize> SizePtr;

class SUICORE_API OPoint : public RefObject
{
public:

    OPoint() {}
    OPoint(const Point * pt);
    OPoint(String value);

    Rect ToRect();
    Size ToSize();
    Point ToPoint();
    String ToString();

protected:

    Point _point;
};

typedef shared<OPoint> PointPtr;

class SUICORE_API OColor : public RefObject
{
public:

    OColor(Uint32 value);
    OColor(String value);

    static Color StringToColor(String value);

    Color ToColor()
    {
        return _value;
    }

    String ToString();

protected:

    Uint32 _value;
};

typedef shared<OColor> ColorPtr;

class SUICORE_API Boolean : public RefObject
{
public:

    Boolean(bool value);
    Boolean(String value);

    bool ToBool();
    Int32 ToInt32();
    Double ToDouble();
    String ToString();

protected:

    bool _value;
};

typedef shared<OColor> ColorPtr;

class SUICORE_API ODouble : public RefObject
{
public:

    ODouble(double value);
    ODouble(String value);

    Int32 ToInt32()
    {
        return (Int32)_value;
    }

    Double ToDouble()
    {
        return _value;
    }

    String ToString();

protected:

    double _value;
};

typedef shared<ODouble> DoublePtr;

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

    Vector<ObjectPtr> _items;
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
