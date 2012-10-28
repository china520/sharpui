//////////////////////////////////////////////////////////////////////////////
// ComboBox.cpp

#include <sui/ComboBox.h>
#include <suicore/drawing/uirender.h>
#include <suicore/uipopup.h>
#include <suicore/hwndhelper.h>

#include <animation/DoubleAnimation.h>
#include <animation/StoryBoard.h>

namespace ui
{

/// <summary>
///  组合框下拉列表，处理鼠标事件
/// </summary>
class ComboBoxListBox : public ListBox
{
public:

    ComboBoxListBox()
    {
        //SetClassName(suic::COMBOBOXLISTBOX);
    }

    void OnMouseLeftButtonUp(suic::MouseEventArg& e)
    {
        __super::OnMouseLeftButtonUp(e);

        suic::HwndHelper::CloseWindow(this);
    }

    virtual void OnMouseMove(suic::MouseEventArg& e)
    {
        if (e.LeftButton() != suic::eMousePress)
        {
            if (IsMouseCaptured())
            {
                suic::HwndHelper::CloseWindow(this);
            }
            return;
        }

        __super::OnMouseMove(e);
    }
};

/// <summary>
///  组合框适配项，可加入任意类型元素
/// </summary>
ComboBoxItem::ComboBoxItem()
{
    SetClassName(_T("ComboBoxItem"));
    SetHorizontalContentAlignment(suic::LEFT);
}

ComboBoxItem::~ComboBoxItem()
{
}

void ComboBoxItem::OnSetterChanged(suic::SetterChangedEventArg& e)
{
    __super::OnSetterChanged(e);
}

void ComboBoxItem::OnMouseMove(suic::MouseEventArg& e)
{
    __super::OnMouseMove(e);

    ComboBoxListBox* pParent = dynamic_cast<ComboBoxListBox*>(LogicalParent());

    if (pParent)
    {
        if (e.LeftButton() == suic::eMousePress)
        {
            pParent->SetCaptureMouse();
        }
    }
}

void ComboBoxItem::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    suic::Element::OnMouseLeftButtonDown(e);

    if (!e.Handled())
    {
        Selector::SelectItem(this, true);

        InvalidateVisual();
        e.Handled(true);
    }
}

void ComboBoxItem::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    suic::Control::OnMouseLeftButtonUp(e);

    ComboBoxListBox* pParent = dynamic_cast<ComboBoxListBox*>(LogicalParent());

    if (pParent)
    {
        pParent->OnMouseLeftButtonUp(e);
    }
}

void ComboBoxItem::OnRender(suic::DrawingContext * drawing)
{
    suic::StylePtr sty(GetStyle());

    if (IsEnabled() && (ReadFlag(CoreFlags::IsSelected) || IsMouseOver()))
    {
        suic::TriggerPtr trg = sty->GetTrigger(suic::FOCUSED);

        if (!trg)
        {
            trg = GetStyle()->GetTrigger(_T(""));
        }

        if (trg)
        {
            suic::Render::Draw(drawing, this, trg);
        }
    }
    else
    {
        suic::Control::OnRender(drawing);
    }
}

//================================================================
// DropDownEventArg
//
DropDownEventArg::DropDownEventArg(suic::PopupPtr popup, suic::ElementPtr list)
    : _popup(popup)
    , _list(list)
{
    ;
}

///////////////////////////////////////////////////////
// ComboListHookPopup
//
class ComboListHookPopup : public suic::HwndSourceHookSystemPopup
{
public:

    ComboListHookPopup(suic::UIPopup* pPopup)
        : suic::HwndSourceHookSystemPopup(pPopup)
    {
    }

    bool OnFilterMessage(suic::ObjectPtr sender, suic::MessageParameter& mp)
    {
        if (WM_LBUTTONUP == mp.message)
        {
            ComboBoxListBox* pList = dynamic_cast<ComboBoxListBox*>(_popup->GetPopupRoot().get());

            if (pList)
            {
                suic::ElementPtr selObj = suic::ElementPtr::cast(pList->SelectedItem());

                if (selObj && selObj->IsEnabled())
                {
                    _popup->Close();
                }
            }
        }

        return __super::OnFilterMessage(sender, mp);
    }
};

//////////////////////////////////////////////////////////
// ComboBox
//
ComboBox::ComboBox()
    : _bReadOnly(false)
    , _downHeight(16)
{
    SetClassName(_T("ComboBox"));
    _popup = new suic::UIPopup();
    _list = new ComboBoxListBox();

    _textBox = new TextBox();
    _items = _list->GetItems();

    // 支持鼠标传递绘制
    WriteFlag(CoreFlags::IsSupportMouseOver, true);
}

