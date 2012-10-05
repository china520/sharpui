// 华勤科技版权所有 2010-2011
// 
// 文件名：WndHelper.h
// 功  能：实现窗口的基本操作，包括窗口属性的存取。
// 
// 作  者：汪荣
// 时  间：2010-09-23
// 
// ============================================================================

# ifndef _UIWNDHELPER_H_
# define _UIWNDHELPER_H_

#include <sui/sharpuiconfig.h>
#include <suicore/uicontrol.h>

namespace ui
{

/*****************************************************************
* 所有界面元素类的基类，实现一般界面元素的公共操作和接口.
*/
class SHARPUI_API WndHelper : public suic::Object
{
public:

    WndHelper(suic::ElementPtr p);
    virtual ~WndHelper();

    bool OpenClipboard();
    void CloseClipboard();

    int PasteText(suic::String & text);
    int CutText(suic::String & text);
    int CopyText(const suic::String & text);

    bool CreateSolidCaret(int w, int h);
    bool DestroyCaret();
    void ShowCaret();
    void HideCaret();
    void SetCaretPos(int x, int y);
    bool GetCaretPos(suic::Point & pt);

protected:

    suic::ElementPtr ePtr;
};

};

# endif