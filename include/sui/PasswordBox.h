// 华勤科技版权所有 2010-2011
// 
// 文件名：PasswordBox.h
// 功  能：实现标准的密码控件。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIPASSWORDBOX_H_
# define _UIPASSWORDBOX_H_

#include <sui/sharpuiconfig.h>
#include <suicore/uicontrol.h>

namespace ui
{

class SHARPUI_API PasswordBox : public suic::Control
{
public:

    PasswordBox();
    virtual ~PasswordBox();

    DECLAREBUILD(PasswordBox)

    suic::String GetText();
    void SetText(const suic::String & text);

    suic::Char GetPasswordChar() const;
    void SetPasswordChar(suic::Char ch);

    suic::String GetPassword() const;
    void SetPassword(suic::String pwd);

    virtual void Cut();
    virtual void Copy();
    virtual void Paste();
    virtual void SelectAll();

public:

    virtual void OnRender(suic::DrawingContext * drawing);

    virtual void OnTextInput(suic::KeyEventArg& e);
    virtual void OnKeyDown(suic::KeyEventArg& e);

    virtual void OnGotFocus(suic::FocusEventArg& e);
    virtual void OnLostFocus(suic::FocusEventArg& e);

    virtual void OnMouseLeftButtonDown(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonUp(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonDbclk(suic::MouseEventArg& e);

    virtual void OnMouseMove(suic::MouseEventArg& e);
    virtual void OnSetCursor(suic::CursorEventArg& e);

    virtual void OnSetterChanged(suic::SetterChangedEventArg& e);
    virtual void OnInitialized();

protected:

    bool InSelectMode() const;
    void CancelSelectMode();
    void DeleteSelection();
    void GetSelectRange(int& iStart, int& iCount);

    void ResetCaretPos();
    int CalcCaretPos(int xOffset);
    void InternalSetCaret(int iOff);

protected:

    suic::Char _passwordChar;
    suic::String _password;
    int _startSel;
    int _selCount;
    int _caretPos;
    int _horizontalOffset;
};

typedef suic::shared<PasswordBox> PasswordBoxPtr;

inline suic::Char PasswordBox::GetPasswordChar() const
{
    return _passwordChar;
}

inline void PasswordBox::SetPasswordChar(suic::Char ch)
{
    _passwordChar = ch;
}

inline suic::String PasswordBox::GetPassword() const
{
    return _password;
}

inline void PasswordBox::SetPassword(suic::String pwd)
{
    _password = pwd;
}

};

# endif