// 华勤科技版权所有 2010-2011
// 
// 文件名：GridViewHeaderRow.h
// 功  能：实现GridViewHeaderRow
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UIGRIDVIEWHEADERROW_H_
# define _UIGRIDVIEWHEADERROW_H_

#include <sui/sharpuiconfig.h>
#include <sui/GridViewColumn.h>

namespace ui
{

// ==============================================================
// GridViewHeaderRow。
// ==============================================================

class SHARPUI_API GridViewHeaderRow : public suic::FrameworkElement
{
public:

    GridViewHeaderRow();
    virtual ~GridViewHeaderRow();

    ColumnHeaderCollectionPtr& Columns();

    int GetColumnCount() const;
    GridViewColumn* GetColumn(int index);

protected:

    suic::Size MeasureOverride(const suic::Size& availableSize);
    suic::Size ArrangeOverride(const suic::Size& size);

    void OnInitialized();
    void OnRender(suic::DrawingContext * drawing);

protected:

    // 列信息
    ColumnHeaderCollectionPtr _colomns;
};

typedef suic::shared<GridViewHeaderRow> GridViewHeaderRowPtr;

};

# endif
