// 华勤科技版权所有 2010-2011
// 
// 文件名：ListBoxItem.h
// 功  能：实现Item的基类
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UILISTBOXITEM_H_
# define _UILISTBOXITEM_H_

#include <sui/sharpuiconfig.h>
#include <suic/framework/uicontentcontrol.h>

namespace ui
{

class SHARPUI_API ListBoxItem : public suic::ContentControl
{
public:

    ListBoxItem();
    virtual ~ListBoxItem();

    DeclareTypeofInfo(ListBoxItem, suic::ContentControl)

protected:

    void OnPropertyChanged(suic::PropertyChangedEventArg& e);

    void OnRender(suic::DrawingContext * drawing);

    void OnMouseLeftButtonDown(suic::MouseEventArg& e);
    void OnMouseLeftButtonUp(suic::MouseEventArg& e);
};

typedef suic::shared<ListBoxItem> ListBoxItemPtr;

};

# endif
