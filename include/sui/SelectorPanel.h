// 华勤科技版权所有 2010-2011
// 
// 文件名：SelectorPanel.h
// 功  能：单选面板。
// 
// 作  者：汪荣
// 时  间：2012-06-02
// 
// ============================================================================

# ifndef _SELECTORPANEL_H_
# define _SELECTORPANEL_H_

#include <sui/sharpuiconfig.h>
#include <suic/framework/uipanel.h>

namespace ui
{

class SHARPUI_API SelectorPanel : public suic::Panel
{
public:

    SelectorPanel();
    virtual ~SelectorPanel();

    DeclareTypeofInfo(SelectorPanel, suic::Panel)

protected:

    void OnInitialized();
    void OnRender(suic::DrawingContext * drawing);

};

typedef suic::shared<SelectorPanel> SelectorPanelPtr;

};

# endif
