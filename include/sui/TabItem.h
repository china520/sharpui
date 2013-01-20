// 华勤科技版权所有 2010-2011
// 
// 文件名：TabItem.h
// 功  能：实现Tab控件项。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UITABITEM_H_
# define _UITABITEM_H_

#include <sui/sharpuiconfig.h>
#include <sui/itemcontainer.h>
#include <sui/HeaderedContentControl.h>

namespace ui
{

// ========================================================
// 所有容器界面元素类的基类，从此类派生的控件都具备布局能力.
//
class SHARPUI_API TabItem : public suic::ContentControl
{
public:

    TabItem();
    virtual ~TabItem();

    DeclareTypeofInfo(TabItem, suic::ContentControl)

    suic::ElementPtr FindName(const suic::String& strName);

    suic::ElementPtr GetTabContent();
    void SetTabContent(suic::ElementPtr elem);

public:

    int AddChild(suic::ObjectPtr child);
   
    void OnInitialized();
    void OnLoaded(suic::LoadedEventArg& e);

    void OnStyleUpdated();

    void OnPropertyChanged(suic::PropertyChangedEventArg& e);
    void OnTabContentChanged(suic::Element* oldVal, suic::Element* newVal);

    void OnRender(suic::DrawingContext * drawing);

    void OnMouseEnter(suic::MouseEventArg& e);
    void OnMouseMove(suic::MouseEventArg& e);
    void OnMouseLeave(suic::MouseEventArg& e);

    void OnPreviewMouseLeftButtonDown(suic::MouseEventArg& e);
    void OnMouseLeftButtonDown(suic::MouseEventArg& e);
    void OnMouseLeftButtonUp(suic::MouseEventArg& e);

    void OnGotFocus(suic::FocusEventArg& e);

protected:

    suic::ElementPtr _tabContent;
};

typedef SHARPUI_API suic::shared<TabItem> TabItemPtr;

inline suic::ElementPtr TabItem::GetTabContent()
{
    return _tabContent;
}

};

# endif
