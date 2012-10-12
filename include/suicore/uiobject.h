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

#include <suicore/uitypes.h>
#include <suicore/uimicro.h>
#include <suicore/uiconst.h>
#include <suicore/uishared.h>
#include <suicore/stringcore.h>
#include <suicore/suicoreids.h>

namespace suic
{

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
    virtual int HashCode() const;

#ifdef _DEBUG
    static void * operator new(size_t size, const char* name=__FILE__, int line=__LINE__);
    static void operator delete(void* ptr, const char* name, int line);
#else
    static void * operator new(size_t size);
#endif

    static void operator delete(void* ptr);

    static void * operator new[](size_t size);
    static void operator delete[](void* ptr);
};

/// <summary>
/// 带引用计数类的基类
/// </summary>
class SUICORE_API RefObject : public Object
{
public:

    RefObject();
    virtual ~RefObject() {}

    RefObject(const RefObject&);
    RefObject& operator=(const RefObject&);

    int ReferenceCount () const;

    bool IsAutoDelete () const;
    bool SetAutoDelete (bool bDel);

    void __addRef ();
    void __release ();

private:

    bool _autoDelete;
    long _count;
};

typedef shared<RefObject> ObjectPtr;

};

# endif
