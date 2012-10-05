// 华勤科技版权所有 2010-2011
// 
// 文件名：FileWindow.h
// 功  能：实现存储、打开对话框。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIFILEWINDOW_H_
# define _UIFILEWINDOW_H_

#include <sui/sharpuiconfig.h>
#include <suicore/uicontrol.h>

namespace ui
{

class SHARPUI_API FileWindow : public suic::Control
{
public:

    FileWindow(bool bDel=false);

    virtual ~FileWindow();

    bool Open(const suic::String& filter=_T("All\0*.*\0"));
    bool Save(const suic::String& filter=_T("All\0*.*\0"));

    suic::String GetFilePath() const;

protected:

    virtual void OnRender(suic::DrawingContext * drawing);

    bool InternalOpen(bool bOpen, const suic::String& filter=_T("All\0*.*\0"));

protected:

    suic::String _path;

};

};

# endif
