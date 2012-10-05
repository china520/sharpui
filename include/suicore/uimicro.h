// 华勤科技版权所有 2010-2011
// 
// 文件名：UIDictionary.h
// 功  能：定义核心库的键/值对象。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIDICTIONARY_H_
# define _UIDICTIONARY_H_

#include <suicore/uicoreconfig.h>
#include <suicore/uitypes.h>

#define HandleToHwnd(h) ((HWND)(LONG_PTR)h)
#define HwndToHandle(h) ((ULONG)(LONG_PTR)h)

#define HandleToHdc(dc) ((HDC)(ULONG_PTR)dc)
#define HdcToHandle(dc) ((suic::Handle)(ULONG_PTR)dc)

#define GetAlpha(clr) (LOBYTE((clr)>>24))
#define GetRed(clr) (LOBYTE((clr)>>16))
#define GetGreen(clr) (LOBYTE((clr)>>8))
#define GetBlue(clr) (LOBYTE(clr))

#define ARGB(a,r,g,b)  ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))
#define ARGBTORGB(clr) ((Color)((((WORD)GetBlue(clr)) << 16) | (((WORD)GetGreen(clr)) << 8) | GetRed(clr)))
#define ALPHACOLOR(d,o,alpha) ((BYTE)(((suic::Uint32)(d * (255.0 - alpha) + o * alpha)) >> 8))
#define UStr(val) L(val)

#define TriggerEvent(handler,e) if (NULL != handler) { handler(this, e); }

#define FindUIName(d,e,n) (sui::##d##Ptr::cast(e->FindName(n)))

#define DECLAREBUILD(c) static suic::ElementPtr Create() { return new c(); }
#define ELEMENTBUILD(c) c::Create

#define ARRANGEHORIZONTALCHILDREN(horz, rcelem, rcmgr, rc, rcclip)\
{\
    if (horz == CoreFlags::Stretch)\
    {\
        rc.left += rcmgr.left;\
        rc.right -= rcmgr.right;\
    }\
    else if (CoreFlags::Left == horz)\
    {\
        rc.left += rcmgr.left;\
        rc.right = rc.left + szelem.cx;\
    }\
    else if (CoreFlags::Right == horz)\
    {\
        rc.right -= rcmgr.right;\
        rc.left = rc.right - szelem.cx;\
    }\
    else\
    {\
        rc.left += (rc.Width() - szelem.cx) / 2;\
        rc.right = rc.left + szelem.cx;\
    }\
    \
    rcclip.left = max(rc.left, rcelem.left);\
    rcclip.right = min(rc.right, rcelem.right);\
}

#define ARRANGEVERTICALCHILDREN(vert, rcelem, rcmgr, rc, rcclip)\
{\
    if (vert == CoreFlags::Stretch)\
    {\
        rc.top += rcmgr.top;\
        rc.bottom -= rcmgr.bottom;\
    }\
    else if (CoreFlags::Bottom == vert)\
    {\
        rc.bottom -= rcmgr.bottom;\
        rc.top = rc.bottom - szelem.cy;\
    }\
    else if (CoreFlags::Center == vert)\
    {\
        rc.top += (rc.Height() - szelem.cy) / 2;\
        rc.bottom = rc.top + szelem.cy;\
    }\
    else\
    {\
        rc.top += rcmgr.top;\
        rc.bottom = rc.top + szelem.cy;\
    }\
    rcclip.top = max(rc.top, rcelem.top);\
    rcclip.bottom = min(rc.bottom, rcelem.bottom);\
}

# endif
