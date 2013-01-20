// 华勤科技版权所有 2010-2011
// 
// 文件名：ProgressBar.h
// 功  能：实现标准b的tab控件。
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UIPROGRESSBAR_H_
# define _UIPROGRESSBAR_H_

#include <sui/sharpuiconfig.h>
#include <sui/RangeBase.h>

namespace ui
{

/// <summary>
/// ProgressBar
/// </summary>
class SHARPUI_API ProgressBar : public RangeBase
{
public:

    ProgressBar();
    virtual ~ProgressBar();

    DeclareTypeofInfo(ProgressBar, RangeBase)

public:

    void OnInitialized();
    void OnTimer(int id);

    virtual void OnRender(suic::DrawingContext * drawing);

    virtual void OnMaximumChanged(double oldMaximum, double newMaximum);
    virtual void OnMinimumChanged(double oldMinimum, double newMinimum);
    virtual void OnValueChanged(double oldValue, double newValue);
};

typedef suic::shared<ProgressBar> ProgressBarPtr;

};

# endif
