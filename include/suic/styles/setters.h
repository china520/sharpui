// 华勤科技版权所有 2010-2011
// 
// 文件名：Setter.h
// 功  能：资源字典的访问实现。
// 
// 作  者：汪荣
// 时  间：2011-08-02
// 
// ============================================================================

# ifndef _UISTYLESETTERS_H_
# define _UISTYLESETTERS_H_

#include <suic/core/uiconst.h>
#include <suic/tools/map.h>

namespace suic 
{

class SUICORE_API Setter : public RefObject
{
public:

    ObjectPtr Value;
    String Property;
    String DefValue;
    bool sealed;
    // 标记 0-本身值；1-继承值
    int flag;

    Setter() : flag(0) {}
};

struct SUICORE_API PropertyDependent
{ 
    int index;
    String property;
    String name;

    PropertyDependent();

    bool operator <(const PropertyDependent& Other);
    bool operator >(const PropertyDependent& Other);
};

typedef shared<Setter> SetterPtr;
typedef Map<String, SetterPtr> SetterMap;

class SUICORE_API SetterCollection : public RefObject
{
public:

    SetterCollection();

    void SetSetter(SetterPtr setter);
    void SetValue(const String& property, ObjectPtr val);

    SetterPtr GetSetter(const String& property);
    ObjectPtr GetValue(const String& property);

    bool ContainsKey(const String& property);
    String ToString();

public:

    Set<PropertyDependent>& ResourceDriven();
    SetterMap& SetterColl();

protected:

    // 依赖属性项
    Set<PropertyDependent> _resourceDriven;
    Map<String, SetterPtr> _setterColl;
};

typedef shared<SetterCollection> SetterCollectionPtr;

inline Set<PropertyDependent>& SetterCollection::ResourceDriven()
{
    return _resourceDriven;
}

inline SetterMap& SetterCollection::SetterColl()
{
    return _setterColl;
}

}

#endif
