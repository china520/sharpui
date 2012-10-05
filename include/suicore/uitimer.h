// 华勤科技版权所有 2010-2011
// 
// 文件名：UITimer
// 功  能：定义核心库的计时器对象。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UITIMER_H_
# define _UITIMER_H_

#include <suicore/uitypes.h>

namespace suic
{

class SUICORE_API Timer : public RefObject
{
public:

    Timer();
    virtual ~Timer();
};

};

# endif
