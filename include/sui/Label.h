// 华勤科技版权所有 2010-2011
// 
// 文件名：Label.h
// 功  能：标签控件，支持组合方式实现。
// 
// 作  者：汪荣
// 时  间：2011-07-02
// 
// ============================================================================

# ifndef _UILABEL_H_
# define _UILABEL_H_

#include <sui/sharpuiconfig.h>
#include <suic/framework/uicontentcontrol.h>

namespace ui
{

class SHARPUI_API Label : public suic::ContentControl
{
public:

    Label();
    Label(suic::String text);
    virtual ~Label();

    DeclareTypeofInfo(Label, suic::ContentControl)

protected:

    suic::Size MeasureOverride(const suic::Size& availableSize);

    void OnInitialized(); 
    void OnRender(suic::DrawingContext * drawing);
};

typedef suic::shared<Label> LabelPtr;

};

# endif
