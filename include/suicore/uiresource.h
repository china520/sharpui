// 华勤科技版权所有 2010-2011
// 
// 文件名：UIResource
// 功  能：定义核心库的资源和样式风格接口。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIRESOURCE_H_
# define _UIRESOURCE_H_

#include <suicore/uitypes.h>
#include <suicore/uiobject.h>

namespace suic
{

// ============================================================================
// 用户数据，每个界面元素都允许用户设置自己的数据
//
class IUserData : public RefObject
{
public:

    virtual ~IUserData() {}
};

typedef shared<IUserData> UserDataPtr;

class IAttribute;
typedef shared<IAttribute> AttributePtr;

class IAttribute : public RefObject
{
public:

    virtual ~IAttribute() {}

    virtual AttributePtr Clone(bool filter) = 0;

    virtual String GetName() = 0;

    virtual bool ContainsKey(const String& key) = 0;
    virtual String GetValue(const String& key) = 0;
    virtual void SetValue(const String& key, const String& val) = 0;
    virtual void Remove(const String& key) = 0;

    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsEndOf() = 0;

    virtual String Key(const String& key) = 0;
    virtual String Value(const String& key) = 0;
};

class INode;
typedef shared<INode> NodePtr;

class INode : public RefObject
{
public:

    virtual ~INode() {};

    virtual AttributePtr GetAttribute() = 0;

    virtual int GetCount() = 0;
    virtual NodePtr GetChild(int index) = 0;

    virtual NodePtr Clone(bool filter) = 0;
};

/*class ISetter : public RefObject
{
public:

    virtual ~ISetter() {};

    virtual String GetTargetName() = 0;
    virtual void SetTargetName(const String& targetName) = 0;
    virtual void SetValue(const String& prop, ObjectPtr value, bool bHerit) = 0;
    virtual ObjectPtr TryGetValue(const String& key) = 0;

    virtual bool IsCanHerit() = 0;
};

typedef shared<ISetter> SetterPtr;

class ITrigger : public RefObject
{
public:

    virtual ~ITrigger() {};

    virtual AttributePtr GetAttribute() = 0;

    virtual SetterPtr FindSetter(const String& prop) = 0;
    virtual ObjectPtr GetSetter(const String& prop) = 0;
    virtual void SetSetter(const String& prop, ObjectPtr val, bool) = 0;
    virtual void RemoveSetter(const String& prop) = 0;
};

typedef shared<ITrigger> TriggerPtr;

class ITriggers : public RefObject
{
public:

    virtual ~ITriggers() {};

    virtual AttributePtr GetAttribute() = 0;

    virtual TriggerPtr GetTrigger(const String& strName, int iFlag) = 0;    
    virtual TriggerPtr GetMultiTrigger(const String& strCondition) = 0;
    virtual TriggerPtr GetDataTrigger(const String& strBinding) = 0;
    virtual TriggerPtr GetEventTrigger(const String& strEvent) = 0;
};

typedef shared<ITriggers> TriggersPtr;

class IResources : public RefObject
{
public:

    virtual ~IResources() {};

    virtual AttributePtr GetAttribute() = 0;

    virtual ObjectPtr Lookup(const String& key) = 0;
};

typedef shared<IResources> ResourcesPtr;

class IStyle;
typedef shared<IStyle> StylePtr;

class IStyle : public RefObject
{
public:

    virtual ~IStyle() {};

    virtual AttributePtr GetAttribute() = 0;
    virtual String Attribute(const String& key) = 0;

    virtual ObjectPtr GetSetter(const String& prop) = 0;
    virtual void SetSetter(const String& prop, ObjectPtr val) = 0;

    virtual TriggerPtr GetTrigger() = 0;
    virtual TriggersPtr GetTriggers() = 0;
};

class IStyleSelector : public RefObject
{
public:

    virtual ~IStyleSelector() {};

    virtual StylePtr GetStyle() = 0;
    virtual StylePtr GetStyle(const String strName) = 0;
    virtual StylePtr SearchStyle(const String name) = 0;
    virtual ObjectPtr GetResource(const String& key) = 0;
    virtual ObjectPtr SearchResource(const String& key) = 0;
};

typedef shared<IStyleSelector> StyleSelectorPtr;*/

}

# endif
