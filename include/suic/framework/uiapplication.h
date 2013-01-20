// 华勤科技版权所有 2010-2011
// 
// 文件名：Application.h
// 功  能：应用程序对象。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIAPPLICATION_H_
# define _UIAPPLICATION_H_

#include <suic/framework/uiwindow.h>
#include <suic/styles/ResourceDictionary.h>

namespace suic {

class Application;
typedef shared<Application> ApplicationPtr;

typedef delegate<void(ApplicationPtr, const EventArg&)> LoadCompletedEventHandler;
typedef delegate<void(ApplicationPtr, const EventArg&)> StartupEventHandler;
typedef delegate<void(ApplicationPtr, const EventArg&)> ExitEventHandler;

class SUICORE_API Application : public RefObject
{
public:

    LoadCompletedEventHandler LoadCompleted;
    StartupEventHandler Startup;
    ExitEventHandler Exit;
    EventHandler Activated;
    EventHandler Deactivated;

    Application();
    virtual ~Application();

    void Run(WindowPtr element);
    void Run();

    void Shutdown();
    void Shutdown(int exitCode);

    static ApplicationPtr Current();
    static void PlaySound(String soundName);

    // Windows();

    ResourceDictionaryPtr GetResources() const;
    void SetResources(ResourceDictionary* resources);
    void SetResources(const AsciiStr& res);

    ObjectPtr FindResource(const String& name);

    static ObjectPtr LoadComponent(ObjectPtr parent, const AsciiStr& res);

protected:

    virtual void DoShutdown();

// 属性访问定义
public:

    /// <summary>
    ///  取得当前应用的主窗口
    /// </summary>
    WindowPtr GetMainWindow() const;
    void SetMainWindow(WindowPtr val);

    String GetStartupUri() const;
    void SetStartupUri(String val);

    bool IsShuttingDown() const;

protected:

    String _startupUri;
    WindowPtr _mainWindow;
   
    ResourceDictionaryPtr _resources;
};

inline ResourceDictionaryPtr Application::GetResources() const
{
    return _resources;
}

}

# endif
