// 华勤科技版权所有 2010-2011
// 
// 文件名：systemhelper.h
// 功  能：系统帮助类。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UISYSTEMHELPER_H_
# define _UISYSTEMHELPER_H_

#include <suic/core/uiobject.h>
#include <suic/core/uiinterface.h>
#include <suic/framework/uiwindow.h>
#include <suic/tools/uibuilder.h>

namespace suic
{

class SUICORE_API SystemHelper : public Object
{
public:

    static void* suiMalloc(int);
    static void suiFree(void*);

    static void suiTrace(suic::Char * format, ...);
    static String suiCalculatePath(const String& path);
    static String suiApplicationDir();

    // 检测正则表达式 flag:0不连续；1：连续
    static bool suiRegexCheck(const char* regex, const String& val, int flag);

    static void suiInitialize();
    static void suiUninitialize();

    static bool suiLoadResource(const String& path, const String& pwd);

    static void SetTrackingPopup(FrameworkElement*);
    static FrameworkElementPtr GetTrackingPopup();

    static ObjectPtr CalcProperty(Element*, String prop, String val);
    static ObjectPtr GetRefObj(Element*, const String&);

    static Point ToScreenPoint(Element* element, Point pt);
    static Point GetCursorPoint(Element* element);
    static Point CalcuCusorPoint(ElementPtr element);
    static Point CalcScreenElementPoint(Element* element, int flag);
    static ElementPtr GetMouseOverElement(ElementPtr root);

    static suic::Int32 suiSetTimer(suic::Element*, suic::Int32, TimerFunc);
    static void suiKillTimer(suic::Element*, suic::Int32&);

    static suic::Int32 suiAddTimer(AssignerPtr, suic::Int32 uElapse, TimerFunc tf, InvokerPriority pri);
    static void suiRemoveTimer(suic::Int32& uId);

    static suic::ImagePtr GetImage();
    static suic::ImagePtr RenderToImage(suic::FrameworkElement* root);

    static void LoadGif(const suic::String& path, GifDescriptor& gd, suic::Vector<AnimateItem>& anis);

    static void RegisterInitializeHook(suic::InitializeHookPtr);
    static void RegisterHwndMessageSystemHook(suic::HwndAdapterHookPtr hook);
    static void RemoveHwndMessageSystemHook(suic::HwndAdapterHookPtr hook);
    static void RegisterHwndMessageHook(suic::ElementPtr, suic::HwndAdapterHookPtr);
    static void RemoveHwndMessageHook(suic::ElementPtr, suic::HwndAdapterHookPtr);

    static void SetElementTopMost(suic::ElementPtr, bool);

    static void AddSystemMessageListener(MessageListener ml);
    static void RemoveSystemMessageListener(MessageListener ml);
    static void AddMessageListener(suic::Element*, MessageListener ml);
    static void RemoveMessageListener(suic::Element*, MessageListener ml);

    static void RegisterContent(ContentBuilder val);

protected:

    SystemHelper();
};

};

#define suiSys suic::SystemHelper
#define suiBuildApp(xml,m,res) suic::SystemHelper::BuildApp(xml,m,res)
#define suiBuildElem(xml,m,res) suic::SystemHelper::BuildElement(xml,m,res)

# endif
