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

    SystemHelper();

    static void* Malloc(int);
    static void Free(void*);

    static void Trace(suic::Char * format, ...);

    static String CalculatePath(const String& path);
    static bool ReadResource(const String& path);

    static DrawingContextPtr GetRenderContext(Element* pElem);

    static Uint32 SetTimer(suic::ElementPtr, suic::Uint32, int iPriority=-10);
    static void KillTimer(suic::ElementPtr, suic::Uint32);

    static suic::ImagePtr GetImage();

    /// <summary>
    ///     解析样式描述文件并返回根元素
    /// </summary>
    /// <remarks>
    ///     此函数解析资源文件生成界面元素，外部可以传入
    ///     根元素的实现类，系统将使用此类关联根元素，也可
    ///     以传入一个公共的资源对象，这样，系统将使用传入的
    ///     资源对象初始化元素样式，否则使用系统默认（建议传入）
    /// </remarks>
    /// <param name="resid">
    ///     资源对象标识
    /// </param>
    /// <param name="main">
    ///     根元素实现类
    /// </param>
    /// <param name="xml">
    ///     资源描述文件
    /// </param>
    /// <returns>根元素对象，如果main不为空，则为main</returns>

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
};

};

#define UISys suic::SystemHelper
#define UIBuildApp(xml,m,res) suic::SystemHelper::BuildApp(xml,m,res)
#define UIBuildElem(xml,m,res) suic::SystemHelper::BuildElement(xml,m,res)

# endif
