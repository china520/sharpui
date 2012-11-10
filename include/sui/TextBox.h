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

#include <suicore/uicontrol.h>
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
    void OnMouseRightButtonUp(suic::MouseEventArg& e);

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

    DECLAREBUILD(TextBox)

    suic::String GetText();
    void SetText(const suic::String & text);

    void AppendText(suic::String & text);

    void GetText(suic::String & text);

    bool IsReadOnly() const;
    void SetReadOnly(bool bReadOnly);

public:

    suic::Rect DocumentRect(suic::Point pt);

    virtual void Cut();
    virtual void Copy();
    virtual void Paste();
    virtual void SelectAll();

public:

    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

    void OnMenuItemSelected(suic::ObjectPtr mPtr, MenuItemPtr itemPtr);

    void OnRender(suic::DrawingContext * drawing);

    void OnTextInput(suic::KeyEventArg& e);
    void OnKeyDown(suic::KeyEventArg& e);

    void OnMouseEnter(suic::MouseEventArg& e);
    void OnMouseMove(suic::MouseEventArg& e);
    void OnMouseLeave(suic::MouseEventArg& e);
    void OnMouseWheel(suic::MouseWheelEventArg& e);

    void OnGotFocus(suic::FocusEventArg& e);
    void OnLostFocus(suic::FocusEventArg& e);

    void OnSetCursor(suic::CursorEventArg& e);

    void OnMouseLeftButtonDown(suic::MouseEventArg& e);
    void OnMouseLeftButtonDbclk(suic::MouseEventArg& e);
    void OnMouseLeftButtonUp(suic::MouseEventArg& e);

    void TextBox::OnMouseRightButtonDown(suic::MouseEventArg& e);
    void OnMouseRightButtonUp(suic::MouseEventArg& e);

    void OnTimer(int nId);

    virtual void OnTrackingMenu(ui::MenuPtr& menu);

public:

    virtual void OnSetterChanged(suic::SetterChangedEventArg& e);
    virtual void OnInitialized();

    void ResetCaretPos(bool bUpDown=false);

protected:

    void UpdateScrollInfo(bool bUpdate);

protected:

    // 编辑框委托实现
    ui::TextBoxDoc _eDoc;
    TextBoxPanel _panel;
    ScrollViewer _view;
    suic::CaretElement _caret;

    bool _isSingle;
    int _eStyle;

    friend class TextBoxPanel;
};

typedef suic::shared<TextBox> TextBoxPtr;

};

# endif