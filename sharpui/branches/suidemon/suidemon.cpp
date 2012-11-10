// suicoredemon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <suicore/uistring.h>
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
    suic::String strRes = _T("iskin/resource.sres");
    suic::String strApp = _T("res/application.xml");

    // 解析命令行
    suic::String strCmd(lpCmdLine);
    suic::VectorString vecStr;

    suic::Split(vecStr, strCmd, _T(" "));

    for (int i = 0; i < (int)vecStr.size(); ++i)
    {
        suic::VectorString vecTmp;

        suic::Split(vecTmp, vecStr[i], _T("="));

        if (vecTmp.size() == 2)
        {
            if (vecTmp[0].Equals(_T("Res")))
            {
                strRes = vecTmp[1];
            }
            else if (vecTmp[0].Equals(_T("App")))
            {
                strApp = vecTmp[1];
            }
        }
    }

    // 初始化打好包的资源和注册系统库
    // 此方法必须调用
    CoreInitialize(strRes);

    // 声明资源构建者类，参数为自定义元素创建回调对象
    // 可以通过此对象来创建我们需要的类
    suic::Builder build;

    AsciiStr resStr(strApp.c_str());

    // 读取Application资源
    // 主窗体为MainFrame对象，读取成功后Application::Current()
    // 会被自动赋值
    build.Build(new MainFrame(), resStr);

    suic::ApplicationPtr pApp = suic::Application::Current();

    pApp->LoadCompleted += OnApplicationLoadCompleted;

    if (suic::Application::Current())
    {
        // 执行消息循环
        pApp->Run();

        // 系统退出最好清除资源
        pApp = suic::ApplicationPtr();
    }

	return 0;
}

