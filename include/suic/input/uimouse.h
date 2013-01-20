// 华勤科技版权所有 2010-2011
// 
// 文件名：uimouse.h
// 功  能：实现标准的窗口样式。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIMOUSE_H_
# define _UIMOUSE_H_

#include <suic/framework/uielement.h>

namespace suic
{

class SUICORE_API Mouse : public Object
{
private:

    Mouse();
    ~Mouse();
    
public:

    static ElementPtr GetMouseDown(int flag);
    static void SetMouseDown(ElementPtr, int flag);
    static Point GetPosition(ElementPtr);
    
    static MouseButtonState LeftButton();
    static MouseButtonState RightButton();
    static MouseButtonState MiddleButton();

    static ElementPtr Capture(ElementPtr);
    static ElementPtr Captured();
    static ElementPtr DirectlyOver();

    static void SetMouseOver(ElementPtr);
    static bool IsMouseOver(ElementPtr);
    static bool IsMouseCaptureWithin(ElementPtr);

    static void UpdateCursor();
};

};

# endif
