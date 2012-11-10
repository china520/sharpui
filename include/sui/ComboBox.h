// 华勤科技版权所有 2010-2011
// 
// 文件名：ComboBox.h
// 功  能：实现标准的组合框控件。
// 
// 作  者：汪荣
// 时  间：2010-10-31
// 
// ============================================================================

# ifndef _UICOMBOBOX_H_
# define _UICOMBOBOX_H_

#include <sui/sharpuiconfig.h>
#include <sui/Selector.h>
#include <suicore/uipopup.h>
#include <sui/textbox.h>
#include <sui/ListBox.h>

namespace ui
{

/// <summary>
/// 组合框子项，作为ListBox的项加入
/// </summary>
class SHARPUI_API ComboBoxItem : public ListBoxItem
{
public:

    ComboBoxItem();
    virtual ~ComboBoxItem();

    DECLAREBUILD(ComboBoxItem);

protected:

    void OnSetterChanged(suic::SetterChangedEventArg& e);
    void OnMouseMove(suic::MouseEventArg& e);

    void OnMouseLeftButtonDown(suic::MouseEventArg& e);
    void OnMouseLeftButtonUp(suic::MouseEventArg& e);

    void OnRender(suic::DrawingContext * drawing);
};

/// <summary>
/// 组合框下拉框打开时事件
/// </summary>
class SHARPUI_API DropDownEventArg : public suic::EventArg
{
public:

    DropDownEventArg(suic::PopupPtr popup, suic::ElementPtr list);

    suic::PopupPtr GetPopup() const;
    suic::ElementPtr GetList() const;

protected:

    suic::PopupPtr _popup;
    suic::ElementPtr _list;
};

inline suic::PopupPtr DropDownEventArg::GetPopup() const
{
    return _popup;
}

inline suic::ElementPtr DropDownEventArg::GetList() const
{
    return _list;
}

typedef delegate<void(suic::Element*, DropDownEventArg&)> DropDownEventHandler;

/// <summary>
/// 组合框，由两个子控件组成（TextBox和ListBox）
/// </summary>
class SHARPUI_API ComboBox : public Selector
{
public:

    DropDownEventHandler DropDownClosed;
    DropDownEventHandler DropDownOpened;

    DECLAREBUILD(ComboBox)

    ComboBox();
    virtual ~ComboBox();

    void ClearChildren();

    void SetReadOnly(bool bOnly);
    bool IsReadOnly() const;
    bool IsDropDown() const;

    /// <summary>
    ///     设置下拉框的高度
    /// </summary>
    /// <param name="height">下拉框高度</param>
    /// <returns>无</returns>
    void SetDropDownHeight(int height);

    /// <summary>
    ///     设置元素文本，默认会调_textBox进行设置
    /// </summary>
    /// <param name="text">文本信息</param>
    /// <returns>无</returns>
    void SetText(const suic::String & text);
    suic::String GetText();

    int AddText(const suic::String& text);

    /// <summary>
    ///    检测下拉框是否已经打开
    /// </summary>
    /// <returns>true：打开；false：关闭</returns>
    bool StaysOpenOnEdit() const;

public:

    int AddChild(suic::ObjectPtr child);

    void OnTextBoxCursor(suic::Element*, suic::CursorEventArg& e);

    virtual void OnDropDownClosed(DropDownEventArg& e);
    virtual void OnDropDownOpened(DropDownEventArg& e);

public:

    void OnRender(suic::DrawingContext * drawing);

    void OnKeyDown(suic::KeyEventArg& e);
    void OnTextInput(suic::KeyEventArg& e);

    void OnPreviewSetCursor(suic::CursorEventArg& e);
    void OnPreviewMouseLeftButtonDown(suic::MouseEventArg& e);
    void OnPreviewMouseLeftButtonDbclk(suic::MouseEventArg& e);

    void OnMouseLeftButtonDown(suic::MouseEventArg& e);
    void OnMouseLeftButtonUp(suic::MouseEventArg& e);
    void OnMouseLeftButtonDbclk(suic::MouseEventArg& e);
    void OnPreviewMouseEnter(suic::MouseEventArg& e);
    void OnPreviewMouseMove(suic::MouseEventArg& e);

    void OnSetCursor(suic::CursorEventArg& e);

    void OnGotFocus(suic::FocusEventArg& e);
    void OnLostFocus(suic::FocusEventArg& e);

    void OnSelectionChanged(SelectionChangedEventArg& e);

protected:

    void CheckAddingItem(suic::ObjectPtr& itemObj);

    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

    void OnInitialized();
    void OnStyleUpdated();
    void OnSetterChanged(suic::SetterChangedEventArg& e);

protected:

    // 下拉弹出框,用于list的容器
    suic::PopupPtr _popup;
    // 下拉列表框
    ListBoxPtr _list;
    // 编辑框
    TextBoxPtr _textBox;
    // 是否只读
    bool _bReadOnly;
    // 下拉框的高度
    int _downHeight;
};

typedef suic::shared<ComboBox> ComboBoxPtr;

};

# endif
