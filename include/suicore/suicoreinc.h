// 华勤科技版权所有 2010-2011
// 
// 文件名：suicoreinc.h
// 功  能：定义核心库的配置文件信息。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _SUICOREINC_H_
# define _SUICOREINC_H_

#define __OS_WIN32

#ifdef _MSC_VER

#pragma warning (disable : 4275)
#pragma warning (disable : 4511) // copy operator could not be generated
#pragma warning (disable : 4512) // assignment operator could not be generated
#pragma warning (disable : 4702) // unreachable code (bugs in Microsoft's STL)
#pragma warning (disable : 4786) // identifier was truncated
#pragma warning (disable : 4996) // function or variable may be unsafe (deprecated)
#pragma warning (disable : 4748) // function or variable may be unsafe (deprecated)
#pragma warning (disable : 4251) // function or variable may be unsafe (deprecated)

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS // eliminate deprecation warnings for VS2005
#endif
#endif // _MSC_VER
#ifdef __BORLANDC__
#pragma option -w-8027		   // function not expanded inline
#endif

#pragma comment(lib, "msimg32.lib")
#ifdef _DEBUG
#pragma comment(lib, "suicoreud.lib")
#else
#pragma comment(lib, "suicoreu.lib")
#endif

#ifndef SUICORE_LIB

#ifdef SUICORE_EXPORTS

#define SUICORE_API __declspec(dllexport)
#else
#define SUICORE_API __declspec(dllimport)
#endif

#else

#define SUICORE_API

#endif

#include <windows.h>
#include <commctrl.h>
#include <stddef.h>
#include <tchar.h>
#include <assert.h>
#include <crtdbg.h>
#include <malloc.h>

#include <util/locker.h>
#include <util/vector.h>
#include <util/map.h>
#include <util/hashmap.h>

#include <suicore/drawing/uirender.h>
#include <suicore/hwndhelper.h>
#include <suicore/visualtreehelper.h>
#include <suicore/systemhelper.h>
#include <suicore/uibuilder.h>

#include <suicore/uivisualhost.h>
#include <suicore/uimouse.h>
#include <suicore/uikeyboard.h>

#include <suicore/hwndadapter.h>
#include <suicore/uiwindow.h>
#include <suicore/uiapplication.h>
#include <suicore/uipanel.h>
#include <suicore/uiobject.h>

#include <suicore/drawing/uidrawing.h>
#include <suicore/drawing/uiImageBrush.h>
#include <suicore/drawing/uiLinearGradientBrush.h>
#include <suicore/drawing/uiSolidColorBrush.h>

#include <animation/StoryBoard.h>

# endif
