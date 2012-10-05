// 华勤科技版权所有 2010-2011
// 
// 文件名：UIInterface.h
// 功  能：定义核心库的用户注册接口。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIINTERFACE_H_
# define _UIINTERFACE_H_

#include <suicore/uiconst.h>
#include <suicore/uielement.h>
#include <suicore/uistructure.h>

namespace suic 
{

class IMarkupAttribute : public RefObject
{
public:

    virtual ~IMarkupAttribute() {}

    /// <summary>
    ///     重置记录到第一条
    /// </summary>
    /// <returns>无</returns>
    virtual void Reset() = 0;

    /// <summary>
    ///     判断是否到记录末尾
    /// </summary>
    /// <returns>无</returns>
    virtual bool HasNext() = 0;

    /// <summary>
    ///     移动记录到第一条
    /// </summary>
    /// <returns>无</returns>
    virtual void Next() = 0;

    /// <summary>
    ///     获取当前记录值
    /// </summary>
    /// <returns>当前记录值</returns>
    virtual String Value() = 0;
    virtual String Name() = 0;

    /// <summary>
    ///     查找指定关键字的属性
    /// </summary>
    /// <param name="key">属性名称</param>
    /// <returns>属性值</returns>
    virtual String Lookup(const String&) = 0;

    /// <summary>
    ///     取得记录个数
    /// </summary>
    /// <returns>属性记录个数</returns>
    virtual int GetCount() = 0;
};

typedef shared<IMarkupAttribute> MarkupAttributePtr;

class IMarkupNode;
typedef shared<IMarkupNode> MarkupNodePtr;

class IMarkupNode : public RefObject
{
public:

    virtual ~IMarkupNode() {}

    /// <summary>
    ///     取得当前节点指定属性名称属性值
    /// </summary>
    /// <remarks>
    ///     也可以先获取属性集合再取值
    /// </remarks>
    /// <param name="key">属性名称</param>
    /// <returns>属性值</returns>
    virtual String Attribute(const String& key) const = 0;

    /// <summary>
    ///     获取属性集合
    /// </summary>
    /// <returns>属性集合对象</returns>
    virtual MarkupAttributePtr Attributes() = 0;

    /// <summary>
    ///     获取当前节点名称
    /// </summary>
    /// <returns>节点名称</returns>
    virtual String Name() = 0;

    /// <summary>
    ///     获取当前子节点名称
    /// </summary>
    /// <returns>子节点名称</returns>
    virtual String ChildName() = 0;

    /// <summary>
    ///     重置记录到第一条
    /// </summary>
    /// <returns>无</returns>
    virtual void Reset() = 0;

    /// <summary>
    ///     判断是否到记录末尾
    /// </summary>
    /// <returns>true：记录末尾</returns>
    virtual bool HasNext() = 0;

    /// <summary>
    ///     移动子节点到第一条
    /// </summary>
    /// <returns>无</returns>
    virtual void Next() = 0;

    /// <summary>
    ///     获取当前子节点对象
    /// </summary>
    /// <returns>子节点对象</returns>
    virtual MarkupNodePtr ChildNode() = 0;

    /// <summary>
    ///     获取当前子节点个数
    /// </summary>
    /// <returns>子节点个数</returns>
    virtual int GetCount() = 0;
};

enum eBuildType { eNone, eElement, eResource, eProperty };

typedef delegate<ElementPtr()> BuildListener;
typedef delegate<ObjectPtr(const String&, IMarkupNode*, eBuildType)> ElementBuilder;
typedef delegate<ObjectPtr(const String&, const String&)> AttributeReader;

typedef delegate<bool(ObjectPtr,MessageParameter)> MessageListener;

typedef delegate<ObjectPtr(ObjectPtr)> ContentBuilder;

class IInitializeHook : public RefObject
{
public:

    virtual ~IInitializeHook() {}

    virtual void OnStart(ElementPtr root, ObjectPtr&) = 0;
    virtual void OnEnd(ElementPtr root, ObjectPtr&) = 0;
    virtual void OnError(const String& error) = 0;
};

typedef shared<IInitializeHook> InitializeHookPtr;

class TimerTarget : public RefObject
{
public:

    int id;
    int elapse;
    bool started;

    TimerTarget()
        : id(0)
        , elapse(10)
        , started(false)
    {}
};

typedef shared<TimerTarget> TimerTargetPtr;

typedef delegate<void(int)> TimerFunc;

class TimerEntity : public RefObject
{
public:

    TimerEntity()
    {
    }

    void SetAssigner(AssignerPtr assigner)
    {
        _assigner = assigner;
    }

    AssignerPtr GetAssigner()
    {
        return _assigner;
    }

    virtual void OnTimer(int id)
    {
        ;
    }

    virtual void OnLeftTimer(int id)
    {

    }

    virtual bool IsEndOf() const
    {
        return false;
    }

protected:

    AssignerPtr _assigner;
};

typedef shared<TimerEntity> TimerEntityPtr;

}

# endif