ComboBox::~ComboBox()
{
}

int ComboBox::AddText(const suic::String& text)
{
    ComboBoxItem* item(new ComboBoxItem());

    item->SetText(text);

    return _list->AddChild(item);
}

int ComboBox::AddChild(suic::ObjectPtr child)
{
    return _list->AddChild(child);
}

void ComboBox::ClearChildren()
{
    _list->ClearChildren();
}

void ComboBox::SetReadOnly(bool bOnly)
{
    _bReadOnly = bOnly;
}

bool ComboBox::IsReadOnly() const
{
    return _bReadOnly;
}

bool ComboBox::IsDropDown() const
{
    return (!_popup->IsClosed());
}

void ComboBox::SetDropDownHeight(int height)
{
    _downHeight = height;
}

void ComboBox::SetText(const suic::String & text)
{
    _textBox->SetText(text);
}

suic::String ComboBox::GetText()
{
    return _textBox->GetText();
}

bool ComboBox::StaysOpenOnEdit() const
{
    return !_popup->IsClosed();
}

suic::Size ComboBox::MeasureOverride(const suic::Size& size)
{
    suic::Size ret = suic::Control::MeasureOverride(size);

    _textBox->Measure(size);

    return ret;
}

suic::Size ComboBox::ArrangeOverride(const suic::Size& size)
{
    suic::Rect rect(0, 0, size.cx, size.cy);

    rect.right -= size.cy;

    rect.top = (rect.Height() - _textBox->GetDesiredSize().cy) >> 1;
    rect.bottom = rect.top + _textBox->GetDesiredSize().cy;

    rect.Deflate(GetBorderThickness());
    rect.Deflate(GetPadding());

    _textBox->Arrange(rect);

    return size;
}

void ComboBox::OnInitialized()
{
    // 
    // 调用基类进行事件分发处理
    //
    __super::OnInitialized();

    AddVisualChild(_textBox.get());

    const suic::String COMBOBOXTEXTBOX = _T("ComboBox.TextBox");
    
    _textBox->SetClassName(COMBOBOXTEXTBOX);
    _textBox->SetOwner(this);

    suic::StylePtr style = FindResource(suic::COMBOBOXLISTBOX);

    if (!style)
    {
        _list->SetStyle(style);
    }

    _list->SetStyle(style);

    _textBox->BeginInit();
    _textBox->EndInit();

    _list->BeginInit();
    _list->EndInit();

    _list->SetMaxHeight(_downHeight);
    _textBox->Enable(IsEnabled());

    _textBox->CursorSet += suic::CursorEventHandler(this, &ComboBox::OnTextBoxCursor);
    _list->SelectionChanged += SelectionChangedHandler(this, &ComboBox::OnSelectionChanged);

    suic::ObjectPtr selObj = _list->SelectedItem();

    if (selObj)
    {
        _textBox->SetText(selObj->ToString());
        _list->UnselectAllItems();
    }
}

void ComboBox::OnStyleUpdated()
{
    _list->UpdateStyle();
}

void ComboBox::OnSetterChanged(suic::SetterChangedEventArg& e)
{
    if (e.GetName().Equals(_T("ReadOnly")))
    {
        _bReadOnly = e.GetSetter()->ToBool();
        _textBox->SetReadOnly(_bReadOnly);
    }
    else if (e.GetName().Equals(_T("DropDownHeight")))
    {
        _downHeight = e.GetSetter()->ToInt32();
    }
    else
    {
        //
        // 必须调用基类初始化基本数据
        //
        __super::OnSetterChanged(e);
    }
}

//////////////////////////////////////////////////////////////////////////////
// ComboBox

void ComboBox::OnRender(suic::DrawingContext * drawing)
{
    suic::StylePtr styleArrow = FindResource(_T("ComboBox.Down"));

    suic::Point pt;
    suic::Rect drawrect(pt.x, pt.y, RenderSize().cx, RenderSize().cy);

    // 
    // 先绘制背景
    //
    suic::TriggerPtr bksetter;

    if (IsDropDown())
    {
        bksetter = GetStyle()->GetTrigger(suic::PRESSED);
    }

    if (!bksetter)
    {
        bksetter = suic::Render::GetTriggerByStatus(this, GetStyle());
    }

    suic::Render::DrawBackground(drawing, bksetter, &drawrect);

    // 获取下拉箭头的设置
    if (styleArrow.get())
    {
        suic::TriggerPtr downSet(suic::Render::GetTriggerByStatus(this, styleArrow));
        suic::Rect downRect = drawrect;

        downRect.Deflate(GetBorderThickness());
        downRect.left = downRect.right - 16;

        suic::Render::DrawBackground(drawing, downSet, &downRect);
    }

    suic::Render::DrawBorderBrush(drawing, bksetter, &drawrect);
}

