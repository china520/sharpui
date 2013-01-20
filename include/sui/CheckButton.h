// 华勤科技版权所有 2010-2011
// 
// 文件名：CheckButton.h
// 功  能：实现标准的选项控件。
// 
// 作  者：汪荣
// 时  间：2010-10-31
// 
// ============================================================================

# ifndef _UICHECKBOX_H_
# define _UICHECKBOX_H_

#include <sui/sharpuiconfig.h>
#include <sui/Button.h>

namespace ui
{

class CheckButton;
/// <summary>
/// 选择事件代理对象
/// </summary>
typedef delegate<void(CheckButton*, CheckedEventArg&)> CheckedEventHandler;

/// <summary>
/// 单选按钮
/// </summary>
class SHARPUI_API CheckButton : public ButtonBase
{
public:

    // 选择事件
    CheckedEventHandler Checked;

    CheckButton();
    virtual ~CheckButton();

    DeclareTypeofInfo(CheckButton, ButtonBase)

    /// <summary>
    ///     返回按钮是否勾选
    /// </summary>
    /// <returns>勾选：true；取消：false</returns>
    bool IsChecked() const;

    /// <summary>
    ///     选择按钮
    /// </summary>
    /// <param name="val">true:选择；false；取消</param>
    /// <returns>无</returns>
    void SetCheck(bool val);

// 属性访问定义
public:

    /// <summary>
    ///     设置是否自动计算大小
    /// </summary>
    /// <param name="val">true:自动；false:显式</param>
    /// <returns>无</returns>
    bool GetAutoSize() const;
    void SetAutoSize(bool val);

protected:

    virtual void OnRender(suic::DrawingContext * drawing);

    virtual void OnKeyDown(suic::KeyboardEventArg& e);

    virtual void OnMouseLeftButtonUp(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonDbclk(suic::MouseEventArg& e);

    virtual void OnGotFocus(suic::FocusEventArg& e);
    virtual void OnLostFocus(suic::FocusEventArg& e);

protected:

    suic::String InternalBackgrount();

    virtual void OnInitialized();
    virtual void OnPropertyChanged(suic::PropertyChangedEventArg& e);

    void AutoCalcSize();
    suic::Size MeasureOverride(const suic::Size& size);

protected:

    // 自动调整大小
    bool _bAutoSize;

    // 是否选择标志
    bool _bChecked;
    bool _bAdjusted;
};

typedef suic::shared<CheckButton> CheckButtonPtr;

};

# endif