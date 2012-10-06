// suicoredemon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <suicore/uistring.h>
#include <suicore/uicore.h>
#include <sui/sharpuicore.h>
#include "Application.h"
#include "MainFrame.h"

suic::ApplicationPtr g_appPtr;

void OnApplicationLoadCompleted(suic::ApplicationPtr appPtr, const suic::EventArg&)
{
    suic::WindowPtr winPtr(appPtr->GetMainWindow());        
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/
                     , LPSTR lpCmdLine, int nCmdShow)
{
    // 初始化打好包的资源和注册系统库
    // 此方法必须调用
    CoreInitialize(_T("iskin/uidesign.sres"));

    // 声明资源构建者类，参数为自定义元素创建回调对象
    // 可以通过此对象来创建我们需要的类
    suic::Builder build;

    // 读取Application资源
    // 主窗体为MainFrame对象，读取成功后Application::Current()
    // 会被自动赋值
    build.Build(new MainFrame(), _T("res/uidemon.xml"));

    suic::ApplicationPtr pApp = suic::Application::Current();

    if (suic::Application::Current())
    {
        // 执行消息循环
        pApp->Run();

        // 系统退出最好清除资源
        pApp = suic::ApplicationPtr();
    }

	return 0;
}