void ComboBox::OnKeyDown(suic::KeyEventArg& e)
{
    if (e.IsUpArrow() || e.IsDownArrow())
    {
        _list->OnKeyDown(e);
    }
    else
    {
        _textBox->OnKeyDown(e);
    }
}

void ComboBox::OnTextInput(suic::KeyEventArg& e)
{
    _textBox->OnTextInput(e);
}

void ComboBox::OnTextBoxCursor(suic::Element*, suic::CursorEventArg& e)
{
    if (_textBox->IsReadOnly())
    {
        e.Handled(true);
    }
}

void ComboBox::OnDropDownClosed(DropDownEventArg& e)
{
    TriggerEvent(DropDownClosed, e);
}

void ComboBox::OnDropDownOpened(DropDownEventArg& e)
{
    TriggerEvent(DropDownOpened, e);
}

void ComboBox::OnPreviewSetCursor(suic::CursorEventArg& e)
{
    if (_bReadOnly)
    {
        e.Handled(true);
    }
}

void ComboBox::OnPreviewMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    if (_textBox->IsReadOnly())
    {
        OnMouseLeftButtonDown(e);
    }
}

void ComboBox::OnPreviewMouseLeftButtonDown(suic::MouseEventArg& e)
{
    if (_textBox->IsReadOnly())
    {
        OnMouseLeftButtonDown(e);
    }
}

void ComboBox::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDown(e);

    if (_popup->IsValid())
    {
        _popup->Close();
    }
    else
    {
        suic::Point point = suic::SystemHelper::CalcScreenElementPoint(this, CoreFlags::eLeftBottom);

        suic::Size availableSize;
        int iWid = RenderSize().cx;

        _list->Measure(availableSize);
        _popup->SetWidth(iWid);

        if (_list->GetDesiredSize().cy > _downHeight
            || _list->GetDesiredSize().cy <= 16)
        {
            _popup->SetHeight(_downHeight);
        }
        else
        {
            int iHei = _list->GetDesiredSize().cy 
                + _list->GetBorderThickness().top
                + _list->GetBorderThickness().bottom;

            _popup->SetHeight(iHei);
        }

        _popup->SetOwner(this);
        _popup->SetPopupRoot(_list.get());

        DropDownEventArg eo(_popup, _list);

        OnDropDownOpened(eo);

        _popup->TrackingPopup(point.x, point.y, false, 0, 0, new ComboListHookPopup(_popup));

        suic::ObjectPtr selObj = _list->SelectedItem();

        if (selObj)
        {
            SelectionChangedEventArg e;

            e.AddedItems()->Add(selObj);
            OnSelectionChanged(e);
        }

        _list->UnselectAllItems();

        OnDropDownClosed(eo);

        if (!_textBox->IsReadOnly() && _textBox->IsEnabled())
        {
            _textBox->Focus();
        }
    }
}

void ComboBox::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonUp(e);

    InvalidateVisual();

    //
    // 下拉框已经打开并且已获取鼠标控制权，传递事件
    //
    if (IsDropDown() && _list->IsMouseCaptured())
    {
        _list->OnMouseLeftButtonUp(e);
    }
}

void ComboBox::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    OnMouseLeftButtonDown(e);
}

void ComboBox::OnPreviewMouseEnter(suic::MouseEventArg& e)
{
}

void ComboBox::OnPreviewMouseMove(suic::MouseEventArg& e)
{
    if (e.LeftButton() == suic::MouseButtonState::eMousePress)
    {
        if (suic::VisualHelper::CursorPointIsInElement(_list.get()))
        {
            _list->OnMouseLeftButtonDown(e);
        }
    }
}

void ComboBox::OnSetCursor(suic::CursorEventArg& e)
{
}

void ComboBox::OnGotFocus(suic::FocusEventArg& e)
{
    _textBox->OnGotFocus(e);
}

void ComboBox::OnLostFocus(suic::FocusEventArg& e)
{
    _textBox->OnLostFocus(e);
}

void ComboBox::OnSelectionChanged(SelectionChangedEventArg& e)
{
    if (e.AddedItems()->GetCount() > 0)
    {
        _textBox->SetText(e.AddedItems()->GetAt(0)->ToString());

        if (_textBox->IsReadOnly() || !_textBox->IsEnabled() || StaysOpenOnEdit())
        {
            _textBox->InvalidateVisual();
        }
        else
        {
            _textBox->Focus();
        }
    }
}

}
