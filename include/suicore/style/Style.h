// 华勤科技版权所有 2010-2011
// 
// 文件名：Style.h
// 功  能：元素样式的访问实现。
// 
// 作  者：汪荣
// 时  间：2011-08-02
// 
// ============================================================================

# ifndef _UISTYLE_H_
# define _UISTYLE_H_

#include <suicore/style/Triggers.h>
#include <suicore/style/Setters.h>

namespace suic
{

class Style;
typedef shared<Style> StylePtr;

class SUICORE_API Style : public RefObject
{
public:

    String Key;
    String TargetType;
    String BasedOn;
    String RefStyle;
    StylePtr RefBasedOn;

    TriggerCollection Triggers;
    SetterCollectionPtr Setters;
    Map<String, StylePtr> StylePart;

    //Vector<String> ContainerDriven;
    Set<PropertyDependent> ResourceDriven;

public:

    Style();
    virtual ~Style();

    StylePtr Clone();

    void SetSetter(SetterPtr val);

    SetterPtr GetSetter(const String& property);
    ObjectPtr GetValue(const String& property);
    SetterPtr GetSetter(const String& state, const String& property);

    TriggerPtr GetTrigger();
    TriggerPtr GetTrigger(const String& state);

    StylePtr GetStylePart(const String& part);

    String ToString();
};

class SUICORE_API StyleCollection : public Dictionary<String, StylePtr,suic::Object>
{
public:

    StyleCollection();

    StylePtr GetStyle(const String& property);
    void SetStyle(StylePtr value);
};

}

#endif
