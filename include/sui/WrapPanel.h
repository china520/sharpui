// 华勤科技版权所有 2010-2011
// 
// 文件名：WrapPanel.h
// 功  能：控件布局管理，支持对子窗体的自动布局。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIWARPPANEL_H_
# define _UIWARPPANEL_H_

#include <sui/sharpuiconfig.h>
#include <suicore/uipanel.h>
#include <sui/scrollbar.h>

namespace ui
{

class SHARPUI_API WrapPanel : public suic::Panel
{
public:

    WrapPanel();
    virtual ~WrapPanel();

    DECLAREBUILD(WrapPanel)

    void SetItemWidth(int val);
    void SetItemHeight(int val);

    int GetItemWidth() const;
    int GetItemHeight() const;

    void SetHorizontalSpace(int val);
    void SetVerticalSpace(int val);

    int GetHorizontalSpace() const;
    int GetVerticalSpace() const;

protected:

    virtual suic::Size MeasureOverride(const suic::Size& size);
    virtual suic::Size ArrangeOverride(const suic::Size& size);

protected:

    int _horizontalSpace;
    int _verticalSpace;

    int _itemWidth;
    int _itemHeight;

    ScrollBarPtr _hScroll;
    ScrollBarPtr _vScroll;
};

typedef suic::shared<WrapPanel> FlowLayoutPtr;

inline void WrapPanel::SetItemWidth(int val)
{
    _itemWidth = val;
}

inline void WrapPanel::SetItemHeight(int val)
{
    _itemHeight = val;
}

inline int WrapPanel::GetItemWidth() const
{
    return _itemWidth;
}

inline int WrapPanel::GetItemHeight() const
{
    return _itemHeight;
}

inline void WrapPanel::SetHorizontalSpace(int val)
{
    _horizontalSpace = val;
}

inline void WrapPanel::SetVerticalSpace(int val)
{
    _verticalSpace = val;
}

inline int WrapPanel::GetHorizontalSpace() const
{
    return _horizontalSpace;
}

inline int WrapPanel::GetVerticalSpace() const
{
    return _verticalSpace;
}

}

# endif
