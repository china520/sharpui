// 华勤科技版权所有 2010-2011
// 
// 文件名：GridViewColumn.h
// 功  能：实现GridViewColumn
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UIGRIDVIEWCOLOMN_H_
# define _UIGRIDVIEWCOLOMN_H_

#include <sui/sharpuiconfig.h>
#include <sui/GridViewColumnHeader.h>

namespace ui
{

// ============================================================================
// GridViewColumn。
// ============================================================================

class SHARPUI_API GridViewColumn : public suic::RefObject
{
public:

    DragDeltaHandler DragDelta;

    GridViewColumn();
    virtual ~GridViewColumn();

    GridViewColumnHeader* ColumnHeader();

    int GetActualIndex() const;
    void SetActualIndex(int index);

    int GetColumnWidth() const;
    void SetColumnWidth(int index);

    int GetColumnDesired() const;
    void SetColumnDesired(int val);

    void OnHeaderGripperStarted(suic::Element* sender, suic::MouseEventArg& e);
    void OnHeaderGripperResize(suic::Element* sender, suic::MouseEventArg& e);
    void OnHeaderGripperCompleted(suic::Element* sender, suic::MouseEventArg& e);

protected:

    // 实际列的索引
    int _actualIndex;
    int _columnWidth;
    int _columnDesired;

    int _prevWidth;
    suic::Point _point;
    // 显示列
    GridViewColumnHeaderPtr _header;
};

typedef suic::shared<GridViewColumn> GridViewColumnPtr;

inline int GridViewColumn::GetColumnWidth() const
{
    return _columnWidth;
}

inline void GridViewColumn::SetColumnWidth(int index)
{
    _columnWidth = index;
}

inline int GridViewColumn::GetColumnDesired() const
{
    return _columnDesired;
}

inline void GridViewColumn::SetColumnDesired(int val)
{
    _columnDesired = val;
}

typedef delegate<void(GridViewColumn*,int)> ColumnHeaderChangedHandler;

class SHARPUI_API ColumnHeaderCollection : public suic::RefObject
{
public:

    ColumnHeaderCollection();

    ColumnHeaderChangedHandler ColumnHeaderChanged;

    void Add(GridViewColumn* pColumn, int wid);
    void Add(suic::String text, int wid);

    void Remove(GridViewColumn* pColumn);
    int GetCount() const;

    GridViewColumn* GetColumn(int index);

    void Clear();

protected:

    suic::Vector<GridViewColumnPtr> _colomns;
};

typedef suic::shared<ColumnHeaderCollection> ColumnHeaderCollectionPtr;

}

# endif
