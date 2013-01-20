// 华勤科技版权所有 2010-2011
// 
// 文件名：TextBox.h
// 功  能：实现标准的win32编辑控件。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIEDIT_H_
# define _UIEDIT_H_

#include <suic/framework/uicontrol.h>
#include <sui/textboxdoc.h>
#include <sui/scrollbar.h>
#include <sui/ScrollViewer.h>
#include <sui/menu.h>

namespace ui
{

class TextBox;
class SHARPUI_API TextBoxPanel : public suic::Panel
{
public:

    TextBoxPanel();

    bool IsRender() const;

    void SetTextBox(TextBox* textBox);

    void OnSetCursor(suic::CursorEventArg& e);

    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

    void OnRenderSizeChanged(suic::RenderSizeChangedEventArg& e);
    void OnRender(suic::DrawingContext * drawing);
    void OnMouseRightButtonDown(suic::MouseEventArg& e);

protected:

    TextBox* _textBox;
};

inline bool TextBoxPanel::IsRender() const
{
    return true;
}

class SHARPUI_API TextBox : public suic::Control
{
public:

    TextBox();
    TextBox(suic::Uint32 eStyle);
    virtual ~TextBox();

    DeclareTypeofInfo(TextBox, suic::Control)

    suic::String GetText() const;
    void SetText(const suic::String & text);

    void AppendText(suic::String & text);

    void GetText(suic::String & text);

    bool IsReadOnly() const;
    void SetReadOnly(bool bReadOnly);

// 属性访问定义
public:

    /// <summary>
    ///     正则表达式检测
    /// </summary>
    suic::String GetRegularExp() const;
    void SetRegularExp(suic::String val);

public:

    suic::Rect DocumentRect(suic::Point pt);

    virtual void Cut();
    virtual void Copy();
    virtual void Paste();
    virtual void SelectAll();

public:

    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

    void OnMenuItemSelected(suic::ObjectPtr menu, MenuItem* sender);

    void OnRender(suic::DrawingContext * drawing);

    void OnTextInput(suic::KeyboardEventArg& e);
    void OnKeyDown(suic::KeyboardEventArg& e);

    void OnMouseMove(suic::MouseEventArg& e);
    void OnMouseWheel(suic::MouseWheelEventArg& e);

    void OnGotFocus(suic::FocusEventArg& e);
    void OnLostFocus(suic::FocusEventArg& e);

    void OnSetCursor(suic::CursorEventArg& e);

    void OnMouseLeftButtonDown(suic::MouseEventArg& e);
    void OnMouseLeftButtonDbclk(suic::MouseEventArg& e);
    void OnMouseLeftButtonUp(suic::MouseEventArg& e);

    void OnMouseRightButtonDown(suic::MouseEventArg& e);

    void OnTimer(int nId);

    virtual void OnTrackingMenu(ui::MenuPtr& menu);

public:

    void OnPropertyChanged(suic::PropertyChangedEventArg& e);
    void OnInitialized();

    void ResetCaretPos(bool bUpDown=false);

protected:

    void UpdateScrollInfo(bool bUpdate);

protected:

    // 编辑框委托实现
    ui::TextBoxDoc _eDoc;
    TextBoxPanel _panel;
    ScrollViewer _view;
    suic::CaretElement _caret;
    suic::String _regExp;

    bool _isSingle;
    int _eStyle;

    friend class TextBoxPanel;
};

typedef suic::shared<TextBox> TextBoxPtr;

};

# endif