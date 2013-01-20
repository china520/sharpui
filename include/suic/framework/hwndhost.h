// 华勤科技版权所有 2010-2011
// 
// 文件名：HwndHost.h
// 功  能：实现真实窗口嵌入
// 
// 作  者：汪荣
// 时  间：2012-08-31
// 
// ============================================================================

# ifndef _UIHWNDHOST_H_
# define _UIHWNDHOST_H_

#include <suic/framework/uiframeworkelement.h>

namespace suic
{

/// <summary>
/// 适配真实窗口句柄，在排列时放大或缩小窗口。
/// </summary>
class SUICORE_API HwndHost : public suic::FrameworkElement
{
public:

    HwndHost();
    virtual ~HwndHost();

    DeclareTypeofInfo(HwndHost, suic::FrameworkElement)

    suic::Handle GetHandle() const;
    void Sethandle(suic::Handle h);

protected:

    void OnInitialized();

    void OnLoaded(LoadedEventArg& e);
    void OnUnloaded(LoadedEventArg& e);

    void OnRender(suic::DrawingContext * drawing);

    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

protected:

    void BuildWindow(Handle hwndParent);
    void UpdateWindowPos();

protected:

    // 真实窗口句柄
    suic::Handle _handle;
    // 是否为内部创建句柄
    bool _selfHost;
};

typedef suic::shared<HwndHost> HwndHostPtr;

inline suic::Handle HwndHost::GetHandle() const
{
    return _handle;
}

inline void HwndHost::Sethandle(suic::Handle h)
{
    _handle = h;
}

};

# endif
