// 华勤科技版权所有 2010-2011
// 
// 文件名：FileWindow.h
// 功  能：实现存储、打开对话框。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIDIRGROWSER_H_
# define _UIDIRGROWSER_H_

#include <sui/sharpuiconfig.h>
#include <suic/framework/uicontrol.h>

namespace ui
{

class SHARPUI_API DirBrowser : public suic::Control
{
public:

    DirBrowser(bool bDel=false);

    virtual ~DirBrowser();

    bool Open(suic::String dir, suic::Handle owner=0, bool bMulti=false);

    suic::String GetDir() const;

protected:

    virtual void OnRender(suic::DrawingContext * drawing);

protected:

    suic::String _dir;

};

};

# endif
