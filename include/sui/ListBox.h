// 华勤科技版权所有 2010-2011
// 
// 文件名：ListBox.h
// 功  能：实现Item的基类
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UILISTBOX_H_
# define _UILISTBOX_H_

#include <sui/sharpuiconfig.h>
#include <sui/selector.h>
#include <sui/listboxitem.h>

namespace ui
{

/// <summary>
/// 实现标准的列表框，其子项由ListBoxItem进行包装
/// </summary>
class SHARPUI_API ListBox : public Selector
{
public:

    enum eSelectionMode 
    {
        Single,
        Multiple,
        Extended
    };

    ListBox();
    virtual ~ListBox();

    DECLAREBUILD(ListBox);

    int AddText(const suic::String& text);

protected:

    void CheckAddingItem(suic::ObjectPtr& itemObj);

public:

    virtual void OnInitialized();
    virtual void OnUnloaded(suic::LoadedEventArg& e);

    virtual void OnRender(suic::DrawingContext * drawing);
    virtual void OnTimer(int iTimerId);

    virtual void OnTextInput(suic::KeyEventArg& e);
    virtual void OnKeyDown(suic::KeyEventArg& e);

    virtual void OnGotFocus(suic::FocusEventArg& e);
    virtual void OnLostFocus(suic::FocusEventArg& e);

    virtual void OnMouseMove(suic::MouseEventArg& e);
    virtual void OnMouseWheel(suic::MouseWheelEventArg& e);

    virtual void OnMouseLeftButtonDown(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonUp(suic::MouseEventArg& e);

    virtual void OnItemSelected(suic::ObjectPtr item, ItemSelectionEventArg& e);

protected:

    suic::TimerIdentityPtr _timerid;
};

typedef suic::shared<ListBox> ListBoxPtr;

};

# endif
