// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// TextBox.cpp

#include <sui/TextBox.h>
#include <sui/WindowHelper.h>
#include <suicore/drawing/uirender.h>

namespace suic
{
    /////////////////////// 定义TextBox控件风格
    static const int UTE_READONLY = 0X0001;
    static const int UTE_MULTILINE = 0X0002;
    static const int UTE_AUTOHORZSCROLL = 0X0004;
    static const int UTE_AUTOVERTSCROLL = 0X0008;
    static const int UTE_HORZSCROLL = 0X0010;
    static const int UTE_VERTSCROLL = 0X0020;
    static const int UTE_SHOWCARET = 0X0040;
}

namespace ui
{

TextBoxPanel::TextBoxPanel()
{
}

void TextBoxPanel::SetTextBox(TextBox* textBox)
{
    _textBox = textBox;
}

void TextBoxPanel::OnSetCursor(suic::CursorEventArg& e)
{
    _textBox->OnSetCursor(e);
}

suic::Size TextBoxPanel::MeasureOverride(const suic::Size& size)
{
    int iVertVisual = 0;
    int iVertLogic = 0;
    int iHoriVisual = 0;
    int iHoriLogic = 0;

    _textBox->_eDoc.GetVertScrollInfo(iVertVisual, iVertLogic);
    _textBox->_eDoc.GetHorzScrollInfo(iHoriVisual, iHoriLogic);

    return suic::Size(iHoriLogic, iVertLogic);
}

suic::Size TextBoxPanel::ArrangeOverride(const suic::Size& size)
{
    suic::Rect rect(0, 0, size.cx, size.cy);

    rect.Deflate(_textBox->GetPadding());

    _textBox->_eDoc.SetVertScrollPos(_textBox->_view.VerticalVisualPos());
    _textBox->_eDoc.SetHorzScrollPos(_textBox->_view.HorizontalVisualPos());

    _textBox->_eDoc.SetVisualRect(&rect);
    _textBox->ResetCaretPos();

    return size;
}

void TextBoxPanel::OnRender(suic::DrawingContext * drawing)
{
    suic::TriggerPtr trg(suic::UIRender::GetTriggerByStatus(this, GetStyle()));        
    suic::Rect rcdraw(0, 0, RenderSize().cx, RenderSize().cy);

    // 绘制文本

    suic::Color clrText(ARGB(255,0,0,0));
    suic::ObjectPtr oValue = trg->GetValue(suic::FOREGROUND);

    rcdraw.Deflate(_textBox->GetPadding());

    if (oValue)
    {
        clrText = oValue->ToColor();
    }

    if (_textBox->_isSingle)
    {
        _textBox->_eDoc.DrawSingleLine(drawing, _textBox->IsFocused(), &rcdraw, clrText);
    }
    else
    {
        _textBox->_eDoc.Draw(drawing, _textBox->IsFocused(), &rcdraw, clrText);
    }
}

void TextBoxPanel::OnMouseRightButtonUp(suic::MouseEventArg& e)
{
    _textBox->OnMouseRightButtonUp(e);
}

///////////////////////////////////////////////////////////////////////////////////
// TextBox
TextBox::TextBox()
	: _eStyle(0)
{
    _isSingle = true;

    SetClassName(_T("TextBox"));
    _eDoc.SetAutoDelete(false);
    SetMinHeight(16);

    _panel.SetAutoDelete(false);
    _view.SetAutoDelete(false);

    _panel.SetTextBox(this);
}

TextBox::TextBox(suic::Uint32 eStyle)
    : _isSingle(true)
    , _eStyle(0)
{
    SetClassName(_T("TextBox"));
    _eDoc.SetAutoDelete(false);
    SetMinHeight(16);

    _panel.SetTextBox(this);
}

TextBox::~TextBox()
{
}

suic::String TextBox::GetText()
{
    suic::String text;

    _eDoc.GetText(text);

    return text;
}

void TextBox::SetText(const suic::String & text)
{
    _eDoc.SelectAll();
    _eDoc.ReplaceSelect(text);

    UpdateScrollInfo(true);
}

void TextBox::AppendText(suic::String & text)
{
    _eDoc.Add(text);

    UpdateScrollInfo(true);
    
    _panel.InvalidateVisual();
}

void TextBox::GetText(suic::String & text)
{
    _eDoc.GetText(text);
}

bool TextBox::IsReadOnly() const
{
    return (_eStyle & suic::UTE_READONLY);
}

void TextBox::SetReadOnly(bool bReadOnly)
{
    if (bReadOnly)
    {
        _eStyle |= suic::UTE_READONLY;
    }
    else
    {
        _eStyle &= ~suic::UTE_READONLY;
    }
}

suic::Rect TextBox::DocumentRect(suic::Point pt)
{
    suic::Rect rc(_panel.GetVisualOffset().x, _panel.GetVisualOffset().y
        , _panel.RenderSize().cx, _panel.RenderSize().cy);

    rc.Deflate(GetPadding());
    rc.Offset(GetBorderThickness().left, GetBorderThickness().top);
    rc.Offset(pt);

    return rc;
}

void TextBox::Cut()
{
    if (IsReadOnly() || !_eDoc.IsSelectMode())
    {
        return;
    }

    Copy();

    _eDoc.DeleteSelect();

    UpdateScrollInfo(true);

    _panel.InvalidateVisual();
    ResetCaretPos();
}

void TextBox::Copy()
{
    if (!_eDoc.IsSelectMode())
    {
        return;
    }
    ui::WndHelper helper(this);
    helper.HideCaret();

    if (!helper.OpenClipboard())
    {
        return;
    }

    suic::String strSel;
    _eDoc.GetSelectText(strSel);

    helper.CopyText(strSel);

    helper.CloseClipboard();
}

void TextBox::Paste()
{
    if (IsReadOnly())
    {
        return;
    }

    ui::WndHelper helper(this);

    if (!helper.OpenClipboard()) 
    {
        return;
    }

    suic::String text;
    helper.PasteText(text);
    _eDoc.Add(text);

    helper.CloseClipboard();

    UpdateScrollInfo(true);

    DWORD dwTime = ::GetTickCount();

    _panel.InvalidateVisual();
    dwTime = ::GetTickCount() - dwTime;

    UI_Trace(_T("Reflesh Time cose: %d\n"), dwTime);

    ResetCaretPos();
}

void TextBox::SelectAll()
{
    WndHelper(this).HideCaret();
    _eDoc.SelectAll();
    UpdateScrollInfo(false);
    _panel.InvalidateVisual();
    ResetCaretPos();
}

suic::Size TextBox::MeasureOverride(const suic::Size& size)
{
    _view.Measure(size);

    return _view.GetDesiredSize();
}

suic::Size TextBox::ArrangeOverride(const suic::Size& size)
{
    suic::Rect finalRect(0, 0, size.cx, size.cy);

    finalRect.Deflate(GetBorderThickness());

    _view.Arrange(finalRect);

    return size;
}

void TextBox::OnMenuItemSelected(suic::ObjectPtr mPtr, MenuItemPtr itemPtr)
{
    suic::String strText = itemPtr->GetText();

    if (strText.Equals(_T("剪切")))
    {
        Cut();
    }
    else if (strText.Equals(_T("复制")))
    {
        Copy();
    }
    else if (strText.Equals(_T("粘贴")))
    {
        Paste();
        Focus();
    }
    else if (strText.Equals(_T("全部选择")))
    {
        SelectAll();
    }
}

void TextBox::OnRender(suic::DrawingContext * drawing)
{
    suic::TriggerPtr trg(suic::UIRender::GetTriggerByStatus(this, GetStyle()));        
    suic::Rect rcdraw(0, 0, RenderSize().cx, RenderSize().cy);

    // 先填充背景
    suic::UIRender::DrawBackground(drawing, trg, &rcdraw);
    suic::UIRender::DrawBorderBrush(drawing, trg, &rcdraw);
}

static suic::Uint32 WCharToChar(wchar_t w, suic::Byte * asc)   
{
    DWORD dwNum = WideCharToMultiByte(CP_ACP, 0, &w, 1, NULL, 0, NULL, NULL);
    WideCharToMultiByte(CP_ACP, 0, &w, 1, (LPSTR)asc, dwNum, NULL, NULL);

    return dwNum;
}

void TextBox::OnTextInput(suic::KeyEventArg& e)
{
    if (IsReadOnly())
    {
        return;
    }

    int ch = e.GetKey();
    int code = e.State();

    union wcharfmt
    {
        suic::Char w;
        suic::Byte asc[2];
    };

    static bool bUnicode = false;
    static wcharfmt wf;

    suic::Uint32 nNum = WCharToChar((wchar_t)ch, (suic::Byte*)&wf.asc[0]);

    suic::Byte nChar = (suic::Byte)ch;

    // 这是一个双字节的编码
    if (ch >= 0x80)
    {
        _eDoc.Add(ch);
        UpdateScrollInfo(true);

        _panel.InvalidateVisual();
    }
    // 处理ascii码，注意这里可能是多字节的一部分
    else if (nChar >= 0x80)
    {
        bUnicode = true;
        wf.asc[0] = nChar;
    }
    else
    {
        if (bUnicode)
        {
            wf.asc[1] = nChar;
        }
        else
        {
            if (VK_BACK == nChar)
            {
                _eDoc.DelLeftOne();
                UpdateScrollInfo(true);
                _panel.InvalidateVisual();
            }
            //else if (VK_RETURN != nChar)
            else if (nChar >= 32 && nChar <= 126)
            {
                bool bCtrl = (code & MK_CONTROL) == MK_CONTROL;
                if (!bCtrl)
                {
                    _eDoc.Add(ch);
                    UpdateScrollInfo(true);
                    _panel.InvalidateVisual();
                }
                else if (nChar == 'v' || 
                    nChar == 'V')
                {
                    Paste();
                }
            }
        }
        bUnicode = false;
    }

    ResetCaretPos();
}

void TextBox::OnKeyDown(suic::KeyEventArg& e)
{
    if (IsReadOnly())
    {
        return;
    }

    WndHelper(this).HideCaret();

    int state = e.State();
    int ch = e.GetKey();

    bool bShift = (state & MK_SHIFT) == MK_SHIFT;
    bool bCtrl = (state & MK_CONTROL) == MK_CONTROL;

    bool bValid = true;
    bool bUpDown = false;
    bool bSel = _eDoc.IsSelectMode();

    suic::Rect oldCaret = _eDoc.GetCaret(true);

    if (VK_LEFT == ch)
    {
        bValid = _eDoc.OnLeftCaret(bShift);
    }
    else if (VK_RIGHT == ch)
    {
        bValid = _eDoc.OnRightCaret(bShift);
    }
    else if (VK_UP == ch)
    {
        bValid = _eDoc.OnUpCaret(bShift);
        bUpDown = true;
    }
    else if (VK_DOWN == ch)
    {
        bValid = _eDoc.OnDownCaret(bShift);
        bUpDown = true;
    }
    else if (VK_DELETE == ch)
    {
        _eDoc.DelRightOne();
        UpdateScrollInfo(true);
    }
    else if (VK_RETURN == ch)
    {
        if (!_isSingle)
        {
            _eDoc.InsertLine();
        }
    }
    else if (VK_ESCAPE == ch)
    {
        _eDoc.CancelSelect();
    }
    else if (VK_HOME == ch)
    {
        if (bCtrl)
        {
            bValid = _eDoc.OnDocHome(bShift);
        }
        else
        {
            bValid = _eDoc.OnLineHome(bShift);
        }
    }
    else if (VK_END == ch)
    {
        if (bCtrl)
        {
            bValid = _eDoc.OnDocEnd(bShift);
        }
        else
        {
            bValid = _eDoc.OnLineEnd(bShift);
        }
    }
    // 下一页
    else if (VK_NEXT == ch)
    {
        if (bCtrl)
        {
            bValid = _eDoc.OnVisualHome(bShift);
        }
        else
        {
            bValid = _eDoc.OnPageNext(bShift);
        }
    }
    // 上一页
    else if (VK_PRIOR == ch)
    {
        if (bCtrl)
        {
            bValid = _eDoc.OnVisualEnd(bShift);
        }
        else
        {
            bValid = _eDoc.OnPagePrior(bShift);
        }
    }
    else if (bCtrl && (ch == 'v' || ch == 'V'))
    {
        Paste();
        return;
    }
    else if (bCtrl && (ch == 'c' || ch == 'C'))
    {
        Copy();
        return;
    }
    else if (bCtrl && (ch == 'x' || ch == 'X'))
    {
        Cut();
        return;
    }
    else if (bCtrl && (ch == 'a' || ch == 'A'))
    {
        SelectAll();
        return;
    }
    else
    {
        return;
    }

    if (bValid || bSel)
    {
        UpdateScrollInfo(false);
        _panel.InvalidateVisual();
    }

    ResetCaretPos(bUpDown);
}

void TextBox::OnMouseEnter(suic::MouseEventArg& e)
{
    e.Handled(true);
}

void TextBox::OnMouseMove(suic::MouseEventArg& e)
{
    e.Handled(true);

    if (IsMouseCaptured())
    {
        WndHelper(this).HideCaret();

        suic::Rect rc(DocumentRect(PointToScreen(suic::Point())));

        suic::Point tmPt(e.MousePoint());
        tmPt.x -= rc.left;
        tmPt.y -= rc.top;
        _eDoc.TrackCaret(&tmPt);

        UpdateScrollInfo(false);

        _panel.InvalidateVisual();
        ResetCaretPos();
    }
}

void TextBox::OnMouseLeave(suic::MouseEventArg& e)
{
    suic::ElementPtr thisPtr(this);

    /*if (ui::WindowData::MouseWheel() == thisPtr)
    {
        ui::WindowData::MouseWheel(suic::ElementPtr());
    }*/
}

void TextBox::OnMouseWheel(suic::MouseWheelEventArg& e)
{
    if (!_isSingle)
    {
        _view.OnMouseWheel(e);

        e.Handled(true);
    }
}

void TextBox::OnGotFocus(suic::FocusEventArg& e)
{
    e.Handled(true);

    WndHelper(this).HideCaret();

    _panel.InvalidateVisual();

    WndHelper(this).CreateSolidCaret(1, 16);
    ResetCaretPos();
}

void TextBox::OnLostFocus(suic::FocusEventArg& e)
{
    WndHelper(this).HideCaret();
    DestroyCaret();

    _panel.InvalidateVisual();

    __super::OnLostFocus(e);
}

void TextBox::OnSetCursor(suic::CursorEventArg& e)
{
    __super::OnSetCursor(e);

    if (!e.Handled())
    {
        ::SetCursor(LoadCursor(NULL, IDC_IBEAM));
        e.Handled(true);
    }
}

void TextBox::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    SetCaptureMouse();

