// 华勤科技版权所有 2010-2011
// 
// 文件名：carethelper.h
// 功  能：封装windows的句柄。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UICARETHELPER_H_
# define _UICARETHELPER_H_

#include <suicore/uiobject.h>
#include <suicore/uielement.h>

namespace suic
{

class SUICORE_API CaretHelper : public Object
{
public:

    CaretHelper();

    static bool CreateCaret(Element* pElem, int w, int h);
    static void SetCaretPos(Element* pElem, int x, int y);
    static void ShowCaret(Element* pElem);
    static void HideCaret(Element* pElem);
};

};

# endif

