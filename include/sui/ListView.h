// 华勤科技版权所有 2010-2011
// 
// 文件名：ListView.h
// 功  能：实现标准的ListView控件
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UILISTVIEW_H_
# define _UILISTVIEW_H_

#include <sui/sharpuiconfig.h>
#include <sui/listbox.h>
#include <sui/GridViewHeaderRow.h>
#include <sui/listviewitem.h>

namespace ui
{

/// <summary>
/// 实现标准的列表框
/// </summary>
class SHARPUI_API ListView : public ListBox
{
public:

    ListView();
    virtual ~ListView();

    DECLAREBUILD(ListView);

    ColumnHeaderCollectionPtr& Columns();

    int Add(suic::ObjectPtr value);
    int Insert(int index, suic::ObjectPtr value);
    int AddText(const suic::String& text);

    void SetLargeImageList();
    void SetSmallImageList();

    int GetHeaderStyle() const;
    void SetHeaderStyle(int iStyle);

    void SetBackgroundImage(suic::ImagePtr img);

    void OnColumnHeaderResize(suic::ObjectPtr sender, DragDeltaEventArg& e);
    void OnColumnHeaderChanged(GridViewColumn* pColumn, int flag);

protected:

    void CheckAddingItem(suic::ObjectPtr& itemObj);
    int GetVisualEndIndex();

    void InitializeScrollView();

    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

    void OnInitialized();

protected:

    GridViewHeaderRowPtr _header;
};

typedef suic::shared<ListView> ListViewPtr;

};

# endif