    e.Handled(true);

    suic::Rect rcClnt(DocumentRect(PointToScreen(suic::Point())));

    if (!rcClnt.PointIn(e.MousePoint()))
    {
        return;
    }
    WndHelper(this).HideCaret();

    int code = e.State();

    bool bShift = (code & MK_SHIFT) == MK_SHIFT;
    bool bCtrl = (code & MK_CONTROL) == MK_CONTROL;

    suic::Rect rc(rcClnt);

    suic::Point tmPt(e.MousePoint());
    tmPt.x -= rc.left;
    tmPt.y -= rc.top;
    bool bValid = false;

    if (bShift)
    {
        _eDoc.TrackCaret(&tmPt);
        bValid = true;
    }
    else if (bCtrl)
    {
        _eDoc.SelectWord(&tmPt);
        bValid = true;
    }
    else
    {
        bValid = _eDoc.SetCaret(&tmPt);
    }

    if (bValid)
    {
        UpdateScrollInfo(false);
        _panel.InvalidateVisual();
    }

    ResetCaretPos();
}

void TextBox::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    suic::Point pt(PointToScreen(suic::Point()));
    suic::Rect rc(pt.x, pt.y, RenderSize().cx, RenderSize().cy);

    suic::Point tmPt(e.MousePoint());

    tmPt.x -= rc.left;
    tmPt.y -= rc.top;

    bool bValid = _eDoc.SelectWord(&tmPt);

    if (bValid)
    {
        UpdateScrollInfo(false);
        _panel.InvalidateVisual();
    }

    ResetCaretPos();

    e.Handled(true);
}

