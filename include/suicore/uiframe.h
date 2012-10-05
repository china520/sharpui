// 华勤科技版权所有 2010-2011
// 
// 文件名：uiframe.h
// 功  能：实现标准的窗口样式。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIFRAME_H_
# define _UIFRAME_H_

#include <suicore/uipanel.h>

namespace suic
{

class SUICORE_API UIFrame : public Panel
{
public:

    UIFrame();
    virtual ~UIFrame();

    virtual void Show();
    virtual void SetPopupPos(bool position, int x, int y, bool size, int width, int height);

    bool IsActive();

    virtual void Hide();
    virtual void Close();
    void Activate();

protected:

    virtual void OnActivated(EventArg& e);
    virtual void OnDeactivated(EventArg& e);

    Int32 PopupFilterMessage(Handle hwnd, int msg, Int32 wParam, Int32 lParam, bool& handled);

protected:
    
    virtual suic::Size MeasureOverride(const suic::Size& size);
    virtual suic::Size ArrangeOverride(const suic::Size& size);

    virtual void OnInitialized();
    virtual void OnRender(suic::DrawingContext * drawing);

protected:
    
};

typedef shared<UIFrame> FramePtr;

};

# endif
