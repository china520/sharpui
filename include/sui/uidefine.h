// 华勤科技版权所有 2010-2011
// 
// 文件名：UIDefine.h
// 功  能：定义系统各种结构，变量等。
// 
// 作  者：汪荣
// 时  间：2010-07-30
// 
// ============================================================================

# ifndef _UIDEFINE_H_
# define _UIDEFINE_H_

#include <suicore/uitypes.h>

namespace ui
{

static const int SUI_RANGE = 0x0001;
static const int SUI_PAGE = 0x0002;
static const int SUI_POS = 0x0004;
static const int SUI_DISABLENOSCROLL = 0x0008;
static const int SUI_TRACKPOS = 0x0010;
static const int SUI_ALL = (SUI_RANGE | SUI_PAGE | SUI_POS | SUI_TRACKPOS);

static const int SUI_LINEUP = 0;
static const int SUI_LINELEFT = 0;
static const int SUI_LINEDOWN = 1;
static const int SUI_LINERIGHT = 1;
static const int SUI_PAGEUP = 2;
static const int SUI_PAGELEFT = 2;
static const int SUI_PAGEDOWN = 3;
static const int SUI_PAGERIGHT = 3;
static const int SUI_THUMBPOSITION = 4;
static const int SUI_THUMBTRACK = 5;
static const int SUI_TOP = 6;
static const int SUI_LEFT = 6;
static const int SUI_BOTTOM = 7;
static const int SUI_RIGHT = 7;

static const suic::Uint32 UIF_VERT_ORIENTATION = 0x00000100;

static const suic::Uint32 UIF_ALIGN_CENTER = 0x00000000;
static const suic::Uint32 UIF_ALIGN_LEFT = 0x00000001;
static const suic::Uint32 UIF_ALIGN_RIGHT = 0x00000002;
static const suic::Uint32 UIF_ALIGN_STRETCH = 0x00000003;

static const suic::Uint32 UIF_ALIGN_TOP = 0x00000001;
static const suic::Uint32 UIF_ALIGN_BOTTOM = 0x00000002;

typedef struct tagUIScrollInfo
{
    int iMax;
    int iPage;
    int iVisualPos;
    int iLogicPos;
    int _iTrackPos;

}UIScrollInfo;

}

# endif
