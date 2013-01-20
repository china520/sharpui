// 华勤科技版权所有 2010-2011
// 
// 文件名：UIMouseDriver.h
// 功  能：定义核心库的鼠标事件处理类。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIMOUSEDRIVER_H_
# define _UIMOUSEDRIVER_H_

#include <suic/framework/uielement.h>

namespace suic
{

class SUICORE_API MouseDriver : public Object
{
public:

    static bool HandleMouseEnter(ElementPtr element, Point point);
    static bool HandleMouseLeave(ElementPtr element, Point point);

    static bool HandleLeftMouseDown(ElementPtr element, Point point);
    static bool HandleLeftMouseUp(ElementPtr element, Point point);

    static bool HandleRightMouseDown(ElementPtr element, Point point);
    static bool HandleRightMouseUp(ElementPtr element, Point point);

private:

    MouseDriver();
    virtual ~MouseDriver();
};

};

# endif
