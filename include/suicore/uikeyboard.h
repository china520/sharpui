// 华勤科技版权所有 2010-2011
// 
// 文件名：uikeyboard.h
// 功  能：实现标准的窗口样式。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIKEYBOARD_H_
# define _UIKEYBOARD_H_

#include <suicore/uielement.h>

namespace suic
{

class SUICORE_API Keyboard : public Object
{
private:

    Keyboard();
    ~Keyboard();
    
public:

    static ElementPtr GetKeyBoardFocused();
    static void SetKeyBoardFocused(ElementPtr);

    static ElementPtr GetFocused();
    static bool SetFocus(ElementPtr);

    static bool IsFocusedWithin(ElementPtr);

};

};

# endif
