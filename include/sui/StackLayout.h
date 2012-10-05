// 华勤科技版权所有 2010-2011
// 
// 文件名：StackLayout.h
// 功  能：栈式控件布局管理，支持对子窗体的自动布局。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UISTACKLAYOUT_H_
# define _UISTACKLAYOUT_H_

#include <sui/StackPanel.h>

namespace ui
{

class SHARPUI_API StackLayout : public StackPanel
{
public:

    StackLayout();
    StackLayout(bool bHorz);

    DECLAREBUILD(StackLayout)

    virtual ~StackLayout();

protected:

    void OnRender(suic::DrawingContext * drawing);

    virtual suic::Size MeasureOverride(const suic::Size& size);
    virtual suic::Size ArrangeOverride(const suic::Size& size);

private:

    void RelayoutHorizontal(const suic::Size& size);
    void RelayoutVertical(const suic::Size& size);
};

typedef suic::shared<StackLayout> StackLayoutPtr;

}

# endif
