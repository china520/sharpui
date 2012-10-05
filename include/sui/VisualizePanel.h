// 华勤科技版权所有 2010-2011
// 
// 文件名：VisualizePanel.h
// 功  能：实现轻量级的元素布局器，支持滚筒条
// 
// 作  者：汪荣
// 时  间：2011-08-31
// 
// ============================================================================

# ifndef _UIVISUALIZEPANEL_H_
# define _UIVISUALIZEPANEL_H_

#include <sui/sharpuiconfig.h>
#include <suicore/uipanel.h>
#include <sui/itemcontainer.h>

namespace ui
{

// ============================================================================
// VisualizePanel。
// ============================================================================

class SHARPUI_API VisualizePanel : public suic::Panel
{
public:

    VisualizePanel(ItemContainerPtr container);
    virtual ~VisualizePanel();

protected:

    virtual void OnInitialized();
    virtual void OnRender(suic::DrawingContext * drawing);

    virtual suic::Size MeasureOverride(const suic::Size& size);
    virtual suic::Size ArrangeOverride(const suic::Size& size);

protected:

    suic::Size ArrangeHorizontal(const suic::Size& size);
    suic::Size ArrangeVertical(const suic::Size& size, int iOffset);

protected:

    ItemContainerPtr _container;
};

typedef suic::shared<VisualizePanel> VisualizePanelPtr;

class SHARPUI_API VisualizeHeaderPanel : public VisualizePanel
{
public:

    VisualizeHeaderPanel(ItemContainerPtr container);

    suic::FrameworkElementPtr GetHeader();
    void SetHeader(suic::FrameworkElementPtr val);

protected:

    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

protected:

    suic::FrameworkElementPtr _header;
};

typedef suic::shared<VisualizeHeaderPanel> VisualizeHeaderPanelPtr;

}

# endif
