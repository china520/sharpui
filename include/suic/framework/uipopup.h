// 华勤科技版权所有 2010-2011
// 
// 文件名：uipopup.h
// 功  能：实现标准的弹出窗口（无焦点）。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIPOPUP_H_
# define _UIPOPUP_H_

#include <suic/framework/uicontentcontrol.h>
#include <suic/framework/hwndadapter.h>
#include <suic/core/uiassigner.h>

namespace suic
{

class SUICORE_API UIPopup : public ContentControl
{
public:

    UIPopup();
    virtual ~UIPopup();

    DeclareTypeofInfo(UIPopup, ContentControl)

    void SetPopupRoot(ElementPtr root);
    ElementPtr GetPopupRoot() const;

    virtual void Show();
    virtual void SetPopupPos(bool position, int x, int y, bool size, int width, int height);
    virtual void TrackingPopup(int x, int y, bool size, int width, int height, HwndAdapterHookPtr hook);

    bool IsActive();

    virtual void Hide();
    virtual void Close();

    void Activate();

    bool IsChildPopup() const;
    void SetChildPopup(bool value);

    bool IsClosing() const;
    bool IsClosed() const;
    bool IsValid() const;

    void SetPopupCapture();
    void ReleasePopupCapture();

    AssignerFramePtr GetAssignerFrame() const;

    virtual void OnClosing(CancelEventArg& e);
    virtual void OnClosed(EventArg& e);

protected:
    
    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

    void OnHitTest(HitResultEventArg& e);
    void OnMouseWheel(suic::MouseWheelEventArg& e);

protected:

    int InternalCreate();

protected:

    bool _bClosing;
    bool _bClosed;
    ElementPtr _popupRoot;
    AssignerFramePtr _frame;

    Point _location;
};

typedef shared<UIPopup> PopupPtr;

class SUICORE_API HwndSourceHookSystemPopup : public suic::IHwndAdapterHook
{
public:

    HwndSourceHookSystemPopup(UIPopup* pPopup);

    bool OnFilterMessage(ObjectPtr sender, MessageParameter& mp);

    void SetAssignerFrame(AssignerFramePtr assignerStage);

protected:

    bool IsMouseInOwner();

protected:

    PopupPtr _popup;
    AssignerFramePtr _frame;
};

};

# endif
