// 华勤科技版权所有 2010-2011
// 
// 文件名：uihwndadapter.h
// 功  能：封装windows的句柄。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIHWNDADAPTER_H_
# define _UIHWNDADAPTER_H_

#include <suicore/uiobject.h>
#include <suicore/uistructure.h>

namespace suic
{

typedef struct SUICORE_API tagHwndParameter
{
    Handle parent;

    Uint32 style;
    Uint32 styleEx;
    Uint32 state;
    Uint32 classStyle;

    Int32 x;
    Int32 y;

    Int32 width;
    Int32 height;

    tagHwndParameter();

}HwndParameter;

typedef struct SUICORE_API tagMessageParameter
{
    Handle hwnd;
    Int32 message;
    Uint32 wParam;
    Uint32 lParam;
    Point point;
    Uint32 timestamp;
    Uint32 result;
    Uint32 state;

    tagMessageParameter();

}MessageParameter;

class SUICORE_API IHwndAdapterHook : public RefObject
{
public:

    virtual ~IHwndAdapterHook() {}

    virtual bool OnFilterMessage(ObjectPtr sender, MessageParameter& mp) = 0;
};

typedef shared<IHwndAdapterHook> HwndAdapterHookPtr;

class HwndAdapter : public IHwndAdapterHook
{
public:

    HwndAdapter(HwndParameter hp);
    HwndAdapter();

    bool OnFilterMessage(ObjectPtr sender, MessageParameter& mp);

    Handle GetHwnd() const;
    void SetHwnd(Handle hwnd);

    bool BuildHwnd(Object* param);
    bool BuildHwnd(HwndParameter hp, Object* param);

    void Close();

    void Clear();
    void RegisterHook(HwndAdapterHookPtr hook);
    void RemmoveHook(HwndAdapterHookPtr hook);

protected:

    Handle _value;
    HwndParameter _hp;
    EnumeratorPtr _hooks;
};

typedef shared<HwndAdapter> HwndAdapterPtr;

};

# endif