void TextBox::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    suic::Point pt(PointToScreen(suic::Point()));
    suic::Rect rc(pt.x, pt.y, RenderSize().cx, RenderSize().cy);

    if (!rc.PointIn(e.MousePoint()))
    {
    }

    ReleaseCaptureMouse();
}

void TextBox::OnTrackingMenu(ui::MenuPtr& menu)
{

}

void TextBox::OnMouseRightButtonUp(suic::MouseEventArg& e)
{
    suic::Point pt(PointToScreen(suic::Point()));
    suic::Rect rc(pt.x, pt.y, RenderSize().cx, RenderSize().cy);

    if (rc.PointIn(e.MousePoint()))
    {
        pt = UI_ToScreenPoint(this, e.MousePoint());

        ui::MenuPtr editMenu(new Menu());
        suic::StylePtr style(FindResource(_T("TextBox.Menu")));

        if (!style)
        {
            style = FindResource(_T("Menu"));
        }

        editMenu->SetStyle(style);

        editMenu->AddText(_T("剪切"));
        editMenu->AddText(_T("复制"));
        editMenu->AddText(_T("粘贴"));
        editMenu->AddText(_T("全部选择"));

        if (!_eDoc.IsSelectMode())
        {
            suic::ElementPtr it(editMenu->GetItem(0));

            it->Enable(false);

            suic::ElementPtr it1(editMenu->GetItem(1));

            it1->Enable(false);
        }

        if (IsReadOnly())
        {
            suic::ElementPtr it(editMenu->GetItem(2));

            it->Enable(false);

            suic::ElementPtr it1(editMenu->GetItem(0));

            it1->Enable(false);
        }

        if (!_eDoc.HasContent())
        {
            suic::ElementPtr it(editMenu->GetItem(3));

            it->Enable(false);
        }

        editMenu->MenuItemClick.Add(this, &TextBox::OnMenuItemSelected);

        OnTrackingMenu(editMenu);

        Menu::TrackPopupMenu(pt.x, pt.y, editMenu);

        Focus();
    }
}

