// 华勤科技版权所有 2010-2011
// 
// 文件名：StackPanel.h
// 功  能：栈式控件布局管理，支持对子窗体的自动布局。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UISTACKPANEL_H_
# define _UISTACKPANEL_H_

#include <sui/sharpuiconfig.h>
#include <suic/framework/uipanel.h>

#define ARRANGEHORIZONTALCHILDREN(horz, rcelem, rcmgr, rc)\
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
        rc.left += (rcelem.Width() - szelem.cx) / 2;\
        rc.right = rc.left + szelem.cx;\
    }\
}

#define ARRANGEVERTICALCHILDREN(vert, rcelem, rcmgr, rc)\
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
        rc.top += (rcelem.Height() - szelem.cy) / 2;\
        rc.bottom = rc.top + szelem.cy;\
    }\
    else\
    {\
        rc.top += rcmgr.top;\
        rc.bottom = rc.top + szelem.cy;\
    }\
}

namespace ui
{

class SHARPUI_API StackPanel : public suic::Panel
{
public:

    StackPanel();
    StackPanel(bool bHorz);

    DeclareTypeofInfo(StackPanel, suic::Panel)

    virtual ~StackPanel();

protected:

    void OnRender(suic::DrawingContext * drawing);

    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

protected:

    void CalcHorzElement(suic::FrameworkElement* ePtr, suic::Rect& rcLay, suic::Rect& rc);
    void CalcVertElement(suic::FrameworkElement* ePtr, suic::Rect& rcLay, suic::Rect& rc);

private:

    void RelayoutHorizontal(const suic::Size& size);
    void RelayoutVertical(const suic::Size& size);
};

typedef suic::shared<StackPanel> StackPanelPtr;

}

# endif
