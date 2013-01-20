// 华勤科技版权所有 2010-2011
// 
// 文件名：ToolBarItem.h
// 功  能：实现工具栏项控件。
// 
// 作  者：汪荣
// 时  间：2011-07-02
// 
// ============================================================================

# ifndef _TOOLBARITEM_H_
# define _TOOLBARITEM_H_

#include <sui/sharpuiconfig.h>
#include <sui/Button.h>

namespace ui
{

class SHARPUI_API ToolBarItem : public ui::ButtonBase
{
public:

    ToolBarItem();
    virtual ~ToolBarItem();

    DeclareTypeofInfo(ToolBarItem, ButtonBase)

public:

    bool IsChecked() const;
    void SetChecked(bool val);

protected:

    void OnClick(suic::RoutedEventArg& e);

    void OnInitialized();
    void OnRender(suic::DrawingContext * drawing);
};

typedef suic::shared<ToolBarItem> ToolBarItemPtr;

};

# endif
