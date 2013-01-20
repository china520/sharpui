// 华勤科技版权所有 2010-2011
// 
// 文件名：GridViewRow.h
// 功  能：实现GridViewRow
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UIGRIDVIEWROW_H_
# define _UIGRIDVIEWROW_H_

#include <sui/sharpuiconfig.h>
#include <sui/GridViewColumn.h>

namespace ui
{

/// <summary>
/// GridViewRow
/// </summary>
class SHARPUI_API GridViewRow : public suic::FrameworkElement
{
public:

    GridViewRow(ColumnHeaderCollectionPtr& colomns);
    virtual ~GridViewRow();

    void AddColumn(suic::ObjectPtr item);
    void SetColumn(int index, suic::ObjectPtr item);
    suic::ObjectPtr GetColumn(int index);

protected:

    suic::Element* GetLogicalChild(int index);
    suic::Int32 GetLogicalChildrenCount();

    suic::Size MeasureOverride(const suic::Size& availableSize);
    suic::Size ArrangeOverride(const suic::Size& size);

    void OnInitialized();
    void OnRender(suic::DrawingContext * drawing);

protected:

    // 列信息
    ColumnHeaderCollectionPtr _colomns;
    suic::Vector<suic::ElementPtr> _cells;
};

typedef suic::shared<GridViewRow> GridViewRowPtr;

};

# endif
