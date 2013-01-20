// 华勤科技版权所有 2010-2011
// 
// 文件名：HeaderItemsControl.h
// 功  能：带有头和内容的控件
// 
// 作  者：汪荣
// 时  间：2011-12-25
// 
// ============================================================================

# ifndef _UIHEADERITEMSCONTROL_H_
# define _UIHEADERITEMSCONTROL_H_

#include <sui/sharpuiconfig.h>
#include <sui/itemscontrol.h>

namespace ui
{

/// <summary>
/// HeaderItemsControl所有选择项的基类。
/// </summary>
class SHARPUI_API HeaderedItemsControl : public ItemsControl
{
public:

    HeaderedItemsControl();
    virtual ~HeaderedItemsControl();

    DeclareTypeofInfo(HeaderedItemsControl, ItemsControl)

    void SetText(const suic::String & text);
    suic::String GetText();

// 属性访问定义
public:

    suic::ElementPtr GetHeader() const;
    void SetHeader(suic::ElementPtr val);

public:

    int AddChild(suic::ObjectPtr child);

    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

    void OnInitialized();
    void OnRender(suic::DrawingContext * drawing);

    void OnPropertyChanged(suic::PropertyChangedEventArg& e);
    void OnHeaderChanged(suic::Element* oldHeader, suic::Element* newHeader);

    void OnPreviewMouseLeftButtonDown(suic::MouseEventArg& e);

protected:

    void InitializeScrollView();

protected:

    // Header的布局器
    suic::PanelPtr _headerHost;
    suic::FrameworkElementPtr _header;
};

typedef suic::shared<HeaderedItemsControl> HeaderedItemsControlPtr;

}

# endif
