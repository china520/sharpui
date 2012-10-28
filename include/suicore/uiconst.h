// 华勤科技版权所有 2010-2011
// 
// 文件名：UIConst.h
// 功  能：定义核心库用到的常量。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UICONST_H_
# define _UICONST_H_

#include <suicore/uitypes.h>

class CoreFlags
{
public:

    enum Orientation
    {
        Horizontal = 0,
        Vertical = 1,
    };

    enum eVertState
    {
        Center = 0,
        Top = 1,
        Bottom = 2,
        Stretch = 3,
        VerticalOrientation = 0x100,
    };

    enum eHorzState
    {
        Left = 1,
        Right = 2,
    };

    enum eHitFlag
    {
        HitValid = HTERROR,
        HitCaption = HTCAPTION,
        HitClient = HTCLIENT,
    };

    enum
    {
        eLeftTop,
        eLeftBottom,
        eRightTop,
        eRightBottom,
    };

    enum eCoreFlags
    {
        None = 0x00000000,
        MeasureInProgress = 0x00000001,
        ArrangeInProgress = 0x00000002,
        IsInitialized = 0x00000004,
        IsInitPending = 0x00000008,
        IsLoaded = 0x00000010,
        IsMouseOver = 0x00000020,
        IsMouseCaptured = 0x00000040,
        IsFocusedWithin = 0x00000080,
        IsDisabled = 0x00000100,
        IsHidden = 0x00000200,
        IsCollapsed = 0x00000400,
        IsTopMost = 0x00000800,
        IsLayeredWindow = 0x00001000,

        IsSupportMouseOver = 0x00002000,
        IsFocusable = 0x00004000,

        IsMeasureDirty = 0x00008000,
        IsArrangeDirty = 0x00010000,
        IsRenderDirty = 0x00020000,
        IsZStateDirty = 0x00040000,

        IsSizeModing = 0x00080000,
        IsSelected = 0x00100000,
        IsTabStop = 0x00200000,

        IsComposition = 0x00400000,
        IsAllowDrop = 0x00800000,
    };
};

struct HorizontalAlignment
{
     enum
     {
         Center = 0,
         Left,
         Right,
         Stretch,
     };
};

struct VerticalAlignment
{
    enum
    {
        Center = 0,
        Top,
        Bottom,  
        Stretch,
    };
};

struct HorizontalContentAlignment
{
    enum
    {
        Center = 0,
        Left,
        Right,
    };
};

struct VerticalContentAlignment
{
    enum
    {
        Center = 0,
        Top,
        Bottom,
    };
};

struct TileMode
{
    enum 
    {
        None = 0,
        FlipX = 1,
        FlipY = 2,
        FlipXY = 3,
        Tile = 4,
    };
};

struct AlignmentX
{
    enum 
    {
        Left = 0,
        Center = 1,
        Right = 2,
    };
};

struct AlignmentY
{
    enum 
    {
        Top = 0,
        Center = 1,
        Bottom = 2,
    };
};

struct Stretch
{
    enum 
    {
        None = 0,
        Fill = 1,
        Uniform = 2,
        UniformToFill = 3,
    };
};

namespace suic
{

static const int RESIZE_LEN = 4;

}

# endif
