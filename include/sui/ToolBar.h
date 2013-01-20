// 华勤科技版权所有 2010-2011
// 
// 文件名：ToolBar.h
// 功  能：实现工具条控件。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _TOOLBAR_H_
# define _TOOLBAR_H_

#include <sui/sharpuiconfig.h>
#include <sui/HeaderedItemsControl.h>

namespace ui
{

class SHARPUI_API ToolBar : public HeaderedItemsControl
{
public:

    ToolBar();
    ToolBar(suic::String source);
    virtual ~ToolBar();

    DeclareTypeofInfo(ToolBar, HeaderedItemsControl)

protected:

    void OnInitialized();
    void OnRender(suic::DrawingContext * drawing);

};

typedef suic::shared<ToolBar> ToolBarPtr;

};

# endif
