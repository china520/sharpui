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

#include <suicore/uiobject.h>
#include <suicore/uiinterface.h>
#include <suicore/uiwindow.h>
#include <suicore/uibuilder.h>

namespace suic
{

class SUICORE_API SystemHelper : public Object
{
public:

    static void* suiMalloc(int);
    static void suiFree(void*);

    static void suiTrace(suic::Char * format, ...);

    static String suiCalculatePath(const String& path);

    static void suiInitialize();
    static void suiClear();

    static bool ReadResource(const String& path);

    static ObjectPtr GetRefObj(Element*, const String&);

    static Point ToScreenPoint(Element* element, Point pt);
    static Point GetCursorPoint(Element* element);
    static Point CalcuCusorPoint(ElementPtr element);
    static Point CalcScreenElementPoint(Element* element, int flag);
    static ElementPtr GetMouseOverElement(ElementPtr root);

    static DrawingContextPtr GetRenderContext(Element* pElem);

    static void suiSetTimer(TimerIdentityPtr&, suic::Element*, suic::Uint32, int iPriority=-10);
    static void suiRestartTimer(TimerIdentityPtr& tip);
    static void suiKillTimer(TimerIdentityPtr& tip);

    static suic::ImagePtr GetImage();
    static void LoadGif(const suic::String& path, GifDescriptor& gd, suic::Vector<AnimateItem>& anis);

    static suic::ImagePtr RenderToImage(suic::FrameworkElementPtr root);

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

#define UISys suic::SystemHelper
#define UIBuildApp(xml,m,res) suic::SystemHelper::BuildApp(xml,m,res)
#define UIBuildElem(xml,m,res) suic::SystemHelper::BuildElement(xml,m,res)

# endif
