// 华勤科技版权所有 2010-2011
// 
// 文件名：GridView.h
// 功  能：实现GridView
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UIGRIDVIEW_H_
# define _UIGRIDVIEW_H_

#include <sui/sharpuiconfig.h>
#include <suicore/uicontrol.h>

namespace ui
{

// ============================================================================
// GridView。
// ============================================================================

class SHARPUI_API GridView : public suic::Control
{
public:

    GridView();
    virtual ~GridView();

protected:

    virtual void OnInitialized();

    virtual void OnRender(suic::DrawingContext * drawing);

protected:
};

typedef suic::shared<GridView> GridViewPtr;

};

# endif
