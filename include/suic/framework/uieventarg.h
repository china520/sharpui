// 华勤科技版权所有 2010-2011
// 
// 文件名：uieventarg.h
// 功  能：定义核心库的事件基类。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIEVENTARG_H_
# define _UIEVENTARG_H_

#include <suic/core/uiobject.h>
#include <suic/core/delegate.h>

namespace suic
{

/// <summary>
/// 界面元素的事件，这是所有界面元素的基类，其它的界面元素都会直接或
/// 或间接地派生它
/// </summary>
class SUICORE_API EventArg : public Object
{
public:

    EventArg();
    Uint32 Timestamp() const;

    virtual void CallEventHandler(ObjectPtr& handler, ObjectPtr& target);

    template<typename T, typename H, typename A>
    void InternalCall(ObjectPtr& handler, ObjectPtr& target)
    {
        T* pElem(dynamic_cast<T*>(target.get()));
        H* pHandler(dynamic_cast<H*>(handler.get()));

        if (pHandler && pElem)
        {
            (*pHandler)(pElem, *((A*)this));
        }
    }

protected:

    Uint32 _timestamp;
};

};

# endif
