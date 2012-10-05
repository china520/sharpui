// 华勤科技版权所有 2010-2011
// 
// 文件名：Menu.h
// 功  能：实现标准的Menu控件
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UIMENU_H_
# define _UIMENU_H_

#include <sui/sharpuiconfig.h>
#include <sui/selector.h>
#include <sui/MenuItem.h>

namespace ui
{

// ============================================================================
// Menu，实现标准的列表框。
// ============================================================================

class Menu;
typedef suic::shared<Menu> MenuPtr;

class SHARPUI_API Menu : public Selector
{
public:

    MenuItemClickEventHandler MenuItemClick;

    Menu();
    virtual ~Menu();

    DECLAREBUILD(Menu)

    static int TrackPopupMenu(int x, int y, MenuPtr menu);
    static void AddSubMenu(MenuItemPtr item, MenuPtr subMenu);

    MenuItemPtr GetMenuItem(int index);
    int AddText(const suic::String& text);

public:

    virtual suic::Size MeasureOverride(const suic::Size& size);
    virtual suic::Size ArrangeOverride(const suic::Size& size);

    virtual void OnItemLeftButtonDown(MenuItem* item, suic::MouseEventArg& e);

    virtual void OnInitialized();

    virtual void OnRender(suic::DrawingContext * drawing);

    virtual void OnTextInput(suic::KeyEventArg& e);
    virtual void OnKeyDown(suic::KeyEventArg& e);

    virtual void OnGotFocus(suic::FocusEventArg& e);
    virtual void OnLostFocus(suic::FocusEventArg& e);
    virtual void OnSetCursor(suic::CursorEventArg& e);

    virtual void OnMouseEnter(suic::MouseEventArg& e);
    virtual void OnMouseMove(suic::MouseEventArg& e);
    virtual void OnMouseLeave(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonDown(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonDbclk(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonUp(suic::MouseEventArg& e);

    virtual void OnSelectionChanged(SelectionChangedEventArg& e);

protected:

    MenuItemPtr _currentSelection;
};

};

# endif