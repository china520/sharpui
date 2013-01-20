// 华勤科技版权所有 2010-2011
// 
// 文件名：UIEvent.h
// 功  能：定义核心库的事件基类。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIEVENT_H_
# define _UIEVENT_H_

#include <suic/core/uiobject.h>
#include <suic/core/delegate.h>
#include <suic/framework/uiroutedeventarg.h>

namespace suic
{

class DragDropEffects
{
public:

    enum
    {
        Scroll = -2,
        All = -1,
        None = 0,
        Copy = 1,
        Move = 2,
        Link = 4,
    };
};

class SUICORE_API CancelEventArg  : public suic::EventArg
{
public:

    CancelEventArg(bool cancel);

    bool IsCancel();
    void SetCancel(bool cancel);

protected:

    bool _cancel;
};

};

# endif
