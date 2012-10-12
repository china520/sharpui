// 华勤科技版权所有 2010-2011
// 
// 文件名：uitooltip.h
// 功  能：实现提示窗口。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UITOOLTIP_H_
# define _UITOOLTIP_H_

#include <suicore/uipopup.h>

namespace suic
{

class SUICORE_API ToolTip : public UIPopup
{
public:

    ToolTip();
    virtual ~ToolTip();

    void Show(suic::Point pt);
    void Hide();

    void SetToolTip(String tooltip);
    void SetContent(String content);

protected:

    void OnInitialized();

    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

    void OnHitTest(HitResultEventArg& e);
};

typedef shared<ToolTip> ToolTipPtr;

};

# endif
