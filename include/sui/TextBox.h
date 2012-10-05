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

    void SetTextBox(TextBox* textBox);

    void OnSetCursor(suic::CursorEventArg& e);

    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

    void OnRender(suic::DrawingContext * drawing);

    void OnMouseRightButtonUp(suic::MouseEventArg& e);

protected:

    TextBox* _textBox;
};

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

    virtual suic::Size MeasureOverride(const suic::Size& size);
    virtual suic::Size ArrangeOverride(const suic::Size& size);

    void OnMenuItemSelected(suic::ObjectPtr mPtr, MenuItemPtr itemPtr);

    virtual void OnRender(suic::DrawingContext * drawing);

    virtual void OnTextInput(suic::KeyEventArg& e);
    virtual void OnKeyDown(suic::KeyEventArg& e);

    virtual void OnMouseEnter(suic::MouseEventArg& e);
    virtual void OnMouseMove(suic::MouseEventArg& e);
    virtual void OnMouseLeave(suic::MouseEventArg& e);
    virtual void OnMouseWheel(suic::MouseWheelEventArg& e);

    virtual void OnGotFocus(suic::FocusEventArg& e);
    virtual void OnLostFocus(suic::FocusEventArg& e);

    virtual void OnSetCursor(suic::CursorEventArg& e);

    virtual void OnMouseLeftButtonDown(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonDbclk(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonUp(suic::MouseEventArg& e);
    virtual void OnMouseRightButtonUp(suic::MouseEventArg& e);
    virtual void OnTimer(int nId);

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
    bool _isSingle;
    int _eStyle;

    TextBoxPanel _panel;
    ScrollViewer _view;

    friend class TextBoxPanel;
};

typedef suic::shared<TextBox> TextBoxPtr;

};

# endif