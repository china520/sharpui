// 华勤科技版权所有 2010-2011
// 
// 文件名：UIDictionary.h
// 功  能：定义核心库的键/值对象。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

#ifndef _UIDICTIONARY_H_
#define _UIDICTIONARY_H_

#include <suic/types/uitypes.h>

//--------------------------------------------------------------------

#define __DeclareTypeofInfo(This, Base) \
    static suic::TypeofInfo type##This;\
    static suic::TypeofInfo* __stdcall BaseType();\
    static suic::TypeofInfo* __stdcall ThisType();\
    static suic::String Typeid() { return (type##This).typeName; }\
    virtual suic::TypeofInfo* GetThisType() const { return (suic::TypeofInfo*)&(This::type##This); }\
    virtual suic::String GetTypeid() const { return (type##This).typeName; }\

#define DeclareAbstractTypeofInfo(This, Base) \
    __DeclareTypeofInfo(This, Base)\
    static Object* __stdcall Create() { return NULL; }\

#define DeclareTypeofInfo(This, Base) \
    __DeclareTypeofInfo(This, Base)\
    static Object* __stdcall Create() { return new This(); }\

#define ImplementTypeofInfo(This, Base) \
    suic::TypeofInfo This::type##This = {#This, &Base::ThisType, &This::Create};\
    suic::TypeofInfo* __stdcall This::BaseType()\
    {\
        return Base::ThisType();\
    }\
    suic::TypeofInfo* __stdcall This::ThisType()\
    {\
        return (suic::TypeofInfo*)&(This::type##This);\
    }\

//--------------------------------------------------------------------

// 定义句柄转换
#define HandleToHwnd(h) ((HWND)(LONG_PTR)h)
#define HwndToHandle(h) ((ULONG)(LONG_PTR)h)

#define HandleToHdc(dc) ((HDC)(ULONG_PTR)dc)
#define HdcToHandle(dc) ((suic::Handle)(ULONG_PTR)dc)

#define UIGetAlpha(clr) (LOBYTE((clr)>>24))
#define UIGetRed(clr) (LOBYTE((clr)>>16))
#define UIGetGreen(clr) (LOBYTE((clr)>>8))
#define UIGetBlue(clr) (LOBYTE(clr))

#define ARGB(a,r,g,b)  ((COLORREF)(((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)|(((DWORD)(BYTE)(a))<<24)))
#define ARGBTORGB(clr) ((Color)((((WORD)UIGetBlue(clr)) << 16) | (((WORD)UIGetGreen(clr)) << 8) | UIGetRed(clr)))
#define ALPHACOLOR(d,o,alpha) ((BYTE)(((suic::Uint32)(d * (255.0 - alpha) + o * alpha)) >> 8))
#define UStr(val) L(val)

#define FindUIName(d,e,n) (sui::##d##Ptr::cast(e->FindName(n)))

#endif
