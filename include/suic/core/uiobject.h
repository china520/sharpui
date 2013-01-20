// 华勤科技版权所有 2010-2011
// 
// 文件名：UIObjecth
// 功  能：定义核心库的基对象，所有的对象都必须从此继承。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIOBJECT_H_
# define _UIOBJECT_H_

#include <suic/core/uimicro.h>
#include <suic/core/uiconst.h>
#include <suic/core/uishared.h>
#include <suic/core/stringcore.h>

namespace suic
{

class Object;
struct TypeofInfo
{
    // 类名
    const char* typeName;
    // 基类型信息
    TypeofInfo* (__stdcall* baseType)();
    Object* (__stdcall* typeCreate)();

    // 判断是否从指定类继承
    bool IsDerivedFrom(TypeofInfo* baseType);
};

/// <summary>
/// 框架界面所有类的基类，重载new和delete，实现内存管理
/// </summary>
class SUICORE_API Object
{
public:

    virtual ~Object();

    virtual String ToString();
    virtual bool ToBool();
    virtual Double ToDouble();
    virtual Int32 ToInt32();
    virtual Rect ToRect();
    virtual Size ToSize();
    virtual Point ToPoint();
    virtual Color ToColor();
    virtual int GetHashCode() const;

#ifdef _DEBUG
    static void* operator new(size_t size, const char* name=__FILE__, int line=__LINE__);
    static void operator delete(void* ptr, const char* name, int line);
#else
    static void* operator new(size_t size);
#endif

    static void operator delete(void* ptr);

    static void* operator new[](size_t size);
    static void operator delete[](void* ptr);

public:

    static TypeofInfo typeObject;
    static TypeofInfo* __stdcall BaseType();
    static TypeofInfo* __stdcall ThisType();
    static Object* __stdcall Create();

    virtual suic::TypeofInfo* GetThisType() const;
    virtual suic::String GetTypeid() const;
};

/// <summary>
/// 带引用计数类的基类
/// </summary>
class SUICORE_API RefObject : public Object
{
public:

    RefObject();
    virtual ~RefObject() {}

    DeclareTypeofInfo(RefObject, Object)

    RefObject(const RefObject&);
    RefObject& operator=(const RefObject&);

    bool SetAutoDelete(bool val);
    bool IsAutoDelete() const;

    int GetCount() const;
 
public:

    void __addRef();
    void __release();

private:

    bool _autoDelete;
    long _count;
};

typedef shared<RefObject> ObjectPtr;

};

# endif
