// 华勤科技版权所有 2010-2011
// 
// 文件名：FileWindow.h
// 功  能：实现存储、打开对话框。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIFILEGROWSER_H_
# define _UIFILEGROWSER_H_

#include <sui/sharpuiconfig.h>
#include <suic/framework/uicontrol.h>

namespace ui
{

class SHARPUI_API FileBrowser : public suic::Control
{
public:

    FileBrowser(bool bDel=false);

    virtual ~FileBrowser();

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
