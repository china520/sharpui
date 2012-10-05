// 华勤科技版权所有 2010-2011
// 
// 文件名：ListViewItem.h
// 功  能：实现标准的ListView控件的子项
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UILISTVIEWITEM_H_
# define _UILISTVIEWITEM_H_

#include <sui/sharpuiconfig.h>
#include <sui/listbox.h>

namespace ui
{

class ListViewItem : public ListBoxItem
{
public:

    ListViewItem();
    ~ListViewItem();

    DECLAREBUILD(ListViewItem)

    suic::String ToString();

    suic::ElementPtr GetColumn(int index);

    void AddColumn(suic::String text);
    void AddColumn(suic::Element* elem);

    void SetColumn(int index, suic::String text);
    void SetColumn(int index, suic::Element* elem);
};

typedef suic::shared<ListViewItem> ListViewItemPtr;

};

# endif
