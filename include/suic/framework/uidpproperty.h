// 华勤科技版权所有 2010-2012
// 
// 文件名：Visual.h
// 功  能：Sharpui属性实现等逻辑。
// 
// 作  者：汪荣
// 时  间：2010-05-01
// 
// ============================================================================

#include <suic/core/uiobject.h>
#include <suic/tools/map.h>
#include <suic/tools/hashmap.h>
#include <suic/framework/uievent.h>
#include <suic/types/integer.h>

#include <typeinfo>

namespace suic
{

class PropertyChangedEventArg;
class DpProperty;

typedef shared<DpProperty> DpPropertyEntity;

class EffectiveEntry : public RefObject
{
public:

    EffectiveEntry(int index, ObjectPtr val);

    bool IsExpression() const;
    bool IsAnimated() const;

public:

    // 属性定义
    int GetPropertyIndex() const;
    void SetPropertyIndex(int val);

    ObjectPtr GetValue() const;
    void SetValue(ObjectPtr val);

    ObjectPtr GetBaseValue() const;
    void SetBaseValue(ObjectPtr val);

    ObjectPtr GetExpressionValue() const;
    void SetExpressionValue(ObjectPtr val);

    ObjectPtr GetAnimatedValue() const;
    void SetAnimatedValue(ObjectPtr val);

private:

    int _propertyIndex;

    ObjectPtr _value; 

    ObjectPtr _baseValue; 
    ObjectPtr _expressionValue;
    ObjectPtr _animatedValue;
};

typedef shared<EffectiveEntry> EffectiveEntryPtr;
typedef delegate<void(ObjectPtr, PropertyChangedEventArg&)> PropertyChangedCallbackDelegate;

class PropertyMetadata : public RefObject
{
public:

    PropertyChangedCallbackDelegate PropertyChangedCallback; 

    PropertyMetadata();

    PropertyMetadata(int val, PropertyChangedCallbackDelegate propcallback=PropertyChangedCallbackDelegate());
    PropertyMetadata(double val, PropertyChangedCallbackDelegate propcallback=PropertyChangedCallbackDelegate());
    PropertyMetadata(ObjectPtr val, PropertyChangedCallbackDelegate propcallback=PropertyChangedCallbackDelegate());

    TypeofInfo* GetType() const
    {
        return _forType;
    }

    void SetType(TypeofInfo* val)
    {
        _forType = val;
    }

public:

    ObjectPtr GetDefaultValue() const;
    void SetDefaultValue(ObjectPtr val);

protected:

    ObjectPtr _defaultValue;
    TypeofInfo* _forType;
};

typedef shared<PropertyMetadata> PropertyMetadataPtr;

inline ObjectPtr PropertyMetadata::GetDefaultValue() const
{
    return _defaultValue;
}

inline void PropertyMetadata::SetDefaultValue(ObjectPtr val)
{
    _defaultValue = val;
}

class DpProperty : public RefObject
{    
public:

    static HashMap<IntegerType, DpPropertyEntity> RegisteredDps;
    static int globalIndex;

    // 属性名称
    String name;
    // 属性所属的类
    TypeofInfo* owerName;
    // 属性的全局索引
    int index;
    // 属性hash值
    IntegerType hashCode;

    // 默认值
    PropertyMetadataPtr defmetadata;
    mutable Map<TypeofInfo*, PropertyMetadataPtr> metadatas;

    static DpPropertyEntity Register(String name, TypeofInfo* ownerType, PropertyMetadataPtr defaultValue);
    static DpPropertyEntity FindProperty(String name, TypeofInfo* ownerType);

    PropertyMetadataPtr GetMetadata(TypeofInfo* forType) const;

public:

    virtual void OverrideMetadata(TypeofInfo* forType, PropertyMetadataPtr metadata);

public:

    ObjectPtr GetValue() const;
    void SetValue(ObjectPtr val);

    int GetIndex() const;
    void SetIndex(int val);

    String GetName() const;
    void SetName(String val);  

private:

    DpProperty(String strName, TypeofInfo* ownerType, PropertyMetadataPtr defaultValue);
};

inline ObjectPtr DpProperty::GetValue() const
{
    return defmetadata->GetDefaultValue();
}

inline void DpProperty::SetValue(ObjectPtr val)
{
    defmetadata->SetDefaultValue(val);
}

inline int DpProperty::GetIndex() const
{
    return index;
}

inline void DpProperty::SetIndex(int val)
{
    index = val;
}

class SUICORE_API PropertyChangedEventArg : public RoutedEventArg
{
public:

    enum eAction {Add, Remove, Replace};

    PropertyChangedEventArg(const String& name, ObjectPtr obj, int action);

    int GetAction() const
    {
        return _action;
    }

    String GetName() const
    {
        return _name;
    }

    ObjectPtr GetSetter() const
    {
        return _value;
    }

    void CallEventHandler(ObjectPtr& handler, ObjectPtr& target);

public:

    DpPropertyEntity GetProperty() const;
    void SetProperty(DpPropertyEntity val);

    EffectiveEntryPtr GetOldEntry() const;
    void SetOldEntry(EffectiveEntryPtr val);

    EffectiveEntryPtr GetNewEntry() const;
    void SetNewEntry(EffectiveEntryPtr val);

    PropertyMetadataPtr GetMetadata() const;
    void SetMetadata(PropertyMetadataPtr val);

protected:

    String _name;
    ObjectPtr _value;
    int _action;

    DpPropertyEntity _property;    
    PropertyMetadataPtr _metadata;
    EffectiveEntryPtr _oldEntry; 
    EffectiveEntryPtr _newEntry; 
};

}
