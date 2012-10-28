// 华勤科技版权所有 2010-2011
// 
// 文件名：TabPanel.h
// 功  能：实现TabPanel标签布局。
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UITABPANEL_H_
# define _UITABPANEL_H_

#include <sui/sharpuiconfig.h>
#include <suicore/uipanel.h>

namespace ui
{

/// <summary>
///  TabLayout，实现标签布局。
/// </summary>
class SHARPUI_API TabPanel : public suic::Panel
{
public:

    TabPanel();
    virtual ~TabPanel();

protected:

    virtual void OnInitialized();

    virtual void OnRender(suic::DrawingContext * drawing);
    virtual void OnGotFocus(suic::FocusEventArg& e);

protected:
};

typedef suic::shared<TabPanel> TabLayoutPtr;

};

# endif
