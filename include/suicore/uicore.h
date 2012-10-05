// 华勤科技版权所有 2010-2011
// 
// 文件名：UICore.h
// 功  能：定义核心库的功能函数。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UICORE_H_
# define _UICORE_H_

#include <suicore/uiconst.h>
#include <suicore/uiinterface.h>
#include <suicore/uiwindow.h>
#include <suicore/hwndadapter.h>

SUICORE_API void UI_Trace(suic::Char * format, ...);

SUICORE_API void UI_InitializeRootVisual();
SUICORE_API void UI_Clear();

SUICORE_API suic::Point UI_CalcuCusorPoint(suic::ElementPtr);
SUICORE_API suic::ElementPtr UI_GetLogicalParent(suic::ElementPtr child);
SUICORE_API suic::ElementPtr UI_GetMouseOverElement(suic::ElementPtr);

SUICORE_API void UI_SetElementTopMost(suic::ElementPtr, bool);

//------------------------------------------------------------------------

SUICORE_API suic::Point UI_GetScreenPoint(suic::Element*);
SUICORE_API suic::Point UI_ToScreenPoint(suic::Element*, suic::Point);
SUICORE_API suic::Point UI_GetCursorPoint(suic::Element*);
SUICORE_API bool UI_IsMouseInElement(suic::Element*);

SUICORE_API suic::Point UI_CalcScreenElementPoint(suic::Element*, int flag);
SUICORE_API void UI_InvalidateAllWindows(suic::Rect* lprc);

# endif
