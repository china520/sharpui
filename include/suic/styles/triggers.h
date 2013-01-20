// 华勤科技版权所有 2010-2011
// 
// 文件名：StyleTriggers.h
// 功  能：元素触发的访问实现。
// 
// 作  者：汪荣
// 时  间：2011-08-02
// 
// ============================================================================

# ifndef _UISTYLETRIGGERS_H_
# define _UISTYLETRIGGERS_H_

#include <suic/core/uiconst.h>
#include <suic/styles/Setters.h>
#include <suic/tools/vector.h>

namespace suic 
{

class SUICORE_API Trigger : public RefObject
{
protected:

    // 资源定义的索引
    int _index;
    // 关键字
    String _key;
    // Trigger名称
    String _property;
    // Trigger值
    String _value;
    String _sourceName;

    // Trigger的设置值
    SetterCollectionPtr _setters;

public:

    Trigger(int val);

    void SetSetter(SetterPtr val);
    SetterPtr GetSetter(const String& property);
    ObjectPtr GetValue(const String& property);

    String ToString();

public:

    SetterCollectionPtr& Setters();

    int GetIndex() const;

    String GetKey() const;
    void SetKey(String val);

    String GetProperty() const;
    void SetProperty(String val);

    String GetValue() const;
    void SetValue(String val);

    String GetSourceName() const;
    void SetSourceName(String val);
};

typedef shared<Trigger> TriggerPtr;

class SUICORE_API TriggerCollection : public Object
{
public:

    Map<String, TriggerPtr> TriggerColl;

    TriggerCollection();

    void SetTrigger(TriggerPtr trg);
    TriggerPtr GetTrigger(const String& property);

    bool ContainsKey(const String& property);
    String ToString();

};

}

#endif