void TextBox::OnTimer(int nId)
{
    //InvalidateVisual();
}

void TextBox::OnSetterChanged(suic::SetterChangedEventArg& e)
{
    if (e.GetName().Equals(_T("MultiLine")))
    {
        _isSingle = !e.GetSetter()->ToBool();
    }
    else if (e.GetName().Equals(_T("ReadOnly")))
    {
        SetReadOnly(e.GetSetter()->ToBool());
    }
    else
    {
        __super::OnSetterChanged(e);
    }
}

void TextBox::OnInitialized()
{
    __super::OnInitialized();

    AddVisualChild(&_view);
    _view.SetContent(&_panel);

    _view.BeginInit();
    _view.EndInit();

    if (!_isSingle)
    {
        _eDoc.SetSingleLine(false);
        _view.SetScrollBarVisibility(ScrollViewer::Auto);
    }
    else
    {
        _eDoc.SetSingleLine(true);
        _view.SetScrollBarVisibility(ScrollViewer::Hidden);
    }
}

void TextBox::ResetCaretPos(bool bUpDown)
{
    if (IsFocused())
    {
        ui::WndHelper helper(this);

        helper.HideCaret();

        suic::Point pt = PointToScreen(suic::Point());
        suic::Rect rc(DocumentRect(suic::Point()));
        suic::Rect rcCaret = _eDoc.GetCaret(bUpDown);

        rc.Offset(pt.x, pt.y);

        //
        // 去除父窗口裁剪区域
        //
        suic::Element* pParent = GetParent();
        while (pParent)
        {
            suic::Rect tmp = suic::VisualHelper::GetRenderRect(pParent);

            rc.Intersect(&tmp);
            pParent = pParent->GetParent();
        }

        rc.Offset(-pt.x, -pt.y);

        if (rcCaret.left < 0 || rcCaret.left > rc.Width() ||
            rcCaret.bottom < 0 || rcCaret.top > rc.Height())
        {
            helper.HideCaret();
            return;
        }

        rcCaret.left += rc.left;

        if (_isSingle)
        {
            int iCaretHei = rcCaret.Height();
            int iClientHei = _eDoc.GetVisualRect().Height();

            rcCaret.top = GetPadding().top + GetBorderThickness().top + 2;
            rcCaret.bottom = RenderSize().cy - GetPadding().bottom - GetBorderThickness().bottom - 2;
        }
        else
        {
            rcCaret.top += rc.top;
            rcCaret.bottom += rc.top;
        }

        if (rcCaret.top < rc.top)
        {
            rcCaret.top = rc.top;
        }

        if (rcCaret.bottom > rc.bottom)
        {
            rcCaret.bottom = rc.bottom;
        }

        //SetCaretBlinkTime
        helper.CreateSolidCaret(1, rcCaret.Height());
        helper.SetCaretPos(rcCaret.left, rcCaret.top);
        helper.ShowCaret();
    }
}

void TextBox::UpdateScrollInfo(bool bUpdate)
{
    int iVert = _eDoc.GetVertScrollPos();
    int iHorz = _eDoc.GetHorzScrollPos();

    _view.SetHorizontalStep(_eDoc.GetCharWid());
    _view.SetVerticalStep(_eDoc.GetCharHei());

    if (bUpdate)
    {
        _view.InvalidateMeasure();
        _view.InvalidateArrange();
    }

    _view.ScrollToVerticalOffset(iVert);
    _view.ScrollToHorizontalOffset(iHorz);

    _eDoc.SetVertScrollPos(_view.VerticalVisualPos());
    _eDoc.SetHorzScrollPos(_view.HorizontalVisualPos());

    _view.InvalidateScrollBar();
}

}
 
