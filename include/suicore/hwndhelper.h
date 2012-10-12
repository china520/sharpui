// 华勤科技版权所有 2010-2011
// 
// 文件名：hwndhelper.h
// 功  能：封装windows的句柄。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIHWNDHELPER_H_
# define _UIHWNDHELPER_H_

#include <suicore/uiobject.h>
#include <suicore/uivisualhost.h>
#include <suicore/uielement.h>

namespace suic
{

class SUICORE_API HwndHelper : public Object
{
public:

    static VisualHostPtr GetVisualHost(Element* pElem); 
    static suic::Handle GetHandle(Element* pElem);
    static void LoadedElement(Element* pElem);

    static bool IsMouseInElement(suic::Element* element);

    static void DragMoveWindow(Element* pElem);

    static Point GetCursorPoint();
    static Point GetWindowPoint(Element*);    

    static void InvalidateAllWidows();
    static void AssignWindowMessage(suic::MessageParameter& mp);
    static Uint32 HandleDefWndMessage(suic::MessageParameter& mp);

    static void MaximizeWindow(suic::ElementPtr);
    static void RestoreWindow(suic::ElementPtr);
    static void MinimizeWindow(suic::ElementPtr);
    static void CloseWindow(suic::ElementPtr);
    static void ForceCloseWindow(suic::ElementPtr);

    static bool IsWindowMinimize(suic::ElementPtr);
    static bool IsWindowMaximize(suic::ElementPtr);
    static bool IsWindowVisible(suic::ElementPtr);
    static bool IsWindowEnable(suic::ElementPtr);

protected:

    HwndHelper();
};

};

# endif
