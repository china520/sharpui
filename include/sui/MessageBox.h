// 华勤科技版权所有 2010-2011
// 
// 文件名：MessageBox.h
// 功  能：实现消息提示框。
// 
// 作  者：汪荣
// 时  间：2012-08-02
// 
// ============================================================================

# ifndef _UIMESSAGEBOX_H_
# define _UIMESSAGEBOX_H_

#include <sui/sharpuiconfig.h>
#include <suicore/uiwindow.h>

namespace ui
{

/// <summary>
/// 消息提示框
/// </summary>
class SHARPUI_API MsgBox : public suic::Window
{
public:

    enum { OK, YES, NO, }; 

    static int Show(const suic::String& title, const suic::String& msg);
    static int Show(const suic::String& title, const suic::String& msg, int flag);

    static int Show(const suic::String& title, const suic::Object* msg);
    static int Show(const suic::String& title, const suic::Object* msg, int flag);

protected:

    MsgBox();
    virtual ~MsgBox();

protected:

    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

    void OnRender(suic::DrawingContext * drawing);
};

}

# endif
